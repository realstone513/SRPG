#include "OverlayTile.h"

OverlayTile::OverlayTile()
{
	SetType("Overlay");
	shape.setSize(Vector2f(30.f, 30.f));
	shape.setOutlineColor(Color(0.f, 0.f, 0.f));
	shape.setFillColor(Color(255.f, 255.f, 255.f, 30.f));
	shape.setOutlineThickness(2.f);
}

OverlayTile::~OverlayTile()
{
}

void OverlayTile::Init()
{
	//Object::Init(); hitbox를 쓰지않음
}

void OverlayTile::Release()
{
}

void OverlayTile::Reset()
{
	Object::Reset();
	SetActive(false);
}

void OverlayTile::Update(float dt)
{
	RectangleObj::Update(dt);
}

void OverlayTile::Draw(RenderWindow& window)
{
	RectangleObj::Draw(window);
}