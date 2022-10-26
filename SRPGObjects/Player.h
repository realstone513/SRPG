#pragma once
#include "Piece.h"

class Player : public Piece
{
protected:

public:
	Player(PieceTypes pt);
	virtual ~Player() {}

	virtual void Init();
	virtual void Release();
	virtual void Reset();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	virtual void SetPos(const Vector2f& pos) override;

	virtual void SetAnimations() override;
	virtual void SetState(States newState) override;
};