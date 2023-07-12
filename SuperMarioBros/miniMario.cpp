#include"miniMario.h"
#include "Game.h"
#include "Animation.h"
#include "Animations.h"
#include "debug.h"

CMini::CMini(float x, float y) :CGameObject(x, y)
{
	SetState(MINI_STATE_STOP);
}

void CMini::Render()
{
	int aniID = ID_ANI_MINI;
	CAnimations::GetInstance()->Get(aniID)->Render(x, y);
	RenderBoundingBox();
}

void CMini::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MINI_BBOX_WIDTH / 2;
	top = y - MINI_BBOX_HEIGHT / 2;
	right = left + MINI_BBOX_WIDTH;
	bottom = top + MINI_BBOX_HEIGHT;
}
void CMini::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vx = ax * dt;
	vy = ay * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CMini::OnNoCollision(DWORD dt)
{
	x = vx * dt;
	y = vy * dt;
}
void CMini::OnCollisionWith(LPCOLLISIONEVENT e)
{
	/*if (e->nx != 0 || e->ny != 0)
		SetState(MINI_STATE_STOP);*/

}
void CMini::SetState(int state)
{
	CGameObject::SetState(state);
	/*switch (state)
	{
	case MINI_STATE_STOP:
		vx = 0;
		vy = 0;
		break;
	case MINI_STATE_LEFT:
		vx = -MINI_SPEED;
		vy = 0;
		break;
	case MINI_STATE_TOP:
		vx = 0;
		vy = -MINI_SPEED;
		break;
	case MINI_STATE_RIGHT:
		vx = MINI_SPEED;
		vy = 0;
		break;
	case MINI_STATE_BOT:
		vx = 0;
		vy = MINI_SPEED;
		break;
	}*/

	switch (state)
	{
	case MINI_STATE_STOP:
		ax = 0;
		ay = 0;
		break;
	case MINI_STATE_LEFT:
		ax = -MINI_SPEED;
		ay = 0;
		break;
	case MINI_STATE_TOP:
		ax = 0;
		ay = -MINI_SPEED;
		break;
	case MINI_STATE_RIGHT:
		ax = MINI_SPEED;
		ay = 0;
		break;
	case MINI_STATE_BOT:
		ax = 0;
		ay = MINI_SPEED;
		break;
	}
}
