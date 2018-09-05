#include "stdafx.h"
#include "stageScene.h"

HRESULT stageScene::init()
{
	_itemFac = new itemFactory;
	

	_stage = new gameStage;
	_stage->init();

	_player = SAVEDATA->getPlayer();
	_player->linkStage(_stage);
	_player->init();
	_player->setWeapon(_itemFac->createItem(ITEM_SPACESWORD, 1000, 20.f, 0.f, "", "¿ìÁÖ°Ë"));

	CAMERAMANAGER->init();

	_stage->linkPlayer(_player);
	_stage->loadStage();

	return S_OK;
}

void stageScene::update()
{
	_stage->update();
	_player->update();
	CAM->videoShooting((int)_player->getX(), (int)_player->getY());
}

void stageScene::render()
{
	_stage->render();
	_player->render();
}

void stageScene::release()
{
	SAVEDATA->setPlayer(_player);

	_stage->release();
	SAFE_DELETE(_stage);
}