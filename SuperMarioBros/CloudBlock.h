#pragma once
#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_CLOUDBLOCK 21000
#define CBRICK_WIDTH 16
#define CBRICK_BBOX_WIDTH 16
#define CBRICK_BBOX_HEIGHT 16

class CCloudBlock : public CGameObject {
public:
	CCloudBlock(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};
