#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_WOOD 23000
#define WOOD_WIDTH 16
#define WOOD_BBOX_WIDTH 16
#define WOOD_BBOX_HEIGHT 16

class CWood : public CGameObject {
public:
	CWood(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};