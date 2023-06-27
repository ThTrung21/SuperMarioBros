#include "GoldBrick.h"

void CGoldBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_GOLD_BRICK)->Render(x, y);
	//RenderBoundingBox();
}

void CGoldBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - GBRICK_BBOX_WIDTH / 2;
	t = y - GBRICK_BBOX_HEIGHT / 2;
	r = l + GBRICK_BBOX_WIDTH;
	b = t + GBRICK_BBOX_HEIGHT;
}