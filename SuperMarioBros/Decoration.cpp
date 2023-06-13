#include"Decoration.h"
#include "GameObject.h"
CDecoration::CDecoration(float x, float y,int type) : CGameObject(x,y)
{
	this->typeID = type;
}

void CDecoration::Render()
{
	
	CSprites* decorators  = CSprites::GetInstance();
	decorators->Get(typeID)->Draw(x, y);
	
}


void CDecoration::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	/*l = x - DECOR_BBOX_WIDTH / 2;
	t = y - DECOR_BBOX_HEIGHT / 2;
	r = l + DECOR_BBOX_WIDTH;
	b = t + DECOR_BBOX_HEIGHT;*/
}

