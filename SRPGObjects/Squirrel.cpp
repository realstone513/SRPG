#include "Squirrel.h"
#include "../SFML_Framework/Frameworks.h"

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
	Object::Reset();
	SetState((int)States::Idle);
	anim.Play("Squirrel/Idle");
	anim.PlayQueue("Squirrel/Idle2");
	anim.PlayQueue("Squirrel/Move");
	anim.PlayQueue("Squirrel/Dig");
	anim.PlayQueue("Squirrel/Hit");
	anim.PlayQueue("Squirrel/Death");
	anim.PlayQueue("Squirrel/Eat");
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