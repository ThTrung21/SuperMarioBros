#include "RedMushroom.h"

CMushroom::CMushroom(float x, float y,int color) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	this->color = color;
	moveDelay = -1;
	SetState(MUSHROOM_STATE_HIDDEN);
}

void CMushroom::Render()
{

	CAnimations* animations = CAnimations::GetInstance();
	if(color==1)
		animations->Get(ID_ANI_MUSHROOM_RED)->Render(x, y);
	else if(color==2)
		animations->Get(ID_ANI_MUSHROOM_GREEN)->Render(x, y);
	//RenderBoundingBox();
}

void CMushroom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MUSHROOM_BBOX_WIDTH / 2;
	t = y - MUSHROOM_BBOX_HEIGHT / 2;
	r = l + MUSHROOM_BBOX_WIDTH;
	b = t + MUSHROOM_BBOX_HEIGHT;
}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{	
	vy += ay * dt;
	
	if (state == MUSHROOM_STATE_SHOW && (GetTickCount64() - moveDelay > MUSHROOM_MOVE_WAITTIME)) 
		SetState(MUSHROOM_STATE_MOVE);
	
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case MUSHROOM_STATE_SHOW:
			moveDelay = GetTickCount64();
			direction = GetTickCount64();
			vy = -0.03f;
			break;
		case MUSHROOM_STATE_MOVE:
			if(direction%2==0)
				vx = MUSHROOM_SPEED;
			else
			{
				vx = -MUSHROOM_SPEED;
			}
			vy = 0;
			ay = MUSHROOM_GRAVITY;
			break;
	}
}

void CMushroom::OnNoCollision(DWORD dt)
{		
		x += vx * dt;
		y += vy * dt;
};

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	
	
	if (state == MUSHROOM_STATE_MOVE) 
	{
		if (!e->obj->IsBlocking()) return;
		if (e->ny != 0)
		{
			vy = 0;
		}
		else if (e->nx != 0)
		{
			vx = -vx;
		}
	}
}