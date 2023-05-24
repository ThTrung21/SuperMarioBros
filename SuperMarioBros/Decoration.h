#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BUSH 12000
#define BUSH_WIDTH 300



class CDecoration : public CGameObject {
public:
	CDecoration(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	
};
