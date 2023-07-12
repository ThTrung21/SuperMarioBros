#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_HCOIN 27000


#define	HCOIN_WIDTH 10
#define HCOIN_BBOX_WIDTH 10
#define HCOIN_BBOX_HEIGHT 16


#define HCOIN_STATE_HIDDEN 100
#define HCOIN_STATE_SHOW	200


#define HCOIN 100
#define HCOIN_TIMEOUT 300



class CHiddenCoin : public CGameObject {
protected:
	//1:hidden inside box	-	0:not hidden
	bool hidden;
	int id;


public:
	CHiddenCoin(float x, float y, int id);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; }
	int IsHidden();
	virtual void SetState(int state);
};
