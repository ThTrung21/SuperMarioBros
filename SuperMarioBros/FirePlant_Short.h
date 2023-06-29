#pragma once
#include"GameObject.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Game.h"
#include "Animation.h"
#include "Animations.h"

#define SHORT_PLANT_WIDTH 16
#define SHORT_PLANT_HEIGHT 23

#define SHORT_PLANT_DIR_TOPLEFT	1
#define	SHORT_PLANT_DIR_BOTTOMLEFT 2
#define SHORT_PLANT_DIR_TOPRIGHT 3
#define SHORT_PLANT_DIR_BOTTOMRIGHT 4

#define SHORT_PLANT_STATE_SLEEP 100
#define SHORT_PLANT_STATE_AWAKE 200
#define SHORT_PLANT_STATE_STOP 300

#define SHORT_PLANT_SPEED	0.03f
#define SHORT_PLANT_STOP_TIMEOUT 1200

#define ID_ANI_SHORT_FIREPLANT_TOPLEFT 15100
#define	ID_ANI_SHORT_FIREPLANT_BOTTOMLEFT 15101
#define ID_ANI_SHORT_FIREPLANT_TOPRIGHT 15102
#define ID_ANI_SHORT_FIREPLANT_BOTTOMRIGHT 15103

class CFirePlant_Short :public CGameObject
{
protected:

	ULONGLONG stop_start;
	bool IsMoving;
	float TopPos;
	float BotPos;
	float default_y;
	int direction;
	bool isShooting;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	bool MarioDetection(int x, int y);
	//virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CFirePlant_Short(float x, float y);
	void SetDir(int dir);
	virtual void SetState(int state);
};
