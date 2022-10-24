#include "Fox.h"
#include "../SFML_Framework/Frameworks.h"

Fox::Fox(PieceTypes pt)
	: Piece(pt, 120, 30, 10, 1, 5)
{
	SetType("AI");
	SetName("Fox");
	isPlayable = false;
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
	anim.Play("Fox/Idle");
}

void Fox::Update(float dt)
{
	anim.Update(dt);
}

void Fox::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
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