#pragma once

//
// This file contains all IDs of game assets 
//

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20
#define ID_TEX_WORLD 30

#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPA	3
#define OBJECT_TYPE_COIN 4
#define OBJECT_TYPE_PLATFORM 5

#define OBJECT_TYPE_DECOR 6

#define OBJECT_TYPE_MYSTERYBOX 7
#define OBJECT_TYPE_MUSHROOM_RED 8
#define OBJECT_TYPE_TANUKI_LEAF 9

#define OBJECT_TYPE_COLORBOX 10
#define OBJECT_TYPE_PIPE 11

#define OBJECT_TYPE_FIREPLANT 12
#define OBJECT_TYPE_FIREBALL 13
#define OBJECT_TYPE_WINGGOOMBA 14

#define OBJECT_TYPE_INVIS_BLOCK 15

#define OBJECT_TYPE_CLOUD_BLOCK 16
#define OBJECT_TYPE_SHADOW 17
#define OBJECT_TYPE_GOLD_BRICK 18
#define OBJECT_TYPE_WOOD 19

#define OBJECT_TYPE_FIREPLANT_SHORT 20
#define OBJECT_TYPE_CHOMPER 21
#define OBJECT_TYPE_WINGKOOPA 22
#define OBJECT_TYPE_BTN 23
#define OBJECT_TYPE_TAIL 24
#define OBJECT_TYPE_PORTAL	50



#pragma region MARIO 

#define ID_SPRITE_MARIO 10000
#define ID_SPRITE_MARIO_BIG (ID_SPRITE_MARIO + 1000)
#define ID_SPRITE_MARIO_BIG_IDLE (ID_SPRITE_MARIO_BIG + 100)
#define ID_SPRITE_MARIO_BIG_IDLE_LEFT (ID_SPRITE_MARIO_BIG_IDLE + 10)
#define ID_SPRITE_MARIO_BIG_IDLE_RIGHT (ID_SPRITE_MARIO_BIG_IDLE + 20)

#define ID_SPRITE_MARIO_BIG_WALKING (ID_SPRITE_MARIO_BIG + 200)
#define ID_SPRITE_MARIO_BIG_WALKING_LEFT (ID_SPRITE_MARIO_BIG_WALKING + 10)
#define ID_SPRITE_MARIO_BIG_WALKING_RIGHT (ID_SPRITE_MARIO_BIG_WALKING + 20)
#define ID_SPRITE_MARIO_BIG_RUNNING (ID_SPRITE_MARIO_BIG + 300)
#define ID_SPRITE_MARIO_BIG_RUNNING_LEFT (ID_SPRITE_MARIO_BIG_RUNNING + 10)
#define ID_SPRITE_MARIO_BIG_RUNNING_RIGHT (ID_SPRITE_MARIO_BIG_RUNNING + 20)
#define ID_SPRITE_MARIO_BIG_JUMP (ID_SPRITE_MARIO_BIG + 400)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK (ID_SPRITE_MARIO_BIG_JUMP + 10)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_LEFT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN (ID_SPRITE_MARIO_BIG_JUMP + 20)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_LEFT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 6)
#define ID_SPRITE_MARIO_BIG_SIT (ID_SPRITE_MARIO_BIG + 500)
#define ID_SPRITE_MARIO_BIG_SIT_LEFT (ID_SPRITE_MARIO_BIG_SIT + 10)
#define ID_SPRITE_MARIO_BIG_SIT_RIGHT (ID_SPRITE_MARIO_BIG_SIT + 20)
#define ID_SPRITE_MARIO_BIG_BRACE (ID_SPRITE_MARIO_BIG + 600)
#define ID_SPRITE_MARIO_BIG_BRACE_LEFT (ID_SPRITE_MARIO_BIG_BRACE + 10)
#define ID_SPRITE_MARIO_BIG_BRACE_RIGHT (ID_SPRITE_MARIO_BIG_BRACE + 20)

#define ID_SPRITE_MARIO_DIE (ID_SPRITE_MARIO + 3000)

#define ID_SPRITE_MARIO_SMALL (ID_SPRITE_MARIO + 2000)
#define ID_SPRITE_MARIO_SMALL_IDLE (ID_SPRITE_MARIO_SMALL + 100)
#define ID_SPRITE_MARIO_SMALL_IDLE_LEFT (ID_SPRITE_MARIO_SMALL_IDLE + 10)
#define ID_SPRITE_MARIO_SMALL_IDLE_RIGHT (ID_SPRITE_MARIO_SMALL_IDLE + 20)

