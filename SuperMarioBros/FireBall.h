#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Game.h"


#define FIREBALL_WIDTH 8
#define FIREBALL_HEIGHT 8

#define ID_ANI_FIREBALL_LEFT 17000
#define	ID_ANI_FIREBALL_RIGHT 17001


#define FIREBALL_STATE_HIDDEN -1

//direction
#define FIREBALL_DIR_TOP_LEFT 1
#define FIREBALL_DIR_UPMID_LEFT 2
#define FIREBALL_DIR_LOMID_LEFT 3
#define FIREBALL_DIR_BOT_LEFT 4

#define FIREBALL_DIR_TOP_RIGHT 5
#define FIREBALL_DIR_UPMID_RIGHT 6
#define FIREBALL_DIR_LOMID_RIGHT 7
#define FIREBALL_DIR_BOT_RIGHT 8

//different vy,vx for different direction
#define FIREBALL_SPEED_X_FAST 0.07f
#define FIREBALL_SPEED_X_SLOW 0.05f
 

#define FIREBALL_SPEED_Y_FAST 0.05f
#define FIREBALL_SPEED_Y_SLOW 0.02f

class CFireBall : public CGameObject
{
protected:
	float X, Y;
	
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void ResetPos();
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CFireBall(float x, float y);
	float GetX() { return x; }
	virtual void SetState(int state);
	
};
