#pragma once

#include "debug.h"
#include "Brick.h"
#include "Mini.h"
#include "Node.h"

void CMarioMini::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	
	left = x - MINI_WIDTH / 2;
	top = y - MINI_HEIGHT / 2;
	right = x + MINI_WIDTH;
	bottom = y + MINI_HEIGHT;
}
void CMarioMini::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CMarioMini::Render() {
	int aniID = ID_ANI_MINI;
	CAnimations::GetInstance()->Get(aniID)->Render(x, y);
	RenderBoundingBox();

}
void CMarioMini::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}
void CMarioMini::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (dynamic_cast<CNode*>(e->obj))
	{
		CNode* node = dynamic_cast<CNode*>(e->obj);
		node->GetDirections(Left, Right, Top, Bot);
		DebugOut(L"TOUCH NODE\n");
		isAtStage = node->GetisStage();
		x = node->Getx();
		y = node->Gety();
		vx = 0;
		vy = 0;
	}
	if (dynamic_cast<CBrick*>(e->obj))
	{
		Right = 1;
		vx = 0;
		vy = 0;
	}
}

void CMarioMini::SetState(int state) {
	if (vx != 0 || vy != 0) {
		return;
	}
	switch (state)
	{
	case MARIO_MINI_LEFT:
		if (Left)
			vx = -MINI_SPEED;

		break;
	case MARIO_MINI_RIGHT:
		if (Right)
			vx = MINI_SPEED;

		break;
	case MARIO_MINI_TOP:
		if (Top)
			vy = -MINI_SPEED;
		break;
	case MARIO_MINI_BOT:
		if (Bot)
			vy = MINI_SPEED;
		break;
	default:
		return;
	}
	CGameObject::SetState(state);


}