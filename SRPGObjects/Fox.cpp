#include "Fox.h"
#include "../SFML_Framework/Frameworks.h"

void Fox::Init()
{
	SetTexture(*RESOURCE_MGR->GetTexture("graphics/Fox.png"));
	SetScale(5.f, 5.f);
	SetOrigin(Origins::MC);

	SetAnimations();

	Reset();
}

void Fox::Release()
{
}

void Fox::Reset()
{
	Object::Reset();
	SetPos({ 600.f, 500.f });
	SetState((int)States::Idle);
	anim.Play("Fox/Idle");
	anim.PlayQueue("Fox/Idle2");
	anim.PlayQueue("Fox/Move");
	anim.PlayQueue("Fox/Catch");
	anim.PlayQueue("Fox/Hit");
	anim.PlayQueue("Fox/Sleep");
	anim.PlayQueue("Fox/Death");
}

void Fox::Update(float dt)
{
	anim.Update(dt);
}

void Fox::Draw(RenderWindow& window)
{
	window.draw(sprite);
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