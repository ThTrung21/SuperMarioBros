#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"
#include "Koopa.h"
#include "Tail.h"
#include "WingKoopa.h"
void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 

	switch (KeyCode)
	{
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_S:
		mario->SetState(MARIO_STATE_JUMP);
		break;
	case DIK_A:
		mario->IsHolding_AKey(true);
		if (mario->GetLevel() == MARIO_LEVEL_TANUKI)
		{
			//DebugOut(L"[info]slpa trigger\n");
			CTail* tail = (CTail*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetTail();
			if(mario->GetAbsAx()<MARIO_ACCEL_RUN_X)
				tail->SetState(TAIL_STATE_ACTIVE);
			else
				tail->SetState(TAIL_STATE_IDLE);
			mario->IsSlappingTail(true);
		}
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_TANUKI);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_R: // reset
		//Reload();
		break;
	}
}



void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		if (mario->GetLevel() == MARIO_LEVEL_TANUKI)
		{
			if (abs(mario->Getvx()) >= 0.2f) {
				mario->SetState(MARIO_STATE_FLY);
				DebugOut(L"FLYYYY\n");
				break;
			}
			else mario->SetState(MARIO_STATE_RELEASE_JUMP);

		}
		else
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	case DIK_A:
		mario->IsRunning(false);
		CWingKoopa* wkoopa= (CWingKoopa*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetWKoopa();
		CKoopa* koopa = (CKoopa*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetKoopa();
		if (koopa != NULL)
		{
			if (koopa->GetState() == KOOPA_STATE_HOLD)
			{
				if (mario->Getnx() > 0)
					koopa->SetState(KOOPA_STATE_KICK_RIGHT);
				else if (mario->Getnx() < 0)
					koopa->SetState(KOOPA_STATE_KICK_LEFT);
			}
			
		}

		if (wkoopa != NULL)
		{
			if (wkoopa->GetState() == WKOOPA_STATE_HOLD)
			{
				if (mario->Getnx() > 0)
					wkoopa->SetState(WKOOPA_STATE_KICK_RIGHT);
				else if (mario->Getnx() < 0)
					wkoopa->SetState(WKOOPA_STATE_KICK_LEFT);
			}

		}
		if (mario->GetLevel() == MARIO_LEVEL_TANUKI)
		{
			CTail* tail = (CTail*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetTail();
			if (tail != NULL)
				tail->SetState(TAIL_STATE_IDLE);
			mario->IsSlappingTail(false);
		}
		mario->IsHolding_AKey(false);
		
		break;
	}

}


void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CTail* tail = (CTail*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetTail();
	if (game->IsKeyDown(DIK_RIGHT))
	{
		
		if (game->IsKeyDown(DIK_A))
		{
			tail->SetState(TAIL_STATE_IDLE);
			mario->SetState(MARIO_STATE_RUNNING_RIGHT);
			//mario->IsRunning(true);
		}
		else
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A))
		{
			tail->SetState(TAIL_STATE_IDLE);
			mario->SetState(MARIO_STATE_RUNNING_LEFT);
			//mario->IsRunning(true);
		}
		else
			mario->SetState(MARIO_STATE_WALKING_LEFT);
	}
	else
		mario->SetState(MARIO_STATE_IDLE);
}