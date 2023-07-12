#include "Goomba.h"
#include "Koopa.h"
#include "Mario.h"
#include "PlayScene.h"
#include "debug.h"
#include "Tail.h"
CGoomba::CGoomba(float x, float y):CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	flag = 0;
	this->X = x;
	this->Y = y;
	DebugOut(L"the y level is: %d \n", Y);
	SetState(GOOMBA_STATE_IDLE);
	
}


void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	
	else
	{ 
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CTail*>(e->obj))
	{
		CTail* tail = dynamic_cast<CTail*>(e->obj);
		if (tail->GetState() == TAIL_STATE_ACTIVE)
		{
			if (state != GOOMBA_STATE_DIE && state!=GOOMBA_STATE_HIDDEN)
				SetState(GOOMBA_STATE_DIE);
			return;
		}
		else
			return;
	}
	if (!e->obj->IsBlocking()) return; 
	if (dynamic_cast<CGoomba*>(e->obj)) return; 
	
	if (e->ny != 0 )
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
	
}




void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	if (y > 220)
	{
		SetState(GOOMBA_STATE_HIDDEN);
	}
	
	if ( (state==GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT) )
	{
		SetState(GOOMBA_STATE_HIDDEN);
		//isDeleted = true;
		return;
	}

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	int mario_x;
	mario_x = mario->GetX();

	//detect mario to start goomba movement
	if (MarioDetection(mario_x) && flag == 0)
	{
		SetState(GOOMBA_STATE_WALKING);
		flag = 1;
	}

	//respawn mechanic
	if (state == GOOMBA_STATE_HIDDEN && RespawnDetector(mario_x) == 1)
	{
		flag = 0;
		//y -= (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
		SetState(GOOMBA_STATE_IDLE);
	}


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoomba::Render()
{
	if (state != GOOMBA_STATE_HIDDEN)
	{
		int aniId = ID_ANI_GOOMBA_WALKING;
		if (state == GOOMBA_STATE_DIE)
		{
			aniId = ID_ANI_GOOMBA_DIE;
		}
		CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	}
	
	RenderBoundingBox();
}

bool CGoomba::MarioDetection(int mario_x)
{
	int xx = mario_x - (int)x;
	if (abs(xx) < 200)
		return 1;
	return 0;
}

bool CGoomba::RespawnDetector(int mario_x)
{
	int xx = mario_x - (int)X;
	if (abs(xx) > 250)
		return 1;
	return 0;
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_STATE_DIE:
			die_start = GetTickCount64();
			//y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE)/2;
			vx = 0;
			vy = 0;
			ay = GOOMBA_GRAVITY;
			break;
		case GOOMBA_STATE_WALKING: 
			vx = -GOOMBA_WALKING_SPEED;
			break;
		case GOOMBA_STATE_IDLE:	
			x = X;
			y = Y;
			vx = 0;
			ay = GOOMBA_GRAVITY;
			break;
		case GOOMBA_STATE_HIDDEN:
			x = X;
			y = Y;
			ay = GOOMBA_GRAVITY;
			break;
	}
}
