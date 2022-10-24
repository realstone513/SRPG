#pragma once
#include "Piece.h"

class Camera : public Piece
{
protected:
	Vector2f direction;
	Vector2f velocity;
	float accelation;
	float deaccelation;
	float speed;

public:
	Camera(PieceTypes pt);
	virtual ~Camera() {}

	virtual void Init();
	virtual void Release();
	virtual void Reset();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
};