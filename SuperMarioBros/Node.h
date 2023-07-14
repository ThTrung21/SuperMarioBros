#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_NODE 29000

class CNode : public CGameObject {

	bool isStage = false;
	bool Left = false;
	bool Right = false;
	bool Top = false;
	bool Bot = false;
public:
	CNode(float x, float y, int left, int right, int top, int bot, int isStage) : CGameObject(x, y) {
	
		this->Left = (bool)left;
		this->Right = (bool)right;
		this->Top = (bool)top;
		this->Bot = (bool)bot;
		this->isStage = (bool)isStage;
	}
	virtual int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 1; };
	void Render()
	{
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(ID_ANI_NODE)->Render(x, y);
		//RenderBoundingBox();
	}
	bool GetisStage() { return this->isStage; }

	float Getx() { return this->x; }
	float Gety() { return this->y; }
	
	void GetDirections(bool& left, bool& right, bool& top, bool& bot) {
		left = this->Left;
		right = this->Right;
		top = this->Top;
		bot = this->Bot;
	}
	void Update(DWORD dt) {}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {
		float width = 2.0f;
		float height = 2.0f;
		left = x - width / 2;
		top = y - height / 2;
		right = x + width;
		bottom = y + height;
		
	}
}; 
