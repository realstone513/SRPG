#include "Fox.h"
#include "../SFML_Framework/Frameworks.h"

Fox::Fox(PieceTypes pt)
	: Piece(pt, 120, 30, 10, 2, 6, false)
{
	SetType("AI");
	SetName("Fox");
	isPlayable = false;
	speed = 250.f;
}

void Fox::Init()
{
	SetTexture(*RESOURCE_MGR->GetTexture("graphics/Fox.png"));
	SetAnimations();
	Reset();
}

void Fox::Release()
{
}

void Fox::Reset()
{
	Piece::Reset();
	SetState(States::Idle);
}

void Fox::Update(float dt)
{
	Piece::Update(dt);
	anim.Update(dt);
}

void Fox::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Fox::SetPos(const Vector2f& pos)
{
	Piece::SetPos(pos);
}

void Fox::SetAnimations()
{
	anim.SetTarget(&sprite);

	AddClipFast("Fox/Idle", 5);
	AddClipFast("Fox/Idle2", 14);
	AddClipFast("Fox/Move", 8);
	AddClipFast("Fox/Catch", 11);
	AddClipFast("Fox/Hit", 5);
	AddClipFast("Fox/Sleep", 6);
	AddClipFast("Fox/Death", 7);
}

void Fox::SetState(States newState)
{
	Piece::SetState(newState);

	switch (currState)
	{
	case States::Idle:
		anim.Play("Fox/Idle");
		break;

	case States::Move:
		anim.Play("Fox/Move");
		break;

	case States::Attack:
		anim.Play("Fox/Catch");
		anim.PlayQueue("Fox/Idle");
		break;

	case States::Special:
		anim.Play("Fox/Sleep");
		anim.PlayQueue("Fox/Idle");
		break;

	case States::Hit:
		anim.Play("Fox/Hit");
		anim.PlayQueue("Fox/Idle");
		break;

	case States::Death:
		anim.Play("Fox/Death");
		break;

	default:
		break;
	}
}