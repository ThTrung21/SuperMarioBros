#include "Pwr_btn.h"
#include "GoldBrick.h"

void CBtn::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state == BTN_STATE_SHOW)
	{	
		l = x - BTN_BBOX_WIDTH / 2;
		t = y - BTN_BBOX_HEIGHT / 2;
		r = l + BTN_BBOX_WIDTH;
		b = t + BTN_BBOX_HEIGHT;
	}
	else if (state == BTN_STATE_USED)
	{
		l = x - BTN_BBOX_WIDTH / 2;
		t =(y - BTN_BBOX_HEIGHT / 2)+16 ;
		r = l + BTN_BBOX_WIDTH;
		b = t + BTN_BBOX_HEIGHT_USED+2;
	}
}

void CBtn::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BTN_STATE_HIDDEN:
		x = X;
		y = Y;
		break;
	case BTN_STATE_SHOW:
		x = X;
		y = Y;
		break;
	case BTN_STATE_USED:

		x = X;
		//y += (BTN_BBOX_HEIGHT - BTN_BBOX_HEIGHT_USED) / 2;
		y = Y;
		break;
	}
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
		
	}
	RenderBoundingBox();
}

void CBtn::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x = X;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBtn::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CGoldBrick*>(e->src_obj))
	{
		CGoldBrick* b = dynamic_cast<CGoldBrick*>(e->src_obj);
		if (b->GetType() == 1)
		{
			if (e->ny != 0)
				SetState(BTN_STATE_SHOW);
		}
	}
}