#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BTN 26000
#define ID_ANI_BTN_USED 26001

#define BTN_BBOX_WIDTH 16
#define BTN_BBOX_HEIGHT 16
#define BTN_BBOX_HEIGHT_USED 7

#define BTN_STATE_HIDDEN 1
#define BTN_STATE_SHOW	2
#define BTN_STATE_USED	3
class CBtn : public CGameObject {
	float X, Y;
public:
	CBtn(float x, float y) : CGameObject(x, y) 
	{
		X = x;
		Y = y;
		SetState(BTN_STATE_SHOW);
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 1; }
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void OnCollisionWith(LPCOLLISIONEVENT e);
};
