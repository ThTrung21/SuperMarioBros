#pragma once

#include "GameObject.h"





class CTitle :public CGameObject {
protected:
	int spriteID;
public:

	CTitle(float x, float y, int spriteID) : CGameObject(x, y) { this->spriteID = spriteID; }
	void Render();
	int isBlocking() { return 0; }
	void GetBoundingBox(float& l, float& t, float& r, float& b){}
};

