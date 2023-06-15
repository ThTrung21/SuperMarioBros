#include"FireBall.h"
#include "Mario.h"
#include "Game.h"
#include "PlayScene.h"
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
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	int mx = mario->GetX();
	
	
	
		if(mx<this->x)
			//SetState
	




	CGameObject::Update(dt, coObjects);
}

void CFireBall::Render()
{
	int aniID;
	if (dir < FIREBALL_DIR_TOP_RIGHT)
		aniID = ID_ANI_FIREBALL_LEFT;
	else
		aniID = ID_ANI_FIREBALL_RIGHT;


	CAnimations::GetInstance()->Get(aniID)->Render(x, y);
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
	this->dir = dir;
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
