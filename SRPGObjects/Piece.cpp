#include "Piece.h"
#include <sstream>
#include "../SFML_Framework/Framework/ConsoleLogger.h"
#include "../SFML_Framework/Framework/ResourceMgr.h"

Piece::Piece(PieceTypes pt)
	: pType(pt),
	isTurn(false), isPlayable(false), done(false), isDeath(false), speed(300.f),
	animDir(true), curIdx({ -1, -1 }), beforeIdx({ -1, -1 }), recognize(false)
{
}

void Piece::Reset()
{
	Object::Reset();
	stats.ResetStats();
	isTurn = false;
	isDeath = false;
	curIdx = { -1, -1 };
	TurnReset();
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

void Piece::TurnReset()
{
	currState = States::Idle;
	done = false;
	beforeIdx = { -1, -1 };
}

string Piece::GetStatusString() const
{
	stringstream ss;
	ss << GetName() << " stats" << endl <<
		"base health: " << stats.baseHealth << endl <<
		"base damage: " << stats.baseDamage << endl <<
		"base armor: " << stats.baseArmor << endl <<
		"base range: " << stats.baseRange << endl <<
		"base mobility: " << stats.baseMobility << endl <<
		"modify health: " << stats.modifyHealth << endl <<
		"modify damage: " << stats.modifyDamage << endl <<
		"modify armor: " << stats.modifyArmor << endl <<
		"modify range: " << stats.modifyRange << endl <<
		"modify mobility: " << stats.modifyMobility << endl <<
		"current health: " << stats.currentHealth << endl;
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