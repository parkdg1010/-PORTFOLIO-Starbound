#include "stdafx.h"
#include "stageScene.h"

HRESULT stageScene::init()
{
	_itemFac = new itemFactory;
	_enemyFac = new enemyFactory;
	
	_stage = new dungeonStage;
	_stage->init();

	_enemyManager = new enemyManager;
	initMonster();
	_enemyManager->init();

	_player = SAVEDATA->getPlayer();
	_player->linkStage(_stage);
	_player->init();
	_player->setWeapon(_itemFac->createItem(ITEM_SPACESWORD, 1000, 20.f, 0.f, "", "¿ìÁÖ°Ë"));

	_enemyManager->linkMapPixel(_stage->getPixelBuffer());
	_enemyManager->linkPlayer(_player);

	CAMERAMANAGER->init();

	_stage->linkPlayer(_player);
	_stage->loadStage();

	return S_OK;
}

void stageScene::update()
{
	_stage->update();
	_enemyManager->update();
	_player->update();
	CAM->videoShooting((int)_player->getX(), (int)_player->getY());
}

void stageScene::render()
{
	_stage->render();
	_enemyManager->render();
	_player->render();
}

void stageScene::release()
{
	SAVEDATA->setPlayer(_player);

	SAFE_DELETE(_itemFac);
	SAFE_DELETE(_enemyFac);

	_enemyManager->release();
	SAFE_DELETE(_enemyManager);

	_stage->release();
	SAFE_DELETE(_stage);
}

void stageScene::initMonster()
{
	POINTf pos;
	_kluexboss = new kluexboss;
	pos = { 2000,500 };
	_kluexboss->init(pos, LEFT);
	_enemyManager->addEnemy(_kluexboss);
}
