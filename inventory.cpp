#include "stdafx.h"
#include "inventory.h"

HRESULT inventory::init()
{
	_isActive = false;

	_invenWindow = IMAGEMANAGER->findImage("inventory_body");

	_invenTag[INVEN_ITEM] = IMAGEMANAGER->findImage("invenTag_item");
	_invenTag[INVEN_TILES] = IMAGEMANAGER->findImage("invenTag_tiles"); 
	_invenTag[INVEN_OBJECT] = IMAGEMANAGER->findImage("invenTag_object");
	_invenTag[INVEN_WEAPON] = IMAGEMANAGER->findImage("invenTag_weapon");
	_invenEsc = IMAGEMANAGER->findImage("inven_esc");

	_x = WINSIZEX * 0.8f;
	_y = WINSIZEY * 0.5f;

	return S_OK;
}

void inventory::update()
{
	if (_isActive)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			//탭변경
			tabChange();
			//인벤끄기
			closePanel();
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

void inventory::render()
{
	if (_isActive)
	{
		ctrlPanelRender();
	}
}

void inventory::release()
{
}

void inventory::closePanel()
{
	if (PtInRect(&_rcClose, _ptMouse))
	{
		_isActive = false;
	}
}

void inventory::ctrlPanelUpdate()
{
	_rcInventory = RectMakeCenter(_x, _y, 407, 465);
	_rcCurWeapon = RectMakeCenter(_rcInventory.left+46, _rcInventory.top+75, 65, 65);
	_rcCurArmor = RectMakeCenter(_rcInventory.left + 123, _rcInventory.top + 75, 65, 65);
	_rcCurBack = RectMakeCenter(_rcInventory.left + 198, _rcInventory.top + 75, 65, 65);
	_rcItemTag = RectMakeCenter(_rcInventory.left + 58, _rcInventory.top + 140, 65, 38);
	_rcTilesTag = RectMakeCenter(_rcInventory.left + 125, _rcInventory.top + 140, 65, 38);
	_rcObjectTag = RectMakeCenter(_rcInventory.left + 193, _rcInventory.top + 140, 65, 38);
	_rcWeaponTag = RectMakeCenter(_rcInventory.left + 260, _rcInventory.top + 140, 65, 38);
	_rcErase = RectMakeCenter(_rcInventory.left + 357, _rcInventory.top + 140, 39, 39);
	_rcClose = RectMakeCenter(_rcInventory.left + 370, _rcInventory.top + 18, 35, 28);
	for (int i = 0; i < 40; ++i)
	{
		_rcButton[i] = RectMakeCenter(_rcInventory.left + 35 + 48 * (i % 8), _rcInventory.top + 171 + 48 * (i / 8), 40, 40);
	}
}

void inventory::ctrlPanelMove()
{
	//컨트롤 패널을 클릭하면
	if (PtInRect(&_rcInventory, _ptMouse))
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

void inventory::ctrlPanelRender()
{
	_invenWindow->render(getMemDC(), _rcInventory.left, _rcInventory.top);
	_invenTag[INVEN_ITEM]->frameRender(getMemDC(), _rcItemTag.left, _rcItemTag.top);
	_invenTag[INVEN_TILES]->frameRender(getMemDC(), _rcTilesTag.left, _rcTilesTag.top);
	_invenTag[INVEN_OBJECT]->frameRender(getMemDC(), _rcObjectTag.left, _rcObjectTag.top);
	_invenTag[INVEN_WEAPON]->frameRender(getMemDC(), _rcWeaponTag.left, _rcWeaponTag.top);
	_invenEsc->frameRender(getMemDC(), _rcClose.left, _rcClose.top);
}

void inventory::tabButtonSet()
{
	for (int i = 0; i < 4; ++i)
	{
		_invenTag[i]->setFrameX(0);
	}
}

void inventory::tabChange()
{
	if (PtInRect(&_rcItemTag, _ptMouse))
	{
		_currentTab = INVEN_ITEM;
		tabButtonSet();
		_invenTag[INVEN_ITEM]->setFrameX(2);
	}
	if (PtInRect(&_rcTilesTag, _ptMouse))
	{
		_currentTab = INVEN_TILES;
		tabButtonSet();
		_invenTag[INVEN_TILES]->setFrameX(2);
	}
	if (PtInRect(&_rcObjectTag, _ptMouse))
	{
		_currentTab = INVEN_OBJECT;
		tabButtonSet();
		_invenTag[INVEN_OBJECT]->setFrameX(2);
	}
	if (PtInRect(&_rcWeaponTag, _ptMouse))
	{
		_currentTab = INVEN_WEAPON;
		tabButtonSet();
		_invenTag[INVEN_WEAPON]->setFrameX(2);
	}
	if (PtInRect(&_rcErase, _ptMouse))
	{
		_currentTab = INVEN_ERASE;
		tabButtonSet();
	}
}

void inventory::iconRender(image * sample, int X, int Y)
{
	sample->frameRender(getMemDC(), _rcButton[Y * 8 + X].left + 2, _rcButton[Y * 8 + X].top + 2);
}

void inventory::curTabIconRender()
{
	//TODO : 인벤토리창에 아이템 아이콘 띄워주기
}
