#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

class MapControl
{
protected:
	float unit;
	Vector2f lt;
	Vector2f rb;
	float mapRealWidth;
	float mapRealHeight;
	float mapHalfWidth;
	float mapHalfHeight;
	int mapIdxWidth;
	int mapIdxHeight;

public:
	MapControl() {}
	virtual ~MapControl() {}

	void MCInit(float cellWidth, Vector2f _lt, Vector2f _rb)
	{
		unit = cellWidth;
		lt = _lt;
		rb = _rb;
		mapRealWidth = abs(lt.x) + abs(rb.x);
		mapRealHeight = abs(lt.y) + abs(rb.y);
		mapHalfWidth = mapRealWidth * 0.5f;
		mapHalfHeight = mapRealHeight * 0.5f;
		mapIdxWidth = mapRealWidth / unit;
		mapIdxHeight = mapRealHeight / unit;
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

	Vector2f Step(const Vector2f& objPos, int moveX, int moveY)
	{
		return Vector2f(
			objPos.x + moveX * unit,
			objPos.y + moveY * unit);
	}
};