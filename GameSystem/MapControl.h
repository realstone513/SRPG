#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "../SRPGObjects/OverlayTile.h"
#include "../SRPGObjects/Piece.h"

using namespace sf;
using namespace std;

enum class TileType
{
	None = -1,
	Inactive,
	Moveable,
	Immovable,
	AttackRange,
};

class MapControl
{
protected:
	float unit;
	Vector2f lt;
	Vector2f rb;
	float width;
	float height;

	vector<vector<OverlayTile*>>& overlay;
	list<OverlayTile*> activeTiles;
	Piece* focus; 
	vector<Vector2f> offset;
	// test
	int algorithmCount;

public:
	MapControl(vector<vector<OverlayTile*>>& overlay, float cellWidth);
	virtual ~MapControl() {}

	void SetLTRB(Vector2f lt, Vector2f rb);

	void SetMoveable(Vector2i coord, int mobility);
	void SetAttackRange(Vector2i coord, int range, bool fill);
	void SetImmovable(Vector2i coord);
	void SetOverlayInactive();

	Vector2f Step(const Vector2f& objPos, int moveX, int moveY);
	Vector2i PosToIdx(Vector2f pos);
	Vector2f IdxToPos(Vector2i idx);
};