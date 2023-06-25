#include "Shadow.h"
#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"

CShadow::CShadow(float x, float y,
	int height,
	int spriteID_top, int spriteID_body):CGameObject(x, y)
{
	this->height = height;
	this->cellHeight = 8;
	this->cellWidth = 8;

	this->spriteIDTop = spriteID_top;
	this->spriteIDBody = spriteID_body;
}
void CShadow::Render()
{
	if (height < 2) return;
	float yy = y;
	CSprites* s = CSprites::GetInstance();

//
//Top
//
	s->Get(this->spriteIDTop)->Draw(x, yy);
	yy += cellHeight;
//
//body
//
	for (int i = 1; i < height*2; i++)
	{
		s->Get(this->spriteIDBody)->Draw(x, yy);
		yy += cellHeight;
	}
}
void CShadow::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	float cellWidth_div_2 = this->cellWidth / 2;
	l = x - cellWidth_div_2;
	t = y - this->cellHeight / 2;
	r = l + this->cellWidth ;
	b = t + this->cellHeight * this->height;
}
