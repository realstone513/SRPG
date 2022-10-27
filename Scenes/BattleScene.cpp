#include "BattleScene.h"
#include "../SFML_Framework/Frameworks.h"
#include "../SRPGObjects/Camera.h"
#include "../SRPGObjects/Cat.h"
#include "../SRPGObjects/Fox.h"
#include "../SRPGObjects/Minotaurs.h"
#include "../SRPGObjects/OverlayTile.h"
#include "../SRPGObjects/Piece.h"
#include "../SRPGObjects/Player.h"
#include "../SRPGObjects/Squirrel.h"
#include "../GameSystem/GameMgr.h"

BattleScene::BattleScene()
	: MapControl(overlay, 32.f), Scene(Scenes::Battle),
	fsv(false), window(FRAMEWORK->GetWindow()),
	size((Vector2f)FRAMEWORK->GetWindowSize()), curPhase(Phase::Wait)
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
	GAMEMGR->SetMapInfo(width, height);

	camera = new Camera(PieceTypes::None);
	camera->SetLimit(abs(lt.x) + abs(rb.x), abs(lt.y) + abs(rb.y));

	// playable
	player = new Player(PieceTypes::Playable);
	cat = new Cat(PieceTypes::Playable);

	// ai
	mino = new Minotaur(PieceTypes::AI);
	squirrel = new Squirrel(PieceTypes::AI);
	fox = new Fox(PieceTypes::AI);

	objList.push_back(camera);
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

	UIMgr = new BattleSceneUI(this);
	UIMgr->Init();
}

void BattleScene::Release()
{
	CLOG::Print3String("scene[battle] release");
	UIMgr->Release();
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

	// 데모용 배치
	SetPiecePos(player, { 10, 10 });
	SetPiecePos(cat, { 9, 11 });
	SetPiecePos(squirrel, { 20, 10 });
	SetPiecePos(fox, { 30, 10 });
	SetPiecePos(mino, { 40, 10 });

	GAMEMGR->SetList(&gamePieces);
	GAMEMGR->SetUIMgr(UIMgr);
	// player 턴으로 시작
	GAMEMGR->SetPlayerTurn(true);
	viewTarget = camera;
	camera->SetPos(player->GetPos() + Vector2f(0, 16.f));
	UIMgr->Reset();
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
	if (UIMgr->commandUIActive)
	{
		for (SpriteObj*& button : UIMgr->buttons)
		{
			if (button->GetGlobalBounds().contains(ScreenToUiPos(Vector2i(InputMgr::GetMousePos()))))
			{
				button->SetColor(Color::Red);
				CLOG::Print3String("touch");
			}
			else
				button->SetColor(UIMgr->uiBaseColor);
		}
	}

	// Develop Input
	{
		// F7 F8 : hitbox on/off
		// F9 : fullscreen <-> viewTarget
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
				SetViewFocusOnObj(camera);
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
				{
					if ((int)tile->GetTileType() == (int)TileType::Inactive)
						tile->SetActive(false);
				}
			}
		}
	}

	// turn cheat
	{
		if (InputMgr::GetKeyDown(Keyboard::Key::P))
		{
			CLOG::Print3String("scene[battle] player turn");
			GAMEMGR->SetPlayerTurn(true);
			for (auto& piece : gamePieces)
			{
				CLOG::Print3String(piece->GetName(), piece->GetIsTurn() ? "my turn" : "X");
			}
		}
		if (InputMgr::GetKeyDown(Keyboard::Key::O))
		{
			CLOG::Print3String("scene[battle] AI turn");
			GAMEMGR->SetPlayerTurn(false);
			for (auto& piece : gamePieces)
			{
				CLOG::Print3String(piece->GetName(), piece->GetIsTurn() ? "my turn" : "X");
			}
		}
		if (InputMgr::GetKeyDown(Keyboard::Key::U))
		{
			CLOG::Print3String("scene[battle] Done clear");
			for (auto& piece : gamePieces)
			{
				piece->SetDone(false);
			}
		}
		if (InputMgr::GetKeyDown(Keyboard::Key::Y))
		{
			CLOG::Print3String("scene[battle] power overwhelming");

			player->maxHealth = 500;
			player->health = 500;
			player->damage = 1500;
			player->armor = 500;
			player->mobility = 9;
			player->range = 3;

			cat->health = 500;
			cat->damage = 150;
			cat->range = 4;

			mino->damage = 150;
			mino->mobility = 10;
		}
		if (InputMgr::GetKeyDown(Keyboard::Key::Num1))
		{
			CLOG::Print3String("focus on", "player");
			viewTarget = player;
		}
		if (InputMgr::GetKeyDown(Keyboard::Key::Num2))
		{
			CLOG::Print3String("focus on", "cat");
			viewTarget = cat;
		}
		if (InputMgr::GetKeyDown(Keyboard::Key::Num3))
		{
			CLOG::Print3String("focus on", "squ");
			viewTarget = squirrel;
		}
		if (InputMgr::GetKeyDown(Keyboard::Key::Num4))
		{
			CLOG::Print3String("focus on", "fox");
			viewTarget = fox;
		}
		if (InputMgr::GetKeyDown(Keyboard::Key::Num5))
		{
			CLOG::Print3String("focus on", "mino");
			viewTarget = mino;
		}
		if (InputMgr::GetKeyDown(Keyboard::Key::Num6))
		{
			CLOG::Print3String("focus on", "camera");
			viewTarget = camera;
		}
	}

	Scene::Update(dt);
	UIMgr->Update(dt);
	GAMEMGR->Update(dt);
	if (!fsv)
		SetViewFocusOnObj(viewTarget);

	// Game Input
	if (InputMgr::GetKeyDown(Keyboard::Key::Escape))
		exit(0);
	if (InputMgr::GetKeyDown(Keyboard::Key::Space))
	{
		CLOG::Print3String("scene[battle] reset key");
		SCENE_MGR->ChangeScene(Scenes::Battle);
		return;
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::C))
	{
		CLOG::Print3String("scene[battle] overlay tile view");
		for (auto& tiles : overlay)
		{
			for (auto& tile : tiles)
				tile->SetActive(true);
		}
	}
	if (InputMgr::GetKeyUp(Keyboard::Key::C))
	{
		CLOG::Print3String("scene[battle] overlay tile view off");
		for (auto& tiles : overlay)
		{
			for (auto& tile : tiles)
			{
				if ((int)tile->GetTileType() == (int)TileType::Inactive)
					tile->SetActive(false);
			}
		}
	}
	if (InputMgr::GetKeyUp(Keyboard::Key::Z))
	{
		CLOG::Print3String("scene[battle] AI Action");

		Vector2i dest(15, 10);
		mino->SetDest(IdxToPos(dest));
		mino->SetAnimDir(mino->GetIdxPos().x < 15);
		mino->SetState(States::Move);
		mino->SetIdxPos(dest);

		dest = { 15, 12 };
		fox->SetDest(IdxToPos(dest));
		fox->SetAnimDir(fox->GetIdxPos().x < 15);
		fox->SetState(States::Move);
		fox->SetIdxPos(dest);

		dest = { 15, 14 };
		squirrel->SetDest(IdxToPos(dest));
		squirrel->SetAnimDir(squirrel->GetIdxPos().x < 15);
		squirrel->SetState(States::Move);
		squirrel->SetIdxPos(dest);

		AIAction();
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
						viewTarget = focus;
						camera->SetPos(focus->GetPos() + Vector2f(0, -16.f));

						if (!focus->GetType().compare("Playable"))
						{
							UIMgr->SetPlayableInfo(focus);
							UIMgr->SetUIActive("PlayableInfoUI", true);
						}
						else
						{
							UIMgr->SetAIInfo(focus);
							UIMgr->SetUIActive("AIInfoUI", true);
						}
						if (focus->GetDone())
						{
							CLOG::Print3String(piece->GetName(), "is done");
							break;
						}
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
						if (focus->GetIsTurn())
							curPhase = Phase::Action;
						else
							CLOG::Print3String(focus->GetName(), "Not my turn!");
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

					if ((target != nullptr) && (int)tile->GetTileType() == (int)TileType::AttackRange)
					{
						// attack
						if (!target->GetType().compare(focus->GetType()))
						{
							CLOG::Print3String("Can't attack");
							break;
						}
						CLOG::Print3String("Attack1! ", target->GetName());
						GAMEMGR->DamageToPiece(focus, target);
						UIMgr->SetDamageText(WorldToUI(target->GetPos()), GAMEMGR->CalculateDamage(focus, target));

						curPhase = Phase::Wait;
						SetOverlayInactive();
						focus->SetDone(true);
						camera->SetPos(focus->GetPos() + Vector2f(0, -16.f));
						viewTarget = camera;
						focus = nullptr;
						UIMgr->SetUIActive("PlayableInfoUI", false);
						UIMgr->SetUIActive("AIInfoUI", false);
						UIMgr->SetUIActive("CommandWindow", false);
						UIMgr->commandUIActive = false;
					}
					// move
					else if ((int)tile->GetTileType() != (int)TileType::Immovable)
					{
						CLOG::Print3String("Move!");
						// move
						Vector2f destination = tile->GetTilePos();
						focus->SetDest(destination);
						focus->SetAnimDir(focus->GetPos().x < destination.x);
						focus->SetState(States::Move);

						Vector2i curIdx = PosToIdx(destination);
						UIMgr->SetUIActive("CommandWindow", true);
						UIMgr->SetCommandWindow(WorldToUI(focus->GetPos()));
						UIMgr->commandUIActive = true;
						focus->SetIdxPos(curIdx);
						SetOverlayInactive();
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
			// click tile
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
						if (!target->GetType().compare(focus->GetType()))
						{
							CLOG::Print3String("Can't attack");
							break;
						}
						CLOG::Print3String("Attack2! ", target->GetName());
						GAMEMGR->DamageToPiece(focus, target);
						UIMgr->SetDamageText(WorldToUI(target->GetPos()), GAMEMGR->CalculateDamage(focus, target));
					}
					curPhase = Phase::Wait;
					SetOverlayInactive();
					focus->SetDone(true);
					camera->SetPos(focus->GetPos() + Vector2f(0, -16.f));
					viewTarget = camera;
					focus = nullptr;
					UIMgr->SetUIActive("PlayableInfoUI", false);
					UIMgr->SetUIActive("AIInfoUI", false);
					UIMgr->SetUIActive("CommandWindow", false);
					UIMgr->commandUIActive = false;
					break;
				}
			}
			// click another(ground)
			break;
		}

		if (hitGround)
		{
			if (curPhase == Phase::ActionAfterMove)
			{
				focus->SetPos(IdxToPos(focus->GetBeforeIdx()));
				focus->SetIdxPos(focus->GetBeforeIdx());
			}
			curPhase = Phase::Wait;
			SetOverlayInactive();
			viewTarget = camera;
			focus = nullptr;
			UIMgr->SetUIActive("PlayableInfoUI", false);
			UIMgr->SetUIActive("AIInfoUI", false);
			UIMgr->SetUIActive("CommandWindow", false);
			UIMgr->commandUIActive = false;
		}
	}

	if (InputMgr::GetMouseDown(Mouse::Right))
	{
		// 땅 클릭과 같은 효과. 취소 (or 돌아가기)
		if (curPhase == Phase::ActionAfterMove)
			focus->SetDone(true);
		curPhase = Phase::Wait;
		SetOverlayInactive();
		camera->SetPos(focus->GetPos());
		viewTarget = camera;
		focus = nullptr;
	}
}

void BattleScene::Draw(RenderWindow& window)
{
	Scene::Draw(window);

	window.setView(uiView);
	UIMgr->Draw(window);
}

void BattleScene::CreateBackground(int width, int height, float quadWidth, float quadHeight)
{
	if (background == nullptr)
	{
		background = new VertexArrayObj();
		background->SetTexture(GetTexture("graphics/DungeonTileSet.png"));
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
			int texIndexX = Utils::RandomRange(0, 13);//4;
			int texIndexY = Utils::RandomRange(0, 2);//1;

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

Vector2f BattleScene::WorldToUI(Vector2f world)
{
	Vector2i screen = window.mapCoordsToPixel(world, worldView);
	return window.mapPixelToCoords(screen, uiView);
}

// 가장 가까운 playable 캐릭터를 향해 이동
void BattleScene::AIAction()
{
	for (Piece*& ai : GAMEMGR->aiPieces)
	{
		viewTarget = ai;
		Vector2i dist(width, height);

		Piece* target = nullptr;
		for (Piece*& playable : GAMEMGR->playerPieces)
		{
			Vector2i tmp = playable->GetIdxPos() - ai->GetIdxPos();
			if (Utils::SqrMagnitude(dist) > Utils::SqrMagnitude(tmp))
			{
				dist = tmp;
				target = playable;
			}
		}

		if (target != nullptr)
			CLOG::Print3String(ai->GetName(), target->GetName(), "distance");
		CLOG::PrintVectorState(dist);
	}
	//viewTarget = camera;
}