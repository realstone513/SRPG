#pragma once
#include "Piece.h"

class Cat : public Piece
{
protected:

public:
	Cat(PieceTypes pt);
	virtual ~Cat() {}

	virtual void Init();
	virtual void Release();
	virtual void Reset();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	virtual void SetPos(const Vector2f& pos) override;

	virtual void SetAnimations() override;
	virtual void SetState(States newState) override;
};