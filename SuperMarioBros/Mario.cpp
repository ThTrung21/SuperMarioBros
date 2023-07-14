#include <algorithm>

#include "debug.h"
#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "MysteryBox.h"
#include "GameObject.h"
#include "PlayScene.h"

#include "RedMushroom.h"
#include "FirePlant.h"
#include "FirePlant_Short.h"
#include "Koopa.h"
#include "FireBall.h"
#include "Tanuki_Leaf.h"
#include "WingGoomba.h"

#include "Collision.h"

#include "ColorBox.h"
#include "debug.h"
#include "GoldBrick.h"
#include "Chomper.h"
#include "WingKoopa.h"
#include "Pwr_btn.h"
#include "Tail.h"
#include "Hidden_Coin.h"
void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGame::GetInstance()->SetLevel(level);

	//change loacation after exit secret room
	int load_time = CGame::GetInstance()->GetLoadTime();
	
	if (load_time % 2 != 0 && load_time != 1)
	{
		if(posChangeLock)
		{
			
			SetPosition(1200, 20);
			posChangeLock = 0;
		}
	}
	
	CTail* tail = (CTail*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetTail();
	vy += ay * dt;
	vx += ax * dt;
	//mario not tanuki
	if (level != MARIO_LEVEL_TANUKI)
	{
		isSlapTail = false;
		if(tail!=NULL)
		tail->SetState(TAIL_STATE_IDLE);
	}
	//mario glide disable tail
	if (isGlide == true)
	{
		isSlapTail = false;
	}
	//isrunning detector
	if (abs(vx) >= MARIO_ACCEL_RUN_X)
		IsRunning(true);
	if (abs(vx) < MARIO_ACCEL_RUN_X)
		IsRunning(false);
	float x_now, y_now;
	GetPosition(x_now, y_now);

	//die when fall out of map
	if (y_now > 280)
	{
		SetState(MARIO_STATE_DIE);
	}
	//prevent mario flying too high
	if (y_now < -200)
	{
		SetPosition(x, -200);
	}

	//left border
	if (x_now < 10)
		SetPosition(16, y_now);

	if (abs(vx) > abs(maxVx)) vx = maxVx;
	
	if (isSlapTail)
	{
		tail->SetState(TAIL_STATE_ACTIVE);
	}
	else
	{
		tail->SetState(TAIL_STATE_IDLE);
	}

	if (isFlying) {
		if (GetTickCount64() - resetGravity_start > TANUKI_FLY_SET_GRAVITY_BACK) {
			//vy = 0.1f;
			ay = MARIO_GRAVITY;
			//vx = 0.0f;
			isFlying = false;
			//SetState(MARIO_STATE_RELEASE_JUMP);
		}

	}
	else if (isGlide) {
		if (GetTickCount64() - glide_start > 300) {
			vy =(float) 0.1;
			ay = MARIO_GRAVITY;
			vx = 0;
			isGlide = false;
		}
	}
	/*else if (isSlapTail)
	{
		if (GetTickCount64() - slap_time > TANUKI_SLAP_TIME)
			isSlapTail = false;
	}*/
	
	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
		
	}
	/*if (GetTickCount64() - slap_time > TANUKI_SLAP_TIME && state==MARIO_STATE_SLAP)
	{
		SetState(MARIO_STATE_IDLE);
	}*/
	isOnPlatform = false;
	
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CBtn*>(e->obj) && e->nx != 0) return;
	
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	//else
		if (e->nx != 0 && e->obj->IsBlocking())
		{
			
			vx = 0;
		}
	
		
	

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CHiddenCoin*>(e->obj))
		OnCollisionWithHiddenCoin(e);	
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CBox*>(e->obj))
		OnCollisionWithBox(e);
	else if (dynamic_cast<CMushroom*>(e->obj))
		OncCollisionWithMushroom(e);
	else if (dynamic_cast<CFirePlant*>(e->obj))
		OnCollisionWithFirePlant(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CFireBall*>(e->obj))
		OnCollisionWithFireBall(e);
	else if (dynamic_cast<CTanukiLeaf*>(e->obj))
		OnCollisionithTanukiLeaf(e);
	else if (dynamic_cast<CWingGoomba*>(e->obj))
		OnCollisionWithWingGoomba(e);
	else if (dynamic_cast<CChomper*>(e->obj))
		OnCollisionWithChomper(e);
	/*else if (dynamic_cast<CGoldBrick*>(e->obj) && e->nx != 0)
	{
		vx = 0; return;
	}*/
	

	else if (dynamic_cast<CGoldBrick*>(e->obj))
		OnCollisionWithGoldBrick(e);
	else if (dynamic_cast<CFirePlant_Short*>(e->obj))
		OnCollisionWithFirePlantShort(e);
	else if (dynamic_cast<CWingKoopa*>(e->obj))
		OnCollisionWithWingKoopa(e);
	else if (dynamic_cast<CBtn*>(e->obj))
		OnCollisionWithBtn(e);

}



