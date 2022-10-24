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
	anim.Update(dt);
}

void Player::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
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