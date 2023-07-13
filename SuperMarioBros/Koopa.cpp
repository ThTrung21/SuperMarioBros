 #include "Koopa.h"
#include "Goomba.h"
#include "Tanuki_Leaf.h"
#include "MysteryBox.h"
#include "Mario.h"
#include "debug.h"
#include "PlayScene.h"
#include "WingKoopa.h"
#include "WingGoomba.h"
#include "Invis_block.h"
#include "WingKoopa.h"
#include"FirePlant.h"
#include"FirePlant_Short.h"
#include"Chomper.h"
#include "Tail.h"
CKoopa::CKoopa(float x, float y,int type) :CGameObject(x, y)
{
	this->ax = 0;
	default_y = y;
	default_x = x;
	this->ay = KOOPA_GRAVITY;
	shell_start = -1;
	revive_start = -1;
	pre_vx = 0;
	die_timeout = -1;
	this->Ktype = type;
	flag = 0;
	bounce_start = -1;
	pop_height = (int)y - 20;
	SetState(KOOPA_STATE_WALKING);
	
}

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state != KOOPA_STATE_WALKING )
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - SHELL_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + SHELL_BBOX_HEIGHT;
	}
	else
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}

}
bool CKoopa::MarioDetection(int mario_x)
{
	int xx = mario_x - (int)x;
	if (abs(xx) < 300)
		return 1;
	return 0;
}

bool CKoopa::RespawnDetector(int mario_x)
{
	int xx = mario_x - (int)default_x;
	if (abs(xx) > 300)
		return 1;
	return 0;
}

void CKoopa::OnNoCollision(DWORD dt)
{
	if (state != KOOPA_STATE_HOLD)
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

};

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if(state ==KOOPA_STATE_HIT && e->ny!=0)
		SetState(KOOPA_STATE_SHELL);
	if (state == KOOPA_STATE_HIT) return;

	if (dynamic_cast<CTail*>(e->obj))
	{
		CTail* tail = dynamic_cast<CTail*>(e->obj);
		if (tail->GetState() == TAIL_STATE_ACTIVE)
		{
			if (state == KOOPA_STATE_WALKING ||state==KOOPA_STATE_SHELL)
			{
				SetState(KOOPA_STATE_HIT);
				//bounce_start = GetTickCount64();
			}
		}
		else
			return;
	}

	if (e->obj->IsGoomba() && e->obj->GetState() == GOOMBA_STATE_DIE) return;
	if (dynamic_cast<CWingGoomba*>(e->obj) && (e->obj->GetState() == WGOOMBA_STATE_HIDDEN || e->obj->GetState() == WGOOMBA_STATE_IDLE)) return;
	if (e->obj->IsKoopa() && e->obj->GetState() == KOOPA_STATE_HIDDEN) return;
	if (dynamic_cast<CWingKoopa*>(e->obj) && (e->obj->GetState() == WKOOPA_STATE_HIDDEN || e->obj->GetState() == WKOOPA_STATE_IDLE)) return;

	
	if (dynamic_cast<CTanukiLeaf*>(e->obj))
		OnCollisionithTanukiLeaf(e);
	if (dynamic_cast<CBox*>(e->obj))
		OnCollisionWithMysteryBox(e);
	if (dynamic_cast<CFirePlant*>(e->obj))
		OnCollisionWithFirePlant(e);
	if (dynamic_cast<CFirePlant_Short*>(e->obj))
		OnCollisionWithFirePlantShort(e);
	if (dynamic_cast<CChomper*>(e->obj))
		OnCollisionWithChomper(e);
	if (dynamic_cast<CWingKoopa*>(e->obj))
		OnCollisionWithWingKoopa(e);
	if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);

	//invisible barrier for red koopa
	else if (state == KOOPA_STATE_WALKING && Ktype == 1 && dynamic_cast<CInvis*>(e->obj))
	{

		vx = -vx;
	}
	else if (e->ny != 0 && state != KOOPA_STATE_HIT)
	{
		vy = 0;
	}
	else if (e->nx != 0 && !e->obj->IsGoomba() && !dynamic_cast<CInvis*>(e->obj))
	{
		vx = -vx;
	}

	
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CWingGoomba*>(e->obj))
		OnCollisionWithWingGoomba(e);
	
	
	
}
void CKoopa::OnCollisionWithFirePlant(LPCOLLISIONEVENT e)
{
	CFirePlant* plant = dynamic_cast<CFirePlant*>(e->obj);
	if (state == WKOOPA_STATE_KICK_LEFT || state == WKOOPA_STATE_KICK_RIGHT)
	{
		if (plant->GetState() != PLANT_STATE_DIE)
			plant->SetState(PLANT_STATE_DIE);
	}
}
void CKoopa::OnCollisionWithFirePlantShort(LPCOLLISIONEVENT e)
{
	CFirePlant_Short* short_plant = dynamic_cast<CFirePlant_Short*>(e->obj);
	if (state ==WKOOPA_STATE_KICK_LEFT || state == WKOOPA_STATE_KICK_RIGHT)
	{
		if (short_plant->GetState() != SHORT_PLANT_STATE_DIE)
			short_plant->SetState(SHORT_PLANT_STATE_DIE);
	}
}
void CKoopa::OnCollisionWithChomper(LPCOLLISIONEVENT e)
{
	
	CChomper* chomper = dynamic_cast<CChomper*>(e->obj);
	if (state == WKOOPA_STATE_KICK_LEFT || state == WKOOPA_STATE_KICK_RIGHT)
		if (chomper->GetState() != CHOMPER_STATE_DIE)
			chomper->SetState(CHOMPER_STATE_DIE);
}


