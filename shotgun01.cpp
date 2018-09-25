#include "stdafx.h"
#include "shotgun01.h"
#include "enemyManager.h"

HRESULT shotgun01::init(CATEGORY tag, string name, int rarity, int price, float damage, float armor, image * icon, image * img, image * effect1, image * effect2, image * effect3)
{
	rangedWeapon::init(tag, name, rarity, price, damage, armor, icon, img, effect1, effect2, effect3);
	_vBullet = new vector<bullet>;
	bullet blt;
	blt.init(1.5f, 15, _damage, 800, _effect[0]);
	for (int i = 0; i < 15; ++i)
	{
		_vBullet->push_back(blt);
	}

	_fireX = _x;
	_fireY = _y;

	return S_OK;
}

void shotgun01::update()
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
					if(_vBullet->at(i).collideMap(_mapPixel))
						EFFECTMANAGER->play("bulletEffect", _vBullet->at(i).getX(), _vBullet->at(i).getY());
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
						EFFECTMANAGER->play("bulletEffect", _vBullet->at(i).getX(), _vBullet->at(i).getY());
						em[j]->damaged(&_vBullet->at(i));
						_vBullet->at(i).setIsActive(false);
					}
				}
			}
		}
	}
}

void shotgun01::render()
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

void shotgun01::release()
{
}

void shotgun01::attack()
{
	_fireX = _x + _img->getFrameWidth() * 0.5f * cosf(_angle);
	_fireY = _y + _img->getFrameWidth() * 0.5f * -sinf(_angle);

	for (int i = 0; i < _vBullet->size()*0.2; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (_vBullet->at(i * 5 + j).getIsActive()) continue;

			if(_dir == LEFT)
				EFFECTMANAGER->play("muzzleflash", _fireX-5, _fireY-5, _angle - PI_2);
			else
				EFFECTMANAGER->play("muzzleflash", _fireX+5, _fireY - 5, _angle + PI*1.5);
			_vBullet->at(i * 5 + j).fire(_fireX, _fireY, _angle + RAD_TO_DEG(29) - RAD_TO_DEG(15)*j);
		}
		break;
	}
}
