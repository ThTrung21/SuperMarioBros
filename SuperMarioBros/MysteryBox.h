#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BOX 13000
#define ID_ANI_BOX_USED 13001



#define BOX_STATE_NEW 100
#define BOX_STATE_USED 200
#define BOX_CONTENT_COIN 1
#define BOX_CONTENT_MUSHROOM 2



#define BOX_WIDTH 16
#define BOX_BBOX_WIDTH 16
#define BOX_BBOX_HEIGHT 16

class CBox : public CGameObject {
protected:
	//1 is coin;	2 is mushroom;	3 is tanuki tail;	4 is 
	int icontent;
public:
	CBox(float x, float y, int content);
		
	void Render();
	void Update(DWORD dt){}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetContent();
	

};
