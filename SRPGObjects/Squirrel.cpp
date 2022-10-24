#include "Squirrel.h"
#include "../SFML_Framework/Frameworks.h"

Squirrel::Squirrel(PieceTypes pt)
	: Piece(pt, 50, 10, 0, 1, 2)
{
	SetType("AI");
	SetName("Squirrel");
	isPlayable = false;
}

void Squirrel::Init()
{
	SetTexture(*RESOURCE_MGR->GetTexture("graphics/Squirrel.png"));
	SetAnimations();
	Reset();
}

void Squirrel::Release()
{
}

void Squirrel::Reset()
{
	Piece::Reset();
	SetState(States::Idle);
	anim.Play("Squirrel/Idle");
}

void Squirrel::Update(float dt)
{
	anim.Update(dt);
}

void Squirrel::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Squirrel::SetAnimations()
{
	anim.SetTarget(&sprite);

	AddClipFast("Squirrel/Idle", 6);
	AddClipFast("Squirrel/Idle2", 6);
	AddClipFast("Squirrel/Move", 8);
	AddClipFast("Squirrel/Dig", 4);
	AddClipFast("Squirrel/Eat", 2);
	AddClipFast("Squirrel/Hit", 4);
	AddClipFast("Squirrel/Death", 4);
}