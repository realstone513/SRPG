#include "BattleScene.h"
#include "../SFML_Framework/Frameworks.h"
#include "../SFML_Framework/GameObject/SpriteObj.h"
#include "../SRPGObjects/Cat.h"
#include "../SRPGObjects/Fox.h"
#include "../SRPGObjects/Minotaurs.h"
#include "../SRPGObjects/Player.h"
#include "../SRPGObjects/Squirrel.h"
#include "../SRPGObjects/OverlayTile.h"

BattleScene::BattleScene()
	: Scene(Scenes::Battle), fullScreenView(false), size((Vector2f)FRAMEWORK->GetWindowSize()), unit(32.f)
{
	LOG::Print3String("scene[battle] create");
}

BattleScene::~BattleScene()
{
}

void BattleScene::Init()
{
	LOG::Print3String("scene[battle] init");
	int mapSizeR = 25;
	int mapSizeC = 50;
	CreateBackground(mapSizeR, mapSizeC, unit, unit);
	CreateOverlay(mapSizeR, mapSizeC, unit, unit);

	player = new Player();
	mino = new Minotaur();
	cat = new Cat();
	squirrel = new Squirrel();
	fox = new Fox();

	objList.push_back(player);
	objList.push_back(mino);
	objList.push_back(cat);
	objList.push_back(squirrel);
	objList.push_back(fox);

	for (auto& obj : objList)
	{
		obj->Init();
	}
	
	gamePieces.push_back(player);
	gamePieces.push_back(mino);
	gamePieces.push_back(cat);
	gamePieces.push_back(squirrel);
	gamePieces.push_back(fox);

	for (auto& obj : gamePieces)
	{
		obj->SetScale(2.f, 2.f);
	}

	// 실제 크기 비교용
	player->SetHitbox(FloatRect(0, 5, 32.f, 32.f), Origins::BC);
	mino->SetHitbox(FloatRect(0, 5, 64.f, 64.f), Origins::BC);
	cat->SetHitbox(FloatRect(0, 5, 32.f, 32.f), Origins::BC);
	fox->SetHitbox(FloatRect(0, 5, 32.f, 32.f), Origins::BC);
	squirrel->SetHitbox(FloatRect(0, 5, 32.f, 32.f), Origins::BC);

	// 데모용 배치
	player->SetPos(Vector2f(-14 * unit, 0 * unit));
	mino->SetPos(Vector2f(16 * unit, 0 * unit));
	cat->SetPos(Vector2f(-15 * unit, 1 * unit));
	fox->SetPos(Vector2f(4 * unit, 0 * unit));
	squirrel->SetPos(Vector2f(-6 * unit, 0 * unit));
}

void BattleScene::Release()
{
	LOG::Print3String("scene[battle] release");
}

void BattleScene::Enter()
{
	LOG::Print3String("scene[battle] enter");
	for (auto& obj : objList)
	{
		obj->Reset();
	}
	fullScreenView = false;

	if (fullScreenView)
		SetFullScreenWorldView();
	else
	{
		worldView.setSize(size * 0.5f);
		SetViewFocusOnObj(player);
	}

	//overlay[20][15]->SetFillColor(Color(255, 0, 0, 250));
}

void BattleScene::Exit()
{
	LOG::Print3String("scene[battle] exit");
	for (auto& obj : objList)
	{
		obj->SetActive(false);
	}
}

