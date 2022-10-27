#include "BattleSceneUI.h"
#include "../SFML_Framework/Frameworks.h"
#include "../SFML_Framework/GameObject/SpriteObj.h"
#include "../SFML_Framework/GameObject/TextObj.h"
#include "../SFML_Framework/GameObject/RectangleObj.h"
#include "../SFML_Framework/GameObject/FloatingObj.h"
#include "../SRPGObjects/Piece.h"

BattleSceneUI::BattleSceneUI(Scene* scene)
	: UIMgr(scene), commandUIActive(false)
{
	uiBaseColor = Color(0xb3, 0x92, 0x83, 255.f);

	// playable character UI start
	Vector2f leftBase(0.f, 0.f);
	leftUIBackground = new SpriteObj();
	leftThumbnailBackground = new SpriteObj();
	leftThumbnail = new SpriteObj();
	leftDamageIcon = new SpriteObj();
	leftArmorIcon = new SpriteObj();
	leftRangeIcon = new SpriteObj();
	leftMobilityIcon = new SpriteObj();
	leftHealthBarBackground = new RectangleObj();
	leftHealthBar = new RectangleObj();

	leftNameText = new TextObj(*RESOURCE_MGR->GetFont("fonts/DNFBitBitTTF.ttf"), "Player",
		leftBase.x + 220.f, leftBase.y + 50.f, Color::White, 30);
	leftHealthText = new TextObj(*RESOURCE_MGR->GetFont("fonts/DNFBitBitTTF.ttf"), "100",
		leftBase.x + 170.f, leftBase.y + 75.f, Color::White, 25);
	leftMaxHealthText = new TextObj(*RESOURCE_MGR->GetFont("fonts/DNFBitBitTTF.ttf"), "/100",
		leftBase.x + 220.f, leftBase.y + 75.f, Color::White, 25);
	leftDamageText = new TextObj(*RESOURCE_MGR->GetFont("fonts/DNFBitBitTTF.ttf"), "10",
		leftBase.x + 75.f, leftBase.y + 150.f, Color::White, 25);
	leftArmorText = new TextObj(*RESOURCE_MGR->GetFont("fonts/DNFBitBitTTF.ttf"), "5",
		leftBase.x + 175.f, leftBase.y + 150.f, Color::White, 25);
	leftRangeText = new TextObj(*RESOURCE_MGR->GetFont("fonts/DNFBitBitTTF.ttf"), "1",
		leftBase.x + 75.f, leftBase.y + 200.f, Color::White, 25);
	leftMobilityText = new TextObj(*RESOURCE_MGR->GetFont("fonts/DNFBitBitTTF.ttf"), "5",
		leftBase.x + 175.f, leftBase.y + 200.f, Color::White, 25);

	leftNameText->SetOrigin(Origins::MC);

	leftUIBackground->SetType("PlayableInfoUI");
	leftThumbnailBackground->SetType("PlayableInfoUI");
	leftThumbnail->SetType("PlayableInfoUI");
	leftDamageIcon->SetType("PlayableInfoUI");
	leftArmorIcon->SetType("PlayableInfoUI");
	leftRangeIcon->SetType("PlayableInfoUI");
	leftMobilityIcon->SetType("PlayableInfoUI");
	leftHealthBarBackground->SetType("PlayableInfoUI");
	leftHealthBar->SetType("PlayableInfoUI");
	
	leftNameText->SetType("PlayableInfoUI");
	leftHealthText->SetType("PlayableInfoUI");
	leftMaxHealthText->SetType("PlayableInfoUI");
	leftDamageText->SetType("PlayableInfoUI");
	leftArmorText->SetType("PlayableInfoUI");
	leftRangeText->SetType("PlayableInfoUI");
	leftMobilityText->SetType("PlayableInfoUI");

	leftUIBackground->SetTexture(*RESOURCE_MGR->GetTexture("graphics/UIBackground.png"));
	leftUIBackground->SetScale(7.f, 6.f);
	leftThumbnailBackground->SetTexture(*RESOURCE_MGR->GetTexture("graphics/UIBackground.png"));
	leftThumbnailBackground->SetScale(2.f, 2.f);
	leftThumbnail->SetTexture(*RESOURCE_MGR->GetTexture("graphics/CatThumbnail.png"));
	leftThumbnail->SetScale(4.f, 4.f);
	leftDamageIcon->SetTexture(*RESOURCE_MGR->GetTexture("graphics/damageIcon.png"));
	leftDamageIcon->SetScale(0.4f, 0.4f);
	leftArmorIcon->SetTexture(*RESOURCE_MGR->GetTexture("graphics/armorIcon.png"));
	leftArmorIcon->SetScale(0.4f, 0.4f);
	leftRangeIcon->SetTexture(*RESOURCE_MGR->GetTexture("graphics/rangeIcon.png"));
	leftRangeIcon->SetScale(0.4f, 0.4f);
	leftMobilityIcon->SetTexture(*RESOURCE_MGR->GetTexture("graphics/bootsIcon.png"));
	leftMobilityIcon->SetScale(0.4f, 0.4f);
	leftHealthBarBackground->SetFillColor(Color(200.f, 200.f, 200.f, 255.f));
	leftHealthBarBackground->SetSize(100.f, 20.f);
	leftHealthBarBackground->GetShape().setOutlineColor(Color::Black);
	leftHealthBarBackground->GetShape().setOutlineThickness(4.f);
	leftHealthBar->SetFillColor(Color::Green);
	leftHealthBar->SetSize(50.f, 20.f);

	leftUIBackground->SetPos(leftBase);
	leftUIBackground->SetColor(uiBaseColor);
	leftThumbnailBackground->SetPos(leftBase + Vector2f(35.f, 35.f));
	leftThumbnailBackground->SetColor(Color(100, 100, 100, 125.f));
	leftThumbnail->SetPos(leftBase + Vector2f(25.f, 0.f));
	leftDamageIcon->SetPos(leftBase + Vector2f(50.f, 150.f));
	leftArmorIcon->SetPos(leftBase + Vector2f(150.f, 150.f));
	leftRangeIcon->SetPos(leftBase + Vector2f(50.f, 200.f));
	leftMobilityIcon->SetPos(leftBase + Vector2f(150.f, 200.f));
	leftHealthBarBackground->SetPos(leftBase + Vector2f(170.f, 110.f));
	leftHealthBar->SetPos(leftBase + Vector2f(170.f, 110.f));
	// playable character UI end

	// ai character UI start
	Vector2f rightBase(650.f, 0.f);
	rightUIBackground = new SpriteObj();
	rightThumbnailBackground = new SpriteObj();
	rightThumbnail = new SpriteObj();
	rightDamageIcon = new SpriteObj();
	rightArmorIcon = new SpriteObj();
	rightRangeIcon = new SpriteObj();
	rightMobilityIcon = new SpriteObj();
	rightHealthBarBackground = new RectangleObj();
	rightHealthBar = new RectangleObj();

	rightNameText = new TextObj(*RESOURCE_MGR->GetFont("fonts/DNFBitBitTTF.ttf"), "Minotaur",
		rightBase.x + 220.f, rightBase.y + 50.f, Color::White, 30);
	rightHealthText = new TextObj(*RESOURCE_MGR->GetFont("fonts/DNFBitBitTTF.ttf"), "100",
		rightBase.x + 170.f, rightBase.y + 75.f, Color::White, 25);
	rightMaxHealthText = new TextObj(*RESOURCE_MGR->GetFont("fonts/DNFBitBitTTF.ttf"), "/100",
		rightBase.x + 220.f, rightBase.y + 75.f, Color::White, 25);
	rightDamageText = new TextObj(*RESOURCE_MGR->GetFont("fonts/DNFBitBitTTF.ttf"), "10",
		rightBase.x + 75.f, rightBase.y + 150.f, Color::White, 25);
	rightArmorText = new TextObj(*RESOURCE_MGR->GetFont("fonts/DNFBitBitTTF.ttf"), "5",
		rightBase.x + 175.f, rightBase.y + 150.f, Color::White, 25);
	rightRangeText = new TextObj(*RESOURCE_MGR->GetFont("fonts/DNFBitBitTTF.ttf"), "1",
		rightBase.x + 75.f, rightBase.y + 200.f, Color::White, 25);
	rightMobilityText = new TextObj(*RESOURCE_MGR->GetFont("fonts/DNFBitBitTTF.ttf"), "5",
		rightBase.x + 175.f, rightBase.y + 200.f, Color::White, 25);

	rightNameText->SetOrigin(Origins::MC);

	rightUIBackground->SetType("AIInfoUI");
	rightThumbnailBackground->SetType("AIInfoUI");
	rightThumbnail->SetType("AIInfoUI");
	rightDamageIcon->SetType("AIInfoUI");
	rightArmorIcon->SetType("AIInfoUI");
	rightRangeIcon->SetType("AIInfoUI");
	rightMobilityIcon->SetType("AIInfoUI");
	rightHealthBarBackground->SetType("AIInfoUI");
	rightHealthBar->SetType("AIInfoUI");

	rightNameText->SetType("AIInfoUI");
	rightHealthText->SetType("AIInfoUI");
	rightMaxHealthText->SetType("AIInfoUI");
	rightDamageText->SetType("AIInfoUI");
	rightArmorText->SetType("AIInfoUI");
	rightRangeText->SetType("AIInfoUI");
	rightMobilityText->SetType("AIInfoUI");

	rightUIBackground->SetTexture(*RESOURCE_MGR->GetTexture("graphics/UIBackground.png"));
	rightUIBackground->SetScale(7.f, 6.f);
	rightThumbnailBackground->SetTexture(*RESOURCE_MGR->GetTexture("graphics/UIBackground.png"));
	rightThumbnailBackground->SetScale(2.f, 2.f);
	rightThumbnail->SetTexture(*RESOURCE_MGR->GetTexture("graphics/SquirrelThumbnail.png"));
	rightThumbnail->SetScale(4.f, 4.f);
	rightDamageIcon->SetTexture(*RESOURCE_MGR->GetTexture("graphics/damageIcon.png"));
	rightDamageIcon->SetScale(0.4f, 0.4f);
	rightArmorIcon->SetTexture(*RESOURCE_MGR->GetTexture("graphics/armorIcon.png"));
	rightArmorIcon->SetScale(0.4f, 0.4f);
	rightRangeIcon->SetTexture(*RESOURCE_MGR->GetTexture("graphics/rangeIcon.png"));
	rightRangeIcon->SetScale(0.4f, 0.4f);
	rightMobilityIcon->SetTexture(*RESOURCE_MGR->GetTexture("graphics/bootsIcon.png"));
	rightMobilityIcon->SetScale(0.4f, 0.4f);
	rightHealthBarBackground->SetFillColor(Color(200.f, 200.f, 200.f, 255.f));
	rightHealthBarBackground->SetSize(100.f, 20.f);
	rightHealthBarBackground->GetShape().setOutlineColor(Color::Black);
	rightHealthBarBackground->GetShape().setOutlineThickness(4.f);
	rightHealthBar->SetFillColor(Color::Green);
	rightHealthBar->SetSize(50.f, 20.f);

	rightUIBackground->SetPos(rightBase);
	rightUIBackground->SetColor(uiBaseColor);
	rightThumbnailBackground->SetPos(rightBase + Vector2f(35.f, 35.f));
	rightThumbnailBackground->SetColor(Color(100, 100, 100, 125.f));
	rightThumbnail->SetPos(rightBase + Vector2f(25.f, 0.f));
	rightDamageIcon->SetPos(rightBase + Vector2f(50.f, 150.f));
	rightArmorIcon->SetPos(rightBase + Vector2f(150.f, 150.f));
	rightRangeIcon->SetPos(rightBase + Vector2f(50.f, 200.f));
	rightMobilityIcon->SetPos(rightBase + Vector2f(150.f, 200.f));
	rightHealthBarBackground->SetPos(rightBase + Vector2f(170.f, 110.f));
	rightHealthBar->SetPos(rightBase + Vector2f(170.f, 110.f));
	// ai character UI end

	// Command Window start
	commandAttackButton = new SpriteObj();
	commandSpecialButton = new SpriteObj();
	commandToolButton = new SpriteObj();
	commandWaitButton = new SpriteObj();
	commandAttackText = new TextObj(*RESOURCE_MGR->GetFont("fonts/DNFBitBitTTF.ttf"), L"공격",
		0.f, 0.f, Color::Black, 25.f);
	commandSpeicialText = new TextObj(*RESOURCE_MGR->GetFont("fonts/DNFBitBitTTF.ttf"), L"기술",
		0.f, 0.f, Color::Black, 25.f);
	commandToolText = new TextObj(*RESOURCE_MGR->GetFont("fonts/DNFBitBitTTF.ttf"), L"도구",
		0.f, 0.f, Color::Black, 25.f);
	commandWaitText = new TextObj(*RESOURCE_MGR->GetFont("fonts/DNFBitBitTTF.ttf"), L"대기",
		0.f, 0.f, Color::Black, 25.f);

	commandAttackButton->SetType("CommandWindow");
	commandSpecialButton->SetType("CommandWindow");
	commandToolButton->SetType("CommandWindow");
	commandWaitButton->SetType("CommandWindow");
	commandAttackText->SetType("CommandWindow");
	commandSpeicialText->SetType("CommandWindow");
	commandToolText->SetType("CommandWindow");
	commandWaitText->SetType("CommandWindow");

	commandAttackButton->SetTexture(*RESOURCE_MGR->GetTexture("graphics/UIBackground.png"));
	commandAttackButton->SetScale(1.2f, 1.f);
	commandAttackButton->SetColor(uiBaseColor);
	commandSpecialButton->SetTexture(*RESOURCE_MGR->GetTexture("graphics/UIBackground.png"));
	commandSpecialButton->SetScale(1.2f, 1.f);
	commandSpecialButton->SetColor(uiBaseColor);
	commandToolButton->SetTexture(*RESOURCE_MGR->GetTexture("graphics/UIBackground.png"));
	commandToolButton->SetScale(1.2f, 1.f);
	commandToolButton->SetColor(uiBaseColor);
	commandWaitButton->SetTexture(*RESOURCE_MGR->GetTexture("graphics/UIBackground.png"));
	commandWaitButton->SetScale(1.2f, 1.f);
	commandWaitButton->SetColor(uiBaseColor);
	// Command Window end

	// no group
	damageText = new FloatingObj(*RESOURCE_MGR->GetFont("fonts/DNFBitBitTTF.ttf"), "test text",
		0.f, 0.f, Color::Red, 25);
	damageText->SetOrigin(Origins::MC);
	damageText->SetType("Damage");

	size = FRAMEWORK->GetWindowSize();
	turnStateHUD = new TextObj(*RESOURCE_MGR->GetFont("fonts/DNFBitBitTTF.ttf"), "",
		size.x * 0.30f, 10.f, Color::Black, 30.f);
	turnStateHUD->SetOrigin(Origins::TL);
	turnStateHUD->SetType("HUD");
}

