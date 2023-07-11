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
	for (int i = 0; i < height; i++)
	{
		xx = x;
		for (int j = 0; j < width; j++)
		{
			
			s->Get(this->spriteID)->Draw(xx, yy);
			xx += 16;
		}
		yy += 16;
	}

	
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - 8;
	t = y - 16 / 2;
	r = l + 16 * this->width;
	b = t +16 * this->height;
}