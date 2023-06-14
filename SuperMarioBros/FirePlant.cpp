#include "FirePlant.h"

CFirePlant::CFirePlant(float x, float y) :CGameObject(x,y)
{
	this->vy = -1;

}
void CFirePlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void CFirePlant::Render()
{
	int aniID; 
	switch (state)
	{
	case PLANT_DIR_TOPLEFT:
		aniID = ID_ANI_FIREPLANT_TOPLEFT;	break;
	case PLANT_DIR_BOTTOMLEFT:
		aniID = ID_ANI_FIREPLANT_BOTTOMLEFT;	break;
	case PLANT_DIR_TOPRIGHT:
		aniID = ID_ANI_FIREPLANT_TOPRIGHT;	break;
	case PLANT_DIR_BOTTOMRIGHT:
		aniID = ID_ANI_FIREPLANT_BOTTOMRIGHT;	break;
	}

	CAnimations::GetInstance()->Get(aniID)->Render(x, y);
	RenderBoundingBox();
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
	y += vy + dt;
}

void CFirePlant::OnCollisionWith(LPCOLLISIONEVENT e)
{

}
void CFirePlant::SetState(int state)
{	
	CGameObject::SetState(state);
}