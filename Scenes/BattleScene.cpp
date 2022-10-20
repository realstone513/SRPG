#include "BattleScene.h"
#include "../SFML_Framework/Frameworks.h"
#include "../SRPGObjects/Player.h"
#include "../SRPGObjects/Minotaurs.h"

BattleScene::BattleScene()
	: Scene(Scenes::Battle)
{
	LOG::Print3String("scene[battle] create");

	CreateBackground(30, 31, 32.f, 32.f);

	player = new Player();
	mino = new Minotaurs();

	objList.push_back(player);
	objList.push_back(mino);
}

BattleScene::~BattleScene()
{
}

void BattleScene::Init()
{
	LOG::Print3String("scene[battle] init");

	for (auto obj : objList)
	{
		obj->Init();
	}
}

void BattleScene::Release()
{
}

void BattleScene::Enter()
{
	LOG::Print3String("scene[battle] enter");
}

void BattleScene::Exit()
{
	LOG::Print3String("scene[battle] exit");
}

void BattleScene::Update(float dt)
{
	if (InputMgr::GetKeyDown(Keyboard::Key::F1))
	{
		LOG::Print3String("scene[battle]");
		return;
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::Escape))
		exit(0);

	Scene::Update(dt);
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
			int texIndex = Utils::RandomRange(0, 6);
			if ((i == 0 || i == width - 1) || (j == 0 || j == height - 1))
			{
				texIndex = 6;
			}
			int quadIndex = i * height + j;
			for (int k = 0; k < 4; ++k)
			{
				int vertexIndex = quadIndex * 4 + k;
				va[vertexIndex].position = currPos + offsets[k];
				va[vertexIndex].texCoords = offsets[k];
				va[vertexIndex].texCoords.y += quadHeight * texIndex;
			}
			currPos.x += quadWidth;
		}
		currPos.x = startPos.x;
		currPos.y += quadHeight;
	}
}