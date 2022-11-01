#include "GameMgr.h"
#include "../SFML_Framework/Frameworks.h"
#include "../SRPGObjects/Piece.h"
#include "../Scenes/BattleSceneUI.h"
#include "../GameSystem/AbilityStone.h"
#include "../GameSystem/Stats.h"

int GameMgr::turnCount = 1;

GameMgr::GameMgr()
	: isPlayerTurn(true), playerDoneCount(0), aiDoneCount(0),
	duration(2.f), timer(0.f), counterTimer(0.f), aiAction(false),
	bossPhase(false)
{
}

void GameMgr::SetMapInfo(float width, float height)
{
	this->width = width;
	this->height = height;
}

void GameMgr::SetList(list<Piece*>* gamePieces)
{
	this->gamePieces = gamePieces;

	for (Piece*& piece : *gamePieces)
	{
		if (!piece->GetType().compare("Playable"))
		{
			playerPieces.push_back(piece);
			playerCount++;
		}
		else
		{
			aiPieces.push_back(piece);
			aiCount++;
		}
	}

	for (auto& playable : playerPieces)
	{
		CLOG::Print3String(playable->GetName());
		playable->stats.UpdateAddStats(
			updateStoneStat[0], updateStoneStat[1], updateStoneStat[2], 0, 0);
		playable->stats.SetFullCurrentHealth();
	}
}

void GameMgr::SetUIMgr(BattleSceneUI* battleUIMgr)
{
	this->battleUIMgr = battleUIMgr;
}

void GameMgr::SetPlayerTurn(bool isPlayerTurn)
{
	this->isPlayerTurn = isPlayerTurn;
	battleUIMgr->SetHud(isPlayerTurn, turnCount);
	CLOG::Print3String(isPlayerTurn ? "Player Turn" : "AI Turn");
	for (Piece*& piece : *gamePieces)
	{
		piece->SetDone(false);
		if (isPlayerTurn)
			piece->SetIsTurn(!piece->GetType().compare("Playable"));
		else
			piece->SetIsTurn(!piece->GetType().compare("AI"));
	}
}

void GameMgr::Reset()
{
	isPlayerTurn = true;
	turnCount = 1;
	playerDoneCount = 0;
	aiDoneCount = 0;
	bossPhase = false;
}

void GameMgr::Update(float dt)
{
	if (!gameOver && (playerCount == 0 || aiCount == 0))
	{
		gameOver = true;
		timer = 3.0f;
	}

	if (isPlayerTurn)
	{
		playerDoneCount = 0;
		for (Piece*& playable : playerPieces)
		{
			if (playable->GetDone())
				playerDoneCount++;
		}

		if (playerDoneCount == playerCount)
		{
			SetPlayerTurn(false);
			UpdateRecognize();
			timer = duration;
			for (Piece*& piece : *gamePieces)
			{
				piece->TurnReset();
				if (!bossPhase && !piece->GetName().compare("Minotaur") && piece->recognize)
				{
					SOUND_MGR->StopAll();
					SOUND_MGR->Play("sound/boss_bgm.wav", 50.f, true);
					bossPhase = true;
				}
			}
			for (Piece*& death : deathPieces)
				death->SetActive(false);
		}
	}
	else
	{
		aiDoneCount = 0;
		for (Piece*& ai : aiPieces)
		{
			if (!ai->recognize || ai->GetDone())
				aiDoneCount++;
		}
		if (aiDoneCount == aiCount)
		{
			turnCount++;
			SetPlayerTurn(true);
			for (Piece*& piece : *gamePieces)
				piece->TurnReset();
			for (Piece*& death : deathPieces)
				death->SetActive(false);
		}
		else
		{
			if (timer < 0.f)
				timer = duration;
		}
	}
}

void GameMgr::NormalAttack(Piece* attack, Piece* hit, bool counter)
{
	hit->stats.currentHealth -= CalculateDamage(attack, hit);
	CLOG::Print3String(hit->GetStatusString());
	bool isRight = attack->GetIdxPos().x < hit->GetIdxPos().x;
	attack->SetAnimDir(isRight);
	hit->SetAnimDir(!isRight);
	
	attack->SetState(States::Attack);
	hit->SetState(States::Hit);

	// death test
	if (hit->stats.currentHealth <= 0.f)
	{
		hit->stats.currentHealth = 0.f;
		CLOG::Print3String(hit->GetName(), "is die");
		
		if (!hit->GetType().compare("Playable"))
		{
			for (auto it = playerPieces.begin(); it != playerPieces.end();)
			{
				if ((*it)->GetObjId() == hit->GetObjId())
				{
					it = playerPieces.erase(it);
					playerCount--;
				}
				else it++;
			}
		}
		else
		{
			for (auto it = aiPieces.begin(); it != aiPieces.end();)
			{
				if ((*it)->GetObjId() == hit->GetObjId())
				{
					it = aiPieces.erase(it);
					aiCount--;
				}
				else it++;
			}
		}

		hit->SetState(States::Death);
		hit->isDeath = true;
		deathPieces.push_back(hit);

		for (auto it = gamePieces->begin(); it != gamePieces->end();)
		{
			if ((*it)->GetObjId() == hit->GetObjId())
			{
				it = gamePieces->erase(it);
				return;
			}
			else it++;
		}
	}
	else
	{ 
		// counter attack if don't death
		if (!counter)
		{
			bool counterCondition;
			int distance = Utils::ManhattanDistance(hit->GetIdxPos(), attack->GetIdxPos());
			if (hit->stats.rangeFill)
				counterCondition = distance <= hit->stats.modifyRange;
			else
				counterCondition = distance == hit->stats.modifyRange;
			
			if (counterCondition)
			{
				counterList.push(Counter(hit, attack));
				counterTimer = duration;
			}
		}
	}
}

float GameMgr::CalculateDamage(Piece* attack, Piece* hit)
{
	return Utils::RandomRange(attack->stats.modifyDamage * 0.8f,
		attack->stats.modifyDamage * 1.2) * 100.f / (hit->stats.modifyArmor + 100.f);
}

void GameMgr::UpdateRecognize()
{
	for (Piece*& ai : aiPieces)
	{
		if (ai->recognize)
			continue;

		for (Piece*& playable : playerPieces)
		{
			int dist = Utils::ManhattanDistance(ai->GetIdxPos(), playable->GetIdxPos());
			if (dist < ai->stats.modifyMobility * 2)
			{
				ai->recognize = true;
				break;
			}
		}
	}
}

void GameMgr::ApplyEquipmentSetting(AbilityStone* stone)
{
	this->stone = stone;
	vector<string> statText(3);
	updateStoneStat.resize(3);

	for (int i = 0; i < 3; i++)
	{
		switch (this->stone->stats[i])
		{
		case StatsEnum::Health:
			statText[i] = "Health";
			break;
		case StatsEnum::Damage:
			statText[i] = "Damage";
			break;
		case StatsEnum::Armor:
			statText[i] = "Armor";
			break;
		default:
			break;
		}
		statText[i] = (i == 2) ? "-" + statText[i] : "+" + statText[i];
	
		CLOG::Print3String(statText[i], to_string(this->stone->successCounts[i]));

		updateStoneStat[(int)this->stone->stats[i]] +=
			(i != 2) ? this->stone->successCounts[i] : -this->stone->successCounts[i];
	}

	CLOG::Print3String(
		to_string(updateStoneStat[0]),
		to_string(updateStoneStat[1]),
		to_string(updateStoneStat[2]));
}