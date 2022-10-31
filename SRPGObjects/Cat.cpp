#include "Cat.h"
#include "../SFML_Framework/Frameworks.h"

Cat::Cat(PieceTypes pt)
	: Piece(pt, 60, 40, 40, 2, 6, false)
{
	SetType("Playable");
	SetName("Cat");
	isPlayable = true;
}

void Cat::Init()
{
	SetTexture(*RESOURCE_MGR->GetTexture("graphics/Cat.png"));
	SetAnimations();
	Reset();
}

void Cat::Release()
{
}

void Cat::Reset()
{
	Piece::Reset();
	SetState(States::Idle);
	anim.Play("Cat/Idle");
}

void Cat::Update(float dt)
{
	Piece::Update(dt);
	anim.Update(dt);
}

void Cat::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Cat::SetPos(const Vector2f& pos)
{
	Piece::SetPos(pos);
}

void Cat::SetAnimations()
{
	anim.SetTarget(&sprite);

	AddClipFast("Cat/Idle", 4);
	AddClipFast("Cat/Grooming1", 4);
	AddClipFast("Cat/Grooming2", 4);
	AddClipFast("Cat/Move", 8);
	AddClipFast("Cat/Run", 8);
	AddClipFast("Cat/Sleep", 4);
	AddClipFast("Cat/Punch", 6);
	AddClipFast("Cat/Hit", 7);
	AddClipFast("Cat/Threat", 8);
}

void Cat::SetState(States newState)
{
	Piece::SetState(newState);

	switch (currState)
	{
	case States::Idle:
		anim.Play("Cat/Idle");
		break;

	case States::Move:
		anim.Play("Cat/Move");
		break;

	case States::Attack:
		anim.Play("Cat/Punch");
		anim.PlayQueue("Cat/Grooming1");
		break;

	case States::Special:
		anim.Play("Cat/Threat");
		anim.PlayQueue("Cat/Grooming2");
		break;

	case States::Hit:
		anim.Play("Cat/Hit");
		anim.PlayQueue("Cat/Idle");
		break;

	case States::Death:
		anim.Play("Cat/Sleep");
		break;

	default:
		break;
	}
}