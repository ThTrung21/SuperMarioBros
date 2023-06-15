 #include "Koopa.h"
#include "Goomba.h"

CKoopa::CKoopa(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	default_y = y;
	this->ay = KOOPA_GRAVITY;
	shell_start = -1;
	revive_start = -1;
	pre_vx = 0;
	SetState(KOOPA_STATE_WALKING);
	
}

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPA_STATE_SHELL)
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - SHELL_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + SHELL_BBOX_HEIGHT;
	}
	else
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}

}

void CKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CKoopa*>(e->obj)) return;
	if(dynamic_cast<CGoomba*>(e->obj)) return;
	if (e->ny != 0 && e->obj->IsBlocking() && state ==KOOPA_STATE_WALKING)
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
		platform_y = y;
	}
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}
void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (state == KOOPA_STATE_WALKING && isOnPlatform == false)
	{
		y = platform_y;
		vx = -vx;
	}
	if ((state == KOOPA_STATE_SHELL) && (state != KOOPA_STATE_KICK_RIGHT)&& (GetTickCount64() - shell_start > KOOPA_SHELL_TIMEOUT))
	{
		SetState(KOOPA_STATE_REVIVE);
		return;
	}
	if ((state == KOOPA_STATE_REVIVE) && (GetTickCount64() - revive_start > KOOPA_REVIVE_TIME))
	{
		SetState(KOOPA_STATE_WALKING);
		return;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CKoopa::Render()
{
	int aniId = ID_ANI_KOOPA_WALKING_LEFT;
	if (state == KOOPA_STATE_WALKING)
	{
		if (vx > 0)
			aniId = ID_ANI_KOOPA_WALKING_RIGHT;
		if (vx < 0)
			aniId = ID_ANI_KOOPA_WALKING_LEFT;
	}

	else if (state == KOOPA_STATE_SHELL || state== KOOPA_STATE_KICK_LEFT || state == KOOPA_STATE_KICK_RIGHT)
	{
		aniId = ID_ANI_KOOPA_SHELL;
	}
	else if (state == KOOPA_STATE_REVIVE)
	{
		aniId = ID_ANI_KOOPA_REVIVE;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}
void CKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	//shell
	case KOOPA_STATE_SHELL:
		shell_start = GetTickCount64();
		default_y = y;
		y += (KOOPA_BBOX_HEIGHT - SHELL_BBOX_HEIGHT) / 2;
		pre_vx = vx;
		vx = 0;
		vy = 0;
		ay = 0;
		break;

	//walking
	case KOOPA_STATE_WALKING:
		y = default_y;
		if (pre_vx > 0)
			vx = -KOOPA_WALKING_SPEED;
		else if (pre_vx < 0)
			vx = KOOPA_WALKING_SPEED;
		else
		vx = -KOOPA_WALKING_SPEED;

		break;

	//revive
	case KOOPA_STATE_REVIVE:
		revive_start = GetTickCount64();
		break;
	case KOOPA_STATE_KICK_RIGHT:
		vx = KOOPA_SHELL_SPEED;
		break;
	case KOOPA_STATE_KICK_LEFT:
		vx = -KOOPA_SHELL_SPEED;
		break;
	}
}

