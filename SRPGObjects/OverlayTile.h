#pragma once
#include "../SFML_Framework/GameObject/RectangleObj.h"
#include <map>

class OverlayTile : public RectangleObj
{
protected:
	enum class TileType
	{
		None = -1,
		Inactive,
		Moveable,
		Immovable,
		AttackRange,
	};
	map<TileType, Color> colors;
	TileType tileType;

public:
	OverlayTile();
	virtual ~OverlayTile() override;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetFillColor(TileType type);
	void SetFillColor(int type);
	TileType GetTileType() const;
	void SetTileType(TileType type);
	Vector2f GetTilePos() const;
};