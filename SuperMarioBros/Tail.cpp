#include "Tail.h"

#include "Koopa.h"
#include "WingKoopa.h"

#include "FirePlant.h"
#include "FirePlant_Short.h"
#include "GoldBrick.h"
#include"MysteryBox.h"
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

	
	y = mario_y + 4;
	x = mario_x;

	if (state == TAIL_STATE_ACTIVE)
	{
		if (mario->Getnx() > 0)
		{
			x = mario_x + MARIO_BIG_BBOX_WIDTH+4 ;
			slaptime = GetTickCount64();

			//x = mario_x - MARIO_BIG_BBOX_WIDTH + 4;
		}
		else if (mario->Getnx() < 0)
		{
			x = mario_x - TAIL_WIDTH -6;
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
	if (state == TAIL_STATE_IDLE)
		return;
	else
	{
		DebugOut(L"tail active\n");
		if (dynamic_cast<CKoopa*>(e->obj))
		{
			CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
			if(koopa->GetState() != KOOPA_STATE_HOLD && koopa->GetState() != KOOPA_STATE_HIDDEN
				)
				koopa->SetState(KOOPA_STATE_HIT);
			
		}

		if (dynamic_cast<CFirePlant*>(e->obj))
		{
			CFirePlant* f = dynamic_cast<CFirePlant*>(e->obj);
			if (f->GetState() != PLANT_STATE_DIE)
				f->SetState(PLANT_STATE_DIE);
		}
		if (dynamic_cast<CGoldBrick*>(e->obj))
		{
			DebugOut(L"TAIL TOUCH BRICK\n");
			CGoldBrick* gb = dynamic_cast<CGoldBrick*>(e->obj);
			if (gb->GetState() == GBRICK_STATE_NEW)
			{
				if (gb->GetType() == 1)
				{
					gb->SetState(GBRICK_STATE_USED);
				}
				else
				{
					CGoldBrick* brick = (CGoldBrick*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetIdGoldBrick(gb->GetId());
					CHiddenCoin* coin = (CHiddenCoin*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetIdCoins(gb->GetId());
					brick->SetForceBreak(true);
					//e->obj->Delete();
					coin->SetDestroy(true);
					brick->SetState(GBRICK_STATE_HIDDEN);
				}
			}
		}
		if (dynamic_cast<CBox*>(e->obj))
		{
			CBox* b = dynamic_cast<CBox*>(e->obj);
			if (b->GetState() != BOX_STATE_USED)
			{
				b->SetState(BOX_STATE_USED);
			}
		}

	}
}

void CTail::OnNoCollision(DWORD dt)
{
	x = x; y = y;
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
