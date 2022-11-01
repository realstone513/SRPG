#include "TitleScene.h"
#include "../SFML_Framework/Frameworks.h"
#include "../SFML_Framework/GameObject/SpriteObj.h"

TitleScene::TitleScene()
	: Scene(Scenes::Title)
{
	CLOG::Print3String("scene[Title] create");
}

void TitleScene::Init()
{
	CLOG::Print3String("scene[Title] init");
	titleBackground = new SpriteObj();
	titleBackground->SetTexture(*RESOURCE_MGR->GetTexture("graphics/TitleBackground.png"));
	objList.push_back(titleBackground);
	titleBackground->SetOrigin(Origins::TL);

	for (Object*& obj : objList)
	{
		obj->Init();
	}
	SOUND_MGR->SetVolume(50.f);
}

void TitleScene::Release()
{
	CLOG::Print3String("scene[title] release");
}

void TitleScene::Enter()
{
	CLOG::Print3String("scene[Title] enter");
	for (Object*& obj : objList)
	{
		obj->Reset();
	}
	SOUND_MGR->StopAll();
	SOUND_MGR->Play("sound/title_bgm.wav", 50.f, true);
}

void TitleScene::Exit()
{
	CLOG::Print3String("scene[Title] exit");
	for (Object*& obj : objList)
	{
		obj->SetActive(false);
	}
}

void TitleScene::Update(float dt)
{
	Scene::Update(dt);
	// Game Input
	if (InputMgr::GetKeyDown(Keyboard::Key::Escape))
		exit(0);
	if (InputMgr::GetKeyDown(Keyboard::Key::Space))
	{
		CLOG::Print3String("scene[Title] change scene key");
		SCENE_MGR->ChangeScene(Scenes::Equipment);
		return;
	}
}

void TitleScene::Draw(RenderWindow& window)
{
	Scene::Draw(window);
}