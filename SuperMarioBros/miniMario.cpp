#include <algorithm>

#include"miniMario.h"
#include "Game.h"
#include "debug.h"

#include "Brick.h"
#include "Portal.h"
#include "GameObject.h"
#include "PlayScene.h"
#include "Node.h"

#include "Collision.h"

CMini::CMini(float x, float y) :CGameObject(x, y)
{
	vx = 0.0f;
	vy = 0.0f;
}

void CMini::Render()
{
	int aniID = ID_ANI_MINI;
	CAnimations::GetInstance()->Get(aniID)->Render(x, y);
	RenderBoundingBox();
}

void CMini::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MINI_BBOX_WIDTH / 2;
	top = y - MINI_BBOX_HEIGHT / 2;
	right = x + MINI_BBOX_WIDTH;
	bottom = y + MINI_BBOX_HEIGHT;
}
void CMini::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{	
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMini::OnNoCollision(DWORD dt)
{
	x = vx * dt;
	y = vy * dt;
}
void CMini::OnCollisionWith(LPCOLLISIONEVENT e)
{
	
	if (dynamic_cast<CNode*>(e->obj)) {
		CNode* node = dynamic_cast<CNode*>(e->obj);
		node->GetDirections(Left, Right, Top, Bot);
		isAtStage = node->GetisStage();
		x = node->Getx();
		y = node->Gety();
		DebugOut(L"[INFO] now at : %d \n", (int)x);
		vx = 0;
		vy = 0;
	}
}
void CMini::SetState(int state)
{
	
	if (vx != 0 || vy != 0) {
		return;
	}
	switch (state)
	{
	
	case MINI_STATE_LEFT:
		if (Left)
			vx = -MINI_SPEED;
		
		break;
	case MINI_STATE_TOP:
		if(Top)
		vy = -MINI_SPEED;
		
		break;
	case MINI_STATE_RIGHT:
		if(Right)
		vx = MINI_SPEED;
		
		break;
	case MINI_STATE_BOT:
		if(Bot)
		vy = MINI_SPEED;
		break;
	}
	CGameObject::SetState(state);
}
