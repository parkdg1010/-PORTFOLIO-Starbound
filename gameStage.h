#pragma once
#include "gameNode.h"
#include "tileNode.h"

class player;
class gameStage : public gameNode
{
private:
	int _stageNum;
	int _tileX, _tileY;
	int _curBackTop;
	int _curBackBot;
	tagTile* _stage;

	image* _brick[2], *_cobbleBrick[2], *_concrete[2], *_darkwood[2], *_dirt[2];
	image* _fullwood1[2], *_fullwood2[2], *_log[2], *_petalblock[2], *_rooftile[2];
	image* _woodencrate1, *_treeLights, *_ornatetorch;
	int _treeLightsCount, _treeLightsIdx, _ornatetorchCount, _ornatetorchidx;
	image* _item;

	image* _backGroundTop[5];
	image* _backGroundBot[5];
	image* _stageBuffer;

	player* _player;

public:
	void saveStage();
	void loadStage();

	int getTileX() { return _tileX; }
	int getTileY() { return _tileY; }
	tagTile* getStage() { return _stage; }

	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();

	void initImage();

	void stageRender();

	void linkPlayer(player* p) { _player = p; }

	gameStage() {}
	~gameStage() {}
};

