#include "stdafx.h"
#include "enemyManager.h"

HRESULT enemyManager::init(void)
{
	//�̴Ͼ� ����
	this->setMinion();

	_count = 0;

	//�Ѿ�Ŭ���� ���� �� �ʱ�ȭ
	_bullet = new bullet;
	_bullet->init("bullet", 15, 600);

	return S_OK;
}

void enemyManager::release(void)
{
	//�Ѿ�Ŭ���� ����
	_bullet->release();
	SAFE_DELETE(_bullet);
}

void enemyManager::update(void)
{
	//�Ѿ�Ŭ���� ������Ʈ
	_bullet->update();

	//���Ϳ� ��� �̴Ͼ�� ������Ʈ
	//for (int i = 0; i < _vMinion.size(); i++)
	//{
	//	_vMinion[i]->update();
	//}
	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();
	}

	//�̴Ͼ� �Ѿ˹߻�
	this->minionBulletFire();
}

void enemyManager::render(void)
{
	//�Ѿ�Ŭ���� ����
	_bullet->render();
	//���Ϳ� ��� �̴Ͼ�� ����
	//for (int i = 0; i < _vMinion.size(); i++)
	//{
	//	_vMinion[i]->render();
	//}
	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}

}

void enemyManager::setMinion()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			enemy* ufo = new minion;
			ufo->init("ufo", PointMake(50 + j * 100, 100 + i * 100));

			_vMinion.push_back(ufo);
		}
	}
}

void enemyManager::minionBulletFire()
{
	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		if ((*_viMinion)->bulletCountFire())
		{
			RECT rc = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + 30, -PI_2, 3.0f);
		}
	}
}

void enemyManager::removeMinion(int index)
{
	_vMinion.erase(_vMinion.begin() + index);
}
