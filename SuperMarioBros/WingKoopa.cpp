#include "WingKoopa.h"
#include "WingGoomba.h"
#include "Goomba.h"
#include "Tanuki_Leaf.h"
#include "MysteryBox.h"
#include "Koopa.h"
#include "Mario.h"
#include "debug.h"
#include "PlayScene.h"
#include"ColorBox.h"
#include "Invis_block.h"
#include "FirePlant.h"
#include "FirePlant_Short.h"
#include"Chomper.h"
#include "Tail.h"
#include "GoldBrick.h"
#include "Hidden_Coin.h"
CWingKoopa::CWingKoopa(float x, float y)
{
	Y = y;
	die_flag = 0;
	this->ax = 0;
	this->ay = WKOOPA_GRAVITY;
	revive_start = -1;
	flag = 0;
	fly_time = -1;
	fly_timeout = -1;
	shell_start = -1;
	revive_start = -1;
	pre_vx = 0;
	default_x = x;
	default_y = y;
	pop_height = (int)y - 20;
	SetState(WKOOPA_STATE_IDLE);

}

bool CWingKoopa::RespawnDetector(int mario_x)
{
	int xx = mario_x - (int)default_x;
	if (abs(xx) > 230)
		return 1;
	return 0;
}
void CWingKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (state == WKOOPA_STATE_HIT && e->ny != 0)
		SetState(WKOOPA_STATE_SHELL);
	else if (state == WKOOPA_STATE_HIT) return;
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CWingKoopa*>(e->obj))
		OnCollisionWithWingKoopa(e);
	if (dynamic_cast<CTail*>(e->obj))
	{
		CTail* tail = dynamic_cast<CTail*>(e->obj);
		if (tail->GetState() == TAIL_STATE_ACTIVE)
		{

			if (state == WKOOPA_STATE_WALKING|| state == WKOOPA_STATE_JUMPING
				|| state == WKOOPA_STATE_JUMPING_TIMEOUT || state == WKOOPA_STATE_SHELL)
			{
				//ay = WKOOPA_GRAVITY;
				SetState(WKOOPA_STATE_HIT);
			}
			else if (state == WKOOPA_STATE_JUMPING)
			{
				//ay = WKOOPA_GRAVITY;
				SetState(WKOOPA_STATE_HIT);
			}
			return;
		}
		else
			return;
	}
	//if (!e->obj->IsBlocking() && !e->obj->IsGoomba()) return;
	if (e->obj->IsGoomba() &&( e->obj->GetState() == GOOMBA_STATE_HIDDEN ||e->obj->GetState() == GOOMBA_STATE_IDLE)) return;
	if (dynamic_cast<CWingGoomba*>(e->obj) && (e->obj->GetState() == WGOOMBA_STATE_HIDDEN || e->obj->GetState() == WGOOMBA_STATE_IDLE)) return;
	
	if (e->obj->IsKoopa() &&( e->obj->GetState() == KOOPA_STATE_HIDDEN || e->obj->GetState() == KOOPA_STATE_IDLE)) return;
	if(dynamic_cast<CWingKoopa*>(e->obj) &&( e->obj->GetState() == WKOOPA_STATE_HIDDEN || e->obj->GetState() == WKOOPA_STATE_IDLE)) return;

	if (dynamic_cast<CGoldBrick*>(e->obj))
		OnCollisionWithGoldBrick(e);

	if (dynamic_cast<CFirePlant*>(e->obj))
		OnCollisionWithFirePlant(e);
	if (dynamic_cast<CFirePlant_Short*>(e->obj))
		OnCollisionWithFirePlantShort(e);
	if (dynamic_cast<CChomper*>(e->obj))
		OnCollisionWithChomper(e);
	if (dynamic_cast<CTanukiLeaf*>(e->obj))
		OnCollisionithTanukiLeaf(e);
	if (dynamic_cast<CBox*>(e->obj))
		OnCollisionWithMysteryBox(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);

	else if (dynamic_cast<CWingGoomba*>(e->obj))
		OnCollisionWithWingGoomba(e);
	/*else if (dynamic_cast<CWingKoopa*>(e->obj))
		OnCollisionWithWingKoopa(e);*/

	if (!e->obj->IsBlocking())
		return;
	if (e->ny != 0)
	{
		vy = 0;
	}

	else if (e->nx != 0 && !e->obj->IsGoomba()&& !dynamic_cast<CInvis*>(e->obj))
	{
		vx = -vx;
	}
	
	
}
void CWingKoopa::OnCollisionWithGoldBrick(LPCOLLISIONEVENT e)
{
	CGoldBrick* g = dynamic_cast<CGoldBrick*>(e->obj);
	//if (g->GetState() == GBRICK_STATE_BROKEN)	return;
	if (g->GetType() == 2)
	{
		if (state == WKOOPA_STATE_KICK_RIGHT || state == WKOOPA_STATE_KICK_LEFT)
		{

			CGoldBrick* brick = (CGoldBrick*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetIdGoldBrick(g->GetId());
			CHiddenCoin* coin = (CHiddenCoin*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetIdCoins(g->GetId());
			brick->SetForceBreak(true);
			coin->SetDestroy(true);
			brick->SetState(GBRICK_STATE_BROKEN);

		}
	}
}

void CWingKoopa::OnCollisionWithFirePlant(LPCOLLISIONEVENT e)
{
	CFirePlant* plant = dynamic_cast<CFirePlant*>(e->obj);
	if (state == WKOOPA_STATE_KICK_LEFT || state == WKOOPA_STATE_KICK_RIGHT)
	{
		if (plant->GetState() != PLANT_STATE_DIE)
			plant->SetState(PLANT_STATE_DIE);
	}
}
void CWingKoopa::OnCollisionWithFirePlantShort(LPCOLLISIONEVENT e)
{
	CFirePlant_Short* short_plant = dynamic_cast<CFirePlant_Short*>(e->obj);
	if (state == WKOOPA_STATE_KICK_LEFT || state == WKOOPA_STATE_KICK_RIGHT)
	{
		if (short_plant->GetState() != SHORT_PLANT_STATE_DIE)
			short_plant->SetState(SHORT_PLANT_STATE_DIE);
	}
}
void CWingKoopa::OnCollisionWithChomper(LPCOLLISIONEVENT e)
{

	CChomper* chomper = dynamic_cast<CChomper*>(e->obj);
	if (state == WKOOPA_STATE_KICK_LEFT || state == WKOOPA_STATE_KICK_RIGHT)
		if (chomper->GetState() != CHOMPER_STATE_DIE)
			chomper->SetState(CHOMPER_STATE_DIE);
}
void CWingKoopa::OnCollisionithTanukiLeaf(LPCOLLISIONEVENT e)
{
	CTanukiLeaf* leaf = dynamic_cast<CTanukiLeaf*>(e->obj);
	if (e->nx != 0 && (state == WKOOPA_STATE_KICK_LEFT || state == WKOOPA_STATE_KICK_RIGHT) && leaf->GetState() == LEAF_STATE_HIDDEN)
	{
		leaf->SetState(LEAF_STATE_SHOW);
	}
}

void CWingKoopa::OnCollisionWithMysteryBox(LPCOLLISIONEVENT e)
{

	CBox* box = dynamic_cast<CBox*>(e->obj);
	if (e->nx != 0 && (state == WKOOPA_STATE_KICK_LEFT || state == WKOOPA_STATE_KICK_RIGHT))
	{
		//coin mystery box
		if (box->GetState() != BOX_STATE_USED && box->GetContent() == BOX_CONTENT_COIN)
		{


			box->SetState(BOX_STATE_USED);

		}

		if (box->GetState() != BOX_STATE_USED && box->GetContent() == BOX_CONTENT_MUSHROOM)
		{
			box->SetState(BOX_STATE_USED);

		}
	}
}


void CWingKoopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{


	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (goomba->GetState() == GOOMBA_STATE_DIE) return;
	if (goomba->GetState() == GOOMBA_STATE_HIDDEN) return;
	if (state == WKOOPA_STATE_KICK_LEFT || state == WKOOPA_STATE_KICK_RIGHT)
	{
		goomba->SetState(GOOMBA_STATE_DIE);

	}
}
void CWingKoopa::OnCollisionWithWingGoomba(LPCOLLISIONEVENT e)
{
	CWingGoomba* wgoomba = dynamic_cast<CWingGoomba*>(e->obj);
	if (wgoomba->GetState() == GOOMBA_STATE_DIE) return;
	if (wgoomba->GetState() == GOOMBA_STATE_HIDDEN) return;
	if (state == WKOOPA_STATE_KICK_LEFT || state == WKOOPA_STATE_KICK_RIGHT)
	{
		wgoomba->SetState(WGOOMBA_STATE_DIE);

	}
}

void CWingKoopa::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* k = dynamic_cast<CKoopa*>(e->obj);
	DebugOut(L"[info] wkoopa hit koopa\n");
	if (state == WKOOPA_STATE_KICK_LEFT || state == WKOOPA_STATE_KICK_RIGHT)
	{
		if (k->GetState() == KOOPA_STATE_KICK_LEFT || k->GetState() == KOOPA_STATE_KICK_RIGHT)
		{
			vx = -vx;
		}
		else if(k->GetState()!=KOOPA_STATE_HIDDEN)
		{
			DebugOut(L"[info] koopa hit koopa\n");
			k->SetState(KOOPA_STATE_HIT);

		}
	}
}

void CWingKoopa::OnCollisionWithWingKoopa(LPCOLLISIONEVENT e)
{
	CWingKoopa* wk = dynamic_cast<CWingKoopa*>(e->obj);
	if (state == WKOOPA_STATE_KICK_LEFT || state == WKOOPA_STATE_KICK_RIGHT)
	{
		if (wk->GetState() == WKOOPA_STATE_KICK_LEFT || wk->GetState() == WKOOPA_STATE_KICK_RIGHT)
		{
			vx = -vx;
		}
		else if (wk->GetState() != WKOOPA_STATE_HIDDEN)
			wk->SetState(WKOOPA_STATE_HIT);
	}
	if (state != WKOOPA_STATE_KICK_LEFT && state != WKOOPA_STATE_KICK_RIGHT)
	{
		if (wk->GetState() == WKOOPA_STATE_KICK_LEFT || wk->GetState() == WKOOPA_STATE_KICK_RIGHT)
			SetState(WKOOPA_STATE_HIT);
	}
}



void CWingKoopa::OnNoCollision(DWORD dt)
{
	if (state != WKOOPA_STATE_HOLD)
	{
		x += vx * dt;
		y += vy * dt;
	}
	else
	{
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		if (mario->Getnx() < 0) {
			x = (float)mario->GetX() - 15;
			y = (float)mario->GetY();
		}
		else if (mario->Getnx() > 0) {
			x = (float)mario->GetX() + 15;
			y = (float)mario->GetY();
		}
	}
}
bool CWingKoopa::MarioDetection(int mario_x)
{
	int xx = mario_x - (int)x;
	if (abs(xx) < 250)
		return 1;
	return 0;
}


void CWingKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state != WKOOPA_STATE_WALKING &&
		state != WKOOPA_STATE_JUMPING && state!= WKOOPA_STATE_JUMPING_TIMEOUT)
	{
		left = x - WKOOPA_BBOX_WIDTH / 2;
		top = y - WSHELL_BBOX_HEIGHT / 2;
		right = left + WKOOPA_BBOX_WIDTH;
		bottom = top + WSHELL_BBOX_HEIGHT;
	}
	else
	{
		left = x - WKOOPA_BBOX_WIDTH / 2;
		top = y - WKOOPA_BBOX_HEIGHT / 2;
		right = left + WKOOPA_BBOX_WIDTH;
		bottom = top + WKOOPA_BBOX_HEIGHT;
	}
}

void CWingKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	vy += ay * dt;
	vx += ax * dt;
	if (y > 220)
	{
		SetState(WKOOPA_STATE_HIDDEN);
		return;
	}
	//shell kicked timeout
	if ((state == WKOOPA_STATE_KICK_LEFT || state == WKOOPA_STATE_KICK_RIGHT) && GetTickCount64() - die_timeout > WKOOPA_SHELL_TIMEOUT)
	{
		SetState(WKOOPA_STATE_HIDDEN);
		return;
	}
	if (state == WKOOPA_STATE_HIT && y < pop_height)
	{
		ay = WKOOPA_GRAVITY;

	}
	//revive after turn into shell
	if ((state == WKOOPA_STATE_SHELL) && (GetTickCount64() - shell_start > WKOOPA_SHELL_TIMEOUT))
	{
		SetState(WKOOPA_STATE_REVIVE);
		return;
	}
	
	//stop revive ani and turn into walking state
	if ((state == WKOOPA_STATE_REVIVE) && (GetTickCount64() - revive_start > WKOOPA_REVIVE_TIME))
	{
		SetState(WKOOPA_STATE_WALKING);
		return;
	}
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	int mario_x;
	mario_x = mario->GetX();

	//detect mario to start koopa movement
	if (MarioDetection(mario_x) && flag == 0)
	{
		SetState(WKOOPA_STATE_JUMPING_TIMEOUT);
		flag = 1;
	}

	//respawn mechanic
	if (state == WKOOPA_STATE_HIDDEN && RespawnDetector(mario_x) == 1)
	{

		flag = 0;	
		SetState(WKOOPA_STATE_IDLE);
		die_flag = 0;
	}

	//jump mechanic
	if (state == WKOOPA_STATE_JUMPING && (GetTickCount64() - fly_time > WKOOPA_JUMP_TIME)) {
		SetState(WKOOPA_STATE_JUMPING_TIMEOUT);
	}
	else if (state == WKOOPA_STATE_JUMPING_TIMEOUT && (GetTickCount64() - fly_timeout > WKOOPA_JUMP_WAIT)) {
		SetState(WKOOPA_STATE_JUMPING);
	}


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CWingKoopa::Render()
{
	if (state != WKOOPA_STATE_HIDDEN)
	{
		int aniId = ID_ANI_WKOOPA_JUMPING_LEFT;
		if ((state == WKOOPA_STATE_JUMPING || state == WKOOPA_STATE_JUMPING_TIMEOUT)
			&& vx > 0)
			aniId = ID_ANI_WKOOPA_JUMPING_RIGHT;
	
		else if (state == WKOOPA_STATE_WALKING)
		{
			if (vx > 0)
				aniId = ID_ANI_WKOOPA_WALKING_RIGHT;
			if (vx < 0)
				aniId = ID_ANI_WKOOPA_WALKING_LEFT;
		}
		else if (state == WKOOPA_STATE_HIT)
			aniId = ID_ANI_WKOOPA_HIT;
		else if (state == KOOPA_STATE_HOLD||state == WKOOPA_STATE_SHELL || state == WKOOPA_STATE_KICK_LEFT || state == WKOOPA_STATE_KICK_RIGHT)
		{
			aniId = ID_ANI_WKOOPA_SHELL;
		}
		else if (state == WKOOPA_STATE_REVIVE)
		{
			aniId = ID_ANI_WKOOPA_REVIVE;
		}
		CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	}
	//RenderBoundingBox();
}

void CWingKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		//shell
	case WKOOPA_STATE_SHELL:
		shell_start = GetTickCount64();
		kick_cooldown = GetTickCount64();
		y += (WKOOPA_BBOX_HEIGHT - WSHELL_BBOX_HEIGHT) / 2;
		
		vx = 0;
		//vy = 0;
		ay = 0;
		break;

		//idle
	case WKOOPA_STATE_IDLE:

		vx = 0;
		ay = WKOOPA_GRAVITY;
		y = default_y - 5;
		x = default_x;
		break;
		
		//if(die_flag = 0)
			
		//walking
	case WKOOPA_STATE_WALKING:
		//if(die_flag==1)
		y -=  3;
		ay = WKOOPA_GRAVITY;
		if (pre_vx > 0)
			vx = -WKOOPA_WALKING_SPEED;
		else if (pre_vx < 0)
			vx = WKOOPA_WALKING_SPEED;
		else
			vx = -WKOOPA_WALKING_SPEED;
		pre_vx = vx;
		break;

		//revive
	case WKOOPA_STATE_REVIVE:
		revive_start = GetTickCount64();
		break;

		//kick
	case WKOOPA_STATE_KICK_RIGHT:
		y -= 3;
		vx = WKOOPA_SHELL_SPEED;
		ay = WKOOPA_GRAVITY;
		die_timeout = GetTickCount64();
		break;
	case WKOOPA_STATE_KICK_LEFT:
		y -= 3;
		die_timeout = GetTickCount64();
		vx = -WKOOPA_SHELL_SPEED;
		ay = WKOOPA_GRAVITY;
		break;

	case WKOOPA_STATE_JUMPING:
		ay = -WKOOPA_JUMP_SPEED;
		fly_time = GetTickCount64();

		break;

	case WKOOPA_STATE_JUMPING_TIMEOUT:
		vx = -WKOOPA_WALKING_SPEED;
		if (vy < 0)
			ay = WKOOPA_JUMP_SPEED;
		else
			ay = WKOOPA_GRAVITY;

		fly_timeout = GetTickCount64();
		break;

	case WKOOPA_STATE_HIDDEN:
		die_flag = 1;
		x = default_x;
		y = Y - 3;
		vx = 0;
		ay = WKOOPA_GRAVITY;
		break;
	case WKOOPA_STATE_HIT:
		ay = -WKOOPA_GRAVITY;
		pop_height = (int)y - 20;
		pre_vx = vx;
		vx = 0;

		break;
	case KOOPA_STATE_HOLD:
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	}


}
