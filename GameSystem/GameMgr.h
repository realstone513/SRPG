#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "../SFML_Framework/3rd/SingleTon.h"

#define GAMEMGR (GameMgr::GetInstance())

using namespace sf;
using namespace std;

class Piece;
class BattleSceneUI;

// 턴, 데미지 등 게임 관련한 작업들을 하기 위한 클래스
class GameMgr : public Singleton<GameMgr>
{
private:
	static int turnCount;
	list<Piece*>* gamePieces;
	float width;
	float height;

	int playerCount;
	int aiCount;
	int playerDoneCount;
	int aiDoneCount;

	float duration;
	
	BattleSceneUI* UIMgr;

public:
	GameMgr();
	virtual ~GameMgr() {}

	list<Piece*> playerPieces;
	list<Piece*> aiPieces;
	bool isPlayerTurn;
	bool aiAction; // false -> move, true -> action
	float timer;

	void SetMapInfo(float width, float height);
	void SetList(list<Piece*>* gamePieces);
	void SetUIMgr(BattleSceneUI* UIMgr);
	void SetPlayerTurn(bool isPlayerTurn);

	void Reset();
	void Update(float dt);
	void DamageToPiece(Piece* attack, Piece* hit);
	float CalculateDamage(Piece* attack, Piece* hit);
};