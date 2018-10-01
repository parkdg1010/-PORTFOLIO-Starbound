#include "stdafx.h"
#include "drillgun.h"
#include "enemyManager.h"

HRESULT drillgun::init(CATEGORY tag, string name, int rarity, int price, float damage, float armor, image * icon, image * img, image * effect1, image * effect2, image * effect3)
{
	rangedWeapon::init(tag, name, rarity, price, damage, armor, icon, img, effect1, effect2, effect3);

	_vBullet = new vector<bullet>;
	bullet blt;
	blt.init(10.f, 10, _damage, 300, _effect[0]);
	for (int i = 0; i < 5; ++i)
	{
		_vBullet->push_back(blt);
		_vBullet->at(i).setDirtDrill(true);
	}

	_fireX = _x;
	_fireY = _y;

	return S_OK;
}

void drillgun::update()
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
					if (_vBullet->at(i).collideMap(_mapPixel))
					{
						EFFECTMANAGER->play("drillEffect", _vBullet->at(i).getX(), _vBullet->at(i).getY());
						SOUNDMANAGER->play("¼¦°ÇÅ¸°Ý", _effectVolume);
					}
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
						EFFECTMANAGER->play("drillEffect", _vBullet->at(i).getX(), _vBullet->at(i).getY());
						em[j]->damaged(&_vBullet->at(i));
						SOUNDMANAGER->play("¼¦°ÇÅ¸°Ý", _effectVolume);
					}
				}
			}
		}
	}
}

void drillgun::render()
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

void drillgun::release()
{
}

void drillgun::attack()
{
	_fireX = _x + _img->getFrameWidth() * 0.5f * cosf(_angle);
	_fireY = _y + _img->getFrameWidth() * 0.5f * -sinf(_angle);

	for (int i = 0; i < _vBullet->size(); ++i)
	{
		if (_vBullet->at(i).getIsActive()) continue;

		if (_dir == LEFT)
			EFFECTMANAGER->play("muzzleflash", _fireX - 5, _fireY - 5, _angle - PI_2);
		else
			EFFECTMANAGER->play("muzzleflash", _fireX + 5, _fireY - 5, _angle + PI * 1.5);
		_vBullet->at(i).fire(_fireX, _fireY, _angle);
		SOUNDMANAGER->play("¼¦°Ç", _effectVolume);
		break;
	}
}
