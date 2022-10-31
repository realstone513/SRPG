#include "MapControl.h"
#include "../SFML_Framework/Framework/ConsoleLogger.h"
#include "../SRPGObjects/OverlayTile.h"
#include "../SRPGObjects/Piece.h"

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
		if (overlay[tmp.x][tmp.y]->GetTileType() != TileType::Immovable)
			SetMoveable(tmp, mobility - 1);
	}

	if (coord.x < 0 || coord.y < 0 ||
		coord.x > width || coord.y > height)
		return;

	OverlayTile* tile = overlay[coord.x][coord.y];
	if (tile->GetTileType() != TileType::Inactive &&
		tile->GetTileType() != TileType::Immovable)
		return;

	activeTiles.push_back(tile);
	tile->SetActive(true);
	if (tile->GetTileType() == TileType::Inactive)
	{
		tile->SetTileType(TileType::Moveable);
		tile->SetFillColor((int)TileType::Moveable);
	}
	algorithmCount++;
}

void MapControl::SetAttackRange(Vector2i coord, int range, int rangeOrigin, bool fill)
{
	if (range < 0)
		return;

	if (coord.x < 0 || coord.y < 0 ||
		coord.x > width || coord.y > height)
		return;

	for (int i = 0; i < 4; i++)
	{
		Vector2i tmp(
			coord.x + offset[i].x,
			coord.y + offset[i].y);
		SetAttackRange(tmp, range - 1, rangeOrigin, fill);
	}

	if (!fill && !(range == 0 || range == rangeOrigin))
		return;

	OverlayTile* tile = overlay[coord.x][coord.y];
	bool find = false;
	for (auto& aTile : activeTiles)
	{
		if (tile->GetObjId() == aTile->GetObjId())
		{
			tile = aTile;
			find = true;
			break;
		}
	}
	if (!find)
		activeTiles.push_back(tile);
	tile->SetActive(true);
	if (range == rangeOrigin)
	{
		tile->SetTileType(TileType::Immovable);
		tile->SetFillColor((int)TileType::Immovable);
	}
	else
	{
		tile->SetTileType(TileType::AttackRange);
		tile->SetFillColor((int)TileType::AttackRange);
	}
}

void MapControl::SetImmovable(Vector2i coord)
{
	if (coord.x < 0 || coord.y < 0 ||
		coord.x > width || coord.y > height)
		return;

	OverlayTile* tile = overlay[coord.x][coord.y];
	tile->onTheTile = true;
	tile->SetFillColor((int)TileType::Immovable);
	tile->SetTileType(TileType::Immovable);
	activeTiles.push_back(tile);

	for (auto piece : gamePieces)
	{
		Vector2i idx = piece->GetIdxPos();
		if (Utils::ManhattanDistance(coord, idx) <= focus->mobility)
		{
			tile = overlay[idx.x][idx.y];
			tile->onTheTile = true;
			tile->SetFillColor((int)TileType::Immovable);
			tile->SetTileType(TileType::Immovable);
			activeTiles.push_back(tile);
		}
	}
}

void MapControl::SetOverlayInactive()
{
	for (auto tile : activeTiles)
	{
		tile->Reset();
	}
	activeTiles.clear();
}

void MapControl::SetPiecePos(Piece* piece, Vector2i idx)
{
	piece->SetPos(IdxToPos(idx));
	piece->SetIdxPos(idx);
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