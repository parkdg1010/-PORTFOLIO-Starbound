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

	image* _pixelTiles;
	vector<image*> _tiles;
	image* _woodencrate1, *_treeLights, *_ornatetorch;
	int _treeLightsCount, _treeLightsIdx, _ornatetorchCount, _ornatetorchidx;
	image* _item;

	image* _backGroundTop[5];
	image* _backGroundBot[5];
	image* _stageBuffer;
	image* _pixelBuffer;

	player* _player;

public:
	void saveStage();
	void loadStage();

	void loadStageBuffer();

	int getTileX() { return _tileX; }
	int getTileY() { return _tileY; }
	image* getStageBuffer() { return _stageBuffer; }
	image* getPixelBuffer() { return _pixelBuffer; }

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

