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
CWingKoopa::CWingKoopa(float x, float y)
{
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
	SetState(WKOOPA_STATE_IDLE);

}

bool CWingKoopa::RespawnDetector(int mario_x)
{
	int xx = mario_x - (int)default_x;
	if (abs(xx) > 300)
		return 1;
	return 0;
}
void CWingKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	//if (!e->obj->IsBlocking() && !e->obj->IsGoomba()) return;
	if (e->obj->IsGoomba() && e->obj->GetState() == GOOMBA_STATE_DIE) return;
	/*if (e->nx != 0 && dynamic_cast<CColorBox*>(e->obj))
		return;*/
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0 && !e->obj->IsGoomba()&& !dynamic_cast<CInvis*>(e->obj))
	{
		vx = -vx;
	}
	else if (dynamic_cast<CTanukiLeaf*>(e->obj))
		OnCollisionithTanukiLeaf(e);
	else if (dynamic_cast<CBox*>(e->obj))
		OnCollisionWithMysteryBox(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CWingGoomba*>(e->obj))
		OnCollisionWithWingGoomba(e);
	/*else if (dynamic_cast<CWingKoopa*>(e->obj))
		OnCollisionWithWingKoopa(e);*/
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
	DebugOut(L"[info] koopa hit koopa\n");
	if (state == WKOOPA_STATE_KICK_LEFT || state == WKOOPA_STATE_KICK_RIGHT)
	{
		if (k->GetState() == KOOPA_STATE_KICK_LEFT || k->GetState() == KOOPA_STATE_KICK_RIGHT)
		{
			vx = -vx;
		}
		else
		{
			DebugOut(L"[info] koopa hit koopa\n");
			k->SetState(KOOPA_STATE_HIT);

		}
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
	if (abs(xx) < 300)
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
	}
	//shell kicked timeout
	if ((state == WKOOPA_STATE_KICK_LEFT || state == WKOOPA_STATE_KICK_RIGHT) && GetTickCount64() - die_timeout > WKOOPA_SHELL_TIMEOUT)
	{
		SetState(WKOOPA_STATE_HIDDEN);
		return;
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
	RenderBoundingBox();
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
		pre_vx = vx;
		vx = 0;
		//vy = 0;
		ay = 0;
		break;

		//idle
	case WKOOPA_STATE_IDLE:

		vx = 0;
		ay = WKOOPA_GRAVITY;
		break;
		x = default_x;
		if(die_flag = 0)
			y = default_y - 5;
		//walking
	case WKOOPA_STATE_WALKING:
		//if(die_flag==1)
		y = default_y - 3;
		ay = WKOOPA_GRAVITY;
		if (pre_vx > 0)
			vx = -WKOOPA_WALKING_SPEED;
		else if (pre_vx < 0)
			vx = WKOOPA_WALKING_SPEED;
		else
			vx = -WKOOPA_WALKING_SPEED;

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
		y = default_y - 3;
		vx = 0;
		ay = WKOOPA_GRAVITY;
		break;
	case KOOPA_STATE_HOLD:
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	}


}
