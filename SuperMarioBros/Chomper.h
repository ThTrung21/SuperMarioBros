#pragma once
#include"GameObject.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Game.h"
#include "Animation.h"
#include "Animations.h"

#define CHOMPER_WIDTH 16
#define CHOMPER_HEIGHT 23



#define CHOMPER_STATE_SLEEP 100
#define CHOMPER_STATE_AWAKE 200
#define CHOMPER_STATE_STOP 300
#define CHOMPER_STATE_DIE 400

#define CHOMPER_SPEED	0.03f
#define CHOMPER_STOP_TIMEOUT 900

#define ID_ANI_CHOMPER 24000


class CChomper :public CGameObject
{
protected:

	ULONGLONG stop_start;
	bool IsMoving;
	float TopPos;
	float BotPos;
	float default_x, default_y;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	bool MarioDetection(int x, int y);
	bool RespawnDetector(int x);
	virtual int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 1; }
	

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CChomper(float x, float y);
	virtual void SetState(int state);
};
