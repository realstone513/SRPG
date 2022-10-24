#include "GameMgr.h"
#include "../SFML_Framework/Frameworks.h"
#include "../SRPGObjects/Piece.h"

GameMgr::GameMgr()
	: isPlayerTurn(true), globalTimer(0.f),
	playerDoneCount(0), aiDoneCount(0)
{
}

void GameMgr::SetList(list<Piece*>* gamePieces)
{
	this->gamePieces = gamePieces;

	for (Piece*& piece : *gamePieces)
	{
		if (!piece->GetType().compare("Playable"))
			playerCount++;
		else
			aiCount++;
	}
}

void GameMgr::SetPlayerTurn(bool isPlayerTurn)
{
	this->isPlayerTurn = isPlayerTurn;

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
}