#include "stdafx.h"
#include "warpUI.h"
#include "player.h"

HRESULT warpUI::init()
{
	 _uiDC = UIMANAGER->getUIDC();

	_warpUI = IMAGEMANAGER->findImage("����UI");
	_warpButton = IMAGEMANAGER->findImage("������ư");
	_warp[DUNGEON] = IMAGEMANAGER->findImage("����_����");
	_warp[SHIP] = IMAGEMANAGER->findImage("����_���ּ�");
	_warp[HOME] = IMAGEMANAGER->findImage("����_��");

	_x = WINSIZEX * 0.8f;
	_y = WINSIZEY * 0.5f;

	return S_OK;
}

void warpUI::update()
{
	if (_isActive)
	{
		if (PtInRect(&_rcButton, _ptMouse))
			_warpButton->setFrameY(1);
		else _warpButton->setFrameY(0);

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			//�Ǻ���
			tabChange();
			//����
			warpDone();
		}

		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			//�г� �ű��
			ctrlPanelMove();
		}

		ctrlPanelUpdate();

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			if (_isCtrlPanelMove)
			{
				_isCtrlPanelMove = false;
			}
		}
	}
}

void warpUI::render()
{
	if (_isActive)
	{
		_uiDC = UIMANAGER->getUIDC();
		//�����г� ����
		ctrlPanelRender();
	}
}

void warpUI::release()
{
}

void warpUI::ctrlPanelUpdate()
{
	//TODO ��ġ �����Ұ�
	_rcUI = RectMakeCenter(_x, _y, 407, 465);
	_rcButton = RectMakeCenter(_rcUI.left + 46, _rcUI.top + 75, 65, 65);
	_rc[DUNGEON] = RectMakeCenter(_rcUI.left + 123, _rcUI.top + 75, 65, 65);
	_rc[SHIP] = RectMakeCenter(_rcUI.left + 58, _rcUI.top + 140, 65, 38);
	_rc[HOME] = RectMakeCenter(_rcUI.left + 198, _rcUI.top + 75, 65, 65);
}

void warpUI::ctrlPanelMove()
{
	//��Ʈ�� �г��� Ŭ���ϸ�
	if (PtInRect(&_rcUI, _ptMouse))
	{
		//�гι��갡 �ƴϸ�
		if (!_isCtrlPanelMove)
		{
			//���콺 ��ġ�� �г��� ���� �Ÿ��� ����
			_ctrlPanelMove.x = _x - _ptMouse.x;
			_ctrlPanelMove.y = _y - _ptMouse.y;
			_isCtrlPanelMove = true;
		}
	}

	if (_isCtrlPanelMove)
	{
		//������ �Ÿ���ŭ �����ؼ� Ŭ���� ���� ������
		_x = _ptMouse.x + _ctrlPanelMove.x;
		_y = _ptMouse.y + _ctrlPanelMove.y;
	}
}

void warpUI::ctrlPanelRender()
{
	_warpUI->render(_uiDC, _rcUI.left, _rcUI.top);
	_warpButton->frameRender(_uiDC, _rcButton.left, _rcButton.top);
	_warp[DUNGEON]->frameRender(_uiDC, _rc[DUNGEON].left, _rc[DUNGEON].top);
	_warp[SHIP]->frameRender(_uiDC, _rc[SHIP].left, _rc[SHIP].top);
	_warp[HOME]->frameRender(_uiDC, _rc[HOME].left, _rc[HOME].top);
}

void warpUI::tabButtonSet()
{
	_warp[DUNGEON]->setFrameX(0);
	_warp[HOME]->setFrameX(0);
	_warp[SHIP]->setFrameX(0);
}

void warpUI::tabChange()
{
	if (PtInRect(&_rc[DUNGEON], _ptMouse))
	{
		_currentTab = DUNGEON;
		tabButtonSet();
		_warp[DUNGEON]->setFrameY(1);
	}
	if (PtInRect(&_rc[HOME], _ptMouse))
	{
		_currentTab = HOME;
		tabButtonSet();
		_warp[HOME]->setFrameY(1);
	}
	if (PtInRect(&_rc[SHIP], _ptMouse))
	{
		_currentTab = SHIP;
		tabButtonSet();
		_warp[SHIP]->setFrameY(1);
	}
}

void warpUI::warpDone()
{
	
	
	switch (_currentTab)
	{
	case DUNGEON:
		_player->setPosition(1600, 440, LEFT);
		SCENEMANAGER->loadScene("�ΰ���");
		break;
	case HOME:
		break;
	case SHIP:
		_player->setPosition(3350, 750, RIGHT);
		SCENEMANAGER->loadScene("���ּ�");
		break;
	}
}
