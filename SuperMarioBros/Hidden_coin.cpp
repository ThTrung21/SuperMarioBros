#include "Hidden_Coin.h"
#include "Mario.h"
#include "GameObject.h"
void CHiddenCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_HCOIN)->Render(x, y);

	//RenderBoundingBox();
}
CHiddenCoin::CHiddenCoin(float x, float y, int id) : CGameObject(x, y)
{
	this->id = id;
	vy = 0;
	SetState(HCOIN_STATE_HIDDEN);

}
void CHiddenCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - HCOIN_BBOX_WIDTH / 2;
	t = y - HCOIN_BBOX_HEIGHT / 2;
	r = l + HCOIN_BBOX_WIDTH;
	b = t + HCOIN_BBOX_HEIGHT;
}

int CHiddenCoin::IsHidden()
{
	return hidden;
}
void CHiddenCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CHiddenCoin::SetState(int state)
{
	CGameObject::SetState(state);
	

}
