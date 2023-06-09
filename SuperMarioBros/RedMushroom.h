#pragma once
#include "GameObject.h"

#define MUSHROOM_GRAVITY 0.0012f
#define MUSHROOM_SPEED 0.05f

#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 16

#define ID_ANI_MUSHROOM_RED 14000


#define MUSHROOM_STATE_HIDDEN 100
#define MUSHROOM_STATE_SHOW 200

class CMushroom : public CGameObject
{
protected:
	float ay, ax;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsColliable() { return 1; }
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CMushroom(float x, float y);
	virtual void SetState(int state);
};
