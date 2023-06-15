#pragma once
#pragma once
#include "GameObject.h"

#define WGOOMBA_GRAVITY 0.002f
#define WGOOMBA_WALKING_SPEED 0.05f


#define WGOOMBA_BBOX_WIDTH 16
#define WGOOMBA_BBOX_HEIGHT 14
#define WGOOMBA_BBOX_HEIGHT_DIE 7

#define WGOOMBA_DIE_TIMEOUT 500

#define WGOOMBA_STATE_WALKING 100
#define WGOOMBA_STATE_DIE 200

#define ID_ANI_WGOOMBA_WALKING 5000
#define ID_ANI_WGOOMBA_DIE 5001

class CWingGoomba : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
public:
	CWingGoomba(float x, float y);
	virtual void SetState(int state);
};