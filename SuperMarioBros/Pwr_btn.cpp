#include "Pwr_btn.h"


void CBtn::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BTN_BBOX_WIDTH / 2;
	t = y - BTN_BBOX_HEIGHT / 2;
	r = l + BTN_BBOX_WIDTH;
	b = t + BTN_BBOX_HEIGHT;
}

void CBtn::Render()
{
	if (state != BTN_STATE_HIDDEN)
	{
		int aniId = ID_ANI_BTN;
		if (state == BTN_STATE_USED)
			aniId = ID_ANI_BTN_USED;
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(aniId)->Render(x, y);
		//RenderBoundingBox();
	}
}