#include "Player.h"
#include "../SFML_Framework/Frameworks.h"

Player::Player(PieceTypes pt)
	: Piece(pt)
{
	SetType("Playable");
	SetName("Player");
	isPlayable = true;
}

void Player::Init()
{
	SetTexture(*RESOURCE_MGR->GetTexture("graphics/Adventurer.png"));
	SetAnimations();
	stats.SetBaseStats(100, 30, 20, 1, 6);
	Reset();
}

void Player::Release()
{
}

void Player::Reset()
{
	Piece::Reset();
	stats.ResetStats();
	SetState(States::Idle);
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
	AddClipFast("Player/SpecialRight", 20);
	AddClipFast("Player/JumpRight", 6);
	AddClipFast("Player/HitRight", 4);
	AddClipFast("Player/DeathRight", 7);

	AddClipFast("Player/MoveLeft", 8);
	AddClipFast("Player/AttackLeft1", 10);
	AddClipFast("Player/AttackLeft2", 10);
	AddClipFast("Player/AttackLeft3", 10);
	AddClipFast("Player/SpecialLeft", 20);
	AddClipFast("Player/JumpLeft", 6);
	AddClipFast("Player/HitLeft", 4);
	AddClipFast("Player/DeathLeft", 7);
}

void Player::SetState(States newState)
{
	Piece::SetState(newState);

	int ran;
	switch (currState)
	{
	case States::Idle:
		anim.Play("Player/Idle");
		break;

	case States::Move:
		if (animDir)
			anim.Play("Player/MoveRight");
		else
			anim.Play("Player/MoveLeft");
		break;

	case States::Attack:
		ran = Utils::RandomRange(0, 2);
		if (animDir)
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
		anim.PlayQueue("Player/Idle");
		break;

	case States::Special:
		if (animDir)
			anim.Play("Player/SpecialRight");
		else
			anim.Play("Player/SpecialLeft");
		anim.PlayQueue("Player/Idle");
		break;

	case States::Hit:
		if (animDir)
			anim.Play("Player/HitRight");
		else
			anim.Play("Player/HitLeft");
		anim.PlayQueue("Player/Idle");
		break;

	case States::Death:
		if (animDir)
			anim.Play("Player/DeathRight");
		else
			anim.Play("Player/DeathLeft");
		break;
	default:
		break;
	}
}