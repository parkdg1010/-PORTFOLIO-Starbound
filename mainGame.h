#pragma once
#include "gameNode.h"
#include "loadingScene.h"
#include "startScene.h"
#include "mapToolScene.h"
#include "stageScene.h"
#include "player.h"

class mainGame : public gameNode
{
	player* _player;
public:
	HRESULT init();			//부모가 virtual이므로 자식은 자동으로 virtual이 된다.
	void release();
	void update();
	void render();

	mainGame() {}
	~mainGame() {}
};

