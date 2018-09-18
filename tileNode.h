#pragma once

#define TILESIZE 32

enum CTRL
{
	//CTRL_SAVE, CTRL_LOAD,
	CTRL_SIZINGTAB, CTRL_TERRAINTAB, CTRL_ITEMTAB, CTRL_OBJECTTAB, CTRL_ACTORTAB, CTRL_ERASER, CTRL_NONE
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

//오브젝트
enum OBJECT
{
	OBJECT_NONE,
	OBJECT_WOODENCRATE1,
	OBJECT_TREELIGHTS,
	OBJECT_ORNATETORCH,
	OBJECT_FF_WOOD
};

enum ITEM
{
	ITEM_NONE,
	ITEM_SPACESWORD,
	ITEM_SHOTGUN01
};

enum ACTOR
{
	//actor는 100의 자리로 저장
	ACTOR_NONE,
	ACTOR_ENEMY,
	ACTOR_NPC
};

enum ENEMY_TYPE
{
	//10,1의 자리로 저장
	FENNIX,
	SCAVERAN,
	TOUMINGO,
	TRICTUS,
	VOLTIP
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
	ACTOR actor;
	ENEMY_TYPE enemy;
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
	ENEMY_TYPE enemyType;

	int frameX, frameY;
};

struct ACTOR_TYPE_POS
{
	int type;
	float x;
	float y;
};