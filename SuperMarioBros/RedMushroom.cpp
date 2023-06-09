#include "RedMushroom.h"

CMushroom::CMushroom(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = MUSHROOM_GRAVITY;
	//this->vx = 0;
	//this->vy = 0;
	SetState(MUSHROOM_STATE_SHOW);
}

void CMushroom::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_MUSHROOM_RED)->Render(x, y);
	
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
	vx += ax * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case MUSHROOM_STATE_SHOW:
			//y -= 64;
			vx =  -MUSHROOM_SPEED;
			//this->ay = MUSHROOM_GRAVITY;
			break;
		case MUSHROOM_STATE_HIDDEN:
			vx = 0;
			vy = 0;
			ay = 0;
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
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CMushroom*>(e->obj)) return;

	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}