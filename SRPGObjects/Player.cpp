#include "Player.h"
#include "../SFML_Framework/Frameworks.h"

Player::Player(PieceTypes pt)
	: Piece(pt, 100, 30, 20, 1, 5)
{
	SetType("Playable");
	SetName("Player");
	isPlayable = true;
}

void Player::Init()
{
	SetTexture(*RESOURCE_MGR->GetTexture("graphics/Adventurer.png"));
	SetAnimations();
	Reset();
}

void Player::Release()
{
}

void Player::Reset()
{
	Piece::Reset();
	SetState(States::Idle);
	anim.Play("Player/Idle");
}

void Player::Update(float dt)
{
	Piece::Update(dt);
	anim.Update(dt);
}

void Player::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Player::SetPos(const Vector2f& pos)
{
	Piece::SetPos(pos);
}

void Player::SetAnimations()
{
	anim.SetTarget(&sprite);

	AddClipFast("Player/Idle", 13);

	AddClipFast("Player/MoveRight", 8);
	AddClipFast("Player/AttackRight1", 10);
	AddClipFast("Player/AttackRight2", 10);
	AddClipFast("Player/AttackRight3", 10);
	AddClipFast("Player/JumpRight", 6);
	AddClipFast("Player/HitRight", 4);
	AddClipFast("Player/DeathRight", 7);

	AddClipFast("Player/MoveLeft", 8);
	AddClipFast("Player/AttackLeft1", 10);
	AddClipFast("Player/AttackLeft2", 10);
	AddClipFast("Player/AttackLeft3", 10);
	AddClipFast("Player/JumpLeft", 6);
	AddClipFast("Player/HitLeft", 4);
	AddClipFast("Player/DeathLeft", 7);
}

void Player::PlayAnimate(States state)
{
	switch (state)
	{
	case Animatable::States::Idle:
		anim.Play("Player/Idle");
		break;

	case Animatable::States::Move:
		if (dir.x > 0)
			anim.Play("Player/MoveRight");
		else
			anim.Play("Player/MoveLeft");
		break;

	case Animatable::States::Attack:
		int ran = Utils::RandomRange(0, 2);
		if (dir.x > 0)
		{
			switch (ran)
			{
			case 0:
				anim.Play("Player/AttackRight1");
				break;
			case 1:
				anim.Play("Player/AttackRight2");
				break;
			case 2:
				anim.Play("Player/AttackRight3");
				break;
			}
		}
		else
		{
			switch (ran)
			{
			case 0:
				anim.Play("Player/AttackLeft1");
				break;
			case 1:
				anim.Play("Player/AttackLeft2");
				break;
			case 2:
				anim.Play("Player/AttackLeft3");
				break;
			}
		}
		break;

	case Animatable::States::Special:
		break;

	case Animatable::States::Hit:
		if (dir.x > 0)
		{
			anim.Play("Player/HitRight");
		}
		else
		{
			anim.Play("Player/HitLeft");
		}
		break;

	case Animatable::States::Death:
		if (dir.x > 0)
		{
			anim.Play("Player/DeathRight");
		}
		else
		{
			anim.Play("Player/DeathLeft");
		}
		break;
	case Animatable::States::Others:
		break;
	default:
		break;
	}
}