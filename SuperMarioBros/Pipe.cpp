#include "Sprite.h"
#include "Sprites.h"
#include "Pipe.h"

#include "Textures.h"

CPipe::CPipe(float x, float y,
	int Height,
	int spriteID_TopLeft, int spriteID_TopRight,
	int spriteID_BodyLeft, int spriteID_BodyRight, int accessibility):CGameObject(x,y)
{
	this->Height = Height;
	this->spriteIDTopLeft = spriteID_TopLeft;
	this->spriteIDTopRight = spriteID_TopRight;
	this->spriteIDBodyLeft = spriteID_BodyLeft;
	this->spriteIDBodyRight = spriteID_BodyRight;
	this->state = accessibility;

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
	float xx = x - 16 / 2 + rect.right / 2;
	float yy = y - 16 / 2 + rect.bottom / 2;
	CGame::GetInstance()->Draw(xx - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	//cell_width and cell_height == 16
	float cellWidth = 16, cellHeight = 16;

	float cellWidth_div_2 = cellWidth / 2;
	
	l = x - cellWidth_div_2;
	t = y - cellHeight / 2;
	r = l + cellWidth * 2;
	b = t + cellHeight * this->Height;
}
