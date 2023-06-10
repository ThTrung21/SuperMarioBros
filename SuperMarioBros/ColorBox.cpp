#include "ColorBox.h"
#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"

CColorBox::CColorBox(float x, float y, int Width, int Weight,
	float cell_width, float cell_height,
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