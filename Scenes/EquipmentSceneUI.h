#pragma once
#include "../SFML_Framework/UI/UIMgr.h"
#include <vector>

class SpriteObj;
class TextObj;
class RectangleObj;

class EquipmentSceneUI : public UIMgr
{
protected:
	enum class Stats
	{
		Damage,
		Armor,
		Health
	};

	Vector2i size;
	int count;

	vector<TextObj*> statTexts;

	TextObj* successCountText;
	TextObj* successRateText;
	TextObj* gamePlayText;

public:
	EquipmentSceneUI(Scene* scene);
	virtual ~EquipmentSceneUI() {}

	virtual void Init();
	virtual void Release();
	virtual void Reset();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	vector<SpriteObj*> buttons;
	vector<vector<RectangleObj*>> successCountRectangles;
	SpriteObj* gamePlayButton;
	TextObj* successCountNumber;
	TextObj* successRateNumber;
	vector<int> idxCounts;
	int successRate;
	int successCountTotal;
};