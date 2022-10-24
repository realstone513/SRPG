#include "BattleScene.h"
#include "../SFML_Framework/Frameworks.h"
#include "../SRPGObjects/Cat.h"
#include "../SRPGObjects/Fox.h"
#include "../SRPGObjects/Minotaurs.h"
#include "../SRPGObjects/OverlayTile.h"
#include "../SRPGObjects/Piece.h"
#include "../SRPGObjects/Player.h"
#include "../SRPGObjects/Squirrel.h"

BattleScene::BattleScene()
	: MapControl(overlay, 32.f), Scene(Scenes::Battle),
	fsv(false), size((Vector2f)FRAMEWORK->GetWindowSize()),
	curPhase(Phase::Wait)
{
	CLOG::Print3String("scene[battle] create");
}

void BattleScene::Init()
{
	CLOG::Print3String("scene[battle] init");
	int mapSizeR = 25;
	int mapSizeC = 50;
	CreateBackground(mapSizeR, mapSizeC, unit, unit);
	CreateOverlay(mapSizeR, mapSizeC, unit, unit);
	SetLTRB(overlay[0][0]->GetPos(), overlay[mapSizeC - 1][mapSizeR - 1]->GetPos());

	// playable
	player = new Player(PieceTypes::Playable);
	cat = new Cat(PieceTypes::Playable);

	// ai
	mino = new Minotaur(PieceTypes::AI);
	squirrel = new Squirrel(PieceTypes::AI);
	fox = new Fox(PieceTypes::AI);

	objList.push_back(player);
	objList.push_back(mino);
	objList.push_back(cat);
	objList.push_back(squirrel);
	objList.push_back(fox);

	for (Object*& obj : objList)
	{
		obj->Init();
	}

	gamePieces.push_back(player);
	gamePieces.push_back(mino);
	gamePieces.push_back(cat);
	gamePieces.push_back(squirrel);
	gamePieces.push_back(fox);

	for (Piece*& piece : gamePieces)
	{
		piece->SetScale(2.f, 2.f);
	}

	player->SetHitbox(FloatRect(0, 5, unit, unit), Origins::BC);
	mino->SetHitbox(FloatRect(0, 5, unit * 2, unit * 2), Origins::BC);
	cat->SetHitbox(FloatRect(0, 5, unit, unit), Origins::BC);
	fox->SetHitbox(FloatRect(0, 5, unit, unit), Origins::BC);
	squirrel->SetHitbox(FloatRect(0, 5, unit, unit), Origins::BC);

	// 데모용 배치
	SetPiecePos(player, { 10, 10 });
	SetPiecePos(cat, { 9, 11 });
	SetPiecePos(squirrel, { 20, 10 });
	SetPiecePos(fox, { 30, 10 });
	SetPiecePos(mino, { 40, 10 });
}

void BattleScene::Release()
{
	CLOG::Print3String("scene[battle] release");
}

void BattleScene::Enter()
{
	CLOG::Print3String("scene[battle] enter");
	for (Object*& obj : objList)
	{
		obj->Reset();
	}
	fsv = false;

	if (fsv)
		SetFullScreenWorldView();
	else
	{
		worldView.setSize(size * 0.5f);
		SetViewFocusOnObj(player);
	}
}

void BattleScene::Exit()
{
	CLOG::Print3String("scene[battle] exit");
	for (Object*& obj : objList)
	{
		obj->SetActive(false);
	}
}

