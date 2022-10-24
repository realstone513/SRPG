#pragma once
#include "Piece.h"
#include "../SFML_Framework/Framework/Animatable.h"

class Player : public Piece, Animatable
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
};