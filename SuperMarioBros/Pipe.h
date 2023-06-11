#pragma once
#include "GameObject.h"


class CPipe : public CGameObject
{
protected:
	int Height;

	float cellWidth = 16, cellHeight = 16;
	int spriteIDTopLeft, spriteIDTopRight,
		spriteIDBodyLeft, spriteIDBodyRight;
	
public:
	CPipe(float x, float y,
		int Height,
		int spriteID_TopLeft, int spriteID_TopRight,
		int spriteID_BodyLeft, int spriteID_BodyRight,int accessibility);
	void Render();
	void Update() {};

	int IsBlocking() { return 1; }
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();

};


