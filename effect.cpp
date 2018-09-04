#include "stdafx.h"
#include "effect.h"

HRESULT effect::init(image * effectImg, float effectFPS)
{
	//변수 초기화
	_effectImg = effectImg;
	_effectFPS = effectFPS;
	_isRunning = false;

	//이펙트 애니메이션 생성 및 초기화
	_effectAni = new animation;
	_effectAni->init(_effectImg->getWidth(), _effectImg->getHeight(), _effectImg->getMaxFrameX() + 1, _effectImg->getMaxFrameY() + 1);
	_effectAni->setPlayFrame();
	_effectAni->setFPS(1);

	return S_OK;
}

void effect::release(void)
{
	//이펙트애니 해제
	_effectAni->release();
	SAFE_DELETE(_effectAni);
}

void effect::update(void)
{
	if (_isRunning)
	{
		_effectAni->frameUpdate(_effectFPS);
	}
	//이펙트 애니메이션 종료가 되면 멈추기(_isRunning = false;)
	if (!_effectAni->isPlay()) this->stopEffect();
}

void effect::render(void)
{
	if (_isRunning)
	{
		if (_angle >= 0)
		{
			_effectImg->rotateFrameRender(getMemDC(),
				_x - CAMERAMANAGER->getX() + _effectImg->getFrameWidth() / 2,
				_y - CAMERAMANAGER->getY() + _effectImg->getFrameHeight() / 2,
				_effectAni->getFramePos().x / _effectAni->getFrameWidth(),
				_effectAni->getFramePos().y / _effectAni->getFrameHeight(),
				_angle);
		}
		else
		{
			_effectImg->aniRender(getMemDC(), _x - CAMERAMANAGER->getX(), _y - CAMERAMANAGER->getY(), _effectAni);
		}
	}
}

void effect::startEffect(int x, int y)
{
	//위치를 센터좌표로 만들기
	_x = x - (_effectAni->getFrameWidth() / 2);
	_y = y - (_effectAni->getFrameHeight() / 2);

	_isRunning = true;
	_effectAni->start();
	_angle = -1;
}

void effect::startEffect(int x, int y, float angle)
{
	//위치를 센터좌표로 만들기
	_x = x - (_effectAni->getFrameWidth() / 2);
	_y = y - (_effectAni->getFrameHeight() / 2);

	_isRunning = true;
	_effectAni->start();
	_angle = angle;
}

void effect::stopEffect()
{
	_isRunning = false;
}
