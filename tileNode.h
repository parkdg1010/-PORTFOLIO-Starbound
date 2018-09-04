#pragma once

#define TILESIZE 32

enum CTRL
{
	//CTRL_SAVE, CTRL_LOAD,
	CTRL_SIZINGTAB, CTRL_TERRAINTAB, CTRL_ITEMTAB, CTRL_OBJECTTAB, CTRL_ENEMYTAB, CTRL_ERASER, CTRL_NONE
};

//지형
enum TERRAIN
{
	TR_NONE, TR_BRICK, TR_COBBLEBRICK, TR_CONCRETE, TR_DARKWOOD, 
	TR_DIRT, TR_FULLWOOD1, TR_FULLWOOD2, TR_LOG, TR_PETALBLOCK, TR_ROOF, TR_END
};

enum TERRAIN_FRONTBACK
{
	FRONT, BACK
};

//오브젝트
enum OBJECT
{
	OBJECT_NONE,
	OBJECT_WOODENCRATE1
};

enum ITEM
{
	ITEM_NONE,
	ITEM_SPACESWORD
};

enum ACTOR
{
	ACTOR_NONE,
	ACTOR_ENEMY1,
	ACTOR_NPC1
};

enum BACKGROUND_TOP
{
	BACKTOP_0, BACKTOP_1, BACKTOP_2, BACKTOP_3, BACKTOP_4,
};

enum BACKGROUND_BOT
{
	BACKBOT_0, BACKBOT_1, BACKBOT_2, BACKBOT_3
};

struct tagTile
{
	TERRAIN terrain;
	TERRAIN_FRONTBACK frontBack;
	OBJECT object;
	RECT rc;

	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
};

struct tagSampleTile
{
	int type;
	int terrainFrameX;
	int terrainFrameY;
};

struct tagSampleObject
{
	int type;
	int objFrameX;
	int objFrameY;
};

struct tagCurrentTile
{
	TERRAIN terrainType;
	TERRAIN_FRONTBACK frontBack;
	OBJECT objectType;
	ITEM itemType;
	ACTOR actorType;

	int frameX, frameY;
};