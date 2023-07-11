#pragma once
#include "GameObject.h"
#include "Game.h"
#include "Mario.h"
#include "PlayScene.h"

#define TAIL_STATE_IDLE 1
#define TAIL_STATE_ACTIVE 2

#define TAIL_WIDTH 30
#define TAIL_HEIGHT 12

#define SLAP_TIME 250
class CTail : public CGameObject
{
protected:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render() { RenderBoundingBox(); }
	virtual int IsBlocking() { return 0; }

	ULONGLONG slaptime;
public:
	CTail(float x, float y);
	void SetState(int state)
	{
		CGameObject::SetState(state);
	}
};
