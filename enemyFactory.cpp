#include "stdafx.h"
#include "enemyFactory.h"

enemy * enemyFactory::createEnemy(int type, POINTf pos, int dir)
{
	enemy* _enemy = NULL;
	switch (type)
	{
	case FENNIX:
		_enemy = new fennix;
		break;
	case SCAVERAN:
		_enemy = new scaveran;
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
	case KLUEXBOSS:
		_enemy = new kluexboss;
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
		_enemy = new scaveran;
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
	case KLUEXBOSS:
		_enemy = new kluexboss;
		break;
	}

	if (_enemy != NULL)
	{
		_enemy->setPosition(posX, posY, dir);
		//init해버리면 update와 render해야해서 상호참조하기 불편하므로 위치만 잡아준다.
		//또한 init에 있던 x,y,z,dir 0으로 초기화를 생성자에 추가했다.
		return _enemy;
	}

	return NULL;
}