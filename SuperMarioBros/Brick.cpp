#include "Brick.h"

CBrick::CBrick(float x, float y, int width, int height, int spriteID) : CGameObject(x, y) 
{
	this->height = height;
	this->width = width;
	this->spriteID = spriteID;
}

void CBrick::Render()
{
	CSprites* s = CSprites::GetInstance();
	float xx = x;
	float yy = y;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			s->Get(this->spriteID)->Draw(xx, yy);
			yy += 16;
		}
		xx += 16;
	}

	s->Get(this->spriteID)->Draw(xx, yy);
	
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BRICK_BBOX_WIDTH/2;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}