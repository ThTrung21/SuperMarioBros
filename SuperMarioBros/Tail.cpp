#include "Tail.h"

CTail::CTail(float x, float y) :CGameObject(x,y)
{

	SetState(TAIL_STATE_IDLE);

}
void CTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float mario_x, mario_y;
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	mario_x= (int)mario->GetX();
	mario_y = (int)mario->GetY();

	
	y = mario_y + 6;
	x = mario_x;


		
		
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}




void CTail::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x-2;// -TAIL_WIDTH / 2;
	top = y  - TAIL_HEIGHT / 2;
	right = x + (MARIO_BIG_BBOX_WIDTH/2)+20;
	bottom = top + TAIL_HEIGHT;
}
