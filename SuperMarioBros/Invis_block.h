#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_INVIS 18000
#define INVIS_WIDTH 16
#define INVIS_BBOX_WIDTH 16
#define INVIS_BBOX_HEIGHT 16

class CInvis : public CGameObject
{
public:
	CInvis(float x, float y) : CGameObject(x, y) {  }
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};
