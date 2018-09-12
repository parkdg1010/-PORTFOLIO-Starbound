#include "stdafx.h"
#include "kluexbossPh1.h"

/*
kluex_Staff_Plasma
red_Pulse_Cannon_Explosion
energy_Crystal
ice_Eruption
energy_Wave
*/

HRESULT kluexbossPh1::init(POINTf pos, int dir)
{
	enemy::init(pos, dir);

	_pic = IMAGEMANAGER->findImage("BIRDBOSS1");

	_img[MAIN] = new animation;
	_img[MAIN]->init(_pic->getWidth(), _pic->getHeight(), 13, 3);
	_img[MAIN]->setPlayFrame(0, 11, true);
	_img[MAIN]->setFPS(1);

	_img[FIRE] = new animation;
	_img[FIRE]->init(_pic->getWidth(), _pic->getHeight(), 13, 3);
	_img[FIRE]->setPlayFrame(13, 24, true);
	_img[FIRE]->setFPS(1);

	_img[ICE] = new animation;
	_img[ICE]->init(_pic->getWidth(), _pic->getHeight(), 13, 3);
	_img[ICE]->setPlayFrame(26, 37, true);
	_img[ICE]->setFPS(1);

	_state = MAIN;

	_vbullet = new vector<bullet>;
	bullet blt;
	blt.init(24, 1, 5, WINSIZEX* WINSIZEY, "energycrystalImg");
	for (int i = 0; i < 10; ++i)
	{
		_vbullet->push_back(blt);
	}

	return S_OK;
}

void kluexbossPh1::update()
{
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		_img[_state]->start();
		for (int i = 0; i < _vbullet->size(); ++i)
		{
			if (_vbullet->at(i).getIsActive()) continue;
			_vbullet->at(i).fire(_x, _y, -PI*0.5);
			break;
		}
	}
	_img[_state]->frameUpdate(0.46f);
}

void kluexbossPh1::render()
{
	_pic->aniRender(getMemDC(), _x - (_img[_state]->getFrameWidth() >> 1) - CAM->getX(), _y - (_img[_state]->getFrameHeight() >> 1) - CAM->getY(), _img[_state]);
}

void kluexbossPh1::release()
{
	for (int i = 0; i < 3; ++i)
	{
		SAFE_DELETE(_img[i]);
	}
}

void kluexbossPh1::bltUpdate()
{
	for (int i = 0; i < _vbullet->size(); ++i)
	{
		_vbullet->at(i).update(); //벡터를 동적할당했을때 at을 통해 인덱스를 가져온다 at이 대괄호와 같은 의미로 사용
		if (_mapPixel != NULL)
		{
			_vbullet->at(i).collideMap(_mapPixel);
		}
	}
}

void kluexbossPh1::bltRender()
{
	for (int i = 0; i < _vbullet->size(); ++i)
	{
		_vbullet->at(i).render(true); //벡터를 동적할당했을때 at을 통해 인덱스를 가져온다 at이 대괄호와 같은 의미로 사용
	}
}

void kluexbossPh1::move()
{
}

void kluexbossPh1::collide()
{
}

bool kluexbossPh1::collideObject(gameObject * gameObject)
{
	return false;
}

void kluexbossPh1::damaged(gameObject * actor)
{
}

void kluexbossPh1::drawUI()
{
}