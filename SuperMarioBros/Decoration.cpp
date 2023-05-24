#include"Decoration.h"

void CDecoration::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BUSH)->Render(x, y);
	
}

void CDecoration::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BUSH_BBOX_WIDTH / 2;
	t = y - BUSH_BBOX_HEIGHT / 2;
	r = l + BUSH_BBOX_WIDTH;
	b = t + BUSH_BBOX_HEIGHT;
}