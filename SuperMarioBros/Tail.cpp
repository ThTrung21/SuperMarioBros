#include "Tail.h"

CTail::CTail(float x, float y) :CGameObject(x,y)
{

	SetState(TAIL_STATE_IDLE);

}
void CTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float mario_x, mario_y;
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	/*float mario_vx, mario_vy;
	mario->GetSpeed(mario_vx, mario_vy);*/
	mario_x=mario->GetX();
	mario_y = mario->GetY();
	/*vy = mario_vy;
	vx = mario_vx;*/
	
	y = mario_y + 6;
	x = mario_x - 8;
	//if (state == TAIL_STATE_ACTIVE)
	//{
	//	/*if (mario->Getnx() > 0)
	//	{
	//		x = mario_x + MARIO_BIG_BBOX_WIDTH - 2;
	//		slaptime = GetTickCount64();
	//		
	//	}
	//	else if (mario->Getnx() < 0)
	//	{
	//		x = mario_x - TAIL_WIDTH ;
	//		slaptime = GetTickCount64();
	//	}*/
	//}
	//else
	//	if (mario->Getnx() > 0)
	//		x = mario_x - TAIL_WIDTH + 2;
	//	else if (mario->Getnx() < 0)
	//		x = mario_x + MARIO_BIG_BBOX_WIDTH - 4;

		
		
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}




void CTail::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x-8;// -TAIL_WIDTH / 2;
	top = y  - TAIL_HEIGHT / 2;
	right = x + MARIO_BIG_BBOX_WIDTH+16;
	bottom = top + TAIL_HEIGHT;
}
