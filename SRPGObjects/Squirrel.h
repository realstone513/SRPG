#pragma once
#include "Piece.h"

class Squirrel : public Piece
{
protected:

public:
	Squirrel(PieceTypes pt);
	virtual ~Squirrel() {}

	virtual void Init();
	virtual void Release();
	virtual void Reset();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	virtual void SetPos(const Vector2f& pos) override;

	virtual void SetAnimations() override;
};