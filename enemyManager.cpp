#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"

HRESULT enemyManager::init()
{
	//_count = 0;

	return S_OK;
}

void enemyManager::update()
{
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		_vEnemy[i]->setPlayerHitBox(_player->getHitBox());
		_vEnemy[i]->setPlayerX(_player->getX());
		_vEnemy[i]->setPlayerY(_player->getY());

		_vEnemy[i]->bltUpdate();
		_vEnemy[i]->update();
	}
}

void enemyManager::render()
{
	//º¤ÅÍ¿¡ ´ã±ä ¿¡³Ê¹Ì ·»´õ
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		_vEnemy[i]->bltRender();
		_vEnemy[i]->render();
	}
}

void enemyManager::release()
{
}

enemy * enemyFactory::createEnemy(int type, POINTf pos, int dir)
{
	enemy* _enemy = NULL;
	switch (type)
	{
	case FENNIX:
		//_enemy = new fennix;
		break;
	case SCAVERAN:
		//_enemy = new scaveran;
		break;
	case TOUMINGO:
		//_enemy = new toumingo;
		break;
	case TRICTUS:
		//_enemy = new trictus;
		break;
	case VOLTIP:
		//_enemy = new voltip;
		break;
	}

	if (_enemy != NULL)
	{
		_enemy->init(pos, dir);
		return _enemy;
	}
	
	return NULL;
}
