#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Game.h"




class CFireBall : public CGameObject
{
protected:


	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	virtual int IsBlocking() { return 0; }
public:
	CFireBall(float x, float y);


};
