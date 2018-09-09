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
	TR_NONE = -1,
	TR_BRICK, TR_COBBLEBRICK = 2, TR_CONCRETE = 4, TR_DARKWOOD = 6, 
	TR_DIRT = 8, TR_FULLWOOD1 = 10, TR_FULLWOOD2 = 12, TR_LOG = 14, TR_PETALBLOCK = 16, TR_ROOF = 18, TR_END
};

enum TERRAIN_FRONTBACK
{
	FRONT, BACK
};

enum FLATFORM
{
	FF_WOOD
};

//오브젝트
enum OBJECT
{
	OBJECT_NONE,
	OBJECT_WOODENCRATE1,
	OBJECT_TREELIGHTS
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
	FLATFORM flatformType;
	OBJECT objectType;
	ITEM itemType;
	ACTOR actorType;

	int frameX, frameY;
};