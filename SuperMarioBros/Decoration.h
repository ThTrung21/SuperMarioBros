#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BUSH 12000
#define DECOR_WIDTH 16

#define DECOR_BBOX_WIDTH 16
#define DECOR_BBOX_HEIGHT 16

class CDecoration : public CGameObject {
public:
	CDecoration(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	int isBlocking() { return 0; }
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};
