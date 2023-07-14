#include "GoldBrick.h"
#include "Mario.h"
#include "Pwr_btn.h"
#include "Tail.h"
#include "PlayScene.h"

CGoldBrick::CGoldBrick(float x, float y, int brick_type,int id):CGameObject(x,y)
{
	this->interact = brick_type;
	this->max_y = y - 4;
	this->Y = y;
	this->X = x;
	this->id = id;
	hide_start = -1;
	SetState(GBRICK_STATE_NEW);
	
}

void CGoldBrick::Render()
{
	if (state != GBRICK_STATE_HIDDEN && state != GBRICK_STATE_BROKEN)
	{
		int aniID = ID_ANI_GOLD_BRICK;
		if (state == GBRICK_STATE_USED)
			aniID = ID_ANI_GOLD_BRICK_USED;
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(aniID)->Render(x, y);
	}
	//RenderBoundingBox();
}

void CGoldBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state != GBRICK_STATE_BROKEN && state != GBRICK_STATE_HIDDEN)
	{
		l = x - GBRICK_BBOX_WIDTH / 2;
		t = y - GBRICK_BBOX_HEIGHT / 2;
		r = l + GBRICK_BBOX_WIDTH;
		b = t + GBRICK_BBOX_HEIGHT;
	}
}
void CGoldBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;
	x = X;

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (state == GBRICK_STATE_USED)
	{
		vy = 0;
		return;
	}
	if (y <= max_y )
	{
		vy = GBRICK_BOUNCE_SPEED;
	}
	
	if (y != Y &&state==GBRICK_STATE_NEW)
	{
		y = Y;
	
	}
#pragma region brick_with_button

	if (y >= Y && state == GBRICK_STATE_BOUNCE  && mario->GetLevel() == MARIO_LEVEL_SMALL)
	{
		vy = 0;
		
		SetState(GBRICK_STATE_NEW);
	}

	else if (y >= Y && state == GBRICK_STATE_BOUNCE && interact==1 && mario->GetLevel() !=MARIO_LEVEL_SMALL)
	{
		vy = 0;
		
		SetState(GBRICK_STATE_USED);
	}
#pragma endregion


#pragma region reappear_when_times_up
	if (state == GBRICK_STATE_HIDDEN &&(GetTickCount64() - hide_start > TIME_HIDDEN))
	{
		
		if (!isForceBreak)
		{
			SetState(GBRICK_STATE_NEW);
			
		}
		else
		{
			
			isDeleted = true;
			//return;
		}
	}
#pragma endregion

	//brick disapear when button push
#pragma region button_pushed_logic
	CBtn* button = (CBtn*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetButton();
	if (button->GetState() == BTN_STATE_USED)
	{
		if (interact == 2 && state == GBRICK_STATE_NEW)
		{
			SetState(GBRICK_STATE_HIDDEN);

			//return;
		}
		
			//isDeleted = true;
	}
#pragma endregion


	CGameObject::Update(dt, coObjects);
	//CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CGoldBrick::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CTail*>(e->obj))
	{
		CTail* tail = dynamic_cast<CTail*>(e->obj);
		if (tail->GetState() == TAIL_STATE_ACTIVE)
		{
			if (interact == 1)
				SetState(GBRICK_STATE_USED);
			else
			{
				DebugOut(L"TAIL TOUCH BRICK\n");
				CGoldBrick* brick = (CGoldBrick*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetIdGoldBrick(GetId());
				CHiddenCoin* coin = (CHiddenCoin*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetIdCoins(GetId());
				brick->SetForceBreak(true);
				coin->SetDestroy(true);
				brick->SetState(GBRICK_STATE_HIDDEN);
			}
		}

	}
}

void CGoldBrick::SetState(int state)
{
	
	CGameObject::SetState(state);
	switch (state)
	{
	case GBRICK_STATE_NEW:
		vy = 0;
		x = X;
		y = Y;
		break;
	

	case GBRICK_STATE_BOUNCE:
		
		vy = -GBRICK_BOUNCE_SPEED;
	case GBRICK_STATE_USED:
		y = Y;
		break;

	case GBRICK_STATE_HIDDEN:
		hide_start = GetTickCount64();
		break;
	case GBRICK_STATE_BROKEN:
		break;
	}
}


