#pragma once
#include "../SFML_Framework/Scenes/Scene.h"

class SpriteObj;

class TitleScene : public Scene
{
protected:
	SpriteObj* titleBackground;

public:
	TitleScene();
	virtual ~TitleScene() {}

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};