#include "stdafx.h"
#include "kluexbossPh1.h"


HRESULT kluexbossPh1::init(POINTf pos, int dir)
{
	enemy::init(pos, dir);

	_pic = IMAGEMANAGER->findImage("BIRDBOSS1");

	_img[0]->init(_pic->getWidth(), _pic->getHeight(), 13, 3);
	_img[0]->setPlayFrame(0, 11, false);
	_img[0]->setFPS(1);

	_img[1]->init(_pic->getWidth(), _pic->getHeight(), 13, 3);
	_img[1]->setPlayFrame(13, 24, false);
	_img[1]->setFPS(1);

	_img[2]->init(_pic->getWidth(), _pic->getHeight(), 13, 3);
	_img[2]->setPlayFrame(26, 37, false);
	_img[2]->setFPS(1);

	return S_OK;
}

void kluexbossPh1::update()
{
	
	for (int i = 0; i < 3; ++i)
	{
		_img[i]->frameUpdate(0.1f);
	}
}

void kluexbossPh1::render()
{
	_pic->aniRender(getMemDC(), _x - CAM->getX(), _y - CAM->getY(), _img[_state]);
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
}

void kluexbossPh1::bltRender()
{
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