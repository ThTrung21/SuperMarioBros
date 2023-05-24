#include "MysteryBox.h"

void CBox::Render()
{
	int aniID = ID_ANI_BOX;
	if (state == BOX_STATE_USED)
		aniID = ID_ANI_BOX_USED;
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniID)->Render(x, y);
	
	//RenderBoundingBox();
}

CBox::CBox(float x, float y):CGameObject(x, y)
{
	state = ID_ANI_BOX;
}
void CBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BOX_BBOX_WIDTH / 2;
	t = y - BOX_BBOX_HEIGHT / 2;
	r = l + BOX_BBOX_WIDTH;
	b = t + BOX_BBOX_HEIGHT;
}
void CBox::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);	
}


