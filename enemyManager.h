#pragma once
#include "gameNode.h"
#include "minion.h"
#include "bullet.h"


class enemyManager : public gameNode
{
private:
	vector<enemy*> _vMinion;
	vector<enemy*>::iterator _viMinion;

	bullet* _bullet;	//�����Ѿ� Ŭ����
	int _count;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//�̴Ͼ� ���� => �ʱ�ȭ�� �ֱ�
	void setMinion();

	//�̴Ͼ� �Ѿ˹߻�
	void minionBulletFire();

	//�̴Ͼ� ����
	void removeMinion(int index);

	//�̴Ͼ� ���� ��������
	vector<enemy*> getMinion() { return _vMinion; }

	enemyManager() {}
	~enemyManager() {}
};

