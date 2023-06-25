#include "ColorBox.h"
#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"

CColorBox::CColorBox(float x, float y, 
	float cell_width, float cell_height,
	int Width, int Height,
	int spriteID_TopLeft, int spriteID_TopMid, int spriteID_TopRight,
	int spriteID_MidLeft, int spriteID_Center, int spriteID_MidRight,
	int spriteID_BotLeft, int spriteID_BotMid, int spriteID_BotRight) :CGameObject(x, y)
{
	this->Width = Width;
	this->Height = Height;
	this->cellWidth = cell_width;
	this->cellHeight = cell_height;


	this->spriteIDTopLeft = spriteID_TopLeft;
	this->spriteIDTopMid = spriteID_TopMid;
	this->spriteIDTopRight= spriteID_TopRight;

	this->spriteIDMidLeft= spriteID_MidLeft;
	this->spriteIDCenter= spriteID_Center;
	this->spriteIDMidRight= spriteID_MidRight;

	this->spriteIDBotLeft= spriteID_BotLeft;
	this->spriteIDBotMid= spriteID_BotMid;
	this->spriteIDBotRight = spriteID_BotRight;

	

}

void CColorBox::Render()
{
	if (this->Width <2 )	return;
	if (this->Height <2)	return;
	

	//Declare reuseable start point
	float xx = x;
	float yy = y;

	CSprites* s = CSprites::GetInstance();
	
	//
	// Top
	// 
	
	//Top Left
	s->Get(this->spriteIDTopLeft)->Draw(xx, yy);
	xx += this->cellWidth;

	//Top Mid
	for (int i = 1; i < this->Width - 1; i++)
	{
		s->Get(this->spriteIDTopMid)->Draw(xx, yy);
		xx += this->cellWidth;
	}

	//Top Right
	s->Get(this->spriteIDTopRight)->Draw(xx, yy);
	yy += cellHeight;
	xx = x;

	//
	//Mid
	//
	for (int i = 1; i < this->Height-1; i++)
	{
		xx = x;
		//Mid Left
		s->Get(this->spriteIDMidLeft)->Draw(xx, yy);
		xx += this->cellWidth;

		//Center
		for (int j = 1; j < this->Width-1; j++)
		{
			s->Get(this->spriteIDCenter)->Draw(xx, yy);
			xx += this->cellWidth;
		}
		//Mid Right
		s->Get(this->spriteIDMidRight)->Draw(xx, yy);
		
		//if (i!=this->Height-1)
		{
			yy += cellWidth;
		}
		

	}
	xx = x;
	
	//
	//Bottom
	//
	 
	//Bot Left
	s->Get(this->spriteIDBotLeft)->Draw(xx, yy);
	xx += this->cellWidth;

	//Bot Mid
	for (int i = 1; i < this->Width - 1; i++)
	{
		s->Get(this->spriteIDBotMid)->Draw(xx, yy);
		xx += this->cellWidth;
	}

	//Bot Right
	s->Get(this->spriteIDBotRight)->Draw(xx, yy);

	//RenderBoundingBox();
}
void CColorBox::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);
	
	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	float xx = x - this->cellWidth / 2 + rect.right / 2;
	float yy = y - this->cellHeight / 2 + rect.bottom / 2;
	CGame::GetInstance()->Draw(xx - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}


void CColorBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	float cellWidth_div_2 = this->cellWidth / 2;
	l = x - cellWidth_div_2;
	t = y - this->cellHeight / 2;
	r = l + this->cellWidth * this->Width;
	b = t + this->cellHeight * this->Height;
}
