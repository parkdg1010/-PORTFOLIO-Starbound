#include "stdafx.h"
#include "spaceSword.h"
#include "enemyManager.h"

HRESULT spaceSword::init(ITEM name, int price, float damage, float armor, image * icon, image * img)
{
	weapon::init(name, price, damage, armor, icon, img);

	return S_OK;
}

void spaceSword::update()
{
	//»÷µŒ∑Á∏È ¿Ã∆Â∆Æ«√∑π¿Ã
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

void spaceSword::render()
{
	_img->rotateFrameRender(getMemDC(), _x - CAM->getX(), _y - CAM->getY(), 0, _dir, _angle);
}

void spaceSword::release()
{
}

void spaceSword::setup(image * effect1, image * effect2, image * effect3)
{
	weapon::setup(effect1, effect2, effect3);

	_atkWidth = 128;
	_atkHeight = 128;
}

void spaceSword::attack()
{
}
