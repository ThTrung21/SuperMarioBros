#pragma once
#include "GameObject.h"

class CShadow :public CGameObject
{
protected:
	int height;
	float cellWidth, cellHeight;
	int spriteIDTop, spriteIDBody;
public:
	CShadow(float x, float y,
		int height,
		int spriteID_top, int spriteID_body);
	void Render();
	void Update() {};
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }

};
