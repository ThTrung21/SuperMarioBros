#pragma once
#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define MARIO_MINI_LEFT 1
#define MARIO_MINI_RIGHT 2
#define MARIO_MINI_TOP	3
#define MARIO_MINI_BOT 4

#define ID_ANI_MINI	28000

#define MINI_SPEED 0.2f

class CMarioMini : public CGameObject
{
private:
	bool isAtStage = false;
	bool Left = false;
	bool Right = true;
	bool Top = false;
	bool Bot = false;
protected:

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CMarioMini(float x, float y) : CGameObject(x, y) {
		vx = 0;
		vy = 0;
	}
	bool GetIsAtStage() {
		return isAtStage;
	}
	virtual void SetState(int state);
};
