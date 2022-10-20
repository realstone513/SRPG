#pragma once
#include "../SFML_Framework/Scenes/Scene.h"

class Player;
class Minotaurs;

class BattleScene : public Scene
{
protected:
	Player* player;
	Minotaurs* mino;

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