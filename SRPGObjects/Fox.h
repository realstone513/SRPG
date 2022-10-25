#pragma once
#include "Piece.h"

class Fox : public Piece
{
protected:

public:
	Fox(PieceTypes pt);
	virtual ~Fox() {}

	virtual void Init();
	virtual void Release();
	virtual void Reset();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	virtual void SetPos(const Vector2f& pos) override;

	virtual void SetAnimations() override;
};