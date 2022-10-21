#include "Cat.h"
#include "../SFML_Framework/Frameworks.h"

void Cat::Init()
{
	SetTexture(*RESOURCE_MGR->GetTexture("graphics/Cat.png"));
	SetAnimations();
	Reset();
}

void Cat::Release()
{
}

void Cat::Reset()
{
	Object::Reset();
	SetState(States::Idle);
	anim.Play("Cat/Idle");
	anim.PlayQueue("Cat/Grooming1");
	anim.PlayQueue("Cat/Grooming2");
	anim.PlayQueue("Cat/Move");
	anim.PlayQueue("Cat/Run");
	anim.PlayQueue("Cat/Sleep");
	anim.PlayQueue("Cat/Threat");
	anim.PlayQueue("Cat/Hit");
	anim.PlayQueue("Cat/Punch");
}

void Cat::Update(float dt)
{
	anim.Update(dt);
}

void Cat::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Cat::SetAnimations()
{
	anim.SetTarget(&sprite);

	AddClipFast("Cat/Idle", 4);
	AddClipFast("Cat/Grooming1", 4);
	AddClipFast("Cat/Grooming2", 4);
	AddClipFast("Cat/Move", 8);
	AddClipFast("Cat/Run", 8);
	AddClipFast("Cat/Sleep", 4);
	AddClipFast("Cat/Punch", 6);
	AddClipFast("Cat/Hit", 7);
	AddClipFast("Cat/Threat", 8);
}