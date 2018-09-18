#include "stdafx.h"
#include "inventory.h"

HRESULT inventory::init()
{
	_isActive = false;

	_invenWindow = IMAGEMANAGER->findImage("inventory_body");

	_invenTag[0] = IMAGEMANAGER->findImage("invenTag_item");
	_invenTag[1] = IMAGEMANAGER->findImage("invenTag_object");
	_invenTag[2] = IMAGEMANAGER->findImage("invenTag_tiles");
	_invenTag[3] = IMAGEMANAGER->findImage("invenTag_weapon");
	_invenEsc = IMAGEMANAGER->findImage("inven_esc");

	return S_OK;
}

void inventory::update()
{
	if (_isActive)
	{

	}
}

void inventory::render()
{
	if (_isActive)
	{
		_invenWindow->render(getMemDC(), WINSIZEX*0.6f, WINSIZEY*0.1f);
	}
}

void inventory::release()
{
}

void inventory::minimize()
{
	if (PtInRect(&_rcMinimize, _ptMouse))
	{
		_isMinimize = true;
	}

	if (PtInRect(&_rcTaskBar, _ptMouse))
	{
		_isMinimize = false;
	}
}

void inventory::ctrlPanelUpdate()
{
	_rcCtrlPanel = RectMakeCenter(_ctrlPanelX, _ctrlPanelY, 503, 486);
	_rcSave = RectMakeCenter(_rcCtrlPanel.left + 200, _rcCtrlPanel.top + 35, 134, 35);
	_rcLoad = RectMakeCenter(_rcCtrlPanel.left + 350, _rcCtrlPanel.top + 35, 134, 35);
	_rcMinimize = RectMakeCenter(_rcCtrlPanel.left + 455, _rcCtrlPanel.top + 35, 44, 35);
	_rcWorld = RectMakeCenter(_rcCtrlPanel.left + 57, _rcCtrlPanel.top + 114, 65, 38);
	_rcTile = RectMakeCenter(_rcCtrlPanel.left + 124, _rcCtrlPanel.top + 114, 65, 38);
	_rcItem = RectMakeCenter(_rcCtrlPanel.left + 192, _rcCtrlPanel.top + 114, 65, 38);
	_rcObject = RectMakeCenter(_rcCtrlPanel.left + 259, _rcCtrlPanel.top + 114, 65, 38);
	_rcActor = RectMakeCenter(_rcCtrlPanel.left + 327, _rcCtrlPanel.top + 114, 65, 38);
	_rcErase = RectMakeCenter(_rcCtrlPanel.left + 452, _rcCtrlPanel.top + 113, 39, 39);
	for (int i = 0; i < 60; ++i)
	{
		_rcButton[i] = RectMakeCenter(_rcCtrlPanel.left + 35 + 48 * (i % 10), _rcCtrlPanel.top + 171 + 48 * (i / 10), 40, 40);
	}
}

void inventory::ctrlPanelMove()
{
	//컨트롤 패널을 클릭하면
	if (PtInRect(&_rcCtrlPanel, _ptMouse))
	{
		//패널무브가 아니면
		if (!_isCtrlPanelMove)
		{
			//마우스 위치랑 패널의 중점 거리를 저장
			_ctrlPanelMove.x = _ctrlPanelX - _ptMouse.x;
			_ctrlPanelMove.y = _ctrlPanelY - _ptMouse.y;
			_isCtrlPanelMove = true;
		}
	}

	if (_isCtrlPanelMove)
	{
		//저장한 거리만큼 보정해서 클릭한 곳을 끌고가게
		_ctrlPanelX = _ptMouse.x + _ctrlPanelMove.x;
		_ctrlPanelY = _ptMouse.y + _ctrlPanelMove.y;
	}
}

