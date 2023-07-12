#pragma once
#include "GameObject.h"

#define MUSHROOM_GRAVITY 0.002f
#define MUSHROOM_SPEED 0.07f

#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 16

#define ID_ANI_MUSHROOM_RED 14000
#define ID_ANI_MUSHROOM_GREEN 14001

#define MUSHROOM_STATE_HIDDEN 100
#define MUSHROOM_STATE_SHOW 200
#define MUSHROOM_STATE_MOVE 300

#define MUSHROOM_MOVE_WAITTIME 500
class CMushroom : public CGameObject
{
protected:
	float ay, ax;
	ULONGLONG moveDelay;
	ULONGLONG direction;
	int color;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CMushroom(float x, float y,int color);
	virtual void SetState(int state);
};
