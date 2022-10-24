#include "Minotaurs.h"
#include "../SFML_Framework/Frameworks.h"

Minotaur::Minotaur(PieceTypes pt)
	: Piece(pt, 400, 75, 50, 1, 6)
{
	SetType("AI");
	SetName("Minotaur");
	isPlayable = false;
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
	Object::Reset();
	SetState(States::Idle);
	anim.Play("Mino/IdleLeft");
}

void Minotaur::Update(float dt)
{
	anim.Update(dt);
}

void Minotaur::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
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