BattleSceneUI::~BattleSceneUI()
{
	Release();
}

void BattleSceneUI::Init()
{
	// playable character UI start
	uiObjList.push_back(leftUIBackground);
	uiObjList.push_back(leftThumbnailBackground);
	uiObjList.push_back(leftThumbnail);
	uiObjList.push_back(leftDamageIcon);
	uiObjList.push_back(leftArmorIcon);
	uiObjList.push_back(leftRangeIcon);
	uiObjList.push_back(leftMobilityIcon);
	uiObjList.push_back(leftHealthBarBackground);
	uiObjList.push_back(leftHealthBar);

	uiObjList.push_back(leftNameText);
	uiObjList.push_back(leftHealthText);
	uiObjList.push_back(leftMaxHealthText);
	uiObjList.push_back(leftDamageText);
	uiObjList.push_back(leftArmorText);
	uiObjList.push_back(leftRangeText);
	uiObjList.push_back(leftMobilityText);
	// playable character UI end

	// ai character UI start
	uiObjList.push_back(rightUIBackground);
	uiObjList.push_back(rightThumbnailBackground);
	uiObjList.push_back(rightThumbnail);
	uiObjList.push_back(rightDamageIcon);
	uiObjList.push_back(rightArmorIcon);
	uiObjList.push_back(rightRangeIcon);
	uiObjList.push_back(rightMobilityIcon);
	uiObjList.push_back(rightHealthBarBackground);
	uiObjList.push_back(rightHealthBar);

	uiObjList.push_back(rightNameText);
	uiObjList.push_back(rightHealthText);
	uiObjList.push_back(rightMaxHealthText);
	uiObjList.push_back(rightDamageText);
	uiObjList.push_back(rightArmorText);
	uiObjList.push_back(rightRangeText);
	uiObjList.push_back(rightMobilityText);
	// ai character UI end

	// command window start
	uiObjList.push_back(commandAttackButton);
	uiObjList.push_back(commandSpecialButton);
	uiObjList.push_back(commandToolButton);
	uiObjList.push_back(commandWaitButton);
	uiObjList.push_back(commandAttackText);
	uiObjList.push_back(commandSpeicialText);
	uiObjList.push_back(commandToolText);
	uiObjList.push_back(commandWaitText);

	buttons.push_back(commandAttackButton);
	buttons.push_back(commandSpecialButton);
	buttons.push_back(commandToolButton);
	buttons.push_back(commandWaitButton);
	// command window end

	// no group
	uiObjList.push_back(damageText);
	uiObjList.push_back(turnStateHUD);
}

