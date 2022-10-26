#include "Minotaurs.h"
#include "../SFML_Framework/Frameworks.h"

Minotaur::Minotaur(PieceTypes pt)
	: Piece(pt, 400, 75, 50, 1, 6)
{
	SetType("AI");
	SetName("Minotaur");
	isPlayable = false;
	speed = 350.f;
}

void Minotaur::Init()
{
	SetTexture(*RESOURCE_MGR->GetTexture("graphics/Minotaur.png"));
	SetAnimations();
	Reset();
}

void Minotaur::Release()
{
}

void Minotaur::Reset()
{
	Piece::Reset();
	SetState(States::Idle);
}

void Minotaur::Update(float dt)
{
	Piece::Update(dt);
	anim.Update(dt);
}

void Minotaur::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Minotaur::SetPos(const Vector2f& pos)
{
	Piece::SetPos(pos);
}

void Minotaur::SetAnimations()
{
	anim.SetTarget(&sprite);

	AddClipFast("Mino/IdleRight", 5);
	AddClipFast("Mino/RunRight", 8);
	AddClipFast("Mino/ReadyRight", 5);
	AddClipFast("Mino/BigAttackRight", 9);
	AddClipFast("Mino/StabRight", 5);
	AddClipFast("Mino/StompRight", 6);
	AddClipFast("Mino/WheelWindRight", 12);
	AddClipFast("Mino/HitRight", 3);
	AddClipFast("Mino/DeathRight", 6);

	AddClipFast("Mino/IdleLeft", 5);
	AddClipFast("Mino/RunLeft", 8);
	AddClipFast("Mino/ReadyLeft", 5);
	AddClipFast("Mino/BigAttackLeft", 9);
	AddClipFast("Mino/StabLeft", 5);
	AddClipFast("Mino/StompLeft", 6);
	AddClipFast("Mino/WheelWindLeft", 12);
	AddClipFast("Mino/HitLeft", 3);
	AddClipFast("Mino/DeathLeft", 6);
}

void Minotaur::SetState(States newState)
{
	Piece::SetState(newState);

	int ran;
	switch (currState)
	{
	case States::Idle:
		if (animDir)
			anim.Play("Mino/IdleRight");
		else
			anim.Play("Mino/IdleLeft");
		break;

	case States::Move:
		if (animDir)
			anim.Play("Mino/RunRight");
		else
			anim.Play("Mino/RunLeft");
		break;

	case States::Attack:
		if (animDir)
		{
			anim.Play("Mino/BigAttackRight");
			anim.PlayQueue("Mino/IdleRight");
		}
		else
		{
			anim.Play("Mino/BigAttackLeft");
			anim.PlayQueue("Mino/IdleLeft");
		}
		break;

	case States::Special:
		if (animDir)
		{
			anim.Play("Mino/WheelWindRight");
			anim.PlayQueue("Mino/IdleRight");
		}
		else
		{
			anim.Play("Mino/WheelWindLeft");
			anim.PlayQueue("Mino/IdleLeft");
		}
		break;

	case States::Hit:
		if (animDir)
		{
			anim.Play("Mino/HitRight");
			anim.PlayQueue("Mino/IdleRight");
		}
		else
		{
			anim.Play("Mino/HitLeft");
			anim.PlayQueue("Mino/IdleLeft");
		}
		break;

	case States::Death:
		if (animDir)
		{
			anim.Play("Mino/DeathRight");
		}
		else
		{
			anim.Play("Mino/DeathLeft");
		}
		break;
	default:
		break;
	}
}