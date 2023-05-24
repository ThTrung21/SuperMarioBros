#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BOX 13000
#define ID_ANI_BOX_USED 13001


#define BOX_STATE_NEW 100
#define BOX_STATE_USED 200

#define BOX_WIDTH 16
#define BOX_BBOX_WIDTH 16
#define BOX_BBOX_HEIGHT 16

class CBox : public CGameObject {
protected:
	//1 = new;	0 = used;
	
public:
	CBox(float x, float y);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	
};