void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	float gx, gy;
	
	if (goomba->GetState() == GOOMBA_STATE_DIE || goomba->GetState() == GOOMBA_STATE_HIDDEN) return;

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		goomba->GetPosition(gx, gy);
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			
			goomba->SetState(GOOMBA_STATE_DIE);
			goomba->SetPosition(gx,gy);

			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if(goomba->GetState()==GOOMBA_STATE_DIE)
		goomba->SetPosition(gx, gy);

	}
	
	if(state==MARIO_STATE_SLAP||state==Mario_STATE_SLAP_RIGHT)
		if (goomba->GetState() != GOOMBA_STATE_DIE)
			goomba->SetState(GOOMBA_STATE_DIE);
	
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE && goomba->GetState() != GOOMBA_STATE_HIDDEN)
			{
				if (level == MARIO_LEVEL_TANUKI)
				{
					level = MARIO_LEVEL_BIG;
					StartUntouchable();
				}
				else if (level == MARIO_LEVEL_BIG)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}

	
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	CCoin* c = dynamic_cast<CCoin*>(e->obj);
	if (!c->IsHidden())
	{
		e->obj->Delete();
		coin++;
		CGame::GetInstance()->SetCoin(coin);
	}
	else if(e->ny>0)
	{
		c->SetState(COIN_HIDDEN_EATEN);
		
	}
}

void CMario::OnCollisionWithHiddenCoin(LPCOLLISIONEVENT e)
{
	CHiddenCoin* hidden= dynamic_cast<CHiddenCoin*>(e->obj);
	if (hidden->GetState() == HCOIN_STATE_SHOW)
	{

		//CHiddenCoin* c = (CHiddenCoin*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetIdCoins(hidden->GetId());
		//CGoldBrick* brick = (CGoldBrick*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetIdGoldBrick(hidden->GetId());
		//c->SetEaten(true);
		/*DebugOut(L"brick gon\n");
		brick->SetForceBreak(true);*/
		e->obj->Delete();
		coin++;
		CGame::GetInstance()->SetCoin(coin);
	}
}


void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::OnCollisionWithBox(LPCOLLISIONEVENT e)
{
	CBox* box = dynamic_cast<CBox*>(e->obj);
	if (e->ny > 0)
	{
		if (box->GetState() != BOX_STATE_USED && box->GetContent() == BOX_CONTENT_COIN)
		{
			
			coin++;
			CGame::GetInstance()->SetCoin(coin);
			box->SetState(BOX_STATE_BOUNCE);
			
		}
		if (box->GetState() != BOX_STATE_USED && box->GetContent() == BOX_CONTENT_MUSHROOM)
		{
			box->SetState(BOX_STATE_BOUNCE);
			
		}

	}
}

