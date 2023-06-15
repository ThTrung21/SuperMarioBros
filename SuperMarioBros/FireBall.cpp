#include"FireBall.h"
#include "Mario.h"
#include "Game.h"
#include "PlayScene.h"
void CFireBall::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}
void CFireBall::OnCollisionWith(LPCOLLISIONEVENT e)
{
	
}
CFireBall::CFireBall(float x, float y):CGameObject(x,y)
{
	state = FIREBALL_STATE_HIDDEN;
	this->X = x;
	this->Y = y;
	vx = 0;
	vy = 0;
	
}



void CFireBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - FIREBALL_WIDTH / 2;
	top = y - FIREBALL_HEIGHT / 2;
	right = x + FIREBALL_WIDTH;
	bottom = y + FIREBALL_HEIGHT;
}

void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CFireBall::Render()
{
	if (state != FIREBALL_STATE_HIDDEN)
	{
		int aniID = ID_ANI_FIREBALL_LEFT;
		/*if (state < FIREBALL_DIR_TOP_RIGHT)
			aniID = ID_ANI_FIREBALL_LEFT;
		else
			aniID = ID_ANI_FIREBALL_RIGHT;*/


		CAnimations::GetInstance()->Get(aniID)->Render(x, y);
	}
}

void CFireBall::ResetPos()
{
	x = X;
	y = Y;
}

//void CFireBall::SetState(int state)

void CFireBall::SetState(int direction)
{
	CGameObject::SetState(direction);
	switch (state)
	{
		//left side
	case FIREBALL_DIR_BOT_LEFT:
		vy = FIREBALL_SPEED_Y_FAST;
		vx = -FIREBALL_SPEED_X_SLOW;
		ResetPos();
		break;
	case FIREBALL_DIR_LOMID_LEFT:
		vy = FIREBALL_SPEED_Y_SLOW;
		vx = -FIREBALL_SPEED_X_FAST;
		ResetPos();
		break;
	case FIREBALL_DIR_UPMID_LEFT:
		vy = -FIREBALL_SPEED_Y_SLOW;
		vx = -FIREBALL_SPEED_X_FAST;
		ResetPos();
		break;
	case FIREBALL_DIR_TOP_LEFT:
		vy = -FIREBALL_SPEED_Y_FAST;
		vx = -FIREBALL_SPEED_X_SLOW;
		ResetPos();
		break;
		
		//right side
	case FIREBALL_DIR_BOT_RIGHT:
		vy = FIREBALL_SPEED_Y_FAST;
		vx = FIREBALL_SPEED_X_SLOW;
		ResetPos();
		break;
	case FIREBALL_DIR_LOMID_RIGHT:
		vy = FIREBALL_SPEED_Y_SLOW;
		vx = FIREBALL_SPEED_X_FAST;
		ResetPos();
		break;
	case FIREBALL_DIR_UPMID_RIGHT:
		vy = -FIREBALL_SPEED_Y_SLOW;
		vx = FIREBALL_SPEED_X_FAST;
		ResetPos();
		break;
	case FIREBALL_DIR_TOP_RIGHT:
		vy = -FIREBALL_SPEED_Y_FAST;
		vx = FIREBALL_SPEED_X_SLOW;
		ResetPos();
		break;
	}
}
