#include "CloudBlock.h"

void CCloudBlock::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_CLOUDBLOCK)->Render(x, y);
	//RenderBoundingBox();
}

void CCloudBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - CBRICK_BBOX_WIDTH / 2;
	t = y - CBRICK_BBOX_HEIGHT / 2;
	r = l + CBRICK_BBOX_WIDTH;
	b = t + CBRICK_BBOX_HEIGHT;
}