void CKoopa::OnCollisionithTanukiLeaf(LPCOLLISIONEVENT e)
{
	CTanukiLeaf* leaf = dynamic_cast<CTanukiLeaf*>(e->obj);
	if (e->nx != 0 && (state == KOOPA_STATE_KICK_LEFT || state == KOOPA_STATE_KICK_RIGHT)  && leaf->GetState() == LEAF_STATE_HIDDEN)
	{
		leaf->SetState(LEAF_STATE_SHOW);
	}
}
void CKoopa::OnCollisionWithWingKoopa(LPCOLLISIONEVENT e)
{
	CWingKoopa* k = dynamic_cast<CWingKoopa*>(e->obj);
	if (state == KOOPA_STATE_KICK_LEFT || state == KOOPA_STATE_KICK_RIGHT)
	{
		if (k->GetState() == WKOOPA_STATE_KICK_LEFT || k->GetState() == WKOOPA_STATE_KICK_RIGHT)
		{
			vx = -vx;
		}
		else
			k->SetState(WKOOPA_STATE_HIT);
	}
}
void CKoopa::OnCollisionWithMysteryBox(LPCOLLISIONEVENT e)
{

	CBox* box = dynamic_cast<CBox*>(e->obj);
	if (e->nx != 0 && (state == KOOPA_STATE_KICK_LEFT || state == KOOPA_STATE_KICK_RIGHT))
	{

		if (box->GetState() != BOX_STATE_USED )
		{
			box->SetState(BOX_STATE_USED);
			vx = -vx;
		}
	}
}


void CKoopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	
	
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (goomba->GetState() == GOOMBA_STATE_DIE) return;
	if (goomba->GetState() == GOOMBA_STATE_HIDDEN) return;
	if (state == KOOPA_STATE_KICK_LEFT || state == KOOPA_STATE_KICK_RIGHT)
	{
		goomba->SetState(GOOMBA_STATE_DIE);
		
	}
}
void CKoopa::OnCollisionWithWingGoomba(LPCOLLISIONEVENT e)
{
	CWingGoomba* wgoomba = dynamic_cast<CWingGoomba*>(e->obj);
	if (wgoomba->GetState() == WGOOMBA_STATE_DIE) return;
	if (wgoomba->GetState() == WGOOMBA_STATE_HIDDEN) return;
	if (state == KOOPA_STATE_KICK_LEFT || state == KOOPA_STATE_KICK_RIGHT)
	{
		wgoomba->SetState(WGOOMBA_STATE_DIE);

	}
}
void CKoopa::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* k = dynamic_cast<CKoopa*>(e->obj);
	if (state == KOOPA_STATE_KICK_LEFT || state == KOOPA_STATE_KICK_RIGHT)
	{
		if (k->GetState() == KOOPA_STATE_KICK_LEFT || k->GetState() == KOOPA_STATE_KICK_RIGHT)
		{
			
			vx = -vx;
		}
		else
			k->SetState(KOOPA_STATE_HIT);
	}
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	
	if (y > 220)
	{
		SetState(KOOPA_STATE_HIDDEN);
	}
	
	

	//shell kicked timeout
	if ((state == KOOPA_STATE_KICK_LEFT || state == KOOPA_STATE_KICK_RIGHT) && GetTickCount64() - die_timeout > KOOPA_SHELL_TIMEOUT)
	{
		SetState(KOOPA_STATE_HIDDEN);
		return;
	}
	//revive after turn into shell
	if ((state == KOOPA_STATE_SHELL) &&  (GetTickCount64() - shell_start > KOOPA_SHELL_TIMEOUT))
	{
		SetState(KOOPA_STATE_REVIVE);
		return;
	}
	//change revive ani to idle/walking ani
	if ((state == KOOPA_STATE_REVIVE) && (GetTickCount64() - revive_start > KOOPA_REVIVE_TIME))
	{
		SetState(KOOPA_STATE_WALKING);
		return;
	}
	//koopa got hit
	if (state == KOOPA_STATE_HIT && y < pop_height)
	{
		ay = KOOPA_GRAVITY;


	}
	
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	int mario_x;
	mario_x = mario->GetX();

	//detect mario to start koopa movement
	if (MarioDetection(mario_x) && flag == 0)
	{
		SetState(KOOPA_STATE_WALKING);
		flag = 1;
	}

	//respawn mechanic
	if (state == KOOPA_STATE_HIDDEN && RespawnDetector(mario_x) == 1)
	{
		flag = 0;
		//y -= (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
		SetState(KOOPA_STATE_IDLE);
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CKoopa::Render()
{
	if(state != KOOPA_STATE_HIDDEN)
	{
	int aniId;
	if (Ktype == KOOPA_RED)
	{
		aniId = ID_ANI_KOOPA_WALKING_LEFT;
		if (state == KOOPA_STATE_WALKING)
		{
			if (vx > 0)
				aniId = ID_ANI_KOOPA_WALKING_RIGHT;
			if (vx < 0)
				aniId = ID_ANI_KOOPA_WALKING_LEFT;
		}
		else if (state == KOOPA_STATE_HIT)
			aniId = ID_ANI_KOOPA_HIT;
		else if (state == KOOPA_STATE_HOLD ||state == KOOPA_STATE_SHELL || state == KOOPA_STATE_KICK_LEFT || state == KOOPA_STATE_KICK_RIGHT)
		{
			aniId = ID_ANI_KOOPA_SHELL;
		}
		else if (state == KOOPA_STATE_REVIVE)
		{
			aniId = ID_ANI_KOOPA_REVIVE;
		}
	}
	else
	{
		aniId = ID_ANI_KOOPA_GREEN_WALKING_LEFT;
		if (state == KOOPA_STATE_WALKING)
		{
			if (vx > 0)
				aniId = ID_ANI_KOOPA_GREEN_WALKING_RIGHT;
			if (vx < 0)
				aniId = ID_ANI_KOOPA_GREEN_WALKING_LEFT;
		}
		else if (state == KOOPA_STATE_HIT)
			aniId = ID_ANI_KOOPA_GREEN_HIT;
		else if (state == KOOPA_STATE_HOLD || state == KOOPA_STATE_SHELL || state == KOOPA_STATE_KICK_LEFT || state == KOOPA_STATE_KICK_RIGHT)
		{
			aniId = ID_ANI_KOOPA_GREEN_SHELL;
		}
		else if (state == KOOPA_STATE_REVIVE)
		{
			aniId = ID_ANI_KOOPA_GREEN_REVIVE;
		}
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	
	}
	RenderBoundingBox();
}
void CKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		//shell
	case KOOPA_STATE_SHELL:
		shell_start = GetTickCount64();
		kick_cooldown = GetTickCount64();
		
		//y += (KOOPA_BBOX_HEIGHT - SHELL_BBOX_HEIGHT) / 2;
		pre_vx = vx;
		vx = 0;
		//vy = 0;
		ay = KOOPA_GRAVITY;
		break;

		//idle
	case KOOPA_STATE_IDLE:
		vx = 0;
		ay = KOOPA_GRAVITY;
		break;
		
		x = default_x;
		y = default_y-3;
		//walking
	case KOOPA_STATE_WALKING:
		y = default_y - 3;
		ay = KOOPA_GRAVITY;
		if (pre_vx > 0)
			vx = -KOOPA_WALKING_SPEED;
		else if (pre_vx < 0)
			vx = KOOPA_WALKING_SPEED;
		else
			vx = -KOOPA_WALKING_SPEED;

		break;

		//revive
	case KOOPA_STATE_REVIVE:
		revive_start = GetTickCount64();
		break;

		//kick
	case KOOPA_STATE_KICK_RIGHT:	
		y -= 3;
		vx = KOOPA_SHELL_SPEED;
		ay = KOOPA_GRAVITY;
		die_timeout = GetTickCount64();
		break;
	case KOOPA_STATE_KICK_LEFT:
		y -= 3;
		DebugOut(L"koopa kicked left\n");
		die_timeout = GetTickCount64();
		vx = -KOOPA_SHELL_SPEED;
		ay = KOOPA_GRAVITY;
		break;
	case KOOPA_STATE_HIT:
		ay = -KOOPA_GRAVITY;
		pop_height = (int)y - 20;
		vx = 0;
		break;
	case KOOPA_STATE_HOLD:
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case KOOPA_STATE_HIDDEN:
		
		x = default_x;
		y = default_y-3;
		vx = 0;
		ay = KOOPA_GRAVITY;
		break;
	}
}

