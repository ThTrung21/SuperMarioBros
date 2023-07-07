#include "WingKoopa.h"

CWingKoopa::CWingKoopa(float x, float y, int type)
{

}
void CWingKoopa::SetState(int state)
{
}
bool CWingKoopa::RespawnDetector(int mario_x)
{
	int xx = mario_x - (int)default_x;
	if (abs(xx) > 250)
		return 1;
	return 0;
}
void CWingKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
}
void CWingKoopa::OnNoCollision(DWORD dt)
{
}
bool CWingKoopa::MarioDetection(int mario_x)
{
	int xx = mario_x - (int)x;
	if (abs(xx) < 300)
		return 1;
	return 0;
}


void CWingKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}

void CWingKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void CWingKoopa::Render()
{
}


