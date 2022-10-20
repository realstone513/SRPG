#include "Minotaurs.h"
#include "../SFML_Framework/Frameworks.h"

void Minotaurs::Init()
{
	SetTexture(*RESOURCE_MGR->GetTexture("graphics/Minotaurs.png"));
	SetScale(5.f, 5.f);

	SetAnimations(); 
	
	Reset();
}

void Minotaurs::Release()
{
}

void Minotaurs::Reset()
{
	Object::Reset();
	SetPos({ 1000.f, 700.f });
	SetState((int) States::Idle);
	anim.Play("Mino/IdleRight");
	anim.PlayQueue("Mino/RunRight");
	anim.PlayQueue("Mino/ReadyRight");
	anim.PlayQueue("Mino/BigAttackRight");
	anim.PlayQueue("Mino/StabRight");
	anim.PlayQueue("Mino/StompRight");
	anim.PlayQueue("Mino/WheelWindRight");
	anim.PlayQueue("Mino/HitRight");
	anim.PlayQueue("Mino/DeathRight");

	anim.PlayQueue("Mino/IdleLeft");
	anim.PlayQueue("Mino/RunLeft");
	anim.PlayQueue("Mino/ReadyLeft");
	anim.PlayQueue("Mino/BigAttackLeft");
	anim.PlayQueue("Mino/StabLeft");
	anim.PlayQueue("Mino/StompLeft");
	anim.PlayQueue("Mino/WheelWindLeft");
	anim.PlayQueue("Mino/HitLeft");
	anim.PlayQueue("Mino/DeathLeft");
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