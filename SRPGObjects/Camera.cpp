#include "Camera.h"
#include "../SFML_Framework/Frameworks.h"

Camera::Camera(PieceTypes pt)
	: Piece(pt),
	direction(0, 0), accelation(500), deaccelation(500), velocity(0, 0), speed(500.f)
{
	SetType("Camera");
	SetName("Camera");
	isPlayable = false;
	SetOrigin(Origins::TC);
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
	if (position.x < -limitX)
		position.x = -limitX;
	if (position.y < -limitY)
		position.y = -limitY;
	if (position.x >= limitX)
		position.x = limitX;
	if (position.y >= limitY)
		position.y = limitY;
}

void Camera::Draw(RenderWindow& window)
{
}

void Camera::SetLimit(float width, float height)
{
	this->width = width;
	this->height = height;

	halfWidth = width * 0.5f;
	halfHeight = height * 0.5f;

	// TODO
	limitX = halfWidth * 0.64f;
	limitY = halfHeight * 0.5f;

	CLOG::Print3String(to_string(width), to_string(height));
}