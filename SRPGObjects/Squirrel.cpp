#include "Squirrel.h"
#include "../SFML_Framework/Frameworks.h"

void Squirrel::Init()
{
	SetTexture(*RESOURCE_MGR->GetTexture("graphics/Squirrel.png"));
	SetScale(5.f, 5.f);

	SetAnimations();

	Reset();
}

void Squirrel::Release()
{
}

void Squirrel::Reset()
{
	Object::Reset();
	SetPos({ 400.f, 500.f });
	SetState((int)States::Idle);
	anim.Play("Squirrel/Idle");
	anim.PlayQueue("Squirrel/Idle2");
	anim.PlayQueue("Squirrel/Move");
	anim.PlayQueue("Squirrel/Dig");
	anim.PlayQueue("Squirrel/Eat");
	anim.PlayQueue("Squirrel/Hit");
	anim.PlayQueue("Squirrel/Death");
}

void Squirrel::Update(float dt)
{
	anim.Update(dt);
}

void Squirrel::Draw(RenderWindow& window)
{
	window.draw(sprite);
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