#include "GameMgr.h"
#include "../SFML_Framework/Frameworks.h"
#include "../SRPGObjects/Piece.h"

GameMgr::GameMgr()
	: isPlayerTurn(true), globalTimer(0.f),
	playerDoneCount(0), aiDoneCount(0)
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

void GameMgr::SetPlayerTurn(bool isPlayerTurn)
{
	this->isPlayerTurn = isPlayerTurn;
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
	globalTimer = 0.f;
	playerDoneCount = 0;
	aiDoneCount = 0;
}

void GameMgr::Update(float dt)
{
	if (globalTimer > 0.f)
	{
		globalTimer -= dt;
		CLOG::Print3String(to_string(globalTimer));
		return;
	}
	else globalTimer = 0.f;

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
			AIAction();
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
			SetPlayerTurn(true);
	}
}

void GameMgr::DamageToPiece(Piece* attack, Piece* hit)
{
	hit->health -= attack->damage;
	CLOG::Print3String(hit->GetStatusString());

	if (hit->health <= 0.f)
	{
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

		//hit->SetActive(false);
		hit->isDeath = true;
	}
}

// 가장 가까운 playable 캐릭터를 향해 이동
void GameMgr::AIAction()
{
	for (Piece*& ai : aiPieces)
	{
		Vector2i dist(width, height);

		for (Piece*& playable : playerPieces)
		{
			Vector2i tmp = ai->GetIdxPos() - playable->GetIdxPos();
			if (Utils::SqrMagnitude(dist) > Utils::SqrMagnitude(tmp))
				dist = tmp;
		}
		CLOG::PrintVectorState(dist);
	}
}