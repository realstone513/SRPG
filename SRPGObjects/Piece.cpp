#include "Piece.h"
#include <sstream>
#include "../SFML_Framework/Framework/ConsoleLogger.h"

Piece::Piece(PieceTypes pt, int h, int d, int a, int r, int m, bool f)
	: pType(pt), maxHealth(h), damage(d), armor(a),
	range(r), mobility(m), rangeFill(f),
	isTurn(false), isPlayable(false), done(false), isDeath(false), speed(500.f)
{
	health = maxHealth;
}

void Piece::Reset()
{
	Object::Reset();
	health = maxHealth;
	done = false;
	isTurn = false;
	isDeath = false;
}

void Piece::Update(float dt)
{
	if (dist > 0.f)
	{
		dist -= dt * speed;
		Translate(dir * speed * dt);
		if (dist <= 0.f)
		{
			dir = { 0, 0 };
			dist = 0.f;
			SetPos(dest);
			dest = { 0, 0 };
		}
	}
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

void Piece::SetDest(Vector2f dest)
{
	this->dest = dest;
	dir = Utils::Normalize(dest - position);
	dist = Utils::Distance(dest, position);
}

Vector2f Piece::GetDest()
{
	return this->dest;
}