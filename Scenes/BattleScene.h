#pragma once
#include "../SFML_Framework/Scenes/Scene.h"
#include "../GameSystem/MapControl.h"
#include "BattleSceneUI.h"
#include <deque>

class Camera;
class Cat;
class Fox;
class Minotaur;
class Player;
class Piece;
class Squirrel;
class OverlayTile;

class BattleScene : public Scene, MapControl
{
protected:
	enum class Phase
	{
		None = -1,
		Wait,
		Action,
		ActionAfterMove,
	};

	/*struct Task
	{
		Piece* piece;
		float delay;
		void (*Todo)();
		Task(Piece* p, float d) : piece(p), delay(d)
		{
		}

		Task(Piece* p, float d, void(*todo)()) : piece(p), delay(d)
		{
			Todo = todo;
		}
	};*/
	/*deque<Task*> delayQueue;
	Task* task;*/

	// Objects
	Cat* cat;
	Fox* fox;
	Minotaur* mino;
	Player* player;
	Squirrel* squirrel;
	Piece* viewTarget;
	Camera* camera;

	vector<vector<OverlayTile*>> overlay;

	BattleSceneUI* UIMgr;

	// Values
	bool fsv; // fullScreenView
	Vector2f size;
	Phase curPhase;

	

public:
	BattleScene();
	virtual ~BattleScene() {}

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void CreateBackground(int width, int height, float quadWidth, float quadHeight);
	void CreateOverlay(int width, int height, float quadWidth, float quadHeight);
	void SetFullScreenWorldView();
	void SetViewFocusOnObj(Piece* obj);

	void AIAction();
};