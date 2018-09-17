#pragma once
#include "gameNode.h"
#include "gameStage.h"
#include "bullet.h"
#include "enemy.h"
#include "kluexboss.h"
#include "fennix.h"

class player;
class enemyManager : public gameNode
{
private:
	player * _player;
	gameStage* _stage;
	vector<enemy*> _vEnemy;

	int _count;
public:
	HRESULT init();
	void update();
	void render();
	void release();

	//상호참조
	void linkPlayer(player* p) { _player = p; }
	//void linkMapPixel(image* map) { _mapPixel = map; }
	void linkStage(gameStage* stage) { _stage = stage; }

	//미니언 벡터 가져오기
	vector<enemy*> getEnemy() { return _vEnemy; }

	//에너미 추가
	void addEnemy(enemy* enemy) { _vEnemy.push_back(enemy); }
	void setPostion(int index, POINTf pos = { WINSIZEX / 2, WINSIZEY / 2 }, int dir = 1) { _vEnemy[index]->setPosition(pos.x, pos.y, dir); }

	enemyManager() {}
	~enemyManager() {}
};

class enemyFactory
{
public:
	enemy * createEnemy(int type, POINTf pos = { WINSIZEX / 2, WINSIZEY / 2 }, int dir = 1);
	enemy * createEnemy(int type, float posX = WINSIZEX / 2, float posY =  WINSIZEY / 2 , int dir = 1);
};

