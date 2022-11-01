#include "EquipmentScene.h"
#include "../SFML_Framework/Frameworks.h"
#include "../SFML_Framework/GameObject/SpriteObj.h"
#include "../SFML_Framework/GameObject/TextObj.h"
#include "../SFML_Framework/GameObject/RectangleObj.h"
#include "../GameSystem/GameMgr.h"

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
	UIMgr = new EquipmentSceneUI(this);
	UIMgr->Init();
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
	UIMgr->Reset();
}

void EquipmentScene::Exit()
{
	CLOG::Print3String("scene[Equipment] exit");
	SOUND_MGR->StopAll();
}

void EquipmentScene::Update(float dt)
{
	Scene::Update(dt);

	for (SpriteObj*& button : UIMgr->buttons)
	{
		if (button->GetHitbox().getGlobalBounds().contains(ScreenToUiPos(Vector2i(InputMgr::GetMousePos()))))
		{
			if (InputMgr::GetMouseDown(Mouse::Left))
			{
				int idx = stoi(button->GetName());
				if (UIMgr->idxCounts[idx] >= 10)
					return;

				SOUND_MGR->Play("sound/hitmarker.wav", 50.f);
				int ranVal = Utils::RandomRange(1, 100);
				bool success = ranVal <= UIMgr->successRate;
				if (success)
				{
					if (UIMgr->successRate > 25)
						UIMgr->successRate -= 10;
					if (idx != 2)
					{
						UIMgr->successCountTotal++;
						UIMgr->successCountRectangles[idx][UIMgr->idxCounts[idx]]->
							SetFillColor(Color::Blue);
					}
					else
						UIMgr->successCountRectangles[idx][UIMgr->idxCounts[idx]]->
						SetFillColor(Color::Red);
				}
				else
				{
					if (UIMgr->successRate < 75)
						UIMgr->successRate += 10;
					UIMgr->successCountRectangles[idx][UIMgr->idxCounts[idx]]->
						SetFillColor(Color::White);
				}

				UIMgr->successRateNumber->SetString(to_string(UIMgr->successRate));
				UIMgr->successCountNumber->SetString(to_string(UIMgr->successCountTotal));
				UIMgr->idxCounts[idx]++;
			}
		}
	}

	if (UIMgr->gamePlayButton->GetGlobalBounds().contains(ScreenToUiPos(Vector2i(InputMgr::GetMousePos()))))
	{
		UIMgr->gamePlayButton->SetColor(Color::Red);

		if (InputMgr::GetMouseDown(Mouse::Left))
		{
			GAMEMGR;
			SCENE_MGR->ChangeScene(Scenes::Battle);
			return;
		}
	}
	else
	{
		UIMgr->gamePlayButton->SetColor(Color(0xA0, 0xA0, 0xA0));
	}

	// Game Input
	if (InputMgr::GetKeyDown(Keyboard::Key::Escape))
	{
		SCENE_MGR->ChangeScene(Scenes::Title);
		return;
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::Space))
	{
		CLOG::Print3String("scene[Title] change scene key");
		SCENE_MGR->ChangeScene(Scenes::Battle);
		return;
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
}

void EquipmentScene::Draw(RenderWindow& window)
{
	Scene::Draw(window);

	window.setView(uiView);
	UIMgr->Draw(window);
}
