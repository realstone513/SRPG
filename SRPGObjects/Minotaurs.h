#pragma once
#include "Piece.h"
#include "../SFML_Framework/Framework/Animatable.h"

class Minotaur : public Piece, Animatable
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

	virtual void SetAnimations() override;
};