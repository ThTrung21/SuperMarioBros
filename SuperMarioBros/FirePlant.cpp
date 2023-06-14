#include "FirePlant.h"

CFirePlant::CFirePlant(float x, float y) :CGameObject(x,y)
{
	
	IsMoving = true;
	this->vy = PLANT_SPEED;
	this->TopPos = y - 32;
	this->BotPos = y + 32;
	state = PLANT_DIR_TOPLEFT;
	this->default_y = y;

}
void CFirePlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	float mario_x, mario_y;
	mario->GetPosition(mario_x, mario_y);
	//set the plant direction according to mario position.
	if (mario_x <= x && mario_y <= y)
		SetState(PLANT_DIR_TOPLEFT);
	else if (mario_x < x && mario_y > y)
		SetState(PLANT_DIR_BOTTOMLEFT);
	else if (mario_x > x && mario_y < y)
		SetState(PLANT_DIR_TOPRIGHT);
	else if (mario_x > x && mario_y > y)
		SetState(PLANT_DIR_BOTTOMRIGHT);
	else
		SetState(this->state);

	//set the plant moving logic
	if (IsMoving)
		y += vy;

	if (y <= TopPos) 
	{
		IsMoving = false;
		vy = 0;
	}
	else if (y >= BotPos)
	{
		IsMoving = false;
		vy = 0;
	}
	if (IsMoving && y < default_y && abs(mario_x - x) <= 16)
		IsMoving = false;

	if (this->IsMoving == false)
	{
		MoveDelay = GetTickCount64();

		if (GetTickCount64() - MoveDelay > PLANT_MOVE_TIMEOUT)
		{
			IsMoving = false;
			if (y >= TopPos)
				vy = -PLANT_SPEED;
			else if(y<=BotPos)
				vy = PLANT_SPEED;
		}

	}


	CGameObject::Update(dt, coObjects);
}

void CFirePlant::Render()
{
	int aniID = ID_ANI_FIREPLANT_TOPLEFT;
	switch (state)
	{
	case PLANT_DIR_TOPLEFT:
		aniID = /*120001;*/ ID_ANI_FIREPLANT_TOPLEFT;	
		break;
	case PLANT_DIR_BOTTOMLEFT:
		aniID = /*120003;*/ID_ANI_FIREPLANT_BOTTOMLEFT;	
		break;
	case PLANT_DIR_TOPRIGHT:
		aniID = /*120005;*/ID_ANI_FIREPLANT_TOPRIGHT;	
		break;
	case PLANT_DIR_BOTTOMRIGHT:
		aniID = /*120007;*/ID_ANI_FIREPLANT_BOTTOMRIGHT;	
		break;
	default:
		aniID = ID_ANI_FIREPLANT_TOPLEFT;
	}
	
	CAnimations::GetInstance()->Get(aniID)->Render(x, y);
	
}

void CFirePlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - PLANT_WIDTH / 2;
	top = y - PLANT_HEIGHT / 2;
	right = x + PLANT_WIDTH;
	bottom = y + PLANT_HEIGHT;
}

void CFirePlant::OnNoCollision(DWORD dt)
{
	
}

void CFirePlant::OnCollisionWith(LPCOLLISIONEVENT e)
{

}
void CFirePlant::SetState(int state)
{	
	CGameObject::SetState(state);
}