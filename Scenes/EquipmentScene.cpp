#include "EquipmentScene.h"
#include "../SFML_Framework/Frameworks.h"
#include "../SFML_Framework/GameObject/SpriteObj.h"
#include "../SFML_Framework/GameObject/TextObj.h"
#include "../SFML_Framework/GameObject/RectangleObj.h"
#include "../GameSystem/GameMgr.h"
#include "../GameSystem/AbilityStone.h"

EquipmentScene::EquipmentScene()
	: Scene(Scenes::Equipment)
{
	CLOG::Print3String("scene[Equipment] create");
}

void EquipmentScene::Init()
{
	CLOG::Print3String("scene[Equipment] init");
	equipBackground = new SpriteObj();
	equipBackground->SetTexture(*RESOURCE_MGR->GetTexture("graphics/upgrade.png"));
	objList.push_back(equipBackground);

	for (Object*& obj : objList)
	{
		obj->Init();
	}
	equipUIMgr = new EquipmentSceneUI(this);
	equipUIMgr->Init();
}

void EquipmentScene::Release()
{
	CLOG::Print3String("scene[Equipment] release");
}

void EquipmentScene::Enter()
{
	CLOG::Print3String("scene[Equipment] enter");
	for (Object*& obj : objList)
	{
		obj->Reset();
	}
	equipUIMgr->Reset();
}

void EquipmentScene::Exit()
{
	CLOG::Print3String("scene[Equipment] exit");
	SOUND_MGR->StopAll();
}

void EquipmentScene::Update(float dt)
{
	Scene::Update(dt);

	// Game Input
	if (InputMgr::GetKeyDown(Keyboard::Key::Escape))
	{
		SCENE_MGR->ChangeScene(Scenes::Title);
		return;
	}

	for (SpriteObj*& button : equipUIMgr->buttons)
	{
		if (button->GetHitbox().getGlobalBounds().contains(ScreenToUiPos(Vector2i(InputMgr::GetMousePos()))))
		{
			if (InputMgr::GetMouseDown(Mouse::Left))
			{
				int idx = stoi(button->GetName());
				if (equipUIMgr->idxCounts[idx] >= 10)
					return;

				SOUND_MGR->Play("sound/hitmarker.wav", 50.f);
				int ranVal = Utils::RandomRange(1, 100);
				bool success = ranVal <= equipUIMgr->successRate;
				if (success)
				{
					if (equipUIMgr->successRate > 25)
						equipUIMgr->successRate -= 10;
					if (idx != 2)
					{
						equipUIMgr->successCountTotal++;
						equipUIMgr->successCountRectangles[idx][equipUIMgr->idxCounts[idx]]->
							SetFillColor(Color::Blue);
					}
					else
					{
						equipUIMgr->successCountRectangles[idx][equipUIMgr->idxCounts[idx]]->
							SetFillColor(Color::Red);
					}
					equipUIMgr->stone->successCounts[idx]++;
				}
				else
				{
					if (equipUIMgr->successRate < 75)
						equipUIMgr->successRate += 10;
					equipUIMgr->successCountRectangles[idx][equipUIMgr->idxCounts[idx]]->
						SetFillColor(Color::White);
				}

				equipUIMgr->successRateNumber->SetString(to_string(equipUIMgr->successRate));
				equipUIMgr->successCountNumber->SetString(to_string(equipUIMgr->successCountTotal));
				equipUIMgr->idxCounts[idx]++;
			}
		}
	}

	if (equipUIMgr->gamePlayButton->GetGlobalBounds().contains(ScreenToUiPos(Vector2i(InputMgr::GetMousePos()))))
	{
		bool condition = true;
		for (int i = 0; i < equipUIMgr->stone->count; i++)
		{
			if (equipUIMgr->idxCounts[i] != 10)
			{
				condition = false;
				return;
			}
		}
		equipUIMgr->gamePlayButton->SetColor(Color::Red);

		if (condition && InputMgr::GetMouseDown(Mouse::Left))
		{
			GAMEMGR->ApplyEquipmentSetting(equipUIMgr->stone);
			SCENE_MGR->ChangeScene(Scenes::Battle);
			return;
		}
	}
	else
	{
		equipUIMgr->gamePlayButton->SetColor(Color(0xA0, 0xA0, 0xA0));
	}

	// Develop Input
	if (InputMgr::GetKeyDown(Keyboard::Key::F7))
	{
		CLOG::Print3String("scene[battle] dev mode on");
		FRAMEWORK->devMode = true;
		return;
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::F8))
	{
		CLOG::Print3String("scene[battle] dev mode off");
		FRAMEWORK->devMode = false;
		return;
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::P))
	{
		CLOG::Print3String("scene[Title] change scene key");
		GAMEMGR->ApplyEquipmentSetting(equipUIMgr->stone);
		SCENE_MGR->ChangeScene(Scenes::Battle);
		return;
	}
}

void EquipmentScene::Draw(RenderWindow& window)
{
	Scene::Draw(window);

	window.setView(uiView);
	equipUIMgr->Draw(window);
}
