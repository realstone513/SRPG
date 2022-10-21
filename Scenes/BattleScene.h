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
	// Objects
	Cat* cat;
	Fox* fox;
	Minotaurs* mino;
	Player* player;
	Squirrel* squirrel;

	// Values
	Vector2f size;
	float unit;
	bool fullScreenView;

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
	void SetFullScreenWorldView();
	void SetWorldViewCenter(Vector2f center);
	void SetWorldViewSize(Vector2f size);
};