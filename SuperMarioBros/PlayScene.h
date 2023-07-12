#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Decoration.h"
#include "MysteryBox.h"
#include "FirePlant.h"
#include "FireBall.h"



class CPlayScene: public CScene
{
protected: 

	// A play scene has to have player, right? 
	LPGAMEOBJECT player;					
	LPGAMEOBJECT fireball_1;
	LPGAMEOBJECT fireball_2;
	LPGAMEOBJECT koopa;
	LPGAMEOBJECT wkoopa;
	LPGAMEOBJECT tail;
	LPGAMEOBJECT button;

	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> fireballs;
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);
	
public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }
	LPGAMEOBJECT GetFireBall(int index) 
	{
		if(index==1)
			return fireball_1;
		return fireball_2;
	}
	LPGAMEOBJECT GetKoopa() { return koopa; }
	LPGAMEOBJECT GetWKoopa() { return wkoopa; }
	LPGAMEOBJECT GetTail() { return tail; }
	LPGAMEOBJECT GetButton() { return button; }

	
	void Clear();
	void PurgeDeletedObjects();

	void SetKoopa(LPGAMEOBJECT thisKoopa) { this->koopa = thisKoopa; }
	void SetWKoopa(LPGAMEOBJECT thisWingKoopa) { this->wkoopa = thisWingKoopa; }
	//void SetFireBall(LPGAMEOBJECT thisFireball) { this->fireball = thisFireball; }


	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

