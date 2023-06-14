#pragma once
#include"GameObject.h"
#define PLANT_WIDTH 16
#define PLANT_HEIGHT 32

#define PLANT_DIR_TOPLEFT	1
#define PLANT_DIR_TOPRIGHT 2
#define	PLANT_DIR_BOTTOMLEFT 3
#define PLANT_DIR_BOTTOMRIGHT 4



#define ID_ANI_FIREPLANT_TOPLEFT 14000
#define	ID_ANI_FIREPLANT_BOTTOMLEFT 14001

#define ID_ANI_FIREPLANT_TOPRIGHT 14002
#define ID_ANI_FIREPLANT_BOTTOMRIGHT 14003

class CFirePlant :public CGameObject
{
protected:

	ULONGLONG StopTime;
	bool IsStop;
	float TopMost;
	float BotMost;


	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CFirePlant(float x, float y);
	virtual void SetState(int state);
};