#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BUSH 12000
#define BUSH_WIDTH 95
#define BUSH_BBOX_WIDTH 95
#define BUSH_BBOX_HEIGHT 64


class CDecoration : public CGameObject {
public:
	CDecoration(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	int IsBlocking() { return 0; }
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};
