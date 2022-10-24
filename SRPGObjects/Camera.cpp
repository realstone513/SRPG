#include "Camera.h"
#include "../SFML_Framework/Frameworks.h"

Camera::Camera(PieceTypes pt)
	: Piece(pt, 0, 0, 0, 0, 0),
	direction(0, 0), accelation(500), deaccelation(500), velocity(0, 0), speed(500.f)
{
	SetType("Camera");
	SetName("Camera");
	isPlayable = false;
}

void Camera::Init()
{
	Reset();
}

void Camera::Release()
{
}

void Camera::Reset()
{
	Piece::Reset();
}

void Camera::Update(float dt)
{
	direction.x = InputMgr::GetAxisRaw(Axis::Horizontal);
	direction.y = InputMgr::GetAxisRaw(Axis::Vertical);

	//가속
	velocity += direction * accelation * dt;
	if (Utils::Magnitude(velocity) > speed)
	{
		velocity = Utils::Normalize(velocity) * speed;
	}

	//감속
	if (Utils::Magnitude(direction) == 0.f)
	{
		velocity = { 0.f, 0.f };
	}

	if (direction.x == 0.f)
	{
		if (velocity.x > 0.f)
		{
			velocity.x -= deaccelation * dt;
			if (velocity.x < 0.f)
				velocity.x = 0.f;
		}
		if (velocity.x < 0.f)
		{
			velocity.x += deaccelation * dt;
			if (velocity.x > 0.f)
				velocity.x = 0.f;
		}
	}

	if (direction.y == 0.f)
	{
		if (velocity.y > 0.f)
		{
			velocity.y -= deaccelation * dt;
			if (velocity.y < 0.f)
				velocity.y = 0.f;
		}
		if (velocity.y < 0.f)
		{
			velocity.y += deaccelation * dt;
			if (velocity.y > 0.f)
				velocity.y = 0.f;
		}
	}

	Translate(velocity * dt);
}

void Camera::Draw(RenderWindow& window)
{
}