#include "FirePlant_Short.h"
#include "debug.h"
#include "FireBall.h"



CFirePlant_Short::CFirePlant_Short(float x, float y) :CGameObject(x, y)
{
	stop_start = -1;
	IsMoving = true;
	this->vy = SHORT_PLANT_SPEED;
	this->TopPos = y - 8;
	this->BotPos = y + 16;
	SetDir(SHORT_PLANT_DIR_TOPLEFT);
	SetState(SHORT_PLANT_STATE_AWAKE);
	this->default_y = y;
	this->default_x = x;
	this->isShooting = false;

}
bool CFirePlant_Short::MarioDetection(int mario_x, int mario_y)
{
	int xx = mario_x - (int)x;
	if (abs(xx) > 24 && abs(xx) < 150)
		return 1;
	return 0;

}
void CFirePlant_Short::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{


	//set the plant moving logic
	if (state == SHORT_PLANT_STATE_AWAKE)
	{
		y += vy * dt;
		if (y <= TopPos || y >= BotPos)
		{
			SetState(SHORT_PLANT_STATE_STOP);
		}

		return;
	}

	else if (state == SHORT_PLANT_STATE_STOP)
	{

		if (GetTickCount64() - stop_start > SHORT_PLANT_STOP_TIMEOUT)
		{

			SetState(SHORT_PLANT_STATE_AWAKE);
		}

	}

	//DETECTING MARIO POSITION
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	int mario_x, mario_y;
	mario_x = mario->GetX();
	mario_y = mario->GetY();


	//respawn detector
	if (state == SHORT_PLANT_STATE_DIE && RespawnDetector(mario_x) == 1)
	{
		SetState(SHORT_PLANT_STATE_AWAKE);
	}

	if (MarioDetection(mario_x, mario_y) == true)
	{
		if (state == SHORT_PLANT_STATE_SLEEP)
			SetState(SHORT_PLANT_STATE_AWAKE);
	}
	else if (y >= default_y)
		SetState(SHORT_PLANT_STATE_SLEEP);

	//Fireball shooting logic
	CFireBall* fireball = (CFireBall*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetFireBall();

	/*if (isShooting)
	{

		if (mario_x < x)
		{
			if (abs(mario_y - TopPos) >= 16 && mario_y < TopPos)
			{
				fireball->SetState(FIREBALL_DIR_TOP_LEFT);
			}
			else if (abs(mario_y - TopPos) < 16 && mario_y < TopPos)
			{
				fireball->SetState(FIREBALL_DIR_UPMID_LEFT);

			}
			else if (abs(mario_y - TopPos) < 16 && mario_y > TopPos)
			{
				fireball->SetState(FIREBALL_DIR_LOMID_LEFT);

			}
			else if (abs(mario_y - TopPos) >= 16 && mario_y > TopPos)
				fireball->SetState(FIREBALL_DIR_BOT_LEFT);

		}
		else
		{
			if (abs(mario_y - TopPos) >= 16 && mario_y < TopPos)
				fireball->SetState(FIREBALL_DIR_TOP_RIGHT);

			else if (abs(mario_y - TopPos) < 16 && mario_y < TopPos)
				fireball->SetState(FIREBALL_DIR_UPMID_RIGHT);

			else if (abs(mario_y - TopPos) < 16 && mario_y > TopPos)
				fireball->SetState(FIREBALL_DIR_LOMID_RIGHT);
			else if (abs(mario_y - TopPos) >= 16 && mario_y > TopPos)
				fireball->SetState(FIREBALL_DIR_BOT_RIGHT);

		}



	}*/


	//set the plant direction according to mario position.
	if (mario_x <= x && mario_y <= y)
		SetDir(SHORT_PLANT_DIR_TOPLEFT);
	else if (mario_x < x && mario_y > y)
		SetDir(SHORT_PLANT_DIR_BOTTOMLEFT);
	else if (mario_x > x && mario_y < y)
		SetDir(SHORT_PLANT_DIR_TOPRIGHT);
	else if (mario_x > x && mario_y > y)
		SetDir(SHORT_PLANT_DIR_BOTTOMRIGHT);
	else
		SetState(this->state);





	CGameObject::Update(dt, coObjects);
}

void CFirePlant_Short::Render()
{
	if (state != SHORT_PLANT_STATE_DIE)
	{
		int aniID = ID_ANI_SHORT_FIREPLANT_TOPLEFT;
		switch (direction)
		{
		case SHORT_PLANT_DIR_TOPLEFT:
			aniID = ID_ANI_SHORT_FIREPLANT_TOPLEFT;
			break;
		case SHORT_PLANT_DIR_BOTTOMLEFT:
			aniID = ID_ANI_SHORT_FIREPLANT_BOTTOMLEFT;
			break;
		case SHORT_PLANT_DIR_TOPRIGHT:
			aniID = ID_ANI_SHORT_FIREPLANT_TOPRIGHT;
			break;
		case SHORT_PLANT_DIR_BOTTOMRIGHT:
			aniID = ID_ANI_SHORT_FIREPLANT_BOTTOMRIGHT;
			break;
		default:
			aniID = ID_ANI_SHORT_FIREPLANT_TOPLEFT;
		}

		CAnimations::GetInstance()->Get(aniID)->Render(x, y);
	}
	RenderBoundingBox();
}

void CFirePlant_Short::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - SHORT_PLANT_WIDTH / 6;
	top = y - SHORT_PLANT_HEIGHT / 6;
	right = x + SHORT_PLANT_WIDTH - 3;
	bottom = y + SHORT_PLANT_HEIGHT - 6;
}

void CFirePlant_Short::OnNoCollision(DWORD dt)
{


}

void CFirePlant_Short::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->obj->IsBlocking())return;
}

bool CFirePlant_Short::RespawnDetector(int mario_x)
{
	int xx = mario_x - (int)x;
	if (abs(xx) > 250)
		return 1;
	return 0;
}

void CFirePlant_Short::SetState(int state)
{
	float prev_vy = 0;

	CGameObject::SetState(state);

	switch (state)
	{
	case SHORT_PLANT_STATE_STOP:
	{

		if (y <= TopPos)
			isShooting = true;

		prev_vy = vy;
		vy = 0;
		stop_start = GetTickCount64();
		break;
	}
	case SHORT_PLANT_STATE_AWAKE:
	{

		isShooting = false;

		//if (prev_vy != 0)
		if (y <= TopPos)
			vy = SHORT_PLANT_SPEED;
		else if (y >= BotPos)
			vy = -SHORT_PLANT_SPEED;




		break;
	}
	case SHORT_PLANT_STATE_SLEEP:

		isShooting = false;
		vy = 0;
		y = BotPos;

	case SHORT_PLANT_STATE_DIE:
		x = default_x;
		vy = 0;
		y = default_y;
		isShooting = false;
		break;
	
	}
}

void CFirePlant_Short::SetDir(int direction)
{
	this->direction = direction;
}