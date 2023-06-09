#pragma once
#include "GameObject.h"


class CColorBox : public CGameObject
{
protected:
	int Width, Height;
	float cellWidth, cellHeight;
	int spriteIDTopLeft, spriteIDTopMid, spriteIDTopRight,
		spriteIDMidLeft, spriteIDCenter, spriteIDMidRight,
		spriteIDBotLeft, spriteIDBotMid, spriteIDBotRight;
public:
	CColorBox(float x, float y,	
		float cell_width, float cell_height,
		int Width, int Height,
		int spriteID_TopLeft, int spriteID_TopMid, int spriteID_TopRight,
		int spriteID_MidLeft, int spriteID_Center, int spriteID_MidRight,
		int spriteID_BotLeft, int spriteID_BotMid, int spriteID_BotRight);
	void Render();
	void Update() {};
	
	int IsBlocking() { return 1; }
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	bool IsColorBox() { return 1; }
};

