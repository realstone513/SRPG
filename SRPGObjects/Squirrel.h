#pragma once
#include "Piece.h"
#include "../SFML_Framework/Framework/Animatable.h"

class Squirrel : public Piece, Animatable
{
protected:

public:
	Squirrel();
	virtual ~Squirrel() {}

	virtual void Init();
	virtual void Release();
	virtual void Reset();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	virtual void SetAnimations() override;
};