#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "../SFML_Framework/3rd/SingleTon.h"

#define GAMEMGR (GameMgr::GetInstance())

using namespace sf;
using namespace std;

class Piece;

// 턴, 데미지 등 게임 관련한 작업들을 하기 위한 클래스
class GameMgr : public Singleton<GameMgr>
{
private:
	bool isPlayerTurn;
	list<Piece*>* gamePieces;
	
	int playerCount;
	int aiCount;
	int playerDoneCount;
	int aiDoneCount;

	float globalTimer;

public:
	GameMgr();
	virtual ~GameMgr() {}

	void SetList(list<Piece*>* gamePieces);
	void SetPlayerTurn(bool isPlayerTurn);

	void Reset();
	void Update(float dt);
	void SetGlobalTimer(float time) { globalTimer = time; }
};