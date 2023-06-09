#pragma once

#include "GameObject.h"


#define ID_ANI_BUSH 12000
#define DECOR_WIDTH 128



class CDecoration :public CGameObject {
public:
	CDecoration(){}
	CDecoration(float x, float y);
	void Render();
	void Update(DWORD dt) {}
	int isBlocking() { return 0; }
	//void GetBoundingBox(float& l, float& t, float& r, float& b);
};