void CMario::OnCollisionWithGoldBrick(LPCOLLISIONEVENT e)
{
	CGoldBrick* gb = dynamic_cast<CGoldBrick*>(e->obj);
	if (gb->GetType() == 2)
	{
		if (e->ny > 0 && level >= MARIO_LEVEL_BIG)
		{

			CGoldBrick* brick = (CGoldBrick*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetIdGoldBrick(gb->GetId());
			CHiddenCoin* coin = (CHiddenCoin*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetIdCoins(gb->GetId());
			brick->SetForceBreak(true);
			coin->SetDestroy(true);
			brick->SetState(GBRICK_STATE_BROKEN);

		}
	}
		if (gb->GetState() == GBRICK_STATE_NEW)
		{
			if (e->ny > 0)
			{
				gb->SetState(GBRICK_STATE_BOUNCE);
			}
		}
	
}

void CMario::OnCollisionWithBtn(LPCOLLISIONEVENT e)
{
	CBtn* b = dynamic_cast<CBtn*>(e->obj);
	if (b->GetState() == BTN_STATE_HIDDEN && e->ny > 0 && level>=MARIO_LEVEL_BIG)
	{
		b->SetState(BTN_STATE_SHOW);
		return;
	}
	if (b->GetState() == BTN_STATE_HIDDEN ) 
	{
		b->SetState(BTN_STATE_HIDDEN) ;
		return;
	}
	
	if (b->GetState() == BTN_STATE_USED)
	{
		b->SetState(BTN_STATE_USED);
		return;
	}
	else
	{
		if (e->ny < 0)
			b->SetState(BTN_STATE_USED);
	}
			
}

void CMario::OncCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	CMushroom* m = dynamic_cast<CMushroom*>(e->obj);
	if (m->GetState() == MUSHROOM_STATE_HIDDEN && e->ny>0) 
	{
		m->SetState(MUSHROOM_STATE_SHOW);
	}
	else if (m->GetState() == MUSHROOM_STATE_SHOW || m->GetState() == MUSHROOM_STATE_MOVE) {
		if (level == MARIO_LEVEL_SMALL) {
			y -= 15;
			level = MARIO_LEVEL_BIG;
			e->obj->Delete();
		}
		else
			e->obj->Delete();
	}
}

void CMario::OnCollisionWithFirePlant(LPCOLLISIONEVENT e)
{
	CFirePlant* f = dynamic_cast<CFirePlant*>(e->obj);
	//if (state == MARIO_STATE_SLAP || state == Mario_STATE_SLAP_RIGHT)
	//	if (f->GetState() != PLANT_STATE_DIE)
	//		f->SetState(PLANT_STATE_DIE);
	 if (untouchable == 0 && f->GetState()!=PLANT_STATE_DIE)
	{
		if (level == MARIO_LEVEL_TANUKI)
		{
			level = MARIO_LEVEL_BIG;
			StartUntouchable();
		}
		else if (level == MARIO_LEVEL_BIG)
		{
			level = MARIO_LEVEL_SMALL;
			StartUntouchable();
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
		}
	}
}
void CMario::OnCollisionWithFirePlantShort(LPCOLLISIONEVENT e)
{
	CFirePlant_Short* f = dynamic_cast<CFirePlant_Short*>(e->obj);
	/*if (state == MARIO_STATE_SLAP || state == Mario_STATE_SLAP_RIGHT)
		if (f->GetState() != SHORT_PLANT_STATE_DIE)
			f->SetState(SHORT_PLANT_STATE_DIE);*/
	 if (untouchable == 0 && f->GetState() != SHORT_PLANT_STATE_DIE)
	{
		if (level == MARIO_LEVEL_TANUKI)
		{
			level = MARIO_LEVEL_BIG;
			StartUntouchable();
		}
		else if (level == MARIO_LEVEL_BIG)
		{
			level = MARIO_LEVEL_SMALL;
			StartUntouchable();
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
		}
	}
}
void CMario::OnCollisionWithChomper(LPCOLLISIONEVENT e)
{
	CChomper* chomper = dynamic_cast<CChomper*>(e->obj);
	/*if (state == MARIO_STATE_SLAP || state == Mario_STATE_SLAP_RIGHT)
		if (chomper->GetState() != SHORT_PLANT_STATE_DIE)
			chomper->SetState(SHORT_PLANT_STATE_DIE);*/
	 if (untouchable == 0)
	{
		
		if (level == MARIO_LEVEL_TANUKI)
		{
			level = MARIO_LEVEL_BIG;
			StartUntouchable();
		}
		else if (level == MARIO_LEVEL_BIG)
		{
			level = MARIO_LEVEL_SMALL;
			StartUntouchable();
		}
			else
			{
				DebugOut(L">>> Mario DIE >>> \n");
				SetState(MARIO_STATE_DIE);
			}
		
	}
}

void CMario::OnCollisionWithFireBall(LPCOLLISIONEVENT e)
{
	CFireBall* f = dynamic_cast<CFireBall*>(e->obj);
	if (untouchable == 0 && f->GetState()!= FIREBALL_STATE_HIDDEN)
	{
		if (level == MARIO_LEVEL_TANUKI)
		{
			level = MARIO_LEVEL_BIG;
			StartUntouchable();
		}
		else if (level == MARIO_LEVEL_BIG)
		{
			level = MARIO_LEVEL_SMALL;
			StartUntouchable();
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
		}
	}
}

void CMario::OnCollisionithTanukiLeaf(LPCOLLISIONEVENT e)
{
	CTanukiLeaf* leaf = dynamic_cast<CTanukiLeaf*>(e->obj);
	if( leaf->GetState() == LEAF_STATE_HIDDEN && e->ny> 0  )	
	{
		leaf->SetState(LEAF_STATE_SHOW);
	}
	else if (leaf->GetState() == LEAF_STATE_SHOW || leaf->GetState() == LEAF_STATE_FALL)
	{
		if (level != MARIO_LEVEL_TANUKI)
		{
			level = MARIO_LEVEL_TANUKI;
			e->obj->Delete();
		}
		else
			e->obj->Delete();
	}
}

void CMario::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{

	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	if (koopa->GetState() == KOOPA_STATE_HIT)return;
	if ((koopa->GetState() == KOOPA_STATE_SHELL || koopa->GetState() == KOOPA_STATE_REVIVE)&& isHolding_AKey==true)
	{
		isSlapTail = false;
		koopa->SetState(KOOPA_STATE_HOLD);
		((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->SetKoopa(koopa);
	}
	else if (state == MARIO_STATE_SLAP || state == Mario_STATE_SLAP_RIGHT)
		if (koopa->GetState() ==KOOPA_STATE_WALKING)
			koopa->SetState(KOOPA_STATE_HIT);

	if (e->ny < 0 )//&& koopa->GetState() == KOOPA_STATE_WALKING)
	{
		if (koopa->GetState() == KOOPA_STATE_KICK_RIGHT || koopa->GetState() == KOOPA_STATE_KICK_RIGHT)
			koopa->SetState(KOOPA_STATE_SHELL);
		else if (koopa->GetState() == KOOPA_STATE_WALKING)
		{
			koopa->SetState(KOOPA_STATE_SHELL);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (koopa->GetState() == KOOPA_STATE_SHELL)
		{
			if (nx > 0)
				koopa->SetState(KOOPA_STATE_KICK_RIGHT);
			else
				koopa->SetState(KOOPA_STATE_KICK_LEFT);
		}
	}
	else
	{
		if (untouchable == 0   )
		{
			if (koopa->GetState() != KOOPA_STATE_SHELL && koopa->GetState() != KOOPA_STATE_HIDDEN
				&& koopa->GetState() != KOOPA_STATE_HOLD && koopa->GetState()!=KOOPA_STATE_HIT)
			{
				if (level == MARIO_LEVEL_TANUKI)
				{
					level = MARIO_LEVEL_BIG;
					StartUntouchable();
				}
				else if (level == MARIO_LEVEL_BIG)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}

	//kick shell right
	if (koopa->GetState() == KOOPA_STATE_SHELL && ( e->nx < 0 ) )
	{
		
			koopa->SetState(KOOPA_STATE_KICK_RIGHT);
	}
	if (koopa->GetState() == KOOPA_STATE_SHELL && (e->ny < 0) && this->vx>0)
	{
		if (koopa->KickCooldown() == 1)
			koopa->SetState(KOOPA_STATE_KICK_RIGHT);
	}
	//kcik shell left
	if (koopa->GetState() == KOOPA_STATE_SHELL && e->nx > 0)
	{
		koopa->SetState(KOOPA_STATE_KICK_LEFT);
	}
	if (koopa->GetState() == KOOPA_STATE_SHELL && (e->ny < 0) && this->vx < 0)
	{
		if (koopa->KickCooldown() == 1)
			koopa->SetState(KOOPA_STATE_KICK_LEFT);
	}
}

void CMario::OnCollisionWithWingGoomba(LPCOLLISIONEVENT e)
{
	CWingGoomba* wgoomba = dynamic_cast<CWingGoomba*>(e->obj);
	if (state == MARIO_STATE_SLAP || state == Mario_STATE_SLAP_RIGHT)
		if (wgoomba->GetState() == WGOOMBA_STATE_DIE)
			wgoomba->SetState(WGOOMBA_STATE_DIE);
	// jump on top >> kill WingGoomba and deflect a bit 
	if (e->ny < 0 &&wgoomba->GetState()!=WGOOMBA_STATE_HIDDEN)
	{

		if (wgoomba->GetState() != WGOOMBA_STATE_DIE && wgoomba->GetState() != WGOOMBA_STATE_JUMPING &&
			wgoomba->GetState() != WGOOMBA_STATE_JUMPING_TIMEOUT)
		{
			wgoomba->SetState(WGOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if(wgoomba->GetState() == WGOOMBA_STATE_JUMPING ||
			wgoomba->GetState() == WGOOMBA_STATE_JUMPING_TIMEOUT)
		{
			wgoomba->SetState(WGOOMBA_STATE_WALKING);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0 && wgoomba->GetState()!= WGOOMBA_STATE_HIDDEN)
		{
			if (wgoomba->GetState() != WGOOMBA_STATE_DIE)
			{
				if (level == MARIO_LEVEL_TANUKI)
				{
					level = MARIO_LEVEL_BIG;
					StartUntouchable();
				}
				else if (level == MARIO_LEVEL_BIG)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithWingKoopa(LPCOLLISIONEVENT e)
{
	CWingKoopa* wkoopa = dynamic_cast<CWingKoopa*>(e->obj);
	if (wkoopa->GetState() == WKOOPA_STATE_HIT)return;
	if ((wkoopa->GetState() == WKOOPA_STATE_SHELL || wkoopa->GetState() == WKOOPA_STATE_REVIVE) && isHolding_AKey == true)
	{
		isSlapTail = false;
		wkoopa->SetState(WKOOPA_STATE_HOLD);
		((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->SetWKoopa(wkoopa);
	}
	else
		if (state == MARIO_STATE_SLAP || state == Mario_STATE_SLAP_RIGHT)
			if (wkoopa->GetState() == WKOOPA_STATE_WALKING || wkoopa->GetState() == WKOOPA_STATE_JUMPING
				|| wkoopa->GetState() == WKOOPA_STATE_JUMPING_TIMEOUT)
				wkoopa->SetState(WKOOPA_STATE_HIT);
	// jump on top 
	 if (e->ny < 0)
	{
		if (wkoopa->GetState() == WKOOPA_STATE_KICK_RIGHT || wkoopa->GetState() == WKOOPA_STATE_KICK_RIGHT)
			wkoopa->SetState(WKOOPA_STATE_SHELL);

		else if (wkoopa->GetState() ==WKOOPA_STATE_WALKING )
		{
			wkoopa->SetState(WKOOPA_STATE_SHELL);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (wkoopa->GetState() == WKOOPA_STATE_SHELL)
		{
			if (nx > 0)
				wkoopa->SetState(WKOOPA_STATE_KICK_RIGHT);
			else
				wkoopa->SetState(WKOOPA_STATE_KICK_LEFT);
		}
		else if (wkoopa->GetState() == WKOOPA_STATE_JUMPING ||
			wkoopa->GetState() == WKOOPA_STATE_JUMPING_TIMEOUT)
		{
			wkoopa->SetState(WKOOPA_STATE_WALKING);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else
	{
		//mario get hit
		if (untouchable == 0)
		{
			if (wkoopa->GetState() != WKOOPA_STATE_SHELL && wkoopa->GetState() != WKOOPA_STATE_HIDDEN 
				&&wkoopa->GetState()!=WKOOPA_STATE_HOLD )
			{
				if (level == MARIO_LEVEL_TANUKI)
				{
					level = MARIO_LEVEL_BIG;
					StartUntouchable();
				}
				else if (level == MARIO_LEVEL_BIG)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
	//kick shell right
	if (wkoopa->GetState() == WKOOPA_STATE_SHELL && (e->nx < 0))
	{
		wkoopa->SetState(WKOOPA_STATE_KICK_RIGHT);
	}
	if (wkoopa->GetState() == WKOOPA_STATE_SHELL && (e->ny < 0) && this->vx > 0)
	{
		if (wkoopa->KickCooldown() == 1)
		wkoopa->SetState(WKOOPA_STATE_KICK_RIGHT);
	}
	//kcik shell left
	if (wkoopa->GetState() == WKOOPA_STATE_SHELL && e->nx > 0)
	{
		wkoopa->SetState(WKOOPA_STATE_KICK_LEFT);
	}
	if (wkoopa->GetState() == WKOOPA_STATE_SHELL && (e->ny < 0) && this->vx < 0)
	{
		if (wkoopa->KickCooldown() == 1)
		wkoopa->SetState(WKOOPA_STATE_KICK_LEFT);
	}
}

void CMario::OnCollisionWithColorBox(LPCOLLISIONEVENT e)
{
	
	
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}


int CMario::GetAniIdTanuki()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (/*state == MARIO_STATE_FLY*/ isFlying == true)
		{
			if (vx >= 0)
				aniId = ID_ANI_MARIO_TANUKI_FLY_RIGHT;
			else
				aniId = ID_ANI_MARIO_TANUKI_FLY_LEFT;
		}
		else if (isGlide == true)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_TANUKI_FLY_RIGHT;
			else
				aniId = ID_ANI_MARIO_TANUKI_FLY_LEFT;
		}
		else if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_TANUKI_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_TANUKI_JUMP_RUN_LEFT;
		}
		
		else
		{
			/*if(isSlapTail == true)
				if (nx < 0)
				{
					aniId = ID_ANI_MARIO_TANUKI_SLAP_RIGHT;
					DebugOut(L"[info]slpa trigger right\n");
					slap_time = GetTickCount64();
				}
				else if (nx > 0)
				{
					DebugOut(L"[info]slpa trigger LEFT\n");
					aniId = ID_ANI_MARIO_TANUKI_SLAP_LEFT;
					slap_time = GetTickCount64();
				}*/
			//else if (GetTickCount64() - slap_time > TANUKI_SLAP_TIME || 
				//isSlapTail == false)
				{
					if (nx >= 0)
						aniId = ID_ANI_MARIO_TANUKI_JUMP_WALK_RIGHT;
					else
						aniId = ID_ANI_MARIO_TANUKI_JUMP_WALK_LEFT;
				}
		}
		
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_TANUKI_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_TANUKI_SIT_LEFT;
		}
		else
			
			
			
			if (vx == 0)
			{
				/*if (state == MARIO_STATE_SLAP)
				{
					
				}*/
				if (isSlapTail == true )
				{
					
					if (nx > 0)
					{
						aniId = ID_ANI_MARIO_TANUKI_SLAP_RIGHT;
						//DebugOut(L"[info]slpa trigger right\n");
						slap_time = GetTickCount64();
					}
					else if (nx < 0)
					{
						//DebugOut(L"[info]slpa trigger LEFT\n");
						aniId = ID_ANI_MARIO_TANUKI_SLAP_LEFT;
						slap_time = GetTickCount64();
					}
				}
				else if (GetTickCount64() - slap_time > TANUKI_SLAP_TIME)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_TANUKI_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_TANUKI_IDLE_LEFT;
				}
				
					
			}
			else if (vx > 0)
			{
				/*if (isSlapTail == true && isRunning == false)
				{
					DebugOut(L"[info]slpa walk right\n");
					aniId = ID_ANI_MARIO_TANUKI_SLAP_RIGHT;
					slap_time = GetTickCount64();
				}
				else*/ if (ax < 0)
					aniId = ID_ANI_MARIO_TANUKI_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
				{
					IsSlappingTail(false);
					aniId = ID_ANI_MARIO_TANUKI_RUNNING_RIGHT;
				}
				else if (ax == MARIO_ACCEL_WALK_X )
					aniId = ID_ANI_MARIO_TANUKI_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (isSlapTail == true && isRunning == false)
				{
					aniId = ID_ANI_MARIO_TANUKI_SLAP_LEFT;
					//DebugOut(L"[info]slpa walk LEFT\n");
					slap_time = GetTickCount64();
				}
				else if (ax > 0)
					aniId = ID_ANI_MARIO_TANUKI_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_TANUKI_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X && isSlapTail == false && 
					GetTickCount64() - slap_time > TANUKI_SLAP_TIME)
					aniId = ID_ANI_MARIO_TANUKI_WALKING_LEFT;
			}
	
	if (aniId == -1) aniId = ID_ANI_MARIO_TANUKI_IDLE_RIGHT;
	
	return aniId;
}
void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_TANUKI)
		aniId = GetAniIdTanuki();

	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
	
	DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (level == MARIO_LEVEL_TANUKI) {
			if (vy > 0) {
				ay = 0;
				vy = 0.03f;
				isGlide = true;
				glide_start = GetTickCount64();
				break;
			}
		}
		else {
			if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		}
		
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y +=MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		//DebugOut(L"[INFO] idle TIME\n");
		ax = 0.0f;
		vx = 0.0f;
		break;
	case MARIO_STATE_SLAP:
		
		slap_time = GetTickCount64();
		break;
	case MARIO_STATE_FLY:
		ay = 0;
		vy = -0.1f;
		//vx = 0.2f;
		isFlying = true;
		resetGravity_start = GetTickCount64();
		break;

		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level==MARIO_LEVEL_BIG || level ==MARIO_LEVEL_TANUKI)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	if (this->level == MARIO_LEVEL_BIG)
	{
		IsSlappingTail(false);
	}
	level = l;
}

