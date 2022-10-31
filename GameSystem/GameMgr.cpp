#include "GameMgr.h"
#include "../SFML_Framework/Frameworks.h"
#include "../SRPGObjects/Piece.h"
#include "../Scenes/BattleSceneUI.h"

int GameMgr::turnCount = 1;

GameMgr::GameMgr()
	: isPlayerTurn(true), playerDoneCount(0), aiDoneCount(0),
	duration(2.f), timer(0.f), counterTimer(0.f), aiAction(false)
{
}

void GameMgr::SetMapInfo(float width, float height)
{
	this->width = width;
	this->height = height;
}

void GameMgr::SetList(list<Piece*>* gamePieces)
{
	this->gamePieces = nullptr;

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
}

void GameMgr::SetUIMgr(BattleSceneUI* UIMgr)
{
	this->UIMgr = UIMgr;
}

void GameMgr::SetPlayerTurn(bool isPlayerTurn)
{
	this->isPlayerTurn = isPlayerTurn;
	UIMgr->SetHud(isPlayerTurn, turnCount);
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
}

void GameMgr::Update(float dt)
{
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
			timer = duration;
			for (Piece*& piece : *gamePieces)
				piece->TurnReset();
			for (Piece*& death : deathPieces)
				death->SetActive(false);
		}
	}
	else
	{
		aiDoneCount = 0;
		for (Piece*& ai : aiPieces)
		{
			if (ai->GetDone())
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
	hit->health -= CalculateDamage(attack, hit);
	CLOG::Print3String(hit->GetStatusString());
	bool isRight = attack->GetIdxPos().x < hit->GetIdxPos().x;
	attack->SetAnimDir(isRight);
	hit->SetAnimDir(!isRight);
	
	attack->SetState(States::Attack);
	hit->SetState(States::Hit);

	// death test
	if (hit->health <= 0.f)
	{
		hit->health = 0.f;
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
			if (hit->rangeFill)
				counterCondition = distance <= hit->range;
			else
				counterCondition = distance == hit->range;
			
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
	return Utils::RandomRange(attack->damage * 0.8f, attack->damage * 1.2) * 100.f / (hit->armor + 100.f);
}