void BattleScene::Update(float dt)
{
	// Develop Input
	// F7 F8 : hitbox on/off
	// F9 : fullscreen <-> focus
	// F10 F11 : overlay on/off
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
	if (InputMgr::GetKeyDown(Keyboard::Key::F9))
	{
		fsv = !fsv;
		CLOG::Print3String("scene[battle] fullScreenView switch", fsv ? "ON" : "OFF");
		if (fsv)
			SetFullScreenWorldView();
		else
		{
			SetViewFocusOnObj(player);
			worldView.setSize({ size.x / 2, size.y / 2 });
		}
		return;
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::F10))
	{
		CLOG::Print3String("scene[battle] overlay switch on");
		for (auto& tiles : overlay)
		{
			for (auto& tile : tiles)
				tile->SetActive(true);
		}
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::F11))
	{
		CLOG::Print3String("scene[battle] overlay switch off");
		for (auto& tiles : overlay)
		{
			for (auto& tile : tiles)
				tile->SetActive(false);
		}
	}

	// Game Input
	if (InputMgr::GetKeyDown(Keyboard::Key::Escape))
		exit(0);
	if (InputMgr::GetKeyDown(Keyboard::Key::Space))
	{
		CLOG::Print3String("scene[battle] reset key");
		SCENE_MGR->ChangeScene(Scenes::Battle);
		return;
	}
	if (InputMgr::GetMouseDown(Mouse::Left))
	{
		Vector2f worldPos = ScreenToWorldPos(Vector2i(InputMgr::GetMousePos()));
		bool hitGround = true;
		switch (curPhase)
		{
		case BattleScene::Phase::Wait:
			for (auto& piece : gamePieces)
			{
				if (piece->GetHitbox().getGlobalBounds().contains(worldPos))
				{
					Vector2i curIdx = PosToIdx(piece->GetPos());

					if (!focus || focus != piece)
					{
						if (focus)
							SetOverlayInactive();

						focus = piece;
						if (!FRAMEWORK->devMode)
							SetMoveable(curIdx, focus->mobility);
						else
						{
							algorithmCount = 0;
							SetMoveable(curIdx, focus->mobility);
							CLOG::Print3String("count :", to_string(algorithmCount));
						}
						SetAttackRange(curIdx, focus->range, focus->rangeFill);
						SetImmovable(curIdx);
						hitGround = false;
						curPhase = Phase::Action;
						return;
					}
				}
			}
			break;
		case BattleScene::Phase::Action:
			for (auto& tile : activeTiles)
			{
				if (tile->GetGlobalBounds().contains(worldPos))
				{
					hitGround = false;
					Vector2i tileIdx = PosToIdx(tile->GetTilePos());
					Piece* target = nullptr;

					for (auto& piece : gamePieces)
					{
						if (piece->GetIdxPos() == tileIdx && (int)tile->GetTileType() == (int)TileType::AttackRange)
						{
							target = piece;
							break;
						}
					}

					// attack
					if ((target != nullptr) && (int)tile->GetTileType() == (int)TileType::AttackRange)
					{
						CLOG::Print3String("Attack1! ", target->GetName());
						curPhase = Phase::Wait;
						SetOverlayInactive();
						focus = nullptr;
					}
					// move
					else if ((int)tile->GetTileType() != (int)TileType::Immovable)
					{
						CLOG::Print3String("Move!");
						SetPiecePos(focus, PosToIdx(tile->GetTilePos()));
						SetOverlayInactive();
						Vector2i curIdx = PosToIdx(focus->GetPos());
						SetAttackRange(curIdx, focus->range, focus->rangeFill);
						SetImmovable(curIdx);
						curPhase = Phase::ActionAfterMove;
					}
					// Click Immovable cell
					else
						CLOG::Print3String("Can't move!");
					return;
				}
			}
			break;
		case BattleScene::Phase::ActionAfterMove:
			// attack or end
			for (auto& tile : activeTiles)
			{
				if (tile->GetGlobalBounds().contains(worldPos))
				{
					hitGround = false;
					Vector2i tileIdx = PosToIdx(tile->GetTilePos());
					Piece* target = nullptr;

					for (auto& piece : gamePieces)
					{
						if (piece->GetIdxPos() == tileIdx && (int)tile->GetTileType() == (int)TileType::AttackRange)
						{
							target = piece;
							break;
						}
					}

					if (target != nullptr && (int)tile->GetTileType() == (int)TileType::AttackRange)
					{
						// attack
						CLOG::Print3String("Attack2! ", target->GetName());
						SetOverlayInactive();
						focus = nullptr;
						curPhase = Phase::Wait;
					}
					break;
				}
			}
			break;
		}

		if (hitGround)
		{
			SetOverlayInactive();
			focus = nullptr;
			curPhase = Phase::Wait;
		}
	}

	Scene::Update(dt);

	if (!fsv)
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

	background->SetPos(Vector2f(-quadHeight * (height % 2 ? height : height - 1) * 0.5f, -quadWidth * (width % 2 ? width - 1 : width) * 0.5f));

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
			/*int texIndexX = (i + j) % 2 ? 1 : 4;
			int texIndexY = 1;
			if ((i == 0 || i == width - 1) || (j == 0 || j == height - 1))
			{
				texIndexX = 4;
				texIndexY = 4;
			}*/
			int texIndexX = 4;
			int texIndexY = 1;

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

	int cStart = -quadWidth * (width % 2 ? width - 1 : width) * 0.5f;
	int r = -quadHeight * (height % 2 ? height : height - 1) * 0.5f;
	for (auto& tiles : overlay)
	{
		int c = cStart;
		for (auto& tile : tiles)
		{
			tile = new OverlayTile();
			objList.push_back(tile);
			tile->SetPos(Vector2f(r, c));
			c += quadWidth;
		}
		r += quadHeight;
	}
}

void BattleScene::SetFullScreenWorldView()
{
	worldView.setSize(size);
	worldView.setCenter(Vector2f());
}

void BattleScene::SetViewFocusOnObj(Piece* obj)
{
	worldView.setCenter({ obj->GetPos().x, obj->GetPos().y - obj->GetSize().y * 0.5f });
}