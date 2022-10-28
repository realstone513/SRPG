#include "Piece.h"
#include <sstream>
#include "../SFML_Framework/Framework/ConsoleLogger.h"
#include "../SFML_Framework/Framework/ResourceMgr.h"

Piece::Piece(PieceTypes pt, int h, int d, int a, int r, int m, bool f)
	: pType(pt), maxHealth(h), damage(d), armor(a),
	range(r), mobility(m), rangeFill(f),
	isTurn(false), isPlayable(false), done(false), isDeath(false), speed(300.f),
	animDir(true), curIdx({ -1, -1 }), beforeIdx({ -1, -1 })
{
	health = maxHealth;
}

void Piece::Reset()
{
	Object::Reset();
	currState = States::Idle;
	health = maxHealth;
	done = false;
	isTurn = false;
	isDeath = false;
	beforeIdx = { -1, -1 };
	curIdx = { -1, -1 };
}

void Piece::Update(float dt)
{
	if (dist > 0.f)
	{
		dist -= dt * speed;
		Translate(dir * speed * dt);
		if (dist <= 0.f) // 이동 끝나면
		{
			StopTranslate();
		}
	}
}

void Piece::SetPos(const Vector2f& pos)
{
	SpriteObj::SetPos(pos);
}

void Piece::SetIdxPos(const Vector2i& pos)
{
	beforeIdx = curIdx;
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

void Piece::AddClipFast(string clipId, int frame)
{
	anim.AddClip(*RESOURCE_MGR->GetAnimationClip(clipId));
	AnimationEvent ev;
	ev.clipId = clipId;
	ev.frame = frame;
	anim.AddEvent(ev);
}

void Piece::SetState(States newState)
{
	if (currState == newState)
		return;
	currState = newState;
}

void Piece::StopTranslate()
{
	dist = 0.f;
	dir = { 0, 0 };
	SetPos(dest);
	SetState(States::Idle);
	dest = { 0, 0 };
}