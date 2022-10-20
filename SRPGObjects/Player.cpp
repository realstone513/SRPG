#include "Player.h"
#include "../SFML_Framework/Frameworks.h"

void Player::Init()
{
	SetTexture(*RESOURCE_MGR->GetTexture("graphics/Adventurer.png"));
	SetScale(5.f, 5.f);

	SetAnimations(); 
	
	Reset();
}

void Player::Release()
{
}

void Player::Reset()
{
	Object::Reset();
	SetPos({ 200.f, 400.f });
	SetState((int) States::Idle);
	anim.Play("Player/Idle");
	anim.PlayQueue("Player/AttackRight1");
	anim.PlayQueue("Player/AttackRight2");
	anim.PlayQueue("Player/AttackRight3");
	anim.PlayQueue("Player/JumpRight");
	anim.PlayQueue("Player/HitRight");
	anim.PlayQueue("Player/DeathRight");
	anim.PlayQueue("Player/MoveRight");
	anim.PlayQueue("Player/AttackLeft1");
	anim.PlayQueue("Player/AttackLeft2");
	anim.PlayQueue("Player/AttackLeft3");
	anim.PlayQueue("Player/JumpLeft");
	anim.PlayQueue("Player/HitLeft");
	anim.PlayQueue("Player/DeathLeft");
	anim.PlayQueue("Player/MoveLeft");
	anim.PlayQueue("Player/Idle");
}

void Player::Update(float dt)
{
	anim.Update(dt);
}

void Player::Draw(RenderWindow& window)
{
	window.draw(sprite);
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