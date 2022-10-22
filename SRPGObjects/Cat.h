#pragma once
#include "Piece.h"
#include "../SFML_Framework/Framework/Animatable.h"

class Cat : public Piece, Animatable
{
protected:

public:
	Cat();
	virtual ~Cat() {}

	virtual void Init();
	virtual void Release();
	virtual void Reset();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	virtual void SetAnimations() override;
};