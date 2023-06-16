#include "Tanuki_Leaf.h"

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
	

	if (y > Y - 48)
		SetState(LEAF_STATE_FALL);
	if (y > 300)
	{
		isDeleted = true;
		return;
	}
	if (GetTickCount64() - moveDelay > LEAF_FALL_CHANGE_SIDE_TIMEOUT)
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
	SetState(LEAF_STATE_HIDDEN);
}

void CTanukiLeaf::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case LEAF_STATE_SHOW:
		vy = -LEAF_SPEED;
		break;
	case LEAF_STATE_FALL:
		vy = 0;
		ay = LEAF_GRAVITY;
		vx = LEAF_SPEED;
		moveDelay = GetTickCount64();
		break;
		
	default:
		break;
	}
}
