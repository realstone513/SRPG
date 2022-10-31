#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>

using namespace sf;
using namespace std;

class OverlayTile;
class Piece;

class MapControl
{
protected:
	float unit;
	Vector2f lt;
	Vector2f rb;
	float width;
	float height;

	vector<vector<OverlayTile*>>& overlay;
	list<Piece*> gamePieces;
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
	void SetAttackRange(Vector2i coord, int range, int rangeOrigin, bool fill);
	void SetImmovable(Vector2i coord);
	void SetOverlayInactive();
	void SetPiecePos(Piece* piece, Vector2i idx);

	Vector2i PosToIdx(Vector2f pos);
	Vector2f IdxToPos(Vector2i idx);
	int TileDistance(Vector2i start, Vector2i dest);
};