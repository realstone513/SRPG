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
	// playable info
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
	TextObj*		leftHealthText;			// (현재 체력)
	TextObj*		leftMaxHealthText;		// (/ Max HP)
	TextObj*		leftDamageText;
	TextObj*		leftArmorText;
	TextObj*		leftRangeText;
	TextObj*		leftMobilityText;

	// ai info
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
	TextObj*		rightHealthText;		// (현재 체력)
	TextObj*		rightMaxHealthText;		// (/ Max HP)
	TextObj*		rightDamageText;
	TextObj*		rightArmorText;
	TextObj*		rightRangeText;
	TextObj*		rightMobilityText;

	// no group
	FloatingObj*		damageText;

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
	void SetDamageText(const Vector2f pos,
		const Vector2f dir = { 0, -1 }, float speed = 250.f, float range = 250.f);
};