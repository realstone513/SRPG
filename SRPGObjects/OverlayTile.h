#pragma once
#include "../SFML_Framework/GameObject/RectangleObj.h"

class OverlayTile : public RectangleObj
{
protected:

public:
	OverlayTile();
	virtual ~OverlayTile() override;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};