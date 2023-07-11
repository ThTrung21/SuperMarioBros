#include "Sprite.h"
#include "Sprites.h"
#include "Pipe.h"

#include "Textures.h"

CPipe::CPipe(float x, float y,
	int Height,
	int spriteID_TopLeft, int spriteID_TopRight,
	int spriteID_BodyLeft, int spriteID_BodyRight, int color):CGameObject(x,y)
{
	this->Height = Height;
	this->spriteIDTopLeft = spriteID_TopLeft;
	this->spriteIDTopRight = spriteID_TopRight;
	this->spriteIDBodyLeft = spriteID_BodyLeft;
	this->spriteIDBodyRight = spriteID_BodyRight;
	this->state = color;

}

void CPipe::Render()
{
	
	
	if (this->Height < 2)	return;


	//Declare reuseable start point
	float xx = x;
	float yy = y;

	CSprites* s = CSprites::GetInstance();

	//
	// Top
	// 
	//state:	0-green	/	1-black
	if (state == 0)
	{
		//Top Left
		s->Get(this->spriteIDTopLeft)->Draw(xx, yy);
		xx += this->cellWidth;

		//Top Right
		s->Get(this->spriteIDTopRight)->Draw(xx, yy);
		yy += cellHeight;
		xx = x + 1;

		//
		//Body
		//
		for (int i = 1; i < this->Height; i++)
		{

			//Body Left
			s->Get(this->spriteIDBodyLeft)->Draw(xx, yy);
			xx += this->cellWidth - 1;

			//Body Right
			s->Get(this->spriteIDBodyRight)->Draw(xx, yy);

			yy += cellHeight;
			xx = x + 1;

		}
	}
	else if(state==1)
	{
		
		for (int i = 0; i < this->Height-1; i++)
		{
			
			//Body Left
			s->Get(this->spriteIDTopLeft)->Draw(xx, yy);
			xx += this->cellWidth;

			//Body Right
			s->Get(this->spriteIDTopRight)->Draw(xx, yy);

			yy += cellHeight;
			

		}
		//bottom left
		xx = x;
		s->Get(this->spriteIDBodyLeft)->Draw(xx, yy);
		xx += this->cellWidth;
		s->Get(this->spriteIDBodyRight)->Draw(xx, yy);
		
	}
	
}

void CPipe::RenderBoundingBox()
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

	//cell_width and cell_height == 16
	float xx = x - this->cellWidth / 2 + rect.right / 2;
	float yy = y - this->cellHeight / 2 + rect.bottom / 2;
	CGame::GetInstance()->Draw(xx - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	//cell_width and cell_height == 16


	float cellWidth_div_2 = cellWidth / 2;
	
	l = x - cellWidth_div_2;
	t = y - this->cellHeight / 2;
	r = l + this->cellWidth * 2;
	b = t + this->cellHeight * this->Height;
}
