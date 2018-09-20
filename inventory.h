#pragma once
#include "gameObject.h"
#include "progressBar.h"
#include "gameItem.h"
#include "weapon.h"
#include "meleeWeapon.h"
#include "rangedWeapon.h"
#include "shotgun01.h"
enum INVENTAB
{
	INVEN_ITEM,
	INVEN_TILE,
	INVEN_OBJECT,
	INVEN_WEAPON,
	INVEN_ERASE
};

class inventory : public gameObject
{
private:
	HDC _uiDC;
	progressBar* _hpBar;		//�κ�ü�¹�
	image* _invenWindow;
	image* _invenTag[4];
	image* _invenEsc;
	image* _itemBorder;
	image* _number;

	INVENTAB _currentTab;

	RECT _rcInventory, _rcCurWeapon, _rcCurArmor, _rcCurBack, _rcWeaponTag, _rcItemTag, _rcTilesTag, _rcObjectTag, _rcErase, _rcClose;
	bool _isCtrlPanelMove;
	POINT _ctrlPanelMove;
	RECT _rcButton[40];

	vector<gameItem*> _vInventory[4];

	Synthesize(gameItem*, _curWeapon, CurWeapon)
	Synthesize(gameItem*, _curArmor, CurArmor)
	Synthesize(gameItem*, _curBack, CurBack)

public:
	void closePanel();							//�г� �ݱ�

	void ctrlPanelUpdate();						//�г�, �гδ��� ������Ʈ
	void ctrlPanelMove();						//�巡�׷� �гοű��
	void ctrlPanelRender();						//�г�, �гδ��� ����

	void tabButtonSet();						//�� ���̶����� ����(ȸ������)

	void tabChange();							//�г��� ����
	void iconRender(image* sample, int X, int Y, int rarity);	//�гο� ���÷���

	void curTabIconRender();					//�ǿ����� ��ư�� ������ �ٲ��ֱ�
	void itemUse();								//������ ���,����
	void curItemOff();							//���������� ����
	void equipItemRender();						//������ ������ ����

	void itemSwap(gameItem* &a, gameItem* &b);

	progressBar* getInvenHP() { return _hpBar; }

	vector<gameItem*> getItemInven() { return _vInventory[INVEN_ITEM]; }
	vector<gameItem*> getTileInven() { return _vInventory[INVEN_TILE]; }
	vector<gameItem*> getObjectInven() { return _vInventory[INVEN_OBJECT]; }
	vector<gameItem*> getWeaponInven() { return _vInventory[INVEN_WEAPON]; }

	void addItemInven(gameItem* item) { _vInventory[INVEN_ITEM].push_back(item); }
	void addTileInven(gameItem* item) { _vInventory[INVEN_TILE].push_back(item); }
	void addObjectInven(gameItem* item) { _vInventory[INVEN_OBJECT].push_back(item); }
	void addWeaponInven(gameItem* item) { _vInventory[INVEN_WEAPON].push_back(item); }

	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();

	inventory() {};
	~inventory() {};
};

