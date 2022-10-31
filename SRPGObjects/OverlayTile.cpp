#include "OverlayTile.h"

OverlayTile::OverlayTile() : tileType(TileType::None), onTheTile(false)
{
	SetName("Overlay");
	colors[TileType::Inactive] =	Color(255.f, 255.f, 255.f, 30.f);
	colors[TileType::Moveable] =	Color(0.f, 0.f, 255.f, 100.f);
	colors[TileType::Immovable] =	Color(0.f, 255.f, 0.f, 100.f);
	colors[TileType::AttackRange] = Color(255.f, 0, 0, 100.f);

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
	SetFillColor(TileType::Inactive);
	SetTileType(TileType::Inactive);
	onTheTile = false;
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
	case TileType::Inactive:
		SetTileType(TileType::Inactive);
		shape.setFillColor(Color(255.f, 255.f, 255.f, 30.f));
		break;
	case TileType::Moveable:
		SetTileType(TileType::Moveable);
		shape.setFillColor(Color(0, 0, 255.f, 100.f));
		break;
	case TileType::Immovable:
		SetTileType(TileType::Immovable);
		shape.setFillColor(Color(127.f, 127.f, 127.f, 100.f));
		break;
	case TileType::AttackRange:
		SetTileType(TileType::AttackRange);
		shape.setFillColor(Color(255.f, 0, 0, 100.f));
		break;
	default:
		break;
	}
}

void OverlayTile::SetFillColor(int type)
{
	SetFillColor((TileType)type);
}

TileType OverlayTile::GetTileType() const
{
	return tileType;
}

void OverlayTile::SetTileType(TileType type)
{
	tileType = type;
}

Vector2f OverlayTile::GetTilePos() const
{
	return Vector2f(position.x + 16.f, position.y + 32.f);
}