#include "FirePlant.h"
#include "debug.h"

CFirePlant::CFirePlant(float x, float y) :CGameObject(x,y)
{
	stop_start = -1;
	IsMoving = true;
	this->vy = PLANT_SPEED;
	this->TopPos = y - 16;
	this->BotPos = y + 16;
	state = PLANT_DIR_TOPLEFT;
	this->default_y = y;

}
void CFirePlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	float mario_x, mario_y;
	mario->GetPosition(mario_x, mario_y);
	float distance = mario_x -x;
	DebugOut(L"[INFO] position is %d \n", x);
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
	bool movelock = 0;
	
	
	if (IsMoving)
		this->y += vy*dt;

	if (y <= TopPos)
	{
		IsMoving = false;
		vy = 0;
		stop_start = GetTickCount64();
		
	}
	else if (y >= BotPos)
	{
		IsMoving = false;
		vy = 0;
		stop_start = GetTickCount64();
		
	}

	DebugOut(L"[INFO] time right now is %d\n", GetTickCount64() - stop_start < PLANT_MOVE_TIMEOUT);
	if (GetTickCount64() - stop_start < PLANT_MOVE_TIMEOUT)
		//movelock = 1;

	if (!IsMoving && y <= TopPos && !movelock)
	{
		IsMoving = true;
		DebugOut(L"[INFO] can move down\n");

		vy = -PLANT_SPEED;
	}
	else if (!IsMoving && y >= BotPos && !movelock )
	{
		IsMoving = true;
		vy = PLANT_SPEED;
		DebugOut(L"[INFO] plant speed is: ", vy,"\n");
		DebugOut(L"[INFO] can move up\n");
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