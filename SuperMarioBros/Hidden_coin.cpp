#include "Hidden_Coin.h"
#include "Mario.h"
#include "GameObject.h"
#include "GoldBrick.h"
#include "Pwr_btn.h"
#include "PlayScene.h"

void CHiddenCoin::Render()
{
	if (state == HCOIN_STATE_SHOW)
	{
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(ID_ANI_HCOIN)->Render(x, y);
	}
	//RenderBoundingBox();
}
CHiddenCoin::CHiddenCoin(float x, float y, int id) : CGameObject(x, y)
{
	this->id = id;
	//vy = 0;
	SetState(HCOIN_STATE_HIDDEN);

}
void CHiddenCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state == HCOIN_STATE_SHOW)
	{
		l = x - HCOIN_BBOX_WIDTH / 2;
		t = y - HCOIN_BBOX_HEIGHT / 2;
		r = l + HCOIN_BBOX_WIDTH;
		b = t + HCOIN_BBOX_HEIGHT;
	}
}


void CHiddenCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
		


#pragma region button_pushed_logic
	CBtn* button = (CBtn*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetButton();
	if (button->GetState() == BTN_STATE_USED)
	{
		if(!isDestroy)
			SetState(HCOIN_STATE_SHOW);
		else
		{
			isDeleted = true;
		}

	}
#pragma endregion
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}



void CHiddenCoin::SetState(int state)
{
	CGameObject::SetState(state);
	

}
