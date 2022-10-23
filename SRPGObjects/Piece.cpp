#include "Piece.h"
#include <sstream>

Piece::Piece(PieceTypes pt, int h, int d, int a, int r, int m, bool f)
	: pType(pt), health(h), damage(d), armor(a),
	range(r), mobility(m), rangeFill(f)
{
}

void Piece::Update(float dt)
{

}

void Piece::SetPos(const Vector2f& pos)
{
	SpriteObj::SetPos(pos);
}

void Piece::SetIdxPos(const Vector2i& pos)
{
	curIdx = pos;
}

const Vector2i& Piece::GetIdxPos() const
{
	return curIdx;
}

string Piece::GetStatusString() const
{
	stringstream ss;
	ss << "health: " << health << endl <<
		"damage: " << damage << endl <<
		"armor: " << armor << endl <<
		"range: " << range << endl <<
		"mobility: " << mobility << endl;
	return ss.str();
}