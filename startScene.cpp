#include "stdafx.h"
#include "startScene.h"
#include "player.h"

HRESULT startScene::init()
{
	initImage();

	for (int i = 0; i < 4; ++i)
	{
		_rcUi[i] = RectMake(0, WINSIZEY - 230 + 50 * i, _ui[i]->getFrameWidth(), _ui[0]->getFrameHeight());
		_buttonLight[i] = 0;
	}

	_angle = 0;

	_soundOption = false;

	_player = SAVEDATA->getPlayer();
	_player->init();

	SOUNDMANAGER->playBgm("인트로", _soundVolume);

	return S_OK;
}

void startScene::update()
{
	if (!_soundOption)
	{
		_angle += 0.000628f;
		if (_angle > 6.28f) _angle -= 6.28f;
	}
	else
	{
		soundOptionUpdate();
	}

	for (int i = 0; i < 4; ++i)
	{
		buttonLighting(i);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_rcUi[0], _ptMouse))
		{
			_player->setPosition(3350, 750, RIGHT);
			_player->setHp(PLAYER_CONST::MAX_HP);
			_player->setEnergy(PLAYER_CONST::MAX_ENERGY);
			SCENEMANAGER->loadScene("우주선");
		}
		if (PtInRect(&_rcUi[1], _ptMouse))
		{
			SCENEMANAGER->loadScene("맵툴");
		}
		if (PtInRect(&_rcUi[2], _ptMouse))
		{
			if (_soundOption)
				_soundOption = false;
			else
				_soundOption = true;
		}
		if (PtInRect(&_rcUi[3], _ptMouse))
		{
			PostMessage(_hWnd, WM_DESTROY, 0, 0);
		}
	}
}

void startScene::render()
{
	_space->render(getMemDC(), 0, 0);
	_star->rotateRender(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, _angle);

	_earth->rotateRender(getMemDC(), WINSIZEX /2, WINSIZEY + 1200 / 2, _angle);

	for (int i = 0; i < 4; ++i)
	{
		_ui[i]->frameRender(getMemDC(), _rcUi[i].left, _rcUi[i].top, 0, _buttonLight[i]);
	}

	RECT temp = RectMake(0, 120, WINSIZEX, _logo->getHeight());
	HBRUSH myBrush, oldBrush;
	myBrush = CreateSolidBrush(RGB(0, 0, 0));
	oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

	Rectangle(getMemDC(), temp);

	SelectObject(getMemDC(), oldBrush);

	DeleteObject(myBrush);
	DeleteObject(oldBrush);

	_logo->stretchRender(getMemDC(), WINSIZEX / 2 - _logo->getWidth()*0.75f, 100, 1.5f);

	if (_soundOption)
	{
		soundOptionRender();
	}
}

void startScene::release()
{
	SAVEDATA->setPlayer(_player);
}

void startScene::buttonLighting(int index)
{
	if (PtInRect(&_rcUi[index], _ptMouse))
	{
		_buttonLight[index] = 0;
	}
	else
	{
		_buttonLight[index] = 1;
	}
}

void startScene::initImage()
{
	_ui[0] = IMAGEMANAGER->findImage("시작게임");
	_ui[1] = IMAGEMANAGER->findImage("시작맵툴");
	_ui[2] = IMAGEMANAGER->findImage("시작옵션");
	_ui[3] = IMAGEMANAGER->findImage("시작나가기");

	_space = IMAGEMANAGER->findImage("우주");
	_star = IMAGEMANAGER->findImage("별");
	_earth = IMAGEMANAGER->findImage("지구");
	_logo = IMAGEMANAGER->findImage("로고");

	_numbers = IMAGEMANAGER->findImage("숫자");

	_soundUI = IMAGEMANAGER->findImage("소리옵션창");
	_soundButton = IMAGEMANAGER->findImage("소리버튼");
	_soundLeft = IMAGEMANAGER->findImage("왼쪽화살표");
	_soundRight = IMAGEMANAGER->findImage("오른쪽화살표");
}

void startScene::soundOptionUpdate()
{
	_rcSoundUI = RectMakeCenter(WINSIZEX*0.5f, WINSIZEY*0.55f, _soundUI->getWidth(), _soundUI->getHeight());
	_rcSoundButton = RectMakeCenter(WINSIZEX*0.5f, _rcSoundUI.bottom - 20, _soundButton->getFrameWidth(), _soundButton->getFrameHeight());
	_rcSoundNum[0] = RectMakeCenter(_rcSoundUI.right - 123, _rcSoundUI.top + 108, _numbers->getFrameWidth(), _numbers->getFrameHeight());
	_rcSoundNum[1] = RectMakeCenter(_rcSoundUI.right - 103, _rcSoundUI.top + 108, _numbers->getFrameWidth(), _numbers->getFrameHeight());
	_rcSoundNum[2] = RectMakeCenter(_rcSoundUI.right - 83, _rcSoundUI.top + 108, _numbers->getFrameWidth(), _numbers->getFrameHeight());
	_rcSoundArrow[LEFT] = RectMakeCenter(_rcSoundNum[0].left - 30, _rcSoundNum[0].top + 9, _soundLeft->getFrameWidth(), _soundLeft->getFrameHeight());
	_rcSoundArrow[RIGHT] = RectMakeCenter(_rcSoundNum[2].right + 30, _rcSoundNum[2].top + 9, _soundRight->getFrameWidth(), _soundRight->getFrameHeight());
	_rcEffectNum[0] = RectMakeCenter(_rcSoundUI.right - 123, _rcSoundUI.top + 171, _numbers->getFrameWidth(), _numbers->getFrameHeight());
	_rcEffectNum[1] = RectMakeCenter(_rcSoundUI.right - 103, _rcSoundUI.top + 171, _numbers->getFrameWidth(), _numbers->getFrameHeight());
	_rcEffectNum[2] = RectMakeCenter(_rcSoundUI.right - 83, _rcSoundUI.top + 171, _numbers->getFrameWidth(), _numbers->getFrameHeight());
	_rcEffectArrow[LEFT] = RectMakeCenter(_rcEffectNum[0].left - 30, _rcEffectNum[0].top + 9, _soundLeft->getFrameWidth(), _soundLeft->getFrameHeight());
	_rcEffectArrow[RIGHT] = RectMakeCenter(_rcEffectNum[2].right + 30, _rcEffectNum[2].top + 9, _soundRight->getFrameWidth(), _soundRight->getFrameHeight());

	_buttonFrame = 0;
	_soundArrowFrame[RIGHT] = 0;
	_soundArrowFrame[LEFT] = 0;
	_effectArrowFrame[LEFT] = 0;
	_effectArrowFrame[RIGHT] = 0;

	if (PtInRect(&_rcSoundButton, _ptMouse))
	{
		_buttonFrame = 1;
	}
	if (PtInRect(&_rcSoundArrow[LEFT], _ptMouse))
	{
		_soundArrowFrame[LEFT] = 1;
	}
	if (PtInRect(&_rcSoundArrow[RIGHT], _ptMouse))
	{
		_soundArrowFrame[RIGHT] = 1;
	}
	if (PtInRect(&_rcEffectArrow[LEFT], _ptMouse))
	{
		_effectArrowFrame[LEFT] = 1;
	}
	if (PtInRect(&_rcEffectArrow[RIGHT], _ptMouse))
	{
		_effectArrowFrame[RIGHT] = 1;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_rcSoundArrow[LEFT], _ptMouse))
		{
			if(_soundVolume > 0)
				_soundVolume -= 0.01f;
		}
		else if (PtInRect(&_rcSoundArrow[RIGHT], _ptMouse))
		{
			if (_soundVolume < 1.f)
				_soundVolume += 0.01f;
		}
		else if (PtInRect(&_rcEffectArrow[LEFT], _ptMouse))
		{
			if (_effectVolume > 0)
				_effectVolume -= 0.01f;
		}
		else if (PtInRect(&_rcEffectArrow[RIGHT], _ptMouse))
		{
			if (_effectVolume < 1.f)
				_effectVolume += 0.01f;
		}
		else if (PtInRect(&_rcSoundButton, _ptMouse))
		{
			_soundOption = false;
		}
	}
	SOUNDMANAGER->setVolume(_soundVolume);
}

void startScene::soundOptionRender()
{
	_soundUI->render(getMemDC(), _rcSoundUI.left, _rcSoundUI.top);
	_soundButton->frameRender(getMemDC(), _rcSoundButton.left, _rcSoundButton.top, 0, _buttonFrame);
	//사운드볼륨
	_numbers->frameRender(getMemDC(), _rcSoundNum[0].left, _rcSoundNum[0].top, (int)_soundVolume, 0); //100의자리
	_numbers->frameRender(getMemDC(), _rcSoundNum[1].left, _rcSoundNum[1].top, (int)(_soundVolume * 100) % 100 / 10, 0); //10의자리
	_numbers->frameRender(getMemDC(), _rcSoundNum[2].left, _rcSoundNum[2].top, (int)(_soundVolume*100)%10, 0); //1의자리
	//이펙트볼륨
	_numbers->frameRender(getMemDC(), _rcEffectNum[0].left, _rcEffectNum[0].top, (int)_effectVolume, 0); //100의자리
	_numbers->frameRender(getMemDC(), _rcEffectNum[1].left, _rcEffectNum[1].top, (int)(_effectVolume * 100) % 100 / 10, 0); //10의자리
	_numbers->frameRender(getMemDC(), _rcEffectNum[2].left, _rcEffectNum[2].top, (int)(_effectVolume * 100) % 10, 0); //1의자리
	//사운드 화살표
	_soundRight->frameRender(getMemDC(), _rcSoundArrow[RIGHT].left, _rcSoundArrow[RIGHT].top, 0, _soundArrowFrame[RIGHT]);
	_soundLeft->frameRender(getMemDC(), _rcSoundArrow[LEFT].left, _rcSoundArrow[LEFT].top, 0, _soundArrowFrame[LEFT]);
	//이펙트 화살표
	_soundRight->frameRender(getMemDC(), _rcEffectArrow[RIGHT].left, _rcEffectArrow[RIGHT].top, 0, _effectArrowFrame[RIGHT]);
	_soundLeft->frameRender(getMemDC(), _rcEffectArrow[LEFT].left, _rcEffectArrow[LEFT].top, 0, _effectArrowFrame[LEFT]);
}
