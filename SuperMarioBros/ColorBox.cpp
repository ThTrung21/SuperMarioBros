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
	this->cellWidth = cellWidth;
	this->cellHeight = cellHeight;


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
	if (this->Width <3 )	return;
	if (this->Height < 3)	return;
	if (Width < 3* cellWidth || Height < 3* cellHeight) return;
	int sizeHor = Width / cellWidth; // numbers of cells horizontally
	int sizeVer = Height / cellHeight;// number of cells vertically
	//Declare reuseable start point
	float xx = x;
	float yy = y;

	CSprites* s = CSprites::GetInstance();
	// Draw Top Left
	s->Get(spriteIDTopLeft)->Draw(x, y); 
	//Draw Top Mid
	xx += this->cellWidth;
	for (int i = 0; i < sizeHor-2; i++) {
		s->Get(spriteIDTopMid)->Draw(xx, yy);
		xx += this->cellWidth;
	}
	//Draw Top Right
	s->Get(spriteIDTopRight)->Draw(xx, yy);
	//Draw Mid Right
	yy += this->cellHeight;
	for (int i = 0; i < sizeVer - 2; i++) {
		s->Get(spriteIDMidRight)->Draw(xx, yy);
		yy += this->cellHeight;
	}
	//Draw Bot Right
	s->Get(spriteIDBotRight)->Draw(xx, yy);
	//Draw Bot Mid
	xx -= this->cellWidth;
	for (int i = 0; i < sizeHor - 2; i++) {
		s->Get(spriteIDBotMid)->Draw(xx, yy);
		xx -= this->cellWidth;
	}
	//Draw Bot Left
	s->Get(spriteIDBotLeft)->Draw(xx, yy);
	//Draw Mid Left
	yy -= this->cellHeight;
	for (int i = 0; i < sizeVer - 2; i++) {
		s->Get(spriteIDMidLeft)->Draw(xx, yy);
		yy -= this->cellHeight;
	}
	//Draw Center
	int xx_center = x + cellWidth;
	for (int i = 0; i < sizeHor; i++) {
		int yy_center = y + cellHeight;
		for (int j = 0; j < sizeVer; j++) {
			s->Get(spriteIDCenter)->Draw(xx, yy);
			yy_center += cellHeight;
		}
		xx_center += cellWidth;
	}

	RenderBoundingBox();
}

void CColorBox::Update()
{

}

void CColorBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	float cellWidth_div_2 = this->cellWidth / 2;
	l = x - cellWidth_div_2;
	t = y - this->cellHeight / 2;
	r = l + this->cellWidth * this->Width;
	b = t + this->cellHeight;
}