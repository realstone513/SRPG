#include "Fox.h"
#include "../SFML_Framework/Frameworks.h"

Fox::Fox()
	: Piece(120, 30, 20, 1, 5)
{
}

void Fox::Init()
{
	SetType("AI");
	SetName("Fox");
	SetTexture(*RESOURCE_MGR->GetTexture("graphics/Fox.png"));
	SetAnimations();
	Reset();
}

void Fox::Release()
{
}

void Fox::Reset()
{
	Object::Reset();
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