#pragma once
#include "../SFML_Framework/GameObject/SpriteObj.h"

// 공통적으로 쓸 것들 추가
class Piece : public SpriteObj
{
protected:

public:
	int health;
	int damage;
	int armor;
	int range;
	int mobility;
	bool rangeFill;

	Piece(int h, int d, int a, int r, int m, bool f = true)
		: health(h), damage(d), armor(a), range(r), mobility(m), rangeFill(f) {}
	virtual ~Piece() {};
};