#include "Invis_block.h"


void CInvis::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_INVIS)->Render(x, y);
	//RenderBoundingBox();
}
void CInvis::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - INVIS_BBOX_WIDTH / 2;
	t = y - INVIS_BBOX_HEIGHT / 2;
	r = l + INVIS_BBOX_WIDTH;
	b = t + INVIS_BBOX_HEIGHT;
}