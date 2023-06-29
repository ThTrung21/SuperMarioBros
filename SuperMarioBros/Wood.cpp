#include "Wood.h"

void CWood::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_WOOD)->Render(x, y);
	//RenderBoundingBox();
}

void CWood::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - WOOD_BBOX_WIDTH / 2;
	t = y - WOOD_BBOX_HEIGHT / 2;
	r = l + WOOD_BBOX_WIDTH;
	b = t + WOOD_BBOX_HEIGHT;
}