#include "ColorBox.h"
#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"

CColorBox::CColorBox(float x, float y,
	float cell_width, float cell_height,
	int spriteID_TopLeft, int spriteID_TopMid, int spriteID_TopRight,
	int spriteID_MidLeft, int spriteID_Center, int spriteID_MidRight,
	int spriteID_BotLeft, int spriteID_BotMid, int spriteID_BotRight)
{



}

void CColorBox::Render()
{
	if (this->Width <= 0)	return;
	if (this->Height <= 0)	return;
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