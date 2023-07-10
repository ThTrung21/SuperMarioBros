#pragma once


#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define GBRICK_STATE_NEW	100
#define GBRICK_STATE_BOUNCE 150
#define GBRICK_STATE_USED	200
#define GBRICK_STATE_HIDDEN 300

#define GBRICK_BOUNCE_SPEED 0.15f
#define ID_ANI_GOLD_BRICK 22000
#define ID_ANI_GOLD_BRICK_USED 22001

#define GBRICK_WIDTH 16
#define GBRICK_BBOX_WIDTH 16
#define GBRICK_BBOX_HEIGHT 16

class CGoldBrick : public CGameObject {
protected:
	//1- can be hit from under for powerup ;		2-none
	int interact;
	float X,Y, max_y;
	int mario_level;
public:
	CGoldBrick(float x, float y,int brick_type) ;
	void Render();
	void Update(DWORD dt,vector<LPGAMEOBJECT>* coObjects);
	bool GetContent(){ return interact; }
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state,int mario_level);
	
	//virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	int IsCollidable() { return 1; }
	int GetType() { return interact; }
};
