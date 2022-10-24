#pragma once
#include "../SFML_Framework/GameObject/SpriteObj.h"

enum class PieceTypes
{
	None = -1,
	Playable,
	AI,
};

// ���������� �� �͵� �߰�
class Piece : public SpriteObj
{
protected:
	// tile map info
	PieceTypes pType;
	Vector2i curIdx;
	Vector2f dest;
	Vector2f dir;
	float dist;
	float speed;

	// turn
	bool isTurn;		// ��
	bool isPlayable;	// ����
	bool done;			// �ൿ

public:
	// status
	int MaxHealth;
	int health;
	int damage;
	int armor;
	int range;
	bool rangeFill;
	int mobility;
	bool isDeath;

	Piece(PieceTypes pt, int h, int d, int a, int r, int m, bool f = true);
	virtual ~Piece() {};

	virtual void Reset();
	virtual void Update(float dt) override;
	virtual void SetPos(const Vector2f& pos) override;
	void SetIdxPos(const Vector2i& pos);
	const Vector2i& GetIdxPos() const;

	string GetStatusString() const;

	void SetIsTurn(bool isTurn);
	bool GetIsTurn();
	void SetDone(bool done);
	bool GetDone();
	void SetDest(Vector2f dest);
	Vector2f GetDest();

	// �ൿ�� ������ ȸ������
	//void InactiveFillColor(bool condition);
};