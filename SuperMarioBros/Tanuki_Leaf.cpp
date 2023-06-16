#include "Tanuki_Leaf.h"
#include "debug.h"
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
	//vx += ax * dt;

	if (GetTickCount64() - stateDelay > LEAF_STATE_DELAY && state == LEAF_STATE_SHOW)
		SetState(LEAF_STATE_FALL);

	if (y > 300)
	{
		isDeleted = true;
		return;
	}
	if (GetTickCount64() - moveDelay > LEAF_FALL_CHANGE_SIDE_TIMEOUT && state == LEAF_STATE_FALL)
	{
		vx = -vx;
		moveDelay = GetTickCount64();
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CTanukiLeaf::Render()
{
	
	if(state!=LEAF_STATE_HIDDEN)
	{
		int aniID;
		if (state == LEAF_STATE_FALL)
			aniID = ID_ANI_LEAF_FALL;
		else
			aniID = ID_ANI_LEAF_POPUP;

		CAnimations::GetInstance()->Get(aniID)->Render(x, y);
		RenderBoundingBox();
	}
}

void CTanukiLeaf::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CTanukiLeaf::OnCollisionWith(LPCOLLISIONEVENT e)
{
	
}

CTanukiLeaf::CTanukiLeaf(float x, float y): CGameObject(x,y)
{
	this->ax = 0;
	this->ay = 0;
	this->Y = y;
	this->moveDelay = -1;
	this->stateDelay = -1;
	SetState(LEAF_STATE_HIDDEN);
}

void CTanukiLeaf::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case LEAF_STATE_HIDDEN:
	{vy = 0;
	ay = 0;
	vx = 0;

	break;
	}

	case LEAF_STATE_SHOW:
	{
		vy = -LEAF_SPEED;
		vx = 0;
		stateDelay = GetTickCount64();
		DebugOut(L"[info] state show\n");
		break;
	}
	case LEAF_STATE_FALL:
	{
		vy = 0;
		ay = LEAF_GRAVITY;
		ax = LEAF_SPEED;
		DebugOut(L"[info] state fall\n");
		moveDelay = GetTickCount64();
		break;
	}

	}
}
