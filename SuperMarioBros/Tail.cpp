#include "Tail.h"
#include "Koopa.h"
#include "WingKoopa.h"
CTail::CTail(float x, float y) :CGameObject(x,y)
{

	SetState(TAIL_STATE_IDLE);

}
void CTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float mario_x, mario_y;
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	mario_x= (float)mario->GetX();
	mario_y = (float)mario->GetY();

	
	y = mario_y + 6;
	x = mario_x;

	if (state == TAIL_STATE_ACTIVE)
	{
		if (mario->Getnx() > 0)
		{
			x = mario_x + MARIO_BIG_BBOX_WIDTH - 4;
			slaptime = GetTickCount64();

			//x = mario_x - MARIO_BIG_BBOX_WIDTH + 4;
		}
		else if (mario->Getnx() < 0)
		{
			x = mario_x - TAIL_WIDTH + 2;
			slaptime = GetTickCount64();
			//x = mario_x + TAIL_WIDTH - 2;
		}
	}
	else
		if (mario->Getnx() > 0)
			x = mario_x - TAIL_WIDTH + 2;
		else if (mario->Getnx() < 0)
			x = mario_x + MARIO_BIG_BBOX_WIDTH - 4;
		
		
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CTail::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (state == TAIL_STATE_ACTIVE)
	{
		if (dynamic_cast<CKoopa*>(e->obj))
		{
			CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
			if (koopa->GetState() == KOOPA_STATE_SHELL)
				koopa->SetState(KOOPA_STATE_HIT);

		}
	}
}




void CTail::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - TAIL_WIDTH / 2;
	top = y - TAIL_HEIGHT / 2;
	right = x + TAIL_WIDTH;
	bottom = top + TAIL_HEIGHT;
	//left = x-2;// -TAIL_WIDTH / 2;
	//top = y  - TAIL_HEIGHT / 2;
	//right = x + (MARIO_BIG_BBOX_WIDTH/2)+20;
	//bottom = top + TAIL_HEIGHT;
}
