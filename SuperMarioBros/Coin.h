#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN 11000


#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 16
#define COIN_BBOX_HEIGHT 16


#define COIN_POPUP_SPEED 0.05f
#define COIN_HIDDEN_EATEN 100
#define COIN_TIMEOUT 500



class CCoin : public CGameObject {
protected:
	//1:hidden inside box	-	0:not hidden
	bool hidden;
	ULONGLONG coin_disapear_start;
	
	int flag = 0;
public:
	CCoin(float x, float y, bool hidden);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	int IsHidden();
	virtual void SetState(int state);
};