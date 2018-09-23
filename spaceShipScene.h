#pragma once
#include "gameNode.h"
#include "player.h"

class spaceShipScene : public gameNode
{
	player* _player;

	image* _ship;
	image* _shipPixel;
	image* _teleporter;
	image* _background;
	int _offsetX;
public:
	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();

	spaceShipScene() {}
	~spaceShipScene() {}
};

