#include "FirePlant.h"
#include "debug.h"
#include "FireBall.h"
#include "Tail.h"



CFirePlant::CFirePlant(float x, float y) :CGameObject(x,y)
{
	stop_start = -1;
	IsMoving = true;
	this->vy = PLANT_SPEED;
	this->TopPos = y - 16;
	this->BotPos = y + 16;
	SetDir(PLANT_DIR_TOPLEFT);
	SetState(PLANT_STATE_AWAKE);
	this->default_y = y;
	this->default_x = x;
	this->isShooting = false;

}
bool CFirePlant::MarioDetection(int mario_x, int mario_y)
{
	int xx = mario_x -(int) x;
	if (abs(xx)>24 && abs(xx)<150)
		return 1;
	return 0;

}
void CFirePlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	//DETECTING MARIO POSITION
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	int mario_x, mario_y;
	mario_x = mario->GetX();
	mario_y = mario->GetY();

	//respawn detector
	if (state == PLANT_STATE_DIE && RespawnDetector(mario_x) == 1)
	{
		SetState(PLANT_STATE_AWAKE);
	}
	if (state == PLANT_STATE_DIE)
		return;
	//detect mario
	if (MarioDetection(mario_x, mario_y) == true)
	{
		if (state == PLANT_STATE_SLEEP)
			SetState(PLANT_STATE_AWAKE);
	}
	else if(y>=default_y)
		SetState(PLANT_STATE_SLEEP);

	//set the plant moving logic
	if (state == PLANT_STATE_AWAKE)
	{
		y += vy * dt;
		if (y <= TopPos || y >= BotPos)
		{
			SetState(PLANT_STATE_STOP);
		}

		return;
	}

	else if (state == PLANT_STATE_STOP)
	{

		if (GetTickCount64() - stop_start > PLANT_STOP_TIMEOUT)
		{

			SetState(PLANT_STATE_AWAKE);
		}

	}


	//Fireball shooting logic

	CFireBall* fireball = (CFireBall*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetFireBall(1);


	if (isShooting)
	{
		
		if (mario_x < x)
		{
			if (abs(mario_y - TopPos) >= 32 && mario_y < TopPos)
			{
				fireball->SetState(FIREBALL_DIR_TOP_LEFT);
			}
			else if (abs(mario_y - TopPos) < 32 && mario_y < TopPos)
			{
				fireball->SetState(FIREBALL_DIR_UPMID_LEFT);
				
			}
			else if (abs(mario_y - TopPos) < 32 && mario_y > TopPos)
			{
				fireball->SetState(FIREBALL_DIR_LOMID_LEFT);
				
			}
			else if (abs(mario_y - TopPos) >= 32 && mario_y > TopPos)
					fireball->SetState(FIREBALL_DIR_BOT_LEFT);

		}
		else
		{
			if (abs(mario_y - TopPos) >= 32 && mario_y < TopPos)
				fireball->SetState(FIREBALL_DIR_TOP_RIGHT);

			else if (abs(mario_y - TopPos) < 32 && mario_y < TopPos)
					fireball->SetState(FIREBALL_DIR_UPMID_RIGHT);

			else if (abs(mario_y - TopPos) < 32 && mario_y > TopPos)
					fireball->SetState(FIREBALL_DIR_LOMID_RIGHT);
			else if (abs(mario_y - TopPos) >= 32 && mario_y > TopPos)
					fireball->SetState(FIREBALL_DIR_BOT_RIGHT);

		}



	}


	//set the plant direction according to mario position.
	if (mario_x <= x && mario_y <= y)
		SetDir(PLANT_DIR_TOPLEFT);
	else if (mario_x < x && mario_y > y)
		SetDir(PLANT_DIR_BOTTOMLEFT);
	else if (mario_x > x && mario_y < y)
		SetDir(PLANT_DIR_TOPRIGHT);
	else if (mario_x > x && mario_y > y)
		SetDir(PLANT_DIR_BOTTOMRIGHT);
	else
		SetState(this->state);

	
	


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CFirePlant::Render()
{
	if(state!=PLANT_STATE_DIE)
	{
		int aniID = ID_ANI_FIREPLANT_TOPLEFT;
		switch (direction)
		{
		case PLANT_DIR_TOPLEFT:
			aniID = ID_ANI_FIREPLANT_TOPLEFT;
			break;
		case PLANT_DIR_BOTTOMLEFT:
			aniID = ID_ANI_FIREPLANT_BOTTOMLEFT;
			break;
		case PLANT_DIR_TOPRIGHT:
			aniID = ID_ANI_FIREPLANT_TOPRIGHT;
			break;
		case PLANT_DIR_BOTTOMRIGHT:
			aniID = ID_ANI_FIREPLANT_BOTTOMRIGHT;
			break;
		default:
			aniID = ID_ANI_FIREPLANT_TOPLEFT;
		}

		CAnimations::GetInstance()->Get(aniID)->Render(x, y);
	}
	//RenderBoundingBox();
}

void CFirePlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - PLANT_WIDTH / 6;
	top = y - PLANT_HEIGHT / 6;
	right = x + PLANT_WIDTH-3;
	bottom = y + PLANT_HEIGHT-6;
}

void CFirePlant::OnNoCollision(DWORD dt)
{
	

}

void CFirePlant::OnCollisionWith(LPCOLLISIONEVENT e)
{
	
	if (dynamic_cast<CTail*>(e->obj))
	{
		DebugOut(L"TAIL HIT PLANT\n");
		CTail* tail = dynamic_cast<CTail*>(e->obj);
		if (tail->GetState() == TAIL_STATE_ACTIVE)
		{
			if (state != PLANT_STATE_DIE)
				SetState(PLANT_STATE_DIE);
			return;
		}
	}
	
}

bool CFirePlant::RespawnDetector(int mario_x)
{
	int xx = mario_x - (int)x;
	if (abs(xx) > 250)
		return 1;
	return 0;
}

void CFirePlant::SetState(int state)
{	
	float prev_vy=0;

	CGameObject::SetState(state);

	switch (state) 
	{
	case PLANT_STATE_STOP: 
	{
		
		if (y <= TopPos)
			isShooting = true;

		prev_vy = vy;
		vy = 0;
		stop_start = GetTickCount64();
		break;
	}
	case PLANT_STATE_AWAKE:
	{
		
		isShooting = false;

		
			if(y<=TopPos)
				vy = PLANT_SPEED;
			else if(y>=BotPos)
				vy = -PLANT_SPEED;
	
		break;
	}
	case PLANT_STATE_DIE:
	{
		vy = 0;
		x = default_x;
		y = default_y;
		isShooting = false;
		break;
	}
	case PLANT_STATE_SLEEP:
		
		isShooting = false;
		vy = 0;
		y = BotPos;
	}
}

void CFirePlant::SetDir(int direction)
{
	this->direction = direction;
}