void BattleScene::Update(float dt)
{
	// Develop Input
	if (InputMgr::GetKeyDown(Keyboard::Key::F7))
	{
		fullScreenView = !fullScreenView;
		LOG::Print3String("scene[battle] fullScreenView switch", fullScreenView ? "ON" : "OFF");
		if (fullScreenView)
			SetFullScreenWorldView();
		else
		{
			SetViewFocusOnObj(player);
			worldView.setSize({ size.x / 4, size.y / 4 });
		}
		return;
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::F8))
	{
		LOG::Print3String("scene[battle] dev mode on");
		for (auto& obj : objList)
		{
			obj->SetDevMode(true);
		}
		return;
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::F9))
	{
		LOG::Print3String("scene[battle] dev mode off");
		for (auto& obj : objList)
		{
			obj->SetDevMode(false);
		}
		return;
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::F10))
	{
		LOG::Print3String("scene[battle] overlay switch on");
		for (auto& obj : objList)
		{
			if (!obj->GetType().compare("Overlay"))
				obj->SetActive(true);
		}
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::F11))
	{
		LOG::Print3String("scene[battle] overlay switch off");
		for (auto& obj : objList)
		{
			if (!obj->GetType().compare("Overlay"))
				obj->SetActive(false);
		}
	}
	if (InputMgr::GetMouseDown(Mouse::Left))
	{
		LOG::Print3String("scene[battle]");
		LOG::PrintVectorState(InputMgr::GetMousePos());
	}

	// Game Input
	if (InputMgr::GetKeyDown(Keyboard::Key::Escape))
		exit(0);
	if (InputMgr::GetKeyDown(Keyboard::Key::Space))
	{
		LOG::Print3String("scene[battle] reset key");
		SCENE_MGR->ChangeScene(Scenes::Battle);
		return;
	}
	
	Scene::Update(dt);

	if (!fullScreenView)
		SetViewFocusOnObj(player);
}

void BattleScene::Draw(RenderWindow& window)
{
	Scene::Draw(window);
}

void BattleScene::CreateBackground(int width, int height, float quadWidth, float quadHeight)
{
	if (background == nullptr)
	{
		background = new VertexArrayObj();
		background->SetTexture(GetTexture("graphics/ForestTileSet.png"));
	}

	background->SetPos(Vector2f(-unit * (height % 2 ? height : height + 1) * 0.5f, -unit * (width % 2 ? width + 1 : width) * 0.5f));

	Vector2f startPos = background->GetPos();
	VertexArray& va = background->GetVA();
	va.clear();
	va.setPrimitiveType(Quads);
	va.resize(width * height * 4);
	Vector2f currPos = startPos;

	Vector2f offsets[4] = {
		{0, 0},
		{quadWidth, 0},
		{quadWidth, quadHeight},
		{0, quadHeight},
	};

	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			// 지형 선택
			int texIndexX = (i + j) % 2 ? 1 : 4;
			int texIndexY = 1;
			if ((i == 0 || i == width - 1) || (j == 0 || j == height - 1))
			{
				texIndexX = 4;
				texIndexY = 4;
			}

			// 채우기
			int quadIndex = i * height + j;
			for (int k = 0; k < 4; ++k)
			{
				int vertexIndex = quadIndex * 4 + k;
				va[vertexIndex].position = currPos + offsets[k];
				va[vertexIndex].texCoords = offsets[k];
				va[vertexIndex].texCoords.x += quadWidth * texIndexX;
				va[vertexIndex].texCoords.y += quadHeight * texIndexY;
			}
			currPos.x += quadWidth;
		}
		currPos.x = startPos.x;
		currPos.y += quadHeight;
	}
}

void BattleScene::CreateOverlay(int width, int height, float quadWidth, float quadHeight)
{
	// overlay Init
	overlay.resize(height);
	for (int i = 0; i < height; i++)
		overlay[i].resize(width);

	int cStart = -unit * (width % 2 ? width + 1 : width) * 0.5f;
	int r = -unit * (height % 2 ? height : height + 1) * 0.5f;
	for (auto& tiles : overlay)
	{
		int c = cStart;
		for (auto& tile : tiles)
		{
			tile = new OverlayTile();
			objList.push_back(tile);
			tile->SetPos(Vector2f(r, c));
			c += unit;
		}
		r += unit;
	}
}

void BattleScene::SetFullScreenWorldView()
{
	worldView.setSize(size);
	worldView.setCenter(Vector2f());
}

void BattleScene::SetViewFocusOnObj(SpriteObj* obj)
{
	worldView.setCenter({ obj->GetPos().x, obj->GetPos().y - obj->GetSize().y * 0.5f });
}