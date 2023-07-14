#pragma once


#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define GBRICK_STATE_NEW	100
#define GBRICK_STATE_BOUNCE 150
#define GBRICK_STATE_USED	200

#define GBRICK_STATE_HIDDEN 300	//brick become invisible by button
#define GBRICK_STATE_BROKEN	400	//brick destroy by tail or shell

#define GBRICK_BOUNCE_SPEED 0.15f
#define ID_ANI_GOLD_BRICK 22000
#define ID_ANI_GOLD_BRICK_USED 22001

#define TIME_HIDDEN 300

#define GBRICK_WIDTH 16
#define GBRICK_BBOX_WIDTH 16
#define GBRICK_BBOX_HEIGHT 16

class CGoldBrick : public CGameObject {
protected:
	
	int interact;	//1- can be hit from under for powerup ;		2-none
	int id;
	float X,Y, max_y;
	bool isForceBreak = false;
	ULONGLONG hide_start;
public:
	CGoldBrick(float x, float y,int brick_type,int id) ;
	void Render();
	void Update(DWORD dt,vector<LPGAMEOBJECT>* coObjects);
	bool GetContent(){ return interact; }
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
	
	//virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	int IsCollidable() { return 1; }
	int IsBlocking() { return 1; }
	int GetType() { return interact; }
	int GetId() { return id; }
	void SetForceBreak(bool index)
	{
		isForceBreak = index;
	}
	bool GetForceBreak()
	{
		return isForceBreak;
	}
};
