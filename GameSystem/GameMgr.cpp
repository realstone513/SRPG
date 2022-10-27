#include "GameMgr.h"
#include "../SFML_Framework/Frameworks.h"
#include "../SRPGObjects/Piece.h"
#include "../Scenes/BattleSceneUI.h"

int GameMgr::turnCount = 1;

GameMgr::GameMgr()
	: isPlayerTurn(true), playerDoneCount(0), aiDoneCount(0)
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
			SetPlayerTurn(false);
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
			SetPlayerTurn(true);
			turnCount++;
		}
	}
}

void GameMgr::DamageToPiece(Piece* attack, Piece* hit)
{
	hit->health -= CalculateDamage(attack, hit);
	CLOG::Print3String(hit->GetStatusString());
	bool isRight = attack->GetIdxPos().x < hit->GetIdxPos().x;
	attack->SetAnimDir(isRight);
	hit->SetAnimDir(!isRight);
	if (attack->damage > 100)
		attack->SetState(States::Special);
	else
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
	}
}

float GameMgr::CalculateDamage(Piece* attack, Piece* hit)
{
	return attack->damage * 100.f / (hit->armor + 100.f);
}
// attack Damage * (100 / armor + 100)