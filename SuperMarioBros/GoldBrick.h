#pragma once


#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_GOLD_BRICK 10000

#define GBRICK_WIDTH 16
#define GBRICK_BBOX_WIDTH 16
#define GBRICK_BBOX_HEIGHT 16

class CGoldBrick : public CGameObject {
public:
	CGoldBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};
