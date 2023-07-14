#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "miniMario.h"

#include "PlayScene.h"


void CSampleKeyHandlerMap::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMini* mini = (CMini*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetMini();

	switch (KeyCode)
	{
	case DIK_LEFT:
		mini->SetState(MINI_STATE_LEFT);
		break;
	case DIK_RIGHT:
		mini->SetState(MINI_STATE_RIGHT);
		break;
	case DIK_DOWN:
		mini->SetState(MINI_STATE_BOT);
		break;
	case DIK_UP:
		mini->SetState(MINI_STATE_TOP);
		break;
	case DIK_S:
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