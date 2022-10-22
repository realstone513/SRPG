#include "OverlayTile.h"

OverlayTile::OverlayTile()
{
	SetType("Overlay");
	colors[TileType::Inactive] = Color(255.f, 255.f, 255.f, 30.f);
	colors[TileType::Moveable] = Color(255.f, 255.f, 255.f, 30.f);
	colors[TileType::Immovable] = Color(255.f, 255.f, 255.f, 30.f);
	colors[TileType::AttackRange] = Color(255.f, 255.f, 255.f, 30.f);

	shape.setSize(Vector2f(30.f, 30.f));
	shape.setOutlineColor(Color::Black);
	shape.setOutlineThickness(2.f);
}

OverlayTile::~OverlayTile()
{
}

void OverlayTile::Init()
{
	//Object::Init() hitbox¾È¾¸
}

void OverlayTile::Release()
{
}

void OverlayTile::Reset()
{
	shape.setFillColor(Color(255.f, 255.f, 255.f, 30.f));
	shape.setFillColor(colors[TileType::Inactive]);
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

void OverlayTile::SetFillColor(TileType type)
{
	switch (type)
	{
	case OverlayTile::TileType::Inactive:
		shape.setFillColor(Color(255.f, 255.f, 255.f, 30.f));
		break;
	case OverlayTile::TileType::Moveable:
		shape.setFillColor(Color(0, 0, 255.f, 100.f));
		break;
	case OverlayTile::TileType::Immovable:
		shape.setFillColor(Color(127.f, 127.f, 127.f, 100.f));
		break;
	case OverlayTile::TileType::AttackRange:
		shape.setFillColor(Color(255.f, 0, 0, 100.f));
		break;
	default:
		break;
	}
}

void OverlayTile::SetFillColor(int type)
{
	SetFillColor((OverlayTile::TileType)type);
}