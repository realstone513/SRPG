#include "EquipmentSceneUI.h"
#include "../SFML_Framework/Frameworks.h"
#include "../SFML_Framework/GameObject/SpriteObj.h"
#include "../SFML_Framework/GameObject/TextObj.h"
#include "../SFML_Framework/GameObject/RectangleObj.h"

EquipmentSceneUI::EquipmentSceneUI(Scene* scene)
	: UIMgr(scene), count(3), successRate(75), successCountTotal(0)
{
	size = FRAMEWORK->GetWindowSize();
	statTexts.resize(count);
	buttons.resize(count);
	idxCounts.resize(count);
	successCountRectangles.resize(count);

	float rectY = size.y * 0.4f + 55.f;
	for (int i = 0; i < count; i++)
	{
		statTexts[i] = new TextObj(*RESOURCE_MGR->GetFont("fonts/DNFBitBitTTF.ttf"), "", 0, 0, Color::White, 25.f);
		buttons[i] = new SpriteObj();
		idxCounts[i] = 0;
		successCountRectangles[i].resize(10);

		float rectX = size.x * 0.2f + 20.f;
		statTexts[i]->SetPos(Vector2f(rectX - 135.f, rectY - 30.f));
		Stats stat = (Stats)Utils::RandomRange(0, 2);
		string statText = "";
		switch (stat)
		{
		case EquipmentSceneUI::Stats::Damage:
			statText = "Damage";
			break;
		case EquipmentSceneUI::Stats::Armor:
			statText = "Armor";
			break;
		case EquipmentSceneUI::Stats::Health:
			statText = "Health";
			break;
		default:
			break;
		}
		statTexts[i]->SetString(statText);
		if (i != count - 1)
			statTexts[i]->SetColor(Color::Blue);
		else
			statTexts[i]->SetColor(Color::Red);

		for (int j = 0; j < 10; j++)
		{
			RectangleObj* curRecObj;
			successCountRectangles[i][j] = new RectangleObj();
			curRecObj = successCountRectangles[i][j];
			curRecObj->SetSize(20.f, 20.f);
			curRecObj->SetPos(Vector2f(rectX, rectY));
			curRecObj->SetOrigin(Origins::MC);
			if (i != count - 1)
				curRecObj->SetOutline(Color::Blue, 3.5f);
			else
				curRecObj->SetOutline(Color::Red, 3.5f);
			curRecObj->SetRotate(45.f);
			uiObjList.push_back(curRecObj);
			rectX += 50.f;
		}
		buttons[i]->SetName(to_string(i));
		buttons[i]->SetOrigin(Origins::MC);
		buttons[i]->SetHitbox(FloatRect(0, 0, 120.f, 90.f), Origins::MC);
		buttons[i]->SetPos(Vector2f(rectX + 50.f, rectY - 20.f));

		uiObjList.push_back(statTexts[i]);
		uiObjList.push_back(buttons[i]);

		rectY += 120.f;
		if (i == count - 2)
			rectY += 45.f;
	}
	successCountText = new TextObj(*RESOURCE_MGR->GetFont("fonts/DNFBitBitTTF.ttf"), L"성공횟수        회",
		size.x * 0.13f, size.y * 0.86f, Color::White, 50.f);
	successRateText = new TextObj(*RESOURCE_MGR->GetFont("fonts/DNFBitBitTTF.ttf"), L"성공률       %",
		size.x * 0.42f, size.y * 0.86f, Color::White, 50.f);

	successCountNumber = new TextObj(*RESOURCE_MGR->GetFont("fonts/DNFBitBitTTF.ttf"), "0",
		size.x * 0.28f, size.y * 0.86f, Color::Yellow, 45.f);
	successRateNumber = new TextObj(*RESOURCE_MGR->GetFont("fonts/DNFBitBitTTF.ttf"), "75",
		size.x * 0.52f, size.y * 0.86f, Color::Yellow, 45.f);
	
	uiObjList.push_back(successCountText);
	uiObjList.push_back(successRateText);
	uiObjList.push_back(successCountNumber);
	uiObjList.push_back(successRateNumber);
	gamePlayButton = new SpriteObj();
	gamePlayButton->SetPos(Vector2f(size.x * 0.61f, size.y * 0.87f));
	gamePlayButton->SetScale(2.f, 1.f);
	gamePlayButton->SetTexture(*RESOURCE_MGR->GetTexture("graphics/UIBackground.png"));
	gamePlayButton->SetColor(Color(0xA0, 0xA0, 0xA0));
	
	gamePlayText = new TextObj(*RESOURCE_MGR->GetFont("fonts/DNFBitBitTTF.ttf"), L"게임 시작",
		size.x * 0.615f, size.y * 0.88f, Color::White, 20.f);

	uiObjList.push_back(gamePlayButton);
	uiObjList.push_back(gamePlayText);
}

void EquipmentSceneUI::Init()
{
	UIMgr::Init();
}

void EquipmentSceneUI::Release()
{
	UIMgr::Release();
}

void EquipmentSceneUI::Reset()
{
	UIMgr::Reset();
	for (int i = 0; i < count; i++)
	{
		idxCounts[i] = 0;
		for (int j = 0; j < 10; j++)
		{
			successCountRectangles[i][j]->SetFillColor(Color(0x04, 0x04, 0x04));
			
		}
	}
	successRate = 75;
	successCountTotal = 0;
	successRateNumber->SetString(to_string(successRate));
	successCountNumber->SetString(to_string(successCountTotal));

}

void EquipmentSceneUI::Update(float dt)
{
	UIMgr::Update(dt);
}

void EquipmentSceneUI::Draw(RenderWindow& window)
{
	UIMgr::Draw(window);
}