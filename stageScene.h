#pragma once
#include "gameNode.h"
#include "player.h"
#include "gameStage.h"

class stageScene : public gameNode
{
	player* _player;
	gameStage* _stage;
public:
	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();
	
	stageScene() {}
	~stageScene() {}
};