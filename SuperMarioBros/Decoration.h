#pragma once

#include "GameObject.h"


#define ID_ANI_BUSH 12000
#define DECOR_WIDTH 128



class CDecoration :public CGameObject {
protected:
	int typeID;
public:
	
	CDecoration(float x, float y,int type);
	void Render();
	int isBlocking() { return 0; }
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};
