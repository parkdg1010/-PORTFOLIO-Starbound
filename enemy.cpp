#include "stdafx.h"
#include "enemy.h"
#include "player.h"

HRESULT enemy::init()
{
	//������ �ʱ�ȭ
	_count = 0;
	_curFrameX = _curFrameY = 0;

	_oldX = _oldY = 0;

	(_dir == LEFT) ? (_angle = 180) : (_angle = 0);

	_isActive = true;

	//_vbullet = NULL;

	return S_OK;
}

void enemy::update()
{
	move();
}

void enemy::render()
{
}

void enemy::release()
{
}

void enemy::move()
{
}

void enemy::collide()
{
}

bool enemy::collideObject(gameObject * gameObject)
{
	return false;
}

void enemy::damaged(gameObject * actor)
{
}

bool enemy::bulletCountFire()
{
	_fireCount++;
	if (_fireCount % _rndFireCount == 0)
	{
		_rndFireCount = RND->getFromIntTo(1, 1000);
		_fireCount = 0;
		return true;
	}

	return false;
}
