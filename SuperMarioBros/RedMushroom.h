#pragma once
#include "GameObject.h"

#define MUSHROOM_GRAVITY 0.002f
#define MUSHROOM_SPEED 0.07f

#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 16

#define ID_ANI_MUSHROOM_RED 14000


#define MUSHROOM_STATE_HIDDEN 100
#define MUSHROOM_STATE_SHOW 200
class CMushroom : public CGameObject
{
protected:
	float ay, ax;

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsBlocking() { return 0; }
public:
	CMushroom(float x, float y);
	virtual void SetState(int state);
};
