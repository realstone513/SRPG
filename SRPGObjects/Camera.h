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

	float width;
	float height;
	float halfWidth;
	float halfHeight;
	float limitX;
	float limitY;

public:
	Camera(PieceTypes pt);
	virtual ~Camera() {}

	virtual void Init();
	virtual void Release();
	virtual void Reset();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	void SetLimit(float width, float height);
};