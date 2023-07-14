#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mini.h"

#include "PlayScene.h"


void CSampleKeyHandlerMap::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMarioMini* mini = (CMarioMini*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetMini();

	switch (KeyCode)
	{
	case DIK_LEFT:
		DebugOut(L"LEFT\n");
		mini->SetState(MARIO_MINI_LEFT);
		break;
	case DIK_RIGHT:
		DebugOut(L"RIGHT\n");
		mini->SetState(MARIO_MINI_RIGHT);
		break;
	case DIK_DOWN:
		DebugOut(L"BOTTOM\n");
		mini->SetState(MARIO_MINI_BOT);
		break;
	case DIK_UP:
		DebugOut(L"UP\n");
		mini->SetState(MARIO_MINI_TOP);
		break;
	case DIK_S:
		DebugOut(L"PRESSED S\n");
		if (mini->GetIsAtStage()) {
			CGame::GetInstance()->InitiateSwitchScene(5);
		}
		break;
	}
}

void CSampleKeyHandlerMap::OnKeyUp(int KeyCode)
{

}

void CSampleKeyHandlerMap::KeyState(BYTE* states)
{
}