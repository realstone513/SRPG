#pragma once
#include "../SFML_Framework/GameObject/SpriteObj.h"
#include "../SFML_Framework/Framework/Animator.h"
#include "../GameSystem/Stats.h"

enum class PieceTypes
{
	None = -1,
	Playable,
	AI,
};

enum class States
{
	None = -1,
	Idle,
	Move,
	Attack,
	Special,
	Hit,
	Death,
	Others
};

// 공통적으로 쓸 것들 추가
class Piece : public SpriteObj
{
protected:
	// tile map info
	PieceTypes pType;
	Vector2i beforeIdx;
	Vector2i curIdx;
	Vector2f dest;
	Vector2f dir;
	float dist;
	float speed;
	bool animDir; // true = right, false = left

	// turn
	bool isTurn;		// 턴
	bool isPlayable;	// 조작
	bool done;			// 행동

	// Animator
	Animator anim;
	States currState;

public:
	// status
	Stats stats;

	/*int maxHealth;
	int health;
	int damage;
	int armor;
	int range;
	bool rangeFill;
	int mobility;*/

	bool recognize;
	bool isDeath;

	Piece(PieceTypes pt);
	virtual ~Piece() {};

	virtual void Reset();
	virtual void Update(float dt) override;
	virtual void SetPos(const Vector2f& pos) override;
	void SetIdxPos(const Vector2i& pos);
	const Vector2i& GetIdxPos() const;
	
	void TurnReset();

	string GetStatusString() const;

	void SetIsTurn(bool isTurn);
	bool GetIsTurn();
	void SetDone(bool done);
	bool GetDone();
	void SetDest(Vector2f dest);
	Vector2f GetDest();

	void AddClipFast(string clipId, int frame);
	virtual void SetState(States newState);
	States GetState() { return currState; }
	virtual void SetAnimations() = 0;
	void SetAnimDir(bool isRight)
	{
		animDir = isRight;
	}
	Vector2i GetBeforeIdx() { return beforeIdx; }
	void StopTranslate();
};