#include "Chomper.h"
#include "debug.h"




CChomper::CChomper(float x, float y) :CGameObject(x, y)
{
	stop_start = -1;
	IsMoving = true;
	this->vy = CHOMPER_SPEED;
	this->TopPos = y - 8;
	this->BotPos = y + 16;
	this->default_y = y;
	this->default_x = x;
	SetState(CHOMPER_STATE_AWAKE);
	

}
bool CChomper::MarioDetection(int mario_x, int mario_y)
{
	int xx = mario_x - (int)x;
	if (abs(xx) > 24 && abs(xx) < 150)
		return 1;
	return 0;

}
void CChomper::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{


	//set the plant moving logic
	if (state == CHOMPER_STATE_AWAKE)
	{
		y += vy * dt;
		if (y <= TopPos || y >= BotPos)
		{
			SetState(CHOMPER_STATE_STOP);
		}

		return;
	}

	else if (state == CHOMPER_STATE_STOP)
	{

		if (GetTickCount64() - stop_start > CHOMPER_STOP_TIMEOUT)
		{

			SetState(CHOMPER_STATE_AWAKE);
		}

	}

	//DETECTING MARIO POSITION
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	int mario_x, mario_y;
	mario_x = mario->GetX();
	mario_y = mario->GetY();





	//respawn detector
	if (state == CHOMPER_STATE_DIE && RespawnDetector(mario_x) == 1)
	{
		SetState(CHOMPER_STATE_AWAKE);
	}

	if (MarioDetection(mario_x, mario_y) == true)
	{
		if (state == CHOMPER_STATE_SLEEP)
			SetState(CHOMPER_STATE_AWAKE);
	}
	else if (y >= default_y)
		SetState(CHOMPER_STATE_SLEEP);



	CGameObject::Update(dt, coObjects);
}

void CChomper::Render()
{
	if (state != CHOMPER_STATE_DIE)
	{
		int aniID = ID_ANI_CHOMPER;

		CAnimations::GetInstance()->Get(aniID)->Render(x, y);
		RenderBoundingBox();
	}
}

void CChomper::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - CHOMPER_WIDTH / 6;
	top = y - CHOMPER_HEIGHT / 6;
	right = x + CHOMPER_WIDTH - 3;
	bottom = y + CHOMPER_HEIGHT - 6;
}

void CChomper::OnNoCollision(DWORD dt)
{


}

void CChomper::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->obj->IsBlocking())return;
}


void CChomper::SetState(int state)
{
	float prev_vy = 0;

	CGameObject::SetState(state);

	switch (state)
	{
	case CHOMPER_STATE_STOP:
	{



		prev_vy = vy;
		vy = 0;
		stop_start = GetTickCount64();
		break;
	}
	case CHOMPER_STATE_AWAKE:
	{



		//if (prev_vy != 0)
		if (y <= TopPos)
			vy = CHOMPER_SPEED;
		else if (y >= BotPos)
			vy = -CHOMPER_SPEED;




		break;
	}
	case CHOMPER_STATE_SLEEP:
		vy = 0;
		y = BotPos;
		break;

	case CHOMPER_STATE_DIE:
		x = default_x;
		y = default_y;
		vy = 0;
		break;
	}
}
bool CChomper::RespawnDetector(int mario_x)
{
	int xx = mario_x - (int)x;
	if (abs(xx) > 250)
		return 1;
	return 0;
}