#define ID_SPRITE_MARIO_SMALL_WALKING (ID_SPRITE_MARIO_SMALL + 200)
#define ID_SPRITE_MARIO_SMALL_WALKING_LEFT (ID_SPRITE_MARIO_SMALL_WALKING + 10)
#define ID_SPRITE_MARIO_SMALL_WALKING_RIGHT (ID_SPRITE_MARIO_SMALL_WALKING + 20)
#define ID_SPRITE_MARIO_SMALL_RUNNING (ID_SPRITE_MARIO_SMALL + 300)
#define ID_SPRITE_MARIO_SMALL_RUNNING_LEFT (ID_SPRITE_MARIO_SMALL_RUNNING + 10)
#define ID_SPRITE_MARIO_SMALL_RUNNING_RIGHT (ID_SPRITE_MARIO_SMALL_RUNNING + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP (ID_SPRITE_MARIO_SMALL + 400)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK (ID_SPRITE_MARIO_SMALL_JUMP + 10)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN (ID_SPRITE_MARIO_SMALL_JUMP + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 6)

#define ID_SPRITE_MARIO_SMALL_SIT (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_SIT_LEFT (ID_SPRITE_MARIO_SMALL_SIT + 10)
#define ID_SPRITE_MARIO_SMALL_SIT_RIGHT (ID_SPRITE_MARIO_SMALL_SIT + 20)

#define ID_SPRITE_MARIO_SMALL_BRACE (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_BRACE_LEFT (ID_SPRITE_MARIO_SMALL_BRACE + 10)
#define ID_SPRITE_MARIO_SMALL_BRACE_RIGHT (ID_SPRITE_MARIO_SMALL_BRACE + 20)



#define ID_SPRITE_MARIO_TANUKI (ID_SPRITE_MARIO + 3000)

#define ID_SPRITE_MARIO_TANUKI_IDLE (ID_SPRITE_MARIO_TANUKI + 100)
#define ID_SPRITE_MARIO_TANUKI_IDLE_LEFT (ID_SPRITE_MARIO_TANUKI_IDLE + 10)
#define ID_SPRITE_MARIO_TANUKI_IDLE_RIGHT (ID_SPRITE_MARIO_TANUKI_IDLE + 20)

#define ID_SPRITE_MARIO_TANUKI_WALKING (ID_SPRITE_MARIO_TANUKI + 200)
#define ID_SPRITE_MARIO_TANUKI_WALKING_LEFT (ID_SPRITE_MARIO_TANUKI_WALKING + 10)
#define ID_SPRITE_MARIO_TANUKI_WALKING_RIGHT (ID_SPRITE_MARIO_TANUKI_WALKING + 20)
#define ID_SPRITE_MARIO_TANUKI_RUNNING (ID_SPRITE_MARIO_TANUKI + 300)
#define ID_SPRITE_MARIO_TANUKI_RUNNING_LEFT (ID_SPRITE_MARIO_TANUKI_RUNNING + 10)
#define ID_SPRITE_MARIO_TANUKI_RUNNING_RIGHT (ID_SPRITE_MARIO_TANUKI_RUNNING + 20)

#define ID_SPRITE_MARIO_TANUKI_JUMP (ID_SPRITE_MARIO_TANUKI + 400)
#define ID_SPRITE_MARIO_TANUKI_JUMP_WALK (ID_SPRITE_MARIO_TANUKI_JUMP + 10)
#define ID_SPRITE_MARIO_TANUKI_JUMP_WALK_LEFT (ID_SPRITE_MARIO_TANUKI_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_TANUKI_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_TANUKI_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_TANUKI_JUMP_RUN (ID_SPRITE_MARIO_TANUKI_JUMP + 20)
#define ID_SPRITE_MARIO_TANUKI_JUMP_RUN_LEFT (ID_SPRITE_MARIO_TANUKI_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_TANUKI_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_TANUKI_JUMP_RUN + 6)

