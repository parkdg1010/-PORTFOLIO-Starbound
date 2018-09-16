#include "stdafx.h"
#include "fennix.h"

HRESULT fennix::init()
{
	enemy::init();

	for (int i = 0; i < 6; i++)
	{
		_img[i] = new animation;
		_img[i]->init(_pic->getWidth(), _pic->getHeight(), 10, 4);
		_img[i]->setFPS(1);
	}

	_img[FENNIX_IDLE]->setPlayFrame(1, 7);
	_img[FENNIX_HURT]->setPlayFrame(9,9);
	_img[FENNIX_MOVE]->setPlayFrame(11,16);
	_img[FENNIX_JUMP]->setPlayFrame(18,19);
	_img[FENNIX_FALL]->setPlayFrame(21,22);
	_img[FENNIX_SHOOT]->setPlayFrame(27,30);

	return S_OK;
}

void fennix::update()
{
	switch (_state)
	{
	case FENNIX_IDLE:
		break;
	case FENNIX_HURT:
		break;
	case FENNIX_MOVE:
		//평소에는 랜덤한 방향으로 움직이다 플레이어가 가까이 다가오면 감지하고 일정거리까지 따라옴
		break;
	case FENNIX_JUMP:
		break;
	case FENNIX_FALL:
		break;
	case FENNIX_SHOOT:
		break;
	}
	if (!_img[_state]->isPlay())
	{
		_img[_state]->start();
	}

	_img[_state]->frameUpdate(0.46f);
}

void fennix::render()
{

}

void fennix::release()
{

}

void fennix::bltUpdate()
{

}

void fennix::bltRender()
{

}

void fennix::move()
{

}

void fennix::collide()
{

}

bool fennix::collideObject(gameObject * gameObject)
{
	return false;
}

void fennix::damaged(gameObject * actor)
{
}