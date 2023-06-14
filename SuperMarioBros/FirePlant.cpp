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