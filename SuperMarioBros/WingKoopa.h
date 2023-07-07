#pragma once
#include "GameObject.h"

#pragma once
#include "GameObject.h"

#define WKOOPA_GRAVITY 0.002f
#define WKOOPA_WALKING_SPEED 0.05f
#define WKOOPA_SHELL_SPEED 0.3f
#define WKOOPA_JUMP_SPEED 0.001f

#define WKOOPA_SHELL_TIMEOUT 5000
#define WKOOPA_REVIVE_TIME 5000
#define WKOOPA_JUMP_WAIT	1000
#define WKOOPA_JUMP_TIME	200

#define WKOOPA_STATE_IDLE 0

#define WKOOPA_STATE_JUMPING	50
#define WKOOPA_STATE_JUMPING_TIMEOUT	60

#define WKOOPA_STATE_WALKING 100
#define WKOOPA_STATE_SHELL 200
#define WKOOPA_STATE_KICK_LEFT 300
#define WKOOPA_STATE_KICK_RIGHT 400
#define WKOOPA_STATE_REVIVE 500
#define WKOOPA_STATE_HIDDEN 600

#define ID_ANI_WKOOPA_JUMPING_LEFT	25001
#define ID_ANI_WKOOPA_JUMPING_RIGHT	25002
#define ID_ANI_WKOOPA_WALKING_LEFT 25003
#define ID_ANI_WKOOPA_WALKING_RIGHT 25004
#define ID_ANI_WKOOPA_SHELL 25005
#define ID_ANI_WKOOPA_REVIVE 25006





#define WKOOPA_BBOX_WIDTH 16
#define WKOOPA_BBOX_HEIGHT 35
#define WKOOPA_BBOX_WALKING_HEIGHT 25
#define WSHELL_BBOX_HEIGHT 16

class CWingKoopa : public CGameObject
{
protected:
	float ax;
	float ay;
	float default_y, default_x;
	float pre_vx;
	int flag;

	ULONGLONG fly_time;
	ULONGLONG fly_timeout;

	ULONGLONG revive_start;
	ULONGLONG shell_start;
	ULONGLONG die_timeout;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	bool MarioDetection(int x);
	bool RespawnDetector(int x);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	//void OnCollisionithTanukiLeaf(LPCOLLISIONEVENT e);
	//void OnCollisionWithMysteryBox(LPCOLLISIONEVENT e);
	//void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
public:
	CWingKoopa(float x, float y);
	virtual void SetState(int state);
	virtual bool IsKoopa() { return 1; }
};

