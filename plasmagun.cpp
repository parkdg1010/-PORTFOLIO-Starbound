#include "stdafx.h"
#include "plasmagun.h"
#include "enemyManager.h"

HRESULT plasmagun::init(CATEGORY tag, string name, int rarity, int price, float damage, float armor, image * icon, image * img, image * effect1, image * effect2, image * effect3)
{
	rangedWeapon::init(tag, name, rarity, price, damage, armor, icon, img, effect1, effect2, effect3);
	
	_vBullet = new vector<bullet>;
	bullet blt;
	blt.init(1.5f, 30, _damage, WINSIZEX, _effect[0]);
	for (int i = 0; i < 20; ++i)
	{
		_vBullet->push_back(blt);
	}

	_fireX = _x;
	_fireY = _y;

	return S_OK;
}

void plasmagun::update()
{
	if (_vBullet != NULL)
	{
		for (int i = 0; i < _vBullet->size(); ++i)
		{
			_vBullet->at(i).update();
			if (_vBullet->at(i).getIsActive())
			{
				if (_mapPixel != NULL)
				{
					_vBullet->at(i).collideMap(_mapPixel);
				}
			}
		}

		if (_enemyManager != NULL)
		{
			vector<enemy*> em = _enemyManager->getEnemy();
			RECT temp;
			for (int i = 0; i < _vBullet->size(); ++i)
			{
				for (int j = 0; j < em.size(); ++j)
				{
					if (_vBullet->at(i).collideActor(em[j]))
					{
						EFFECTMANAGER->play("plasmaEffect", _vBullet->at(i).getX(), _vBullet->at(i).getY());
						em[j]->damaged(&_vBullet->at(i));
					}
				}
			}
		}
	}
}

void plasmagun::render()
{
	if (_vBullet != NULL)
	{
		for (int i = 0; i < _vBullet->size(); ++i)
		{
			_vBullet->at(i).render(true);
		}
	}
	_img->rotateFrameRender(getMemDC(), _x - CAM->getX(), _y - CAM->getY(), 0, _dir, _angle);
}

void plasmagun::release()
{
}

void plasmagun::attack()
{
	_fireX = _x + _img->getFrameWidth() * 0.5f * cosf(_angle);
	_fireY = _y + _img->getFrameWidth() * 0.5f * -sinf(_angle);

	for (int i = 0; i < _vBullet->size(); ++i)
	{
			if (_vBullet->at(i).getIsActive()) continue;

			if (_dir == LEFT)
				EFFECTMANAGER->play("plasmaflash", _fireX - 5, _fireY - 5, _angle - PI_2);
			else
				EFFECTMANAGER->play("plasmaflash", _fireX + 5, _fireY - 5, _angle + PI * 1.5);
			_vBullet->at(i).fire(_fireX, _fireY, _angle);

		break;
	}
}