void inventory::ctrlPanelRender()
{
	_ctrlPanel->render(getMemDC(), _rcCtrlPanel.left, _rcCtrlPanel.top);
	_saveButton->frameRender(getMemDC(), _rcSave.left, _rcSave.top);
	_loadButton->frameRender(getMemDC(), _rcLoad.left, _rcLoad.top);
	_minimizeButton->frameRender(getMemDC(), _rcMinimize.left, _rcMinimize.top);
	_worldButton->frameRender(getMemDC(), _rcWorld.left, _rcWorld.top);
	_tilesButton->frameRender(getMemDC(), _rcTile.left, _rcTile.top);
	_itemButton->frameRender(getMemDC(), _rcItem.left, _rcItem.top);
	_objectButton->frameRender(getMemDC(), _rcObject.left, _rcObject.top);
	_actorButton->frameRender(getMemDC(), _rcActor.left, _rcActor.top);
	IMAGEMANAGER->render("빈패드", getMemDC(), _rcCtrlPanel.left + 9, _rcCtrlPanel.top + 9);
	IMAGEMANAGER->frameRender("숫자", getMemDC(), _rcCtrlPanel.left + 10, _rcCtrlPanel.top + 10, _saveCount, 0);
}

void inventory::tabButtonSet()
{
	_worldButton->setFrameX(0);
	_tilesButton->setFrameX(0);
	_itemButton->setFrameX(0);
	_objectButton->setFrameX(0);
	_actorButton->setFrameX(0);
}

void inventory::tabChange()
{
	if (PtInRect(&_rcWorld, _ptMouse))
	{
		_currentTab = CTRL_SIZINGTAB;
		tabButtonSet();
		_worldButton->setFrameX(2);
	}
	if (PtInRect(&_rcTile, _ptMouse))
	{
		_currentTab = CTRL_TERRAINTAB;
		tabButtonSet();
		_tilesButton->setFrameX(2);
	}
	if (PtInRect(&_rcItem, _ptMouse))
	{
		_currentTab = CTRL_ITEMTAB;
		tabButtonSet();
		_itemButton->setFrameX(2);
	}
	if (PtInRect(&_rcObject, _ptMouse))
	{
		_currentTab = CTRL_OBJECTTAB;
		tabButtonSet();
		_objectButton->setFrameX(2);
	}
	if (PtInRect(&_rcActor, _ptMouse))
	{
		_currentTab = CTRL_ACTORTAB;
		tabButtonSet();
		_actorButton->setFrameX(2);
	}
	if (PtInRect(&_rcErase, _ptMouse))
	{
		_currentTab = CTRL_ERASER;
		tabButtonSet();
	}
}

void inventory::sampleRender(image * sample, int X, int Y)
{
	sample->frameRender(getMemDC(), _rcButton[Y * 10 + X].left + 2, _rcButton[Y * 10 + X].top + 2, X, Y);
}

void inventory::curTabIconRender()
{
	if (_currentTab == CTRL_SIZINGTAB)
	{
		IMAGEMANAGER->render("큰월드", getMemDC(), _rcButton[0].left + 2, _rcButton[0].top + 2);
		IMAGEMANAGER->render("중간월드", getMemDC(), _rcButton[1].left + 2, _rcButton[1].top + 2);
		IMAGEMANAGER->render("작은월드", getMemDC(), _rcButton[2].left + 2, _rcButton[2].top + 2);
		IMAGEMANAGER->render("월드삭제", getMemDC(), _rcButton[3].left + 2, _rcButton[3].top + 2);
	}
	else if (_currentTab == CTRL_TERRAINTAB)
	{
		for (int i = 0; i < 6; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				sampleRender(_tileIcon, j, i);
			}
		}
	}
	else if (_currentTab == CTRL_ITEMTAB)
	{
		for (int i = 0; i < 6; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				sampleRender(_itemIcon, j, i);
			}
		}
	}
	else if (_currentTab == CTRL_OBJECTTAB)
	{
		for (int i = 0; i < 6; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				sampleRender(_objectIcon, j, i);
			}
		}
	}
	else if (_currentTab == CTRL_ACTORTAB)
	{
		for (int i = 0; i < 6; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				sampleRender(_actorIcon, j, i);
			}
		}
	}
}
