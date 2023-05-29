#include "Coin.h"
#include "Mario.h"
#include "GameObject.h"
void CCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COIN)->Render(x, y);

	//RenderBoundingBox();
}
CCoin::CCoin(float x, float y, bool isHidden) : CGameObject(x, y)
{
	state = 1;
	coin_disapear_start = -1;
	hidden = isHidden;
}
void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}

int CCoin::IsHidden()
{
	return hidden;
}
void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == COIN_HIDDEN_EATEN && (GetTickCount64()- coin_disapear_start > COIN_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CCoin::SetState(int state)
{
	CGameObject::SetState(state);
	if (state == COIN_HIDDEN_EATEN && hidden == 1)
	{
		coin_disapear_start = GetTickCount64();
		y -= 16;
		flag = 1;

		//vy = -COIN_POPUP_SPEED;
		//this->Delete();

	}

}
