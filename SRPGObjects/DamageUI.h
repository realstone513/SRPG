#pragma once
#include "../SFML_Framework/GameObject/FloatingUI.h"

class DamageUI : public FloatingUI
{
protected:

public:
	DamageUI();
	virtual ~DamageUI() {}

	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};