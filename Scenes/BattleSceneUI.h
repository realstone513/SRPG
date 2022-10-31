#pragma once
#include "../SFML_Framework/UI/UIMgr.h"

class Scene;
class Piece;
class SpriteObj;
class TextObj;
class RectangleObj;
class FloatingObj;
class DamageUI;

class BattleSceneUI : public UIMgr
{
protected:
	Vector2i size;

	// Playable Info
	SpriteObj*		leftUIBackground;
	SpriteObj*		leftThumbnailBackground;
	SpriteObj*		leftThumbnail;
	SpriteObj*		leftDamageIcon;
	SpriteObj*		leftArmorIcon;
	SpriteObj*		leftRangeIcon;
	SpriteObj*		leftMobilityIcon;
	RectangleObj*	leftHealthBarBackground;
	RectangleObj*	leftHealthBar;
		
	TextObj*		leftNameText;
	TextObj*		leftHealthText;
	TextObj*		leftMaxHealthText;
	TextObj*		leftDamageText;
	TextObj*		leftArmorText;
	TextObj*		leftRangeText;
	TextObj*		leftMobilityText;

	// AI Info
	SpriteObj*		rightUIBackground;
	SpriteObj*		rightThumbnailBackground;
	SpriteObj*		rightThumbnail;
	SpriteObj*		rightDamageIcon;
	SpriteObj*		rightArmorIcon;
	SpriteObj*		rightRangeIcon;
	SpriteObj*		rightMobilityIcon;
	RectangleObj*	rightHealthBarBackground;
	RectangleObj*	rightHealthBar;

	TextObj*		rightNameText;
	TextObj*		rightHealthText;
	TextObj*		rightMaxHealthText;
	TextObj*		rightDamageText;
	TextObj*		rightArmorText;
	TextObj*		rightRangeText;
	TextObj*		rightMobilityText;

	// Command Window
	SpriteObj*		commandAttackButton;
	SpriteObj*		commandSpecialButton;
	SpriteObj*		commandToolButton;
	SpriteObj*		commandWaitButton;
	
	TextObj*		commandAttackText;
	TextObj*		commandSpeicialText;
	TextObj*		commandToolText;
	TextObj*		commandWaitText;

	// no group
	FloatingObj*	damageText;
	TextObj*		turnStateHUD;
	TextObj*		gameResultText;

public:
	BattleSceneUI(Scene* scene);
	virtual ~BattleSceneUI();

	virtual void Init();
	virtual void Release();
	virtual void Reset();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	void SetPlayableInfo(Piece* playable);
	void SetAIInfo(Piece* ai);
	void SetUIActive(string type, bool enable);
	void SetDamageText(Vector2f pos, float dmg);
	void SetCommandWindow(Vector2f pos);
	void SetHud(bool isPlayerTurn, int count);

	void ShowResultText(bool isPlayerWin);

	list<SpriteObj*> buttons;
	Color uiBaseColor;
	bool commandUIActive;
};