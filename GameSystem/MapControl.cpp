#include "MapControl.h"
#include "../SFML_Framework/Framework/ConsoleLogger.h"

MapControl::MapControl(vector<vector<OverlayTile*>>& overlay, float cellWidth)
	: overlay(overlay), unit(cellWidth)
{
	offset = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };
}

void MapControl::SetLTRB(Vector2f lt, Vector2f rb)
{
	this->lt = lt;
	this->rb = rb;
	width = (abs(lt.x) + abs(rb.x)) / unit;
	height = (abs(lt.y) + abs(rb.y)) / unit;
}

void MapControl::SetMoveable(Vector2i coord, int mobility)
{
	if (mobility < 0)
		return;

	for (int i = 0; i < 4; i++)
	{
		Vector2i tmp(
			coord.x + offset[i].x,
			coord.y + offset[i].y);
		SetMoveable(tmp, mobility - 1);
	}

	OverlayTile* tile = overlay[coord.x][coord.y];
	if ((int)tile->GetTileType() !=
		(int)TileType::Inactive)
		return;

	activeTiles.push_back(tile);
	tile->SetActive(true);
	tile->SetFillColor((int)TileType::Moveable);
	algorithmCount++;
}

void MapControl::SetAttackRange(Vector2i coord, int range, bool fill)
{
	if (range < 0)
		return;

	if (coord.x < 0 || coord.x >= width || coord.y < 0 || coord.y >= height)
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
	OverlayTile* tile = overlay[coord.x][coord.y];
	activeTiles.push_back(tile);
	tile->SetActive(true);
	tile->SetFillColor((int)TileType::AttackRange);
}

void MapControl::SetImmovable(Vector2i coord)
{
	overlay[coord.x][coord.y]->SetFillColor((int)TileType::Immovable);
	// 장애물 추가시
}

void MapControl::SetOverlayInactive()
{
	for (auto tile : activeTiles)
	{
		tile->Reset();
	}
	activeTiles.clear();
}

Vector2f MapControl::Step(const Vector2f& objPos, int moveX, int moveY)
{
	return Vector2f(
		objPos.x + moveX * unit,
		objPos.y + moveY * unit);
}

Vector2i MapControl::PosToIdx(Vector2f pos)
{
	return Vector2i(
		((-lt.x + pos.x) / unit),
		((-lt.y + pos.y) / unit) - 1);
}

Vector2f MapControl::IdxToPos(Vector2i idx)
{
	return Vector2f(
		lt.x + ((float)idx.x + 0.5f) * unit,
		lt.y + (idx.y + 1) * unit
	);
}