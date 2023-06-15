#include"FireBall.h"

CFireBall::CFireBall(float x, float y):CGameObject(x,y)
{
	state = FIREBALL_STATE_HIDDEN;
	this->X = x;
	this->Y = y;
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
}

void CFireBall::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_FIREBALL_LEFT)->Render(x, y);
}

void CFireBall::ResetPos()
{
	x = X;
	y = Y;
}

void CFireBall::SetState(int state)
{

}

void CFireBall::SetDir(int dir)
{
	switch (dir)
	{
		//left side
	case FIREBALL_DIR_TOP_LEFT:
		vy = FIREBALL_SPEED_Y_FAST;
		vx = -FIREBALL_SPEED_X_SLOW;
		ResetPos();
		break;
	case FIREBALL_DIR_UPMID_LEFT:
		vy = FIREBALL_SPEED_Y_SLOW;
		vx = -FIREBALL_SPEED_X_FAST;
		ResetPos();
		break;
	case FIREBALL_DIR_LOMID_LEFT:
		vy = -FIREBALL_SPEED_Y_SLOW;
		vx = -FIREBALL_SPEED_X_FAST;
		ResetPos();
		break;
	case FIREBALL_DIR_BOT_LEFT:
		vy = -FIREBALL_SPEED_Y_FAST;
		vx = -FIREBALL_SPEED_X_SLOW;
		ResetPos();
		break;
		
		//right side
	case FIREBALL_DIR_TOP_RIGHT:
		vy = FIREBALL_SPEED_Y_FAST;
		vx = FIREBALL_SPEED_X_SLOW;
		ResetPos();
		break;
	case FIREBALL_DIR_UPMID_RIGHT:
		vy = FIREBALL_SPEED_Y_SLOW;
		vx = FIREBALL_SPEED_X_FAST;
		ResetPos();
		break;
	case FIREBALL_DIR_LOMID_RIGHT:
		vy = -FIREBALL_SPEED_Y_SLOW;
		vx = FIREBALL_SPEED_X_FAST;
		ResetPos();
		break;
	case FIREBALL_DIR_BOT_RIGHT:
		vy = -FIREBALL_SPEED_Y_FAST;
		vx = FIREBALL_SPEED_X_SLOW;
		ResetPos();
		break;
	}
}
