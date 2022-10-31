#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <stack>
#include "../SFML_Framework/3rd/SingleTon.h"

#define GAMEMGR (GameMgr::GetInstance())

using namespace sf;
using namespace std;

class Piece;
class BattleSceneUI;

struct Counter
{
	Piece* attacker;
	Piece* hit;
	Counter(Piece* a, Piece* h)
		: attacker(a), hit(h)
	{

	}
};

// 턴, 데미지 등 게임 관련한 작업들을 하기 위한 클래스
class GameMgr : public Singleton<GameMgr>
{
private:
	static int turnCount;
	list<Piece*>* gamePieces;
	list<Piece*> deathPieces;
	float width;
	float height;

	int playerCount;
	int aiCount;
	int playerDoneCount;
	int aiDoneCount;

	float duration;
	
	BattleSceneUI* UIMgr;
	bool bossPhase;
	bool gameOver;

public:
	GameMgr();
	virtual ~GameMgr() {}

	list<Piece*> playerPieces;
	list<Piece*> aiPieces;
	stack<Counter> counterList;
	bool isPlayerTurn;
	bool aiAction; // false -> move, true -> action
	float timer;
	float counterTimer;

	void SetMapInfo(float width, float height);
	void SetList(list<Piece*>* gamePieces);
	void SetUIMgr(BattleSceneUI* UIMgr);
	void SetPlayerTurn(bool isPlayerTurn);

	void Reset();
	void Update(float dt);
	void NormalAttack(Piece* attack, Piece* hit, bool counter = false);
	float CalculateDamage(Piece* attack, Piece* hit);

	void UpdateRecognize();
};