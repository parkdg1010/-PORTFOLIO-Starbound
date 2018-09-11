#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "enemy.h"

enum ENEMY_TYPE
{
	FENNIX,
	SCAVERAN,
	TOUMINGO,
	TRICTUS,
	VOLTIP
};

class player;
class enemyManager : public gameNode
{
private:
	player * _player;
	image* _mapPixel;
	vector<enemy*> _vEnemy;

	int _count;
public:
	HRESULT init();
	void update();
	void render();
	void release();

	//��ȣ����
	void linkPlayer(player* p) { _player = p; };
	void linkMapPixel(image* map) { _mapPixel = map; };

	//�̴Ͼ� ���� ��������
	vector<enemy*> getEnemy() { return _vEnemy; }

	//���ʹ� �߰�
	void addEnemy(enemy* enemy) { _vEnemy.push_back(enemy); }
	void setPostion(int index, POINTf pos = { WINSIZEX / 2, WINSIZEY / 2 }, int dir = 1) { _vEnemy[index]->setPos(pos.x, pos.y); }

	enemyManager() {}
	~enemyManager() {}
};

class enemyFactory
{
public:
	enemy * createEnemy(int type, POINTf pos = { WINSIZEX / 2, WINSIZEY / 2 }, int dir = 1);
};

