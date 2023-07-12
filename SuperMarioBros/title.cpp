#pragma once

#include"title.h"

void CTitle::Render()
{
	CSprites* title = CSprites::GetInstance();
	title->Get(spriteID)->Draw(x, y);
}

