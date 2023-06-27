#include "GoldBrick.h"
#include "Mario.h"

CGoldBrick::CGoldBrick(float x, float y, int brick_type):CGameObject(x,y)
{
	this->interact = brick_type;
}

void CGoldBrick::Render()
{
	int aniID = ID_ANI_GOLD_BRICK;

	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniID)->Render(x, y);
	
}

void CGoldBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - GBRICK_BBOX_WIDTH / 2;
	t = y - GBRICK_BBOX_HEIGHT / 2;
	r = l + GBRICK_BBOX_WIDTH;
	b = t + GBRICK_BBOX_HEIGHT;
}