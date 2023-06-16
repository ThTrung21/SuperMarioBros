 #include "Koopa.h"
#include "Goomba.h"
#include "Tanuki_Leaf.h"
#include "MysteryBox.h"
#include "Mario.h"

CKoopa::CKoopa(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	default_y = y;
	this->ay = KOOPA_GRAVITY;
	shell_start = -1;
	revive_start = -1;
	pre_vx = 0;
	die_timeout = -1;
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

void CKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	//if (dynamic_cast<CKoopa*>(e->obj)) return;
	//if(dynamic_cast<CGoomba*>(e->obj)) return;
	//if (e->ny != 0 && e->obj->IsBlocking()) /*&&
	//	(state ==KOOPA_STATE_WALKING || state==KOOPA_STATE_KICK_LEFT|| state == KOOPA_STATE_KICK_RIGHT))*/
	//{
	//	vy = 0;	
	//}
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}

	if (dynamic_cast<CTanukiLeaf*>(e->obj))
		OnCollisionithTanukiLeaf(e);
	if (dynamic_cast<CBox*>(e->obj))
		OnCollisionWithMysteryBox(e);
	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
}

void CKoopa::OnCollisionithTanukiLeaf(LPCOLLISIONEVENT e)
{
	CTanukiLeaf* leaf = dynamic_cast<CTanukiLeaf*>(e->obj);
	if ((state == KOOPA_STATE_KICK_LEFT || state == KOOPA_STATE_KICK_RIGHT) && e->nx != 0 && leaf->GetState() == LEAF_STATE_HIDDEN)
	{
		leaf->SetState(LEAF_STATE_SHOW);
	}
}

void CKoopa::OnCollisionWithMysteryBox(LPCOLLISIONEVENT e)
{

	CBox* box = dynamic_cast<CBox*>(e->obj);
	if (e->nx != 0 && (state == KOOPA_STATE_KICK_LEFT || state == KOOPA_STATE_KICK_RIGHT))
	{
		//coin mystery box
		/*if (box->GetState() != BOX_STATE_USED && box->GetContent() == BOX_CONTENT_COIN)
		{


			box->SetState(BOX_STATE_USED);

		}*/

		if (box->GetState() != BOX_STATE_USED && box->GetContent() == BOX_CONTENT_MUSHROOM)
		{
			box->SetState(BOX_STATE_USED);

		}
	}
}

//need fixing
void CKoopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (state == KOOPA_STATE_KICK_LEFT || state == KOOPA_STATE_KICK_RIGHT)
		
		goomba->SetState(GOOMBA_STATE_DIE);
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == KOOPA_STATE_KICK_LEFT || state == KOOPA_STATE_KICK_RIGHT) && GetTickCount64() - die_timeout > KOOPA_SHELL_TIMEOUT)
	{
		isDeleted = true;
		return;
	}
	if ((state == KOOPA_STATE_SHELL) &&  (GetTickCount64() - shell_start > KOOPA_SHELL_TIMEOUT))
	{
		SetState(KOOPA_STATE_REVIVE);
		return;
	}
	if ((state == KOOPA_STATE_REVIVE) && (GetTickCount64() - revive_start > KOOPA_REVIVE_TIME))
	{
		SetState(KOOPA_STATE_WALKING);
		return;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CKoopa::Render()
{
	int aniId = ID_ANI_KOOPA_WALKING_LEFT;
	if (state == KOOPA_STATE_WALKING)
	{
		if (vx > 0)
			aniId = ID_ANI_KOOPA_WALKING_RIGHT;
		if (vx < 0)
			aniId = ID_ANI_KOOPA_WALKING_LEFT;
	}

	else if (state == KOOPA_STATE_SHELL || state== KOOPA_STATE_KICK_LEFT || state == KOOPA_STATE_KICK_RIGHT)
	{
		aniId = ID_ANI_KOOPA_SHELL;
	}
	else if (state == KOOPA_STATE_REVIVE)
	{
		aniId = ID_ANI_KOOPA_REVIVE;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
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
		
		y += (KOOPA_BBOX_HEIGHT - SHELL_BBOX_HEIGHT) / 2;
		pre_vx = vx;
		vx = 0;
		//vy = 0;
		ay = 0;
		break;

	//walking
	case KOOPA_STATE_WALKING:
		
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
	case KOOPA_STATE_KICK_RIGHT:
		y += 8;
		vx = KOOPA_SHELL_SPEED;
		ay = KOOPA_GRAVITY;
		die_timeout = GetTickCount64();
		break;
	case KOOPA_STATE_KICK_LEFT:
		y += 8;
		die_timeout = GetTickCount64();
		vx = -KOOPA_SHELL_SPEED;
		ay = KOOPA_GRAVITY;
		break;
	}
}