void BattleSceneUI::Release()
{
	UIMgr::Release();
}

void BattleSceneUI::Reset()
{
	//UIMgr::Reset();
	for (auto uiObj : uiObjList)
	{
		if (uiObj->GetType().compare("HUD"))
			uiObj->SetActive(false);
	}
}

void BattleSceneUI::Update(float dt)
{
	UIMgr::Update(dt);
}

void BattleSceneUI::Draw(RenderWindow& window)
{
	UIMgr::Draw(window);
}

void BattleSceneUI::SetPlayableInfo(Piece* playable)
{
	if (!playable->GetName().compare("Player"))
	{
		leftThumbnail->SetTexture(*RESOURCE_MGR->GetTexture("graphics/AdventurerThumbnail.png"));
	}
	else if (!playable->GetName().compare("Cat"))
	{
		leftThumbnail->SetTexture(*RESOURCE_MGR->GetTexture("graphics/CatThumbnail.png"));
	}

	leftNameText->SetString(playable->GetName());

	leftHealthText->SetString(to_string(playable->health));
	leftMaxHealthText->SetString("/" + to_string(playable->maxHealth));
	leftDamageText->SetString(to_string(playable->damage));
	leftArmorText->SetString(to_string(playable->armor));
	leftRangeText->SetString(to_string(playable->range));
	leftMobilityText->SetString(to_string(playable->mobility));
	float curHealthRate = Utils::Clamp((float)playable->health / (float)playable->maxHealth, 0.f, 1.0f);
	leftHealthBar->SetSize(curHealthRate * 100.f, 20.f);
	if (curHealthRate > 0.6f)
	{
		leftHealthBar->SetFillColor(Color::Green);
	}
	else if (curHealthRate > 0.3f)
	{
		leftHealthBar->SetFillColor(Color::Yellow);
	}
	else
	{
		leftHealthBar->SetFillColor(Color::Red);
	}
}

