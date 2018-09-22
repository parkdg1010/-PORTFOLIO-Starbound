#include "stdafx.h"
#include "spaceSword.h"
#include "enemyManager.h"
HRESULT spaceSword::init(CATEGORY tag, string name, int rarity, int price, float damage, float armor, image * icon, image * img, image * effect1, image * effect2, image * effect3)
{
	weapon::init(tag, name, rarity, price, damage, armor, icon, img, effect1, effect2, effect3);
	_atkWidth = 128;
	_atkHeight = 128;
	_atkCombo = 1;

	return S_OK;
}

void spaceSword::update()
{
	if (_atkCombo == 0)
	{
		_hitBox = { 0,0,0,0 };
	}
	else
	{
		DELAYCOUNT(_count, 7);
		if (_count == 0)
		{
			++_index;
			if (_index > 2)
			{
				_index = 0;
			}
		}
	}

}

void spaceSword::render()
{
	switch (_atkCombo)
	{
	case 1:
		if (_dir == RIGHT)
		{
			_effect[0]->frameRender(getMemDC(), _x - 90 - CAM->getX(), _y - 120 - CAM->getY(), _index, _dir);
			_effect[0]->setX(_x - 90);
			_effect[0]->setY(_y - 120);
		}
		else if (_dir == LEFT)
		{
			_effect[0]->frameRender(getMemDC(), _x - 150 - CAM->getX(), _y - 120 - CAM->getY(), _index, _dir);
			_effect[0]->setX(_x - 150);
			_effect[0]->setY(_y - 120);
		}
		break;
	case 2:
		if (_dir == RIGHT)
		{
			_effect[1]->frameRender(getMemDC(), _x + 35 - CAM->getX(), _y - 30 - CAM->getY(), _index, _dir);
			_effect[1]->setX(_x + 35);
			_effect[1]->setY(_y - 30);
		}
		else if (_dir == LEFT)
		{
			_effect[1]->frameRender(getMemDC(), _x -150 - CAM->getX(), _y - 30 - CAM->getY(), _index, _dir);
			_effect[1]->setX(_x - 150);
			_effect[1]->setY(_y - 30);
		}
		break;
	case 3:
		if (_dir == RIGHT)
		{
			_effect[2]->frameRender(getMemDC(), _x +35 - CAM->getX(), _y-5 - CAM->getY(), _index, _dir);
			_effect[2]->setX(_x + 35);
			_effect[2]->setY(_y - 5);
		}
		else if (_dir == LEFT)
		{
			_effect[2]->frameRender(getMemDC(), _x -170 - CAM->getX(), _y - 5 - CAM->getY(), _index, _dir);
			_effect[2]->setX(_x - 170);
			_effect[2]->setY(_y - 5);
		}
		break;
	case 4:
		_atkCombo = 0;
		break;
	}
	if (_dir == RIGHT)
	{
		_img->rotateFrameRender(getMemDC(), _x -20* cosf(_angle + PI_2) - CAM->getX(), _y -20*- sinf(_angle + PI_2) - CAM->getY(), 0, _dir, _angle + PI_2);
	}
	else if (_dir == LEFT)
	{
		_img->rotateFrameRender(getMemDC(), _x +20* cosf(_angle + PI_2) - CAM->getX(), _y +20*- sinf(_angle + PI_2) - CAM->getY(), 0, _dir, _angle + PI_2);
	}
	Rectangle(getMemDC(), _hitBox.left - CAM->getX(), _hitBox.top - CAM->getY(), _hitBox.right - CAM->getX(), _hitBox.bottom - CAM->getY());
}

void spaceSword::release()
{
}

void spaceSword::attack()
{	
	//휘두루면 이펙트플레이, 플레이어 손위치 변경
	if (_atkCombo)
	{
		_hitBox = _effect[_atkCombo - 1]->boundingBoxWithFrame();
	}

	if (_enemyManager != NULL)
	{
		vector<enemy*> em = _enemyManager->getEnemy();
		RECT temp;
		for (int i = 0; i < em.size(); ++i)
		{
			if (IntersectRect(&temp, &em[i]->getHitBox(), &_hitBox))
			{

			}
		}
	}
}
