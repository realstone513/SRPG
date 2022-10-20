#include "Minotaurs.h"
#include "../SFML_Framework/Frameworks.h"

void Minotaurs::Init()
{
	SetTexture(*RESOURCE_MGR->GetTexture("graphics/Minotaurs.png"));
	SetPos({ 800.f, 600.f });
	SetScale(5.f, 5.f);
	SetOrigin(Origins::MC);

	anim.SetTarget(&sprite);

	{
		anim.AddClip(*RESOURCE_MGR->GetAnimationClip("Mino/Idle"));
		AnimationEvent ev;
		ev.clipId = "Mino/Idle";
		ev.frame = 5;
		anim.AddEvent(ev);
	}
	
	SetState((int) States::Idle);
	anim.Play("Mino/Idle");
}

void Minotaurs::Release()
{
}

void Minotaurs::Reset()
{
	SetState((int) States::Idle);
}

void Minotaurs::Update(float dt)
{
	anim.Update(dt);
}

void Minotaurs::Draw(RenderWindow& window)
{
	window.draw(sprite);
}

void Minotaurs::SetAnimations()
{

}