void BattleSceneUI::SetAIInfo(Piece* ai)
{
	if (!ai->GetName().compare("Minotaur"))
	{
		rightThumbnail->SetTexture(*RESOURCE_MGR->GetTexture("graphics/MinotaurThumbnail.png"));
	}
	else if (!ai->GetName().compare("Fox"))
	{
		rightThumbnail->SetTexture(*RESOURCE_MGR->GetTexture("graphics/FoxThumbnail.png"));
	}
	else if (!ai->GetName().compare("Squirrel"))
	{
		rightThumbnail->SetTexture(*RESOURCE_MGR->GetTexture("graphics/SquirrelThumbnail.png"));
	}

	rightNameText->SetString(ai->GetName());

	rightHealthText->SetString(to_string(ai->health));
	rightMaxHealthText->SetString("/" + to_string(ai->maxHealth));
	rightDamageText->SetString(to_string(ai->damage));
	rightArmorText->SetString(to_string(ai->armor));
	rightRangeText->SetString(to_string(ai->range));
	rightMobilityText->SetString(to_string(ai->mobility));
	float curHealthRate = Utils::Clamp((float)ai->health / (float)ai->maxHealth, 0.f, 1.0f) ;
	rightHealthBar->SetSize(curHealthRate * 100.f, 20.f);
	if (curHealthRate > 0.6f)
	{
		rightHealthBar->SetFillColor(Color::Green);
	}
	else if (curHealthRate > 0.3f)
	{
		rightHealthBar->SetFillColor(Color::Yellow);
	}
	else
	{
		rightHealthBar->SetFillColor(Color::Red);
	}
}

void BattleSceneUI::SetUIActive(string type, bool enable)
{
	for (auto& ui : uiObjList)
	{
		if (!ui->GetType().compare(type))
			ui->SetActive(enable);
	}
}

void BattleSceneUI::SetDamageText(Vector2f pos, float dmg)
{
	damageText->Fire(pos);
	string dmgString = to_string((int)dmg);
	damageText->SetString(dmgString);
}

void BattleSceneUI::SetCommandWindow(Vector2f pos)
{
	commandAttackButton->SetPos(pos + Vector2f(0.f, 0.f));
	commandSpecialButton->SetPos(pos + Vector2f(0.f, 40.f));
	commandToolButton->SetPos(pos + Vector2f(0.f, 80.f));
	commandWaitButton->SetPos(pos + Vector2f(0.f, 120.f));

	commandAttackText->SetPos(pos + Vector2f(10.f, 5.f));
	commandSpeicialText->SetPos(pos + Vector2f(10.f, 45.f));
	commandToolText->SetPos(pos + Vector2f(10.f, 85.f));
	commandWaitText->SetPos(pos + Vector2f(10.f, 125.f));
}

void BattleSceneUI::SetHud(bool isPlayerTurn, int count)
{
	string turnText = isPlayerTurn ? "Player " : "AI ";
	turnText += to_string(count) + "Turn";
	turnStateHUD->SetString(turnText);
}