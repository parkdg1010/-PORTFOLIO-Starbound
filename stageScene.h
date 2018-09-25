#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"
#include "itemManager.h"
#include "gameStage.h"
#include "homeStage.h"
#include "dungeonStage.h"

class stageScene : public gameNode
{
	player* _player;

	gameStage* _stage;

	enemyManager* _enemyManager;
	enemyFactory* _enemyFac;

	kluexboss* _kluexboss;

	itemFactory* _itemFac;
public:
	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();

	void createMonster();
	
	stageScene() { _itemFac = NULL; _enemyFac = NULL; _stage = NULL; _enemyManager = NULL; }
	~stageScene() {}
};