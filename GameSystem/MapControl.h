#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "../SRPGObjects/OverlayTile.h"
#include "../SRPGObjects/Piece.h"

using namespace sf;
using namespace std;

class MapControl
{
	enum class TileType
	{
		None = -1,
		Inactive,
		Moveable,
		Immovable,
		AttackRange,
	};

protected:
	float unit;
	Vector2f lt;
	vector<vector<OverlayTile*>>& overlay;
	list<OverlayTile*> activeTiles;
	Piece* focus; 
	vector<Vector2f> offset;
	// test
	int algorithmCount;

public:
	MapControl(vector<vector<OverlayTile*>>& overlay,
		float cellWidth)
		: overlay(overlay), unit(cellWidth)
	{
		offset = {
			{ 1, 0 }, { 0, 1 },
			{ -1, 0 }, { 0, -1 } };
	}
	virtual ~MapControl() {}

	void SetLT(Vector2f lt) { this->lt = lt; }

	void SetMoveable(Vector2i coord, int mobility)
	{
		if (mobility < 0)
			return ;

		for (int i = 0; i < 4; i++)
		{
			Vector2i tmp(
				coord.x + offset[i].x,
				coord.y + offset[i].y);
			SetMoveable(tmp, mobility - 1);
		}

		OverlayTile* tile = overlay[coord.x][coord.y];
		if (tile->GetActive())
			return;

		activeTiles.push_back(tile);
		tile->SetActive(true);
		tile->SetFillColor((int)TileType::Moveable);
		algorithmCount++;
	}

	void SetAttackRange(Vector2i coord, int range, bool fill)
	{
		if (range < 0)
			return;

		for (int i = 0; i < 4; i++)
		{
			Vector2i tmp(
				coord.x + offset[i].x,
				coord.y + offset[i].y);
			SetAttackRange(tmp, range - 1, fill);
		}

		if (!fill && range != 0)
			return;
		overlay[coord.x][coord.y]->SetFillColor((int)TileType::AttackRange);
	}

	void SetImmovable(Vector2i coord)
	{
		overlay[coord.x][coord.y]->SetFillColor((int)TileType::Immovable);
		// 장애물 추가시
	}

	void SetOverlayInactive()
	{
		focus = nullptr;
		for (auto tile : activeTiles)
		{
			tile->Reset();
		}
		activeTiles.clear();
	}

	Vector2f Step(const Vector2f& objPos, int moveX, int moveY)
	{
		return Vector2f(
			objPos.x + moveX * unit,
			objPos.y + moveY * unit);
	}

	Vector2i PosToIdx(Vector2f pos)
	{
		return Vector2i(
			((-lt.x + pos.x) / unit),
			((-lt.y + pos.y) / unit) - 1);
	}

	Vector2f IdxToPos(Vector2i idx)
	{
		return Vector2f(
			lt.x + ((float)idx.x + 0.5f) * unit,
			lt.y + (idx.y + 1) * unit
		);
	}
};