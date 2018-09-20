#include "stdafx.h"
#include "stageScene.h"

HRESULT stageScene::init()
{
	_itemFac = new itemFactory;
	_enemyFac = new enemyFactory;
	
	_stage = new dungeonStage;
	_enemyManager = new enemyManager;

	_stage->init();
	_stage->loadStage();

	_player = SAVEDATA->getPlayer();
	_player->linkStage(_stage);
	_player->init();
	_player->getInventory()->addWeaponInven(_itemFac->createItem
	(ITEM_SHOTGUN01, 500, 500.f, 0.f, "¼¦°Ç¾ÆÀÌÄÜ", "¼¦°Ç", "standardBullet", "muzzleflashImg"));
	_player->linkEnemyManager(_enemyManager);

	_stage->linkPlayer(_player);
	_enemyManager->linkPlayer(_player);

	_enemyManager->linkStage(_stage);
	createMonster();
	_enemyManager->init();


	CAMERAMANAGER->init();
	CAMERAMANAGER->setRange(_stage->getTileX() * TILESIZE, _stage->getTileY() * TILESIZE);
	CAMERAMANAGER->setPosition((int)_player->getX(), (int)_player->getY());

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

void stageScene::createMonster()
{
	_kluexboss = new kluexboss;
	POINTf pos;
	pos = { 1000,520 };
	_kluexboss->setPosition(pos, LEFT);
	_enemyManager->addEnemy(_kluexboss);

	vector<ACTOR_TYPE_POS> _vTemp = _stage->getEnemyPosition();

	enemy* temp;
	for (int i = 0; i < _vTemp.size(); ++i)
	{
		temp = _enemyFac->createEnemy(_vTemp[i].type, _vTemp[i].x, _vTemp[i].y);
		_enemyManager->addEnemy(temp);
	}
}
