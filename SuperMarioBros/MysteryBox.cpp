#include "MysteryBox.h"
#include"debug.h"
void CBox::Render()
{
	int aniID = ID_ANI_BOX;
	if (state == BOX_STATE_USED)
		aniID = ID_ANI_BOX_USED;
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniID)->Render(x, y);
	
	//RenderBoundingBox();
}

CBox::CBox(float x, float y,int content):CGameObject(x, y)
{
	state = ID_ANI_BOX;
	icontent = content;
	this->max_y = (int)y - 4;
	this->Y = (int)y;
	vy = 0;
}
void CBox::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BOX_STATE_BOUNCE:
		vy = -BOX_BOUNCE_SPEED;
		
		break;
	case BOX_STATE_USED:
		

		break;
	}
}
void CBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BOX_BBOX_WIDTH / 2;
	t = y - BOX_BBOX_HEIGHT / 2;
	r = l + BOX_BBOX_WIDTH;
	b = t + BOX_BBOX_HEIGHT;
}

int CBox::GetContent()
{
	return icontent	;
}
void CBox::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;

	if (y <= max_y)
	{
		vy = BOX_BOUNCE_SPEED;
		
	}
	if (y >= Y && state==BOX_STATE_BOUNCE)
	{
		vy = 0;
		y = (int)Y;
		SetState(BOX_STATE_USED);
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

;


