#pragma once

#include "GameObject.h"

/*
	Object that triggers scene switching
*/
class CPortal : public CGameObject
{
	int scene_id;	// target scene to switch to 
	int direction=1;	//1 is up	2 is down
	float width;
	float height; 
public:
	CPortal(float l, float t, float r, float b, int scene_id,int dir);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);

	void RenderBoundingBox(void);
	int GetDir()//1 up		2 down
	{ return direction; }
	int GetSceneId() { return scene_id;  }
	int IsBlocking() { return 0; }
};