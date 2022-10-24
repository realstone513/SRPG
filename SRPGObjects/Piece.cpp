#include "Piece.h"
#include <sstream>

Piece::Piece(PieceTypes pt, int h, int d, int a, int r, int m, bool f)
	: pType(pt), MaxHealth(h), damage(d), armor(a),
	range(r), mobility(m), rangeFill(f),
	isTurn(false), isPlayable(false), done(false), isDeath(false)
{
	health = MaxHealth;
	overlaySprite = sprite;
}

void Piece::Reset()
{
	Object::Reset();
	health = MaxHealth;
	done = false;
	isTurn = false;
	isDeath = false;
}

void Piece::Update(float dt)
{
	overlaySprite.setPosition(position);
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

void Piece::SetIsTurn(bool isTurn)
{
	this->isTurn = isTurn;
}

bool Piece::GetIsTurn()
{
	return isTurn;
}

void Piece::SetDone(bool done)
{
	this->done = done;
}

bool Piece::GetDone()
{
	return done;
}