#pragma once
#include "gameNode.h"
#include "tileNode.h"

class player;
class gameStage : public gameNode
{
private:
	int _tileX, _tileY;
	int _curBackTop;
	int _curBackBot;
	tagTile* _stage;

	image* _brick[2], *_cobbleBrick[2], *_concrete[2], *_darkwood[2], *_dirt[2];
	image* _fullwood1[2], *_fullwood2[2], *_log[2], *_petalblock[2], *_rooftile[2];
	image* _woodencrate1;
	image* _item;

	image* _backGroundTop[5];
	image* _backGroundBot[5];

	player* _player;

public:
	//경로를 따로 지정해서 인게임에서 맵에 상호작용한 것을 저장할 수 있게 해보자
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

