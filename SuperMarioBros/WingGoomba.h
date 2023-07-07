#pragma once
#include "GameObject.h"

#define WGOOMBA_GRAVITY 0.002f
#define WGOOMBA_WALKING_SPEED 0.05f
#define WGOOMBA_JUMP_SPEED 0.001f

#define WGOOMBA_BBOX_WIDTH 16
#define WGOOMBA_BBOX_HEIGHT 24
#define WGOOMBA_BBOX_HEIGHT_WALKING 14
#define WGOOMBA_BBOX_HEIGHT_DIE 7

#define WGOOMBA_DIE_TIMEOUT 500
#define WGOOMBA_JUMP_WAIT	1000
#define WGOOMBA_JUMP_TIME	200


#define WGOOMBA_STATE_IDLE	10
#define WGOOMBA_STATE_WALKING 100
#define WGOOMBA_STATE_DIE 200
#define WGOOMBA_STATE_JUMPING 300
#define WGOOMBA_STATE_JUMPING_TIMEOUT 400
#define WGOOMBA_STATE_HIDDEN 500

#define ID_ANI_WGOOMBA_DIE 20001
#define ID_ANI_WGOOMBA_JUMPING 20002
#define ID_ANI_WGOOMBA_WALKING 20003


class CWingGoomba : public CGameObject
{
protected:
	float ax;
	float ay;
	float X, Y;
	int flag;

	ULONGLONG die_start;
	ULONGLONG fly_time;
	ULONGLONG fly_timeout;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	bool MarioDetection(int x);
	bool RespawnDetector(int x);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
public:
	CWingGoomba(float x, float y);
	virtual void SetState(int state);
};