#define ID_SPRITE_MARIO_TANUKI_SIT (ID_SPRITE_MARIO_TANUKI + 500)
#define ID_SPRITE_MARIO_TANUKI_SIT_LEFT (ID_SPRITE_MARIO_TANUKI_SIT + 10)
#define ID_SPRITE_MARIO_TANUKI_SIT_RIGHT (ID_SPRITE_MARIO_TANUKI_SIT + 20)

#define ID_SPRITE_MARIO_TANUKI_BRACE (ID_SPRITE_MARIO_TANUKI + 600)
#define ID_SPRITE_MARIO_TANUKI_BRACE_LEFT (ID_SPRITE_MARIO_TANUKI_BRACE + 10)
#define ID_SPRITE_MARIO_TANUKI_BRACE_RIGHT (ID_SPRITE_MARIO_TANUKI_BRACE + 20)

#define ID_SPRITE_MARIO_TANUKI_SLAP (ID_SPRITE_MARIO_TANUKI +700)
#define ID_SPRITE_MARIO_TANUKI_SLAP_FRONT (ID_SPRITE_MARIO_TANUKI_SLAP + 10)
#define ID_SPRITE_MARIO_TANUKI_SLAP_BACK (ID_SPRITE_MARIO_TANUKI_SLAP+20)
#define ID_SPRITE_MARIO_TANUKI_SLAP_LEFT (ID_SPRITE_MARIO_TANUKI_SLAP +30)
#define ID_SPRITE_MARIO_TANUKI_SLAP_RIGHT (ID_SPRITE_MARIO_TANUKI_SLAP +40)

#define ID_SPRITE_MARIO_TANUKI_FLY (ID_SPRITE_MARIO_TANUKI +800
#define ID_SPRITE_MARIO_FLY_LEFT (ID_SPRITE_MARIO_TANUKI_FLY+10)
#define ID_SPRITE_MARIO_FLY_LEFT_1 (ID_SPRITE_MARIO_FLY_LEFT+1)
#define ID_SPRITE_MARIO_FLY_LEFT_2 (ID_SPRITE_MARIO_FLY_LEFT+2)
#define ID_SPRITE_MARIO_FLY_RIGHT (ID_SPRITE_MARIO_TANUKI_FLY+20)
#define ID_SPRITE_MARIO_FLY_RIGHT_1 (ID_SPRITE_MARIO_FLY_LEFT+1)
#define ID_SPRITE_MARIO_FLY_RIGHT_2 (ID_SPRITE_MARIO_FLY_LEFT+2)
#pragma endregion 

#define ID_SPRITE_BRICK 20000
#define ID_SPRITE_INVIS_BLOCK 20100

#define ID_SPRITE_GOLD_BRICK 20200
#define ID_SPRITE_GOLD_BRICK_1 (ID_SPRITE_GOLD_BRICK+1)
#define ID_SPRITE_GOLD_BRICK_2 (ID_SPRITE_GOLD_BRICK+2)
#define ID_SPRITE_GOLD_BRICK_3 (ID_SPRITE_GOLD_BRICK+3)
#define ID_SPRITE_GOLD_BRICK_4 (ID_SPRITE_GOLD_BRICK+4)
#define ID_SPRITE_GOLD_BRICK_USED (ID_SPRITE_GOLD_BRICK+5)

#define ID_SPRITE_GOOMBA 30000
#define ID_SPRITE_GOOMBA_WALK (ID_SPRITE_GOOMBA + 1000)
#define ID_SPRITE_GOOMBA_DIE (ID_SPRITE_GOOMBA + 2000)

#define ID_SPRITE_COIN 40000

#define ID_SPRITE_CLOUD 50000
#define ID_SPRITE_CLOUD_BEGIN (ID_SPRITE_CLOUD+1000)
#define ID_SPRITE_CLOUD_MIDDLE (ID_SPRITE_CLOUD+2000)
#define ID_SPRITE_CLOUD_END (ID_SPRITE_CLOUD+3000)

#define ID_SPRITE_BASE_PLATFORM 60000
#define ID_SPRITE_BASE_PLATFORM_START (ID_SPRITE_BASE_PLATFORM +1000)
#define ID_SPRITE_BASE_PLATFORM_MID (ID_SPRITE_BASE_PLATFORM +2000)
#define ID_SPRITE_BASE_PLATFORM_END (ID_SPRITE_BASE_PLATFORM +3000)
#define ID_SPRITE_BASE_PLATFORM_UNDER_START (ID_SPRITE_BASE_PLATFORM +4000)
#define ID_SPRITE_BASE_PLATFORM_UNDER_MID (ID_SPRITE_BASE_PLATFORM +5000)
#define ID_SPRITE_BASE_PLATFORM_UNDER_END (ID_SPRITE_BASE_PLATFORM +6000)

#pragma region DECOR
#define ID_SPRITE_DECOR 70000

#define	ID_SPRITE_DECOR_BUSH_BIG (ID_SPRITE_DECOR + 1000)
#define ID_SPRITE_DECOR_BUSH_BIG_FLIP (ID_SPRITE_DECOR + 1001)
#define	ID_SPRITE_DECOR_BUSH_MEDIUM (ID_SPRITE_DECOR + 1100)
#define	ID_SPRITE_DECOR_BUSH_SMALL (ID_SPRITE_DECOR	+ 1200)
#define	ID_SPRITE_DECOR_BUSH_TINY (ID_SPRITE_DECOR_BIG	+ 1300)

#define ID_SPRITE_DECOR_CLOUD_BIG (ID_SPRITE_DECOR +2000)
#define ID_SPRITE_DECOR_CLOUD_MEDIUM (ID_SPRITE_DECOR +2100)
#define ID_SPRITE_DECOR_CLOUD_SMALL (ID_SPRITE_DECOR +2200)

#pragma endregion



#define ID_SPRITE_MYSTERYBOX_1	80000
#define ID_SPRITE_MYSTERYBOX_2	(ID_SPRITE_MYSTERYBOX_1+1000)
#define ID_SPRITE_MYSTERYBOX_3	(ID_SPRITE_MYSTERYBOX_1+2000)
#define ID_SPRITE_MYSTERYBOX_4	(ID_SPRITE_MYSTERYBOX_1+3000)
#define ID_SPRITE_MYSTERYBOX_USED	(ID_SPRITE_MYSTERYBOX_1+4000)

#define ID_SPRTIE_MUSHROOM_RED 90000
#define ID_SPRITE_MUSHROOM_GREEN 91000

#define ID_SPRITE_TANUKI_LEAF 92000
#define ID_SPRITE_TANUKI_LEAF_FLIP 93000

#pragma region COLOR_BOX
#define ID_SPRITE_COLORBOX 100000

//ColorBox	Pink
#define ID_SPRITE_COLORBOX_PINK_TOP_LEFT (ID_SPRITE_COLORBOX+1)
#define ID_SRPITE_COLORBOX_PINK_TOP_MID (ID_SPRITE_COLORBOX+2)
#define ID_SPRITE_COLORBOX_PINK_TOP_RIGHT (ID_SPRITE_COLORBOX+3)

#define ID_SRPITE_COLORBOX_PINK_MID_LEFT (ID_SPRITE_COLORBOX+4)
#define	ID_SRPITE_COLORBOX_PINK_CENTER (ID_SPRITE_COLORBOX+5)
#define ID_SRPITE_COLORBOX_PINK_MID_RIGHT (ID_SPRITE_COLORBOX+6)

#define ID_SRPITE_COLORBOX_PINK_BOT_LEFT (ID_SPRITE_COLORBOX+7)
#define ID_SRPITE_COLORBOX_PINK_BOT_MID (ID_SPRITE_COLORBOX+8)
#define ID_SRPITE_COLORBOX_PINK_BOT_RIGHT (ID_SPRITE_COLORBOX+9)

//ColorBox	Blue
#define ID_SRPITE_COLORBOX_BLUE_TOP_LEFT (ID_SPRITE_COLORBOX+101)
#define ID_SRPITE_COLORBOX_BLUE_TOP_CENTER (ID_SPRITE_COLORBOX+102)
#define ID_SRPITE_COLORBOX_BLUE_TOP_RIGHT (ID_SPRITE_COLORBOX+103)

#define ID_SRPITE_COLORBOX_BLUE_MID_LEFT (ID_SPRITE_COLORBOX+104)
#define ID_SRPITE_COLORBOX_BLUE_CENTER (ID_SPRITE_COLORBOX+105)
#define ID_SRPITE_COLORBOX_BLUE_MID_RIGHT (ID_SPRITE_COLORBOX+106)

#define ID_SRPITE_COLORBOX_BLUE_BOT_LEFT (ID_SPRITE_COLORBOX+107)
#define ID_SRPITE_COLORBOX_BLUE_BOT_MID (ID_SPRITE_COLORBOX+108)
#define ID_SRPITE_COLORBOX_BLUE_BOT_RIGHT (ID_SPRITE_COLORBOX+109)

//ColorBox	GREEN
#define ID_SPRITE_COLORBOX_GREEN_TOP_LEFT (ID_SPRITE_COLORBOX+201)
#define ID_SRPITE_COLORBOX_GREEN_TOP_MID (ID_SPRITE_COLORBOX+202)
#define ID_SPRITE_COLORBOX_GREEN_TOP_RIGHT (ID_SPRITE_COLORBOX+203)

#define ID_SRPITE_COLORBOX_GREEN_MID_LEFT (ID_SPRITE_COLORBOX+204)
#define	ID_SRPITE_COLORBOX_GREEN_CENTER (ID_SPRITE_COLORBOX+205)
#define ID_SRPITE_COLORBOX_GREEN_MID_RIGHT (ID_SPRITE_COLORBOX+206)

#define ID_SRPITE_COLORBOX_GREEN_BOT_LEFT (ID_SPRITE_COLORBOX+207)
#define ID_SRPITE_COLORBOX_GREEN_BOT_MID (ID_SPRITE_COLORBOX+208)
#define ID_SRPITE_COLORBOX_GREEN_BOT_RIGHT (ID_SPRITE_COLORBOX+209)

//ColorBox	WHITE
#define ID_SRPITE_COLORBOX_WHITE_TOP_LEFT (ID_SPRITE_COLORBOX+301)
#define ID_SRPITE_COLORBOX_WHITE_TOP_CENTER (ID_SPRITE_COLORBOX+302)
#define ID_SRPITE_COLORBOX_WHITE_TOP_RIGHT (ID_SPRITE_COLORBOX+303)

#define ID_SRPITE_COLORBOX_WHITE_MID_LEFT (ID_SPRITE_COLORBOX+304)
#define ID_SRPITE_COLORBOX_WHITE_CENTER (ID_SPRITE_COLORBOX+305)
#define ID_SRPITE_COLORBOX_WHITE_MID_RIGHT (ID_SPRITE_COLORBOX+306)

#define ID_SRPITE_COLORBOX_WHITE_BOT_LEFT (ID_SPRITE_COLORBOX+307)
#define ID_SRPITE_COLORBOX_WHITE_BOT_MID (ID_SPRITE_COLORBOX+308)
#define ID_SRPITE_COLORBOX_WHITE_BOT_RIGHT (ID_SPRITE_COLORBOX+309)


#pragma endregion


#define ID_SPRITE_PIPE 110000
#define ID_SPRITE_PIPE_TOP_LEFT (ID_SPRITE_PIPE+1)
#define ID_SPRITE_PIPE_TOP_RIGHT (ID_SPRITE_PIPE+2)
#define ID_SPRITE_PIPE_BODY_LEFT (ID_SPRITE_PIPE+3)
#define ID_SPRITE_PIPE_BODY_RIGHT (ID_SPRITE_PIPE+4)

#define ID_SPRITE_BPIPE_BODY_LEFT (ID_SPRITE_PIPE+5)
#define ID_SPRITE_BPIPE_BODY_RIGHT (ID_SPRITE_PIPE+6)
#define ID_SPRITE_BPIPE_BOTTOM_LEFT (ID_SPRITE_PIPE+7)
#define ID_SPRITE_BPIPE_BOTTOM_RIGHT (ID_SPRITE_PIPE+8)

#pragma region Fire_Plant
#define ID_SPRITE_FIREPLANT 120000

//TOP LEFT
#define ID_SPRITE_FIREPLANT_TOPLEFT_1 (ID_SPRITE_FIREPLANT+1)
#define ID_SPRITE_FIREPLANT_TOPLEFT_2 (ID_SPRITE_FIREPLANT+2)
//BOTTOM LEFT
#define ID_SPRITE_FIREPLANT_BOTTOMLEFT_1 (ID_SPRITE_FIREPLANT+3)
#define ID_SPRITE_FIREPLANT_BOTTOMLEFT_2 (ID_SPRITE_FIREPLANT+4)

//TOP RIGHT
#define ID_SPRITE_FIREPLANT_TOPRIGHT_1 (ID_SPRITE_FIREPLANT+5)
#define ID_SPRITE_FIREPLANT_TOPRIGHT_2 (ID_SPRITE_FIREPLANT+6)
//BOTTOM RIGHT
#define ID_SPRITE_FIREPLANT_BOTTOMRIGHT_1 (ID_SPRITE_FIREPLANT+7)
#define ID_SPRITE_FIREPLANT_BOTTOMRIGHT_2 (ID_SPRITE_FIREPLANT+8)
#pragma endregion

#pragma region Fire_Plant_Short
#define ID_SPRITE_FIREPLANT_SHORT (ID_SPRITE_FIREPLANT+1000)

//TOP LEFT
#define ID_SPRITE_FIREPLANT_SHORT_TOPLEFT_1 (ID_SPRITE_FIREPLANT_SHORT+1)
#define ID_SPRITE_FIREPLANT_SHORT_TOPLEFT_2 (ID_SPRITE_FIREPLANT_SHORT+2)
//BOTTOM LEFT
#define ID_SPRITE_FIREPLAN_SHORTT_BOTTOMLEFT_1 (ID_SPRITE_FIREPLANT_SHORT+3)
#define ID_SPRITE_FIREPLAN_SHORTT_BOTTOMLEFT_2 (ID_SPRITE_FIREPLANT_SHORT+4)

//TOP RIGHT
#define ID_SPRITE_FIREPLANT_SHORT_TOPRIGHT_1 (ID_SPRITE_FIREPLANT_SHORT+5)
#define ID_SPRITE_FIREPLANT_SHORT_TOPRIGHT_2 (ID_SPRITE_FIREPLANT_SHORT+6)
//BOTTOM RIGHT
#define ID_SPRITE_FIREPLANT_SHORT_BOTTOMRIGHT_1 (ID_SPRITE_FIREPLANT_SHORT+7)
#define ID_SPRITE_FIREPLANT_SHORT_BOTTOMRIGHT_2 (ID_SPRITE_FIREPLANT_SHORT+8)
#pragma endregion



#pragma region WING_GOOMBA
#define ID_SPRITE_WINGGOOMBA 130000
#define ID_SPRITE_WINGGOOMBA_WINGUP1	(ID_SPRITE_WINGGOOMBA+1)
#define ID_SPRITE_WINGGOOMBA_WINGUP2	(ID_SPRITE_WINGGOOMBA+2)

#define ID_SPRITE_WINGGOOMBA_WINGDOWN1	(ID_SPRITE_WINGGOOMBA+3)
#define ID_SPRITE_WINGGOOMBA_WINGDOWN2	(ID_SPRITE_WINGGOOMBA+4)
//lost wing
#define ID_SPRITE_WINGGOOMBA_NORMAL1	(ID_SPRITE_WINGGOOMBA+5)
#define ID_SPRITE_WINGGOOMBA_NORMAL2	(ID_SPRITE_WINGGOOMBA+6)

#define ID_SPRITE_WINGGOOMBA_DIE	(ID_SPRITE_WINGGOOMBA+7)
#pragma endregion

#pragma region KOOPA
//RED KOOPA
#define ID_SPRITE_KOOPA 140000

#define ID_SPRITE_KOOPA_WALKING_LEFT1 (ID_SPRITE_KOOPA+1)
#define ID_SPRITE_KOOPA_WALKING_LEFT2 (ID_SPRITE_KOOPA+2)

#define ID_SPRITE_KOOPA_WALKING_RIGHT1 (ID_SPRITE_KOOPA+3)
#define ID_SPRITE_KOOPA_WALKING_RIGHT2 (ID_SPRITE_KOOPA+4)

#define ID_SPRITE_SHELL (ID_SPRITE_KOOPA+10)
#define ID_SPRITE_SHELL_EXTEND (ID_SPRITE_KOOPA+11)
#define ID_SPRITE_SHELL_UPSIDEDOWN (ID_SPRITE_KOOPA+12)
//GREEN KOOPA
#define ID_SPRITE_KOOPA_GREEN (ID_SPRITE_KOOPA +1000)

#define ID_SPRITE_KOOPA_GREEN_WALKING_LEFT1 (ID_SPRITE_KOOPA_GREEN+1)
#define ID_SPRITE_KOOPA_GREEN_WALKING_LEFT2 (ID_SPRITE_KOOPA_GREEN+2)

#define ID_SPRITE_KOOPA_GREEN_WALKING_RIGHT1 (ID_SPRITE_KOOPA_GREEN+3)
#define ID_SPRITE_KOOPA_GREEN_WALKING_RIGHT2 (ID_SPRITE_KOOPA_GREEN+4)

#define ID_SPRITE_SHELL_GREEN (ID_SPRITE_KOOPA_GREEN +10)
#define ID_SPRITE_SHELL_GREEN_EXTEND (ID_SPRITE_KOOPA_GREEN+11)
#define ID_SPRITE_SHELL_GREEN_UPSIDEDOWN (ID_SPRITE_KOOPA_GREEN +12)
#pragma endregion

#define ID_SPRITE_FIREBALL 150000
#define ID_SPRITE_FIREBALL_LEFT_1 (ID_SPRITE_FIREBALL+1)
#define ID_SPRITE_FIREBALL_LEFT_2 (ID_SPRITE_FIREBALL+2)

#define ID_SPRITE_FIREBALL_RIGHT_1 (ID_SPRITE_FIREBALL+3)
#define ID_SPRITE_FIREBALL_RIGHT_2 (ID_SPRITE_FIREBALL+4)



#define ID_SPRITE_CLOUD_BLOCK 160000

#define ID_SPRITE_SHADOW 170000
#define ID_SPRITE_SHADOW_TOP (ID_SPRITE_SHADOW+1)
#define ID_SPRITE_SHADOW_BODY (ID_SPRITE_SHADOW+2)

#define ID_SPRITE_WOOD 180000

#define ID_SPRITE_CHOMPER 190000
#define ID_SPRITE_CHOMPER_1 (ID_SPRITE_CHOMPER+1)
#define ID_SPRITE_CHOMPER_2 (ID_SPRITE_CHOMPER+2)

#pragma region WING_KOOPA
#define ID_SPRITE_WINGKOOPA	200000

//with wing
#define ID_SPRITE_WINGKOOPA_WINGDOWN_LEFT_1 (ID_SPRITE_WINGKOOPA+1)
#define ID_SPRITE_WINGKOOPA_WINGDOWN_LEFT_2 (ID_SPRITE_WINGKOOPA+2)
#define ID_SPRITE_WINGKOOPA_WINGUP_LEFT_1 (ID_SPRITE_WINGKOOPA+3)
#define ID_SPRITE_WINGKOOPA_WINGUP_LEFT_2 (ID_SPRITE_WINGKOOPA+4)

#define ID_SPRITE_WINGKOOPA_WINGDOWN_RIGHT_1 (ID_SPRITE_WINGKOOPA+5)
#define ID_SPRITE_WINGKOOPA_WINGDOWN_RIGHT_2 (ID_SPRITE_WINGKOOPA+6)
#define ID_SPRITE_WINGKOOPA_WINGUP_RIGHT_1 (ID_SPRITE_WINGKOOPA+7)
#define ID_SPRITE_WINGKOOPA_WINGUP_RIGHT_2 (ID_SPRITE_WINGKOOPA+8)

//no wing
#define ID_SPRITE_WINGKOOPA_WALKING_LEFT1 (ID_SPRITE_WINGKOOPA+9)
#define ID_SPRITE_WINGKOOPA_WALKING_LEFT2 (ID_SPRITE_WINGKOOPA+10)

#define ID_SPRITE_WINGKOOPA_WALKING_RIGHT1 (ID_SPRITE_WINGKOOPA+11)
#define ID_SPRITE_WINGKOOPA_WALKING_RIGHT2 (ID_SPRITE_WINGKOOPA+12)

//shell and die
#define ID_SPRITE_WSHELL (ID_SPRITE_WINGKOOPA +13)
#define ID_SPRITE_WSHELL_EXTEND (ID_SPRITE_WINGKOOPA+14)


#pragma endregion

#define ID_SPRITE_BTN 210000
#define ID_SPRITE_BTN_1 (ID_SPRITE_BTN+1)
#define ID_SPRITE_BTN_2 (ID_SPRITE_BTN+2)
#define ID_SPRITE_BTN_3 (ID_SPRITE_BTN+3)
#define ID_SPRITE_BTN_USED (ID_SPRITE_BTN+4)