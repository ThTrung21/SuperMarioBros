#include "GoldBrick.h"
#include "Mario.h"
#include "Pwr_btn.h"
CGoldBrick::CGoldBrick(float x, float y, int brick_type):CGameObject(x,y)
{
	this->interact = brick_type;
	this->max_y = y - 4;
	this->Y = y;
	this->X = x;
	mario_level = -1;
	SetState(GBRICK_STATE_NEW,mario_level);
}

void CGoldBrick::Render()
{
	int aniID = ID_ANI_GOLD_BRICK;
	if (state == GBRICK_STATE_USED)
		aniID = ID_ANI_GOLD_BRICK_USED;
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniID)->Render(x, y);
	
}

void CGoldBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - GBRICK_BBOX_WIDTH / 2;
	t = y - GBRICK_BBOX_HEIGHT / 2;
	r = l + GBRICK_BBOX_WIDTH;
	b = t + GBRICK_BBOX_HEIGHT;
}
void CGoldBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x = X;
	//y = Y;
	if (state == GBRICK_STATE_USED)
	{
		y = Y;
		return;
	}
	if (y <= max_y)
	{
		vy = GBRICK_BOUNCE_SPEED;

	}
	if (y > Y)
	{
		y = Y;
		return;
	}
	if (y >= Y && state == GBRICK_STATE_BOUNCE && (interact == 0 
		||(interact==1 && mario_level == MARIO_LEVEL_SMALL) ) )
	{
		vy = 0;
		y = Y;
		SetState(GBRICK_STATE_NEW,1);
	}

	else if (y >= Y && state == GBRICK_STATE_BOUNCE && interact==1 && mario_level !=MARIO_LEVEL_SMALL)
	{
		vy = 0;
		y = Y;
		SetState(GBRICK_STATE_USED, mario_level);
	}
	y += vy * dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CGoldBrick::SetState(int state,int mario_level)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GBRICK_STATE_NEW:
		vy = 0;
		break;

	case GBRICK_STATE_BOUNCE:
		this->mario_level = mario_level;
		vy = -GBRICK_BOUNCE_SPEED;
	case GBRICK_STATE_USED:
		y = Y;
		break;
	}
}


//
//void CGoldBrick::OnCollisionWith(LPCOLLISIONEVENT e)
//{
//	
//	if (interact == 2)return;
//	
//	if (dynamic_cast<CBtn*>(e->obj)  /*&& e->ny != 0*/)
//	{
//		DebugOut(L"BTNNNNN\n");
//		CBtn* b = dynamic_cast<CBtn*>(e->obj);
//		b->SetState(BTN_STATE_USED);
//	}
//}