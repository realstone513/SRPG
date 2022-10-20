#pragma once
#include "../SFML_Framework/Scenes/Scene.h"

class Cat;
class Fox;
class Minotaurs;
class Player;
class Squirrel;

class BattleScene : public Scene
{
protected:
	Cat* cat;
	Fox* fox;
	Minotaurs* mino;
	Player* player;
	Squirrel* squirrel;

public:
	BattleScene();
	virtual ~BattleScene();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void CreateBackground(int width, int height, float quadWidth, float quadHeight);
};