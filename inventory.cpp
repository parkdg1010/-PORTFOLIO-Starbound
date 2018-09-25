#include "stdafx.h"
#include "inventory.h"

HRESULT inventory::init()
{
	_isActive = false;

	_invenWindow = IMAGEMANAGER->findImage("inventory_body");

	_invenTag[INVEN_ITEM] = IMAGEMANAGER->findImage("invenTag_item");
	_invenTag[INVEN_TILE] = IMAGEMANAGER->findImage("invenTag_tiles"); 
	_invenTag[INVEN_OBJECT] = IMAGEMANAGER->findImage("invenTag_object");
	_invenTag[INVEN_WEAPON] = IMAGEMANAGER->findImage("invenTag_weapon");
	_invenEsc = IMAGEMANAGER->findImage("inven_esc");
	_number = IMAGEMANAGER->findImage("����");

	_itemBorder = IMAGEMANAGER->findImage("inven_itemBorder");

	_x = WINSIZEX * 0.8f;
	_y = WINSIZEY * 0.5f;

	_hpBar = new progressBar;
	_hpBar->init("Texture/ui/inventory/invenHealth", "", -100, -100, 83, 13);

	_uiDC = UIMANAGER->getUIDC();

	return S_OK;
}

void inventory::update()
{
	if (_isActive)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			//�Ǻ���
			tabChange();
			//�κ�����
			closePanel();
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

		//TODO ������ Ŭ������ �����������ϱ� ����.
		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			itemUse();
			curItemOff();
		}

		_hpBar->update();
	}
}

void inventory::render()
{
	if (_isActive)
	{
		//�κ��丮 ����
		ctrlPanelRender();
		//������ ������ ����
		curTabIconRender();
		//����� ����
		equipItemRender();
		//TODO ���ݷ�, ����, ü�� �����ϱ�
		//�Ű������� �÷��̾��� ü�°��� �޾ƴ� ü�¹� ��������
		_hpBar->render(_uiDC);
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
	_hpBar->setPosition(_rcInventory.left + 307, _rcInventory.top + 88);
	for (int i = 0; i < 40; ++i)
	{
		_rcButton[i] = RectMakeCenter(_rcInventory.left + 35 + 48 * (i % 8), _rcInventory.top + 198 + 48 * (i / 8), 40, 40);
	}
}

void inventory::ctrlPanelMove()
{
	//��Ʈ�� �г��� Ŭ���ϸ�
	if (PtInRect(&_rcInventory, _ptMouse))
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

void inventory::ctrlPanelRender()
{
	_invenWindow->render(_uiDC, _rcInventory.left, _rcInventory.top);
	_invenTag[INVEN_ITEM]->frameRender(_uiDC, _rcItemTag.left, _rcItemTag.top);
	_invenTag[INVEN_TILE]->frameRender(_uiDC, _rcTilesTag.left, _rcTilesTag.top);
	_invenTag[INVEN_OBJECT]->frameRender(_uiDC, _rcObjectTag.left, _rcObjectTag.top);
	_invenTag[INVEN_WEAPON]->frameRender(_uiDC, _rcWeaponTag.left, _rcWeaponTag.top);
	_invenEsc->frameRender(_uiDC, _rcClose.left, _rcClose.top);
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
		_currentTab = INVEN_TILE;
		tabButtonSet();
		_invenTag[INVEN_TILE]->setFrameX(2);
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
//������ ����
void inventory::iconRender(image * sample, int X, int Y, int rarity)
{
	_itemBorder->frameRender(_uiDC, _rcButton[Y * 8 + X].left-2, _rcButton[Y * 8 + X].top-2, rarity, 0);
	sample->render(_uiDC, _rcButton[Y * 8 + X].left, _rcButton[Y * 8 + X].top);
}
//������ ����
void inventory::curTabIconRender()
{
	if (_currentTab == INVEN_ITEM)
	{
		for (int i = 0; i < _vInventory[INVEN_ITEM].size(); ++i)
		{
			if (_vInventory[INVEN_ITEM][i] == NULL) continue;
			iconRender(_vInventory[INVEN_ITEM][i]->getIcon(), i % 8, i / 8, _vInventory[INVEN_ITEM][i]->getRarity());
		}
	}
	else if (_currentTab == INVEN_TILE)
	{
		for (int i = 0; i < _vInventory[INVEN_TILE].size(); ++i)
		{
			if (_vInventory[INVEN_TILE][i] == NULL) continue;
			iconRender(_vInventory[INVEN_TILE][i]->getIcon(), i % 8, i / 8, _vInventory[INVEN_TILE][i]->getRarity());
		}
	}
	else if (_currentTab == INVEN_OBJECT)
	{
		for (int i = 0; i < _vInventory[INVEN_OBJECT].size(); ++i)
		{
			if (_vInventory[INVEN_OBJECT][i] == NULL) continue;
			iconRender(_vInventory[INVEN_OBJECT][i]->getIcon(), i % 8, i / 8, _vInventory[INVEN_OBJECT][i]->getRarity());
		}
	}
	else if (_currentTab == INVEN_WEAPON)
	{
		for (int i = 0; i < _vInventory[INVEN_WEAPON].size(); ++i)
		{
			if (_vInventory[INVEN_WEAPON][i] == NULL) continue;
			iconRender(_vInventory[INVEN_WEAPON][i]->getIcon(), i % 8, i / 8, _vInventory[INVEN_WEAPON][i]->getRarity());
		}
	}
}

void inventory::itemUse()
{
	if (_currentTab == INVEN_ITEM)
	{
		for (int i = 0; i < _vInventory[INVEN_ITEM].size(); ++i)
		{
			if (_vInventory[INVEN_ITEM][i] == NULL) continue;

			if (PtInRect(&_rcButton[i], _ptMouse))
			{
				_vInventory[INVEN_ITEM][i]->use();
				break;
			}
		}
	}
	else if (_currentTab == INVEN_TILE)
	{
		for (int i = 0; i < _vInventory[INVEN_TILE].size(); ++i)
		{
			if (_vInventory[INVEN_TILE][i] == NULL) continue;
			
		}
	}
	else if (_currentTab == INVEN_OBJECT)
	{
		for (int i = 0; i < _vInventory[INVEN_OBJECT].size(); ++i)
		{
			if (_vInventory[INVEN_OBJECT][i] == NULL) continue;
			
		}
	}
	else if (_currentTab == INVEN_WEAPON)
	{
		for (int i = 0; i < _vInventory[INVEN_WEAPON].size(); ++i)
		{
			if (_vInventory[INVEN_WEAPON][i] == NULL) continue;
			
			if (PtInRect(&_rcButton[i], _ptMouse))
			{
				itemSwap(_curWeapon, _vInventory[INVEN_WEAPON][i]);
				break;
			}
		}
	}
}

void inventory::curItemOff()
{
	if (_curWeapon != NULL)
	{
		if (PtInRect(&_rcCurWeapon, _ptMouse))
		{
			for (int i = 0; i < _vInventory[INVEN_WEAPON].size(); ++i)
			{
				if (_vInventory[INVEN_WEAPON][i] == NULL)
				{
					itemSwap(_vInventory[INVEN_WEAPON][i], _curWeapon);
					break;
				}
			}
		}
	}
}

void inventory::equipItemRender()
{
	if (_curWeapon != NULL)
	{
		_curWeapon->getIcon()->render(_uiDC, _rcCurWeapon.left + _curWeapon->getIcon()->getWidth()*0.5 - 5, _rcCurWeapon.top + _curWeapon->getIcon()->getHeight()*0.5 - 10);
		_number->frameRender(_uiDC, _rcInventory.left + 355, _rcInventory.top + 43, 0, 0); //0���� ������Ŵ
		_number->frameRender(_uiDC, _rcInventory.left + 343, _rcInventory.top + 43, (int)_curWeapon->getDamage() % 10, 0); //1���ڸ�
		_number->frameRender(_uiDC, _rcInventory.left + 331, _rcInventory.top + 43, (int)_curWeapon->getDamage() / 10, 0); //10���ڸ�
	}
	if (_curArmor != NULL)
	{
		_curArmor->getIcon()->render(_uiDC, _rcCurArmor.left + _curArmor->getIcon()->getWidth()*0.5 - 5, _rcCurArmor.top + _curArmor->getIcon()->getHeight()*0.5 - 10);
	}
	if (_curBack != NULL)
	{
		_curBack->getIcon()->render(_uiDC, _rcCurBack.left + _curBack->getIcon()->getWidth()*0.5 - 5, _rcCurBack.top + _curBack->getIcon()->getHeight()*0.5 - 10);
	}
}

void inventory::itemSwap(gameItem* &a, gameItem* &b)
{
	gameItem* swap = NULL;
	swap = a;
	a = b;
	b = swap;
}
