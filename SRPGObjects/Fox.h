#pragma once
#include "../SFML_Framework/GameObject/SpriteObj.h"
#include "../SFML_Framework/Framework/Animatable.h"

class Fox : public SpriteObj, Animatable
{
protected:
	enum class States
	{
		None = -1,
		Idle,
		Idle2,
		Move,
		Catch,
		Sleep,
		Hit,
		Death
	};

public:
	virtual void Init();
	virtual void Release();
	virtual void Reset();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	virtual void SetAnimations() override;
};