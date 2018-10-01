#include "stdafx.h"
#include "stageScene.h"

HRESULT stageScene::init()
{
	if(_itemFac == NULL)
		_itemFac = new itemFactory;
	if(_stage == NULL)
		_stage = new gameStage;
	if(_enemyManager == NULL)
		_enemyManager = new enemyManager;

	_player = SAVEDATA->getPlayer();

	_stage->linkEnemyManager(_enemyManager);
	_stage->init();
	_stage->setStageNum(_player->getStageNum());
	_stage->loadStage();

	_player->setGravityAccel(0.29f);
	_player->init();
	_player->linkStage(_stage);
	if (_player->getStageNum() == 2)
	{
		_player->getInventory()->addWeaponInven(_itemFac->createItem(TAG_RANGEDWEAPON, "shotgun", 2, 500, 8.f, 0.f,
			"���Ǿ�����", "����", "standardBullet", "muzzleflashImg", "bulletEffectImg"));
		_player->getInventory()->addWeaponInven(_itemFac->createItem(TAG_PLASMAGUN, "plasmagun", 4, 1500, 30.f, 0.f,
			"�ö���Ǿ�����", "�ö����", "plasmaBullet", "plasmaflashImg", "plasmaEffectImg"));
		_player->getInventory()->addWeaponInven(_itemFac->createItem(TAG_DRILLGUN, "drillgun", 1, 1000, 1.f, 0.f,
			"�帱�Ǿ�����", "�帱��", "drillBullet", "muzzleflashImg", "drillEffectImg"));
		//_player->getInventory()->addWeaponInven(_itemFac->createItem(TAG_MELEEWEAPON, "astrosabredeluxe", 4, 1500, 300.f, 0.f, 
		//	"���ְ˾�����", "���ְ�", "tearswoosh1Img", "tearswoosh2Img", "tearswoosh3Img"));
	}

	_player->linkEnemyManager(_enemyManager);

	_stage->linkPlayer(_player);
	_enemyManager->linkPlayer(_player);

	_enemyManager->linkStage(_stage);
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
	if (_enemyManager != NULL)
	{
		for (int i = 0; i < _enemyManager->getEnemy().size(); ++i)
		{
			if (dynamic_cast<kluexboss*>(_enemyManager->getEnemy()[i]) != NULL)
			{
				if (!dynamic_cast<kluexboss*>(_enemyManager->getEnemy()[i])->getIsActive())
				{
					SCENEMANAGER->loadScene("����");
					break;
				}
			}
		}
	}
	
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

	_enemyManager->release();
	SAFE_DELETE(_enemyManager);

	_stage->release();
	SAFE_DELETE(_stage);
}
