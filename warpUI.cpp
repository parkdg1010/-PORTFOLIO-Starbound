#include "stdafx.h"
#include "warpUI.h"
#include "player.h"

HRESULT warpUI::init()
{
	 _uiDC = UIMANAGER->getUIDC();

	_warpUI = IMAGEMANAGER->findImage("워프UI");
	_warpButton = IMAGEMANAGER->findImage("워프버튼");
	_warp[DUNGEON] = IMAGEMANAGER->findImage("워프_던전");
	_warp[SHIP] = IMAGEMANAGER->findImage("워프_우주선");
	_warp[HOME] = IMAGEMANAGER->findImage("워프_집");

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
			//탭변경
			tabChange();
			//워프
			warpDone();
		}

		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			//패널 옮기기
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
		//워프패널 렌더
		ctrlPanelRender();
	}
}

void warpUI::release()
{
}

void warpUI::ctrlPanelUpdate()
{
	_rcUI = RectMakeCenter(_x, _y, 373, 335);
	_rcButton = RectMakeCenter(_rcUI.left+190, _rcUI.top+293, 94, 28);
	_rc[DUNGEON] = RectMakeCenter(_rcUI.left+185, _rcUI.top+90, 340, 40);
	_rc[SHIP] = RectMakeCenter(_rcUI.left+185, _rcUI.top+150, 340, 40);
	_rc[HOME] = RectMakeCenter(_rcUI.left+185, _rcUI.top+210, 340, 40);
}

void warpUI::ctrlPanelMove()
{
	//컨트롤 패널을 클릭하면
	if (PtInRect(&_rcUI, _ptMouse))
	{
		//패널무브가 아니면
		if (!_isCtrlPanelMove)
		{
			//마우스 위치랑 패널의 중점 거리를 저장
			_ctrlPanelMove.x = _x - _ptMouse.x;
			_ctrlPanelMove.y = _y - _ptMouse.y;
			_isCtrlPanelMove = true;
		}
	}

	if (_isCtrlPanelMove)
	{
		//저장한 거리만큼 보정해서 클릭한 곳을 끌고가게
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
	_warp[DUNGEON]->setFrameY(0);
	_warp[HOME]->setFrameY(0);
	_warp[SHIP]->setFrameY(0);
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
	if (PtInRect(&_rcButton, _ptMouse))
	{
		switch (_currentTab)
		{
		case DUNGEON:
			_isActive = false;
			_player->setPosition(3400, 340, LEFT);
			_player->setStageNum(2);
			SCENEMANAGER->loadScene("인게임");
			break;
		case HOME:
			_isActive = false;
			_player->setPosition(2000, 440, LEFT);
			_player->setStageNum(1);
			SCENEMANAGER->loadScene("인게임");
			break;
		case SHIP:
			_isActive = false;
			_player->setPosition(3350, 750, RIGHT);
			SCENEMANAGER->loadScene("우주선");
			break;
		}
	}
}
