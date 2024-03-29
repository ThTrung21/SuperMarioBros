#include <iostream>
#include <fstream>
#include "AssetIDs.h"
#include "Game.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "Decoration.h"
#include "MysteryBox.h"
#include "RedMushroom.h"
#include "ColorBox.h"
#include "Pipe.h"
#include "FirePlant.h"
#include "Koopa.h"
#include "FireBall.h"
#include "Invis_block.h"
#include "Tanuki_Leaf.h"
#include "WingGoomba.h"
#include "CloudBlock.h"
#include "Shadow.h"
#include "GoldBrick.h"
#include "Wood.h"
#include "FirePlant_Short.h"
#include "Chomper.h"
#include "WingKoopa.h"
#include "Pwr_btn.h"
#include "SampleKeyEventHandler.h"
#include"Tail.h"
#include"Hidden_Coin.h"
#include"title.h"
#include "Mini.h"

#include "Node.h"
using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	player = NULL;
	fireball_1 = NULL;
	fireball_2 = NULL;
	mini = NULL;
	if (id != 2)
		key_handler = new CSampleKeyHandler(this);
	else
		key_handler = new CSampleKeyHandlerMap(this);
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);
	
	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
		DebugOut(L"[INFO] Check load ani \n");
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());


	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player!=NULL) 
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}		
			obj = new CMario(x, y);
			player = (CMario*)obj;
		DebugOut(L"[INFO] Player object has been created!\n");
		break;

	case OBJECT_TYPE_TAIL:
		obj = new CTail(x, y);
		tail = (CTail*)obj;
		break;
	case OBJECT_TYPE_MARIO_MINI:
	{
		if (mini!= NULL)
		{
			DebugOut(L"[ERROR] Mini object was created before!\n");
			return;
		}
		obj = new CMarioMini(x, y);
		mini = (CMarioMini*)obj;
		DebugOut(L"[INFO] Mini object has been created!\n");
		break;
	}
	case OBJECT_TYPE_TITLE:
	{
		int id = atoi(tokens[3].c_str());
		obj = new CTitle(x, y, id);
		break; 
	}
	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(x,y); break;

	case OBJECT_TYPE_KOOPA:
	{	
		int koopa_type = atoi(tokens[3].c_str());
		
		obj = new CKoopa(x, y, koopa_type);
		break;
	}
	case OBJECT_TYPE_BRICK:
	{
		int width = atoi(tokens[3].c_str());
		int height = atoi(tokens[4].c_str());
		int sprite = atoi(tokens[5].c_str());
		obj = new CBrick(x, y, width, height, sprite);
	break; 
	}
	
	case OBJECT_TYPE_CLOUD_BLOCK: obj = new CCloudBlock(x, y); break;
	case OBJECT_TYPE_INVIS_BLOCK: obj = new CInvis(x, y); break;
	case OBJECT_TYPE_BTN:
		obj = new CBtn(x, y); 
		button = (CBtn*)obj;
		break;
	case OBJECT_TYPE_COIN:
	{
		bool isHidden = atoi(tokens[3].c_str());
		obj = new CCoin(x, y, isHidden);
		break;
	}
	case OBJECT_TYPE_GOLD_BRICK:
	{
		int content = atoi(tokens[3].c_str());
		int id = atoi(tokens[4].c_str());
		obj = new CGoldBrick(x, y, content, id);
		if (content != 1)
		{
			bricks.push_back(obj);
		}
		break;
	}
	case OBJECT_TYPE_COIN_HIDDEN:
	{
		bool id = atoi(tokens[3].c_str());
		obj = new CHiddenCoin(x, y, id);
		hidden_coins.push_back(obj);
		break;
	}
	case OBJECT_TYPE_PLATFORM:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CPlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}
	case OBJECT_TYPE_COLORBOX:
	{
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int width = atoi(tokens[5].c_str());
		int height = atoi(tokens[6].c_str());

		int sprite_topleft = atoi(tokens[7].c_str());
		int sprite_topmid = atoi(tokens[8].c_str());
		int sprite_topright = atoi(tokens[9].c_str());

		int sprite_midleft = atoi(tokens[10].c_str());
		int sprite_center = atoi(tokens[11].c_str());
		int sprite_midright = atoi(tokens[12].c_str());

		int sprite_botleft = atoi(tokens[13].c_str());
		int sprite_botmid = atoi(tokens[14].c_str());
		int sprite_botright = atoi(tokens[15].c_str());

		obj = new CColorBox(
			x, y,
			cell_width, cell_height, width, height,
			sprite_topleft, sprite_topmid, sprite_topright,
			sprite_midleft, sprite_center, sprite_midright,
			sprite_botleft, sprite_botmid, sprite_botright);

		break;
	}
	case OBJECT_TYPE_SHADOW:
	{
		int height = atoi(tokens[3].c_str());
		int sprite_top = atoi(tokens[4].c_str());
		int sprite_body = atoi(tokens[5].c_str());
		obj = new CShadow(x, y, height, sprite_top, sprite_body);
		break;
	}
	case OBJECT_TYPE_WOOD: obj = new CWood(x, y); break;
	case OBJECT_TYPE_DECOR:
	{	
		int decor_type = atoi(tokens[3].c_str());
		obj = new CDecoration(x, y, decor_type);
		break;
	}
	case OBJECT_TYPE_MYSTERYBOX:
	{
		int icontent = (int)atoi(tokens[3].c_str());
		obj = new CBox(x,y,icontent);
		break;
	}
	case OBJECT_TYPE_MUSHROOM:
	{
		int color = atoi(tokens[3].c_str());
		obj = new CMushroom(x, y,color); break;
	}
	case OBJECT_TYPE_PIPE:
	{
		int height = atoi(tokens[3].c_str());
		int sprite_topleft = atoi(tokens[4].c_str());
		int sprite_topright = atoi(tokens[5].c_str());
		int sprite_bodyleft = atoi(tokens[6].c_str());
		int sprite_bodyright = atoi(tokens[7].c_str());
		int state = atoi(tokens[8].c_str());

		obj = new CPipe(x, y, height,
			sprite_topleft, sprite_topright, sprite_bodyleft, sprite_bodyright, state);
		break;
	}
	case OBJECT_TYPE_FIREPLANT:
		obj = new CFirePlant(x, y);
		break;
	case OBJECT_TYPE_CHOMPER: obj = new CChomper(x, y);	break;
	case OBJECT_TYPE_FIREPLANT_SHORT:
		obj = new CFirePlant_Short(x, y);
		break;
	case OBJECT_TYPE_FIREBALL:
	{
		
		obj = new CFireBall(x, y);
		fireball_1 = (CFireBall*)obj;
	break; 
	}
	case OBJECT_TYPE_FIREBALL_2:
	{
		obj = new CFireBall(x, y);
		fireball_2 = (CFireBall*)obj;
		break;
	}
	case OBJECT_TYPE_TANUKI_LEAF:
		obj = new CTanukiLeaf(x, y);
		break;
	case OBJECT_TYPE_WINGGOOMBA:
		obj = new CWingGoomba(x, y);
		break;
	case OBJECT_TYPE_WINGKOOPA:
		obj = new CWingKoopa(x, y);
		break;

	case OBJECT_TYPE_NODE:
	{
		int Left = (int)atof(tokens[3].c_str());
		int Right = (int)atof(tokens[4].c_str());
		int Top = (int)atof(tokens[5].c_str());
		int Bot = (int)atof(tokens[6].c_str());
		
		int isStage = (int)atof(tokens[7].c_str());
		obj = new CNode(x, y, Left, Right, Top, Bot, isStage);
		break;
	}

	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		int dir = atoi(tokens[6].c_str());
		obj = new CPortal(x, y, r, b, scene_id, dir);
		portal = (CPortal*)obj;
		break;
	}
	


	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);


	objects.push_back(obj);
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)

	if (player == NULL && mini==NULL) //map scenen
	{ 
		return; 
	}
	else //title scene and play scene
	{
		
		float cx, cy;
		if (id!=2) 
		{
			player->GetPosition(cx, cy);

			CGame* game = CGame::GetInstance();
			cx -= game->GetBackBufferWidth() / 2;
			cy -= game->GetBackBufferHeight() / 2;

			if (cx < 0) cx = 0;

			if (cy > -75)cy = 0.0f;
		}
		else 
		{
			cx = 0;
			cy = 0;
		}
		CGame::GetInstance()->SetCamPos(cx, cy /*cy*/);
		
	}
	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well 

*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;
	
	

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}