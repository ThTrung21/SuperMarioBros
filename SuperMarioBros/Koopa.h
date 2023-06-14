#pragma once
#include "GameObject.h"

#define KOOPA_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.05f
#define KOOPA_SHELL_SPEED 0.2f

#define KOOPA_SHELL_TIMEOUT 10000

#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_SHELL 200

#define ID_ANI_KOOPA_WALKIN 16000
#define ID_ANI_KOOPA_RETRACT 16001
#define ID_ANI_KOOPA_EXTEND 16002

class CKoopa : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG shell_start;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CKoopa(float x, float y);
	virtual void SetState(int state);
};
