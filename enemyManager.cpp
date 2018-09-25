#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"
#include "gameStage.h"

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
		if (!_vEnemy[i]->getIsActive()) continue;

		_vEnemy[i]->bltUpdate();
		_vEnemy[i]->update();
	}
}

void enemyManager::render()
{
	//º¤ÅÍ¿¡ ´ã±ä ¿¡³Ê¹Ì ·»´õ
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		if (!_vEnemy[i]->getIsActive()) continue;

		_vEnemy[i]->bltRender();
		_vEnemy[i]->render();
	}
}

void enemyManager::release()
{
	_vEnemy.clear();
}