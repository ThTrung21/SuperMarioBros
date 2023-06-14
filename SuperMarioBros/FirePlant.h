#pragma once
#include"GameObject.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Game.h"
#include "Animation.h"
#include "Animations.h"

#define PLANT_WIDTH 16
#define PLANT_HEIGHT 32

#define PLANT_DIR_TOPLEFT	1
#define	PLANT_DIR_BOTTOMLEFT 2
#define PLANT_DIR_TOPRIGHT 3
#define PLANT_DIR_BOTTOMRIGHT 4

#define PLANT_SPEED	-0.03f
#define PLANT_MOVE_TIMEOUT 50

#define ID_ANI_FIREPLANT_TOPLEFT 15000
#define	ID_ANI_FIREPLANT_BOTTOMLEFT 15001
#define ID_ANI_FIREPLANT_TOPRIGHT 15002
#define ID_ANI_FIREPLANT_BOTTOMRIGHT 15003

class CFirePlant :public CGameObject
{
protected:

	ULONGLONG stop_start;
	bool IsMoving;	
	float TopPos;
	float BotPos;
	float default_y;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CFirePlant(float x, float y);

	virtual void SetState(int state);
};