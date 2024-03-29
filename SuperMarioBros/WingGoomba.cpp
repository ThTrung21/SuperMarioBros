#include "WingGoomba.h"
#include "Koopa.h"
#include "Mario.h"
#include "PlayScene.h"
#include "WingKoopa.h"
#include "Tail.h"
#include"debug.h"
CWingGoomba::CWingGoomba(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = WGOOMBA_GRAVITY;
	die_start = -1;
	flag = 0;
	fly_time = -1;
	fly_timeout = -1;
	X = x;
	Y = y;
	SetState(WGOOMBA_STATE_IDLE);
}

bool CWingGoomba::MarioDetection(int mario_x)
{
	int xx = mario_x - (int)x;
	if (abs(xx) < 200)
		return 1;
	return 0;
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
	else if (state == WGOOMBA_STATE_WALKING)
	{
		left= x - WGOOMBA_BBOX_WIDTH / 2;
		top = (y - WGOOMBA_BBOX_HEIGHT_WALKING / 2);
		right = left + WGOOMBA_BBOX_WIDTH;
		bottom = top + WGOOMBA_BBOX_HEIGHT_WALKING+2;
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
	if (dynamic_cast<CTail*>(e->obj))
	{
		CTail* tail = dynamic_cast<CTail*>(e->obj);
		if (tail->GetState() == TAIL_STATE_ACTIVE)
		{
			if (state != WGOOMBA_STATE_DIE && state != WGOOMBA_STATE_HIDDEN)
				SetState(WGOOMBA_STATE_DIE);
			return;
		}
		else
			return;
	}
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
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
}

void CWingGoomba::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	if ((koopa->GetState() == KOOPA_STATE_KICK_LEFT || koopa->GetState() == KOOPA_STATE_KICK_RIGHT)
		&& (e->nx != 0))
		SetState(WGOOMBA_STATE_DIE);
}

void CWingGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	
	if (y > 220)
	{
		SetState(WGOOMBA_STATE_HIDDEN);
	}
	if ((state == WGOOMBA_STATE_DIE) && (GetTickCount64() - die_start > WGOOMBA_DIE_TIMEOUT))
	{
		SetState(WGOOMBA_STATE_HIDDEN);
		return;
	}
	


	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	int mario_x;
	mario_x = mario->GetX();
	if (MarioDetection(mario_x) && flag == 0)
	{
		SetState(WGOOMBA_STATE_JUMPING_TIMEOUT);
		flag = 1;
	}
	if (state == WGOOMBA_STATE_HIDDEN && RespawnDetector(mario_x) == 1)
	{
		flag = 0;	
		SetState(WGOOMBA_STATE_IDLE);
	}
	
	//jump mechanic
		if (state == WGOOMBA_STATE_JUMPING && (GetTickCount64() - fly_time > WGOOMBA_JUMP_TIME)) {
			SetState(WGOOMBA_STATE_JUMPING_TIMEOUT);
		}
		else if (state == WGOOMBA_STATE_JUMPING_TIMEOUT && (GetTickCount64() - fly_timeout > WGOOMBA_JUMP_WAIT)) {
			SetState(WGOOMBA_STATE_JUMPING);
		}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CWingGoomba::Render()
{
	if (state != WGOOMBA_STATE_HIDDEN)
	{
		int aniId = ID_ANI_WGOOMBA_JUMPING;

		if (state == WGOOMBA_STATE_DIE)
		{

			aniId = ID_ANI_WGOOMBA_DIE;
		}
		else if (state == WGOOMBA_STATE_WALKING)
		{
			DebugOut(L"[INFO] WGoomba \n");
			aniId = ID_ANI_WGOOMBA_WALKING;
		}


		CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	}
	//RenderBoundingBox();
}

void CWingGoomba::SetState(int state)
{
	//if (state == WGOOMBA_STATE_DIE) return;
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	int mario_x = mario->GetX();
	CGameObject::SetState(state);
	switch (state)
	{
	case WGOOMBA_STATE_IDLE:
		vx = 0;
		break;
	case WGOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (WGOOMBA_BBOX_HEIGHT_WALKING - WGOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = WGOOMBA_GRAVITY;
		break;

	case WGOOMBA_STATE_WALKING:
		
		//y += (WGOOMBA_BBOX_HEIGHT - WGOOMBA_BBOX_HEIGHT_WALKING) ;
		y += 2;
		if (mario_x > x)
			vx = WGOOMBA_WALKING_SPEED;
		else if (mario_x < x)
			vx = -WGOOMBA_WALKING_SPEED;

		ay = WGOOMBA_GRAVITY;
		break;
		
	case WGOOMBA_STATE_JUMPING:
		ay = -WGOOMBA_JUMP_SPEED;
		fly_time = GetTickCount64();
		if (mario_x > x)
			vx = WGOOMBA_WALKING_SPEED;
		else if (mario_x < x)
			vx = -WGOOMBA_WALKING_SPEED;
		break;

	case WGOOMBA_STATE_JUMPING_TIMEOUT:
		if (vy < 0)
			ay = WGOOMBA_JUMP_SPEED;
		else
			ay = WGOOMBA_GRAVITY;
		if (mario_x > x)
			vx = WGOOMBA_WALKING_SPEED;
		else if (mario_x < x)
			vx = -WGOOMBA_WALKING_SPEED;
		fly_timeout = GetTickCount64();
		break;
	case WGOOMBA_STATE_HIDDEN:
		x = X;
		y = Y;
		ay = WGOOMBA_GRAVITY;
		break;
	}
}
bool CWingGoomba::RespawnDetector(int mario_x)
{
	int xx = mario_x - (int)X;
	if (abs(xx) > 300)
		return 1;
	return 0;
}