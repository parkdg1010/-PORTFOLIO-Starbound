#pragma once
#include "gameObject.h"
#include "gameItem.h"
#include "weapon.h"
#include "meleeWeapon.h"
#include "rangedWeapon.h"
#include "shotgun01.h"
enum INVENTAB
{
	INVEN_ITEM,
	INVEN_TILES,
	INVEN_OBJECT,
	INVEN_WEAPON,
	INVEN_ERASE
};

class inventory : public gameObject
{
private:
	image* _invenWindow;
	image* _invenTag[4];
	image* _invenEsc;

	INVENTAB _currentTab;

	RECT _rcInventory, _rcCurWeapon, _rcCurArmor, _rcCurBack, _rcWeaponTag, _rcItemTag, _rcTilesTag, _rcObjectTag, _rcErase, _rcClose;
	bool _isCtrlPanelMove;
	POINT _ctrlPanelMove;
	RECT _rcButton[40];

	Synthesize(vector<gameItem*>, _vInventory, vInvetory)
public:
	void closePanel();							//�г� �ݱ�

	void ctrlPanelUpdate();						//�г�, �гδ��� ������Ʈ
	void ctrlPanelMove();						//�巡�׷� �гοű��
	void ctrlPanelRender();						//�г�, �гδ��� ����

	void tabButtonSet();						//�� ���̶����� ����(ȸ������)

	void tabChange();							//�г��� ����
	void iconRender(image* sample, int X, int Y);	//�гο� ���÷���

	void curTabIconRender();					//�ǿ����� ��ư�� ������ �ٲ��ֱ�

	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();

	inventory() {};
	~inventory() {};
};

