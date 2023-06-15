#pragma once
#include "GameObject.h"

#define KOOPA_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.05f
#define KOOPA_SHELL_SPEED 0.2f

#define KOOPA_SHELL_TIMEOUT 10000

#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_SHELL 200

#define ID_ANI_KOOPA_WALKING_LEFT 16000
#define ID_ANI_KOOPA_WALKING_RIGHT 16001
#define ID_ANI_KOOPA_SHELL 16002
#define ID_ANI_KOOPA_EXTEND 16003


#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 25
#define SHELL_BBOX_HEIGHT 16

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
