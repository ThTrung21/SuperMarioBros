#include "Tanuki_Leaf.h"
#include "debug.h"



CTanukiLeaf::CTanukiLeaf(float x, float y) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	this->Y = y;
	this->moveDelay = -1;
	this->stateDelay = -1;
	this->border_l = x - 16;
	this->border_r = x + 16;
	SetState(LEAF_STATE_HIDDEN);

}

void CTanukiLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LEAF_BBOX_WIDTH / 2;
	t = y - LEAF_BBOX_HEIGHT / 2;
	r = l + LEAF_BBOX_WIDTH;
	b = t + LEAF_BBOX_HEIGHT;
}

void CTanukiLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	float xx,yy;
	this->GetPosition(xx, yy);
	if (GetTickCount64() - stateDelay > LEAF_STATE_DELAY && state == LEAF_STATE_SHOW)
		SetState(LEAF_STATE_FALL);

	if (y > 300)
	{
		isDeleted = true;
		return;
	}
	if ((xx <= border_l || xx >= border_r) && state == LEAF_STATE_FALL)
	{
		vx = -vx;
		
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CTanukiLeaf::Render()
{
	
	//if(state!=LEAF_STATE_HIDDEN)
	{
		int aniID;
		if (state == LEAF_STATE_FALL)
		{
			if (vx < 0)
				aniID = ID_ANI_LEAF_FALL_LEFT;
			else
				aniID = ID_ANI_LEAF_FALL_RIGHT;
		}

		else
			aniID = ID_ANI_LEAF_POPUP;

		CAnimations::GetInstance()->Get(aniID)->Render(x, y);
		//RenderBoundingBox();
	}
}

void CTanukiLeaf::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CTanukiLeaf::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (state == LEAF_STATE_FALL &&!e->obj->IsMario())
		return;
	else
	if (e->obj->IsMario() && e->ny > 0)
		SetState(LEAF_STATE_SHOW);

}



void CTanukiLeaf::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case LEAF_STATE_HIDDEN:
	{
		vy = 0;
		ay = 0;
		vx = 0;
	break;
	}

	case LEAF_STATE_SHOW:
	{
		vy = -LEAF_SPEED_Y;
		vx = 0;
		stateDelay = GetTickCount64();
		DebugOut(L"[info] leaf state show\n");
		break;
	}
	case LEAF_STATE_FALL:
	{
		vy = 0;
		ay = LEAF_GRAVITY;
		ax = LEAF_SPEED;
		
		DebugOut(L"[info] state fall\n");
		
		break;
	}

	}
}
