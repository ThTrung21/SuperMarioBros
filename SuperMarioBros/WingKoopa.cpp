#include "WingKoopa.h"
#include "Goomba.h"
#include "Koopa.h"
#include "Mario.h"
#include "debug.h"
#include "PlayScene.h"

CWingKoopa::CWingKoopa(float x, float y)
{
	this->ax = 0;
	this->ay = WKOOPA_GRAVITY;
	revive_start = -1;
	flag = 0;
	fly_time = -1;
	fly_timeout = -1;
	shell_start = -1;
	revive_start = -1;
	pre_vx = 0;
	default_x = x;
	default_y = y;
	SetState(WKOOPA_STATE_IDLE);

}

bool CWingKoopa::RespawnDetector(int mario_x)
{
	int xx = mario_x - (int)default_x;
	if (abs(xx) > 250)
		return 1;
	return 0;
}
void CWingKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking() && !e->obj->IsGoomba()) return;
	if (e->obj->IsGoomba() && e->obj->GetState() == GOOMBA_STATE_DIE) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0 && !e->obj->IsGoomba())
	{
		vx = -vx;
	}
}
void CWingKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}
bool CWingKoopa::MarioDetection(int mario_x)
{
	int xx = mario_x - (int)x;
	if (abs(xx) < 300)
		return 1;
	return 0;
}


void CWingKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state != WKOOPA_STATE_WALKING)
	{
		left = x - WKOOPA_BBOX_WIDTH / 2;
		top = y - WSHELL_BBOX_HEIGHT / 2;
		right = left + WKOOPA_BBOX_WIDTH;
		bottom = top + WSHELL_BBOX_HEIGHT;
	}
	else
	{
		left = x - WKOOPA_BBOX_WIDTH / 2;
		top = y - WKOOPA_BBOX_HEIGHT / 2;
		right = left + WKOOPA_BBOX_WIDTH;
		bottom = top + WKOOPA_BBOX_HEIGHT;
	}
}

void CWingKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	//shell kicked timeout
	if ((state == WKOOPA_STATE_KICK_LEFT || state == WKOOPA_STATE_KICK_RIGHT) && GetTickCount64() - die_timeout > WKOOPA_SHELL_TIMEOUT)
	{
		SetState(WKOOPA_STATE_HIDDEN);
		return;
	}

	//revive after turn into shell
	if ((state == WKOOPA_STATE_SHELL) && (GetTickCount64() - shell_start > WKOOPA_SHELL_TIMEOUT))
	{
		SetState(WKOOPA_STATE_REVIVE);
		return;
	}
	
	//stop revive ani and turn into walking state
	if ((state == WKOOPA_STATE_REVIVE) && (GetTickCount64() - revive_start > WKOOPA_REVIVE_TIME))
	{
		SetState(WKOOPA_STATE_WALKING);
		return;
	}
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	int mario_x;
	mario_x = mario->GetX();

	//detect mario to start koopa movement
	if (MarioDetection(mario_x) && flag == 0)
	{
		SetState(WKOOPA_STATE_JUMPING_TIMEOUT);
		flag = 1;
	}

	//respawn mechanic
	if (state == WKOOPA_STATE_HIDDEN && RespawnDetector(mario_x) == 1)
	{
		flag = 0;
		//y -= (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
		SetState(WKOOPA_STATE_IDLE);
	}

	//jump mechanic
	if (state == WKOOPA_STATE_JUMPING && (GetTickCount64() - fly_time > WKOOPA_JUMP_TIME)) {
		SetState(WKOOPA_STATE_JUMPING_TIMEOUT);
	}
	else if (state == WKOOPA_STATE_JUMPING_TIMEOUT && (GetTickCount64() - fly_timeout > WKOOPA_JUMP_WAIT)) {
		SetState(WKOOPA_STATE_JUMPING);
	}


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CWingKoopa::Render()
{
	if (state != WKOOPA_STATE_HIDDEN)
	{
		int aniId = ID_ANI_WKOOPA_JUMPING_LEFT;
		if ((state == WKOOPA_STATE_JUMPING || state == WKOOPA_STATE_JUMPING_TIMEOUT)
			&& vx > 0)
			aniId = ID_ANI_WKOOPA_JUMPING_RIGHT;
	
		else if (state == WKOOPA_STATE_WALKING)
		{
			if (vx > 0)
				aniId = ID_ANI_WKOOPA_WALKING_RIGHT;
			if (vx < 0)
				aniId = ID_ANI_WKOOPA_WALKING_LEFT;
		}

		else if (state == WKOOPA_STATE_SHELL || state == WKOOPA_STATE_KICK_LEFT || state == WKOOPA_STATE_KICK_RIGHT)
		{
			aniId = ID_ANI_WKOOPA_SHELL;
		}
		else if (state == WKOOPA_STATE_REVIVE)
		{
			aniId = ID_ANI_WKOOPA_REVIVE;
		}
	}
		
}

void CWingKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		//shell
	case WKOOPA_STATE_SHELL:
		shell_start = GetTickCount64();

		y += (WKOOPA_BBOX_HEIGHT - WSHELL_BBOX_HEIGHT) / 2;
		pre_vx = vx;
		vx = 0;
		//vy = 0;
		ay = 0;
		break;

		//idle
	case WKOOPA_STATE_IDLE:

		vx = 0;
		ay = WKOOPA_GRAVITY;
		break;
		x = default_x;
		y = default_y - 3;
		//walking
	case WKOOPA_STATE_WALKING:
		y = default_y - 3;
		if (pre_vx > 0)
			vx = -WKOOPA_WALKING_SPEED;
		else if (pre_vx < 0)
			vx = WKOOPA_WALKING_SPEED;
		else
			vx = -WKOOPA_WALKING_SPEED;

		break;

		//revive
	case WKOOPA_STATE_REVIVE:
		revive_start = GetTickCount64();
		break;

		//kick
	case WKOOPA_STATE_KICK_RIGHT:
		y -= 3;
		vx = WKOOPA_SHELL_SPEED;
		ay = WKOOPA_GRAVITY;
		die_timeout = GetTickCount64();
		break;
	case WKOOPA_STATE_KICK_LEFT:
		y -= 3;
		die_timeout = GetTickCount64();
		vx = -WKOOPA_SHELL_SPEED;
		ay = WKOOPA_GRAVITY;
		break;

	case WKOOPA_STATE_JUMPING:
		ay = -WKOOPA_JUMP_SPEED;
		fly_time = GetTickCount64();

		break;

	case WKOOPA_STATE_JUMPING_TIMEOUT:
		if (vy < 0)
			ay = WKOOPA_JUMP_SPEED;
		else
			ay = WKOOPA_GRAVITY;

		fly_timeout = GetTickCount64();
		break;
	case WKOOPA_STATE_HIDDEN:
		x = default_x;
		y = default_y - 3;
		vx = 0;
		ay = WKOOPA_GRAVITY;
		break;
	}

}
