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
		//init�ع����� update�� render�ؾ��ؼ� ��ȣ�����ϱ� �����ϹǷ� ��ġ�� ����ش�.
		//���� init�� �ִ� x,y,z,dir 0���� �ʱ�ȭ�� �����ڿ� �߰��ߴ�.
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
		//init�ع����� update�� render�ؾ��ؼ� ��ȣ�����ϱ� �����ϹǷ� ��ġ�� ����ش�.
		//���� init�� �ִ� x,y,z,dir 0���� �ʱ�ȭ�� �����ڿ� �߰��ߴ�.
		return _enemy;
	}

	return NULL;
}