#include "FirePlant.h"

CFirePlant::CFirePlant(float x, float y) :CGameObject(x,y)
{
	this->vy = -1;
	state = PLANT_DIR_TOPLEFT;
}
void CFirePlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	//set the plant direction according to mario position.
	float mario_x, mario_y;
	mario->GetPosition(mario_x, mario_y);
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