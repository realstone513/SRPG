#pragma once
#include "Piece.h"

class Minotaur : public Piece
{
protected:

public:
	Minotaur(PieceTypes pt);
	virtual ~Minotaur() {}

	virtual void Init();
	virtual void Release();
	virtual void Reset();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	virtual void SetPos(const Vector2f& pos) override;

	virtual void SetAnimations() override;
};