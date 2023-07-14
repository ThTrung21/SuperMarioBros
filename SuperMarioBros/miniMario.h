#pragma once
#include "GameObject.h"
#include "Game.h"
#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define MINI_STATE_LEFT 100
#define MINI_STATE_TOP 200
#define MINI_STATE_RIGHT 300
#define MINI_STATE_BOT 400

#define ID_ANI_MINI	28000
#define MINI_BBOX_WIDTH 10.0f
#define MINI_BBOX_HEIGHT 10.0f

#define MINI_SPEED 0.15f

class CMini : public CGameObject
{
protected:
	bool isAtStage = false;
	bool Left = false;
	bool Right = true;
	bool Top = false;
	bool Bot = false;

	int IsBlocking() { return 0; }
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	
	int IsCollidable() { return 1; }
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
public:
	CMini(float x, float y);
	void SetState(int state);
	bool GetIsAtStage()
	{
		return isAtStage;
	}
};
