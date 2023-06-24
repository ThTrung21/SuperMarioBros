#pragma once
#include "GameObject.h"

#define LEAF_GRAVITY 0.00001f
#define LEAF_SPEED_Y 0.03f
#define LEAF_SPEED 0.0002f

#define LEAF_BBOX_WIDTH 16
#define LEAF_BBOX_HEIGHT 16

#define ID_ANI_LEAF_POPUP 19000
#define ID_ANI_LEAF_FALL_LEFT 19001
#define ID_ANI_LEAF_FALL_RIGHT 19002

#define LEAF_STATE_HIDDEN 100
#define LEAF_STATE_SHOW 200
#define LEAF_STATE_FALL 300



#define LEAF_FALL_CHANGE_SIDE_TIMEOUT 800
#define LEAF_STATE_DELAY 900
class CTanukiLeaf : public CGameObject
{
protected:
	float ay, ax;
	float border_l, border_r;
	float Y; //default y
	ULONGLONG moveDelay;
	ULONGLONG stateDelay;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	//virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	
public:
	CTanukiLeaf(float x, float y);
	virtual bool IsLeaf() { return 1; }
	virtual void SetState(int state);
};
