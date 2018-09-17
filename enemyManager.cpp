#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"

HRESULT enemyManager::init()
{
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		_vEnemy[i]->linkPlayer(_player);
		_vEnemy[i]->linkMapPixel(_stage->getPixelBuffer());
		_vEnemy[i]->init();
	}

	return S_OK;
}

void enemyManager::update()
{
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		_vEnemy[i]->bltUpdate();
		_vEnemy[i]->update();
	}
}

void enemyManager::render()
{
	//벡터에 담긴 에너미 렌더
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		_vEnemy[i]->bltRender();
		_vEnemy[i]->render();
	}
}

void enemyManager::release()
{
	_vEnemy.clear();
}

enemy * enemyFactory::createEnemy(int type, POINTf pos, int dir)
{
	enemy* _enemy = NULL;
	switch (type)
	{
	case FENNIX:
		_enemy = new fennix;
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
		_enemy->setPosition(pos, dir); 
		//init해버리면 update와 render해야해서 상호참조하기 불편하므로 위치만 잡아준다.
		//또한 init에 있던 x,y,z,dir 0으로 초기화를 생성자에 추가했다.
		return _enemy;
	}
	
	return NULL;
}

enemy * enemyFactory::createEnemy(int type, float posX, float posY, int dir)
{
	enemy* _enemy = NULL;
	switch (type)
	{
	case FENNIX:
		_enemy = new fennix;
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
		_enemy->setPosition(posX,posY, dir);
		//init해버리면 update와 render해야해서 상호참조하기 불편하므로 위치만 잡아준다.
		//또한 init에 있던 x,y,z,dir 0으로 초기화를 생성자에 추가했다.
		return _enemy;
	}

	return NULL;
}
