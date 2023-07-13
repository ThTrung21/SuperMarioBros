#pragma once
#include "GameObject.h"

#define MINI_STATE_STOP 0
#define MINI_STATE_LEFT 100
#define MINI_STATE_TOP 200
#define MINI_STATE_RIGHT 300
#define MINI_STATE_BOT 400

#define ID_ANI_MINI	28000
#define MINI_BBOX_WIDTH 16
#define MINI_BBOX_HEIGHT 16

#define MINI_SPEED 0.0006f
class CMini : public CGameObject
{
protected:
	float ax, ay;
	int IsBlocking() { return 1; }
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
public:
	CMini(float x, float y);
	void SetState(int state);
		
};
