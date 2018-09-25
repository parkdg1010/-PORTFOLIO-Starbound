#pragma once
#include "gameNode.h"
#include "enemyManager.h"

class enemyFactory : public gameNode
{
public:
	enemy* createEnemy(int type, POINTf pos = { WINSIZEX / 2, WINSIZEY / 2 }, int dir = 1);
	enemy* createEnemy(int type, float posX = WINSIZEX / 2, float posY = WINSIZEY / 2, int dir = 1);

	enemyFactory() {}
	~enemyFactory() {}
};

