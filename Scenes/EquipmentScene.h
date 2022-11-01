#pragma once
#include "../SFML_Framework/Scenes/Scene.h"
#include "EquipmentSceneUI.h"

class SpriteObj;

class EquipmentScene : public Scene
{
protected:
	SpriteObj* equipBackground;
	EquipmentSceneUI* UIMgr;

public:
	EquipmentScene();
	virtual ~EquipmentScene() {}

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};