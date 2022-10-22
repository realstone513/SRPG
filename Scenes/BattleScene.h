#pragma once
#include "../SFML_Framework/Scenes/Scene.h"
#include "../GameSystem/MapControl.h"

class Cat;
class Fox;
class Minotaur;
class Player;
class Squirrel;
class Piece;
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

	// Objects
	Cat* cat;
	Fox* fox;
	Minotaur* mino;
	Player* player;
	Squirrel* squirrel;
	list<Piece*> gamePieces;

	vector<vector<OverlayTile*>> overlay;

	// Values
	Vector2f size;
	bool fsv; // fullScreenView
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
};