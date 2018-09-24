#include "stdafx.h"
#include "startScene.h"
#include "player.h"

HRESULT startScene::init()
{
	_ui[0] = IMAGEMANAGER->findImage("���۰���");
	_ui[1] = IMAGEMANAGER->findImage("���۸���");
	_ui[2] = IMAGEMANAGER->findImage("���ۿɼ�");
	_ui[3] = IMAGEMANAGER->findImage("���۳�����");

	for (int i = 0; i < 4; ++i)
	{
		_rcUi[i] = RectMake(0, WINSIZEY - 230 + 50 * i, _ui[i]->getFrameWidth(), _ui[0]->getFrameHeight());
		_buttonLight[i] = 0;
	}

	_space = IMAGEMANAGER->findImage("����");
	_star = IMAGEMANAGER->findImage("��");
	_earth = IMAGEMANAGER->findImage("����");
	_logo = IMAGEMANAGER->findImage("�ΰ�");

	_angle = 0;

	_soundOption = false;

	_player = SAVEDATA->getPlayer();
	_player->init();

	return S_OK;
}

void startScene::update()
{
	if (!_soundOption)
	{
		_angle += 0.000628f;
		if (_angle > 6.28f) _angle -= 6.28f;
	}

	for (int i = 0; i < 4; ++i)
	{
		buttonLighting(i);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_rcUi[0], _ptMouse))
		{
			_player->setPosition(1600, 440, LEFT);
			SCENEMANAGER->loadScene("�ΰ���");
			/*_player->setPosition(3350, 750, RIGHT);
			SCENEMANAGER->loadScene("���ּ�");*/
		}
		if (PtInRect(&_rcUi[1], _ptMouse))
		{
			SCENEMANAGER->loadScene("����");
		}
		if (PtInRect(&_rcUi[2], _ptMouse))
		{
			_soundOption = true;
			//����ɼ�
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
}

void startScene::release()
{
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
