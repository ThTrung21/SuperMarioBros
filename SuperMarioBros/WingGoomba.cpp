#include "WingGoomba.h"

CWingGoomba::CWingGoomba(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = WGOOMBA_GRAVITY;
	die_start = -1;
	SetState(WGOOMBA_STATE_WALKING);
}

void CWingGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == WGOOMBA_STATE_DIE)
	{
		left = x - WGOOMBA_BBOX_WIDTH / 2;
		top = y - WGOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + WGOOMBA_BBOX_WIDTH;
		bottom = top + WGOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - WGOOMBA_BBOX_WIDTH / 2;
		top = y - WGOOMBA_BBOX_HEIGHT / 2;
		right = left + WGOOMBA_BBOX_WIDTH;
		bottom = top + WGOOMBA_BBOX_HEIGHT;
	}
}

void CWingGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CWingGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CWingGoomba*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CWingGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == WGOOMBA_STATE_DIE) && (GetTickCount64() - die_start > WGOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CWingGoomba::Render()
{
	int aniId = ID_ANI_WGOOMBA_WALKING;
	if (state == WGOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_WGOOMBA_DIE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CWingGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case WGOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (WGOOMBA_BBOX_HEIGHT - WGOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case WGOOMBA_STATE_WALKING:
		vx = -WGOOMBA_WALKING_SPEED;
		break;
	}
}
