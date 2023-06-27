#pragma once
#include "GameObject.h"

#define KOOPA_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.05f
#define KOOPA_SHELL_SPEED 0.3f

#define KOOPA_SHELL_TIMEOUT 7000
#define KOOPA_REVIVE_TIME 5000

#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_SHELL 200
#define KOOPA_STATE_KICK_LEFT -300
#define KOOPA_STATE_KICK_RIGHT -400
#define KOOPA_STATE_REVIVE 500

#define ID_ANI_KOOPA_WALKING_LEFT 16000
#define ID_ANI_KOOPA_WALKING_RIGHT 16001
#define ID_ANI_KOOPA_SHELL 16002
#define ID_ANI_KOOPA_REVIVE 16003

#define ID_ANI_KOOPA_GREEN_WALKING_LEFT 16010
#define ID_ANI_KOOPA_GREEN_WALKING_RIGHT 16011
#define ID_ANI_KOOPA_GREEN_SHELL 16012
#define ID_ANI_KOOPA_GREEN_REVIVE 16013


#define KOOPA_RED 1
#define KOOPA_GREEN 2

#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 25
#define SHELL_BBOX_HEIGHT 16

class CKoopa : public CGameObject
{
protected:
	float ax;
	float ay;
	float default_y;
	float pre_vx;
	
	//type: 1-red 2-green
	int Ktype;
	

	ULONGLONG revive_start;
	ULONGLONG shell_start;
	ULONGLONG die_timeout;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	void OnCollisionithTanukiLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithMysteryBox(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
public:
	CKoopa(float x, float y,int type);
	virtual void SetState(int state);
	virtual bool IsKoopa() { return 1; }
};
