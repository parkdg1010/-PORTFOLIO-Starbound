#pragma once
#include "gameNode.h"
#include "player.h"
#include "gameStage.h"
#include "homeStage.h"
#include "dungeonStage.h"

class stageScene : public gameNode
{
	player* _player;
	gameStage* _stage;
	itemFactory* _itemFac;
public:
	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();
	
	stageScene() {}
	~stageScene() {}
};