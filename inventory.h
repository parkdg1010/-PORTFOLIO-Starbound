#pragma once
#include "gameObject.h"
#include "gameItem.h"
#include "weapon.h"
#include "meleeWeapon.h"
#include "rangedWeapon.h"
#include "shotgun01.h"

class inventory : public gameObject
{
private:
	image* _invenWindow;
	image* _invenTag[4];
	image* _invenEsc;

	CTRL _currentTab;

	RECT _rcInventory, _rcCurWeapon, _rcCurArmor, _rcBackpack, _rcWeaponTag, _rcItemTag, _rcTilesTag, _rcObjectTag;
	float _ctrlPanelX, _ctrlPanelY;
	bool _isMinimize, _isCtrlPanelMove;
	POINT _ctrlPanelMove;
	image* _tileIcon, *_objectIcon, *_itemIcon, *_actorIcon;
	RECT _rcButton[60];

	Synthesize(vector<gameItem*>, _vInventory, vInvetory)
public:
	void minimize();							//�г� �ݱ�

	void ctrlPanelUpdate();						//�г�, �гδ��� ������Ʈ
	void ctrlPanelMove();						//�巡�׷� �гοű��
	void ctrlPanelRender();						//�г�, �гδ��� ����

	void tabButtonSet();						//�� ���̶����� ����(ȸ������)

	void tabChange();							//�г��� ����
	void sampleRender(image* sample, int X, int Y);	//�гο� ���÷���

	void curTabIconRender();					//�ǿ����� ��ư�� ������ �ٲ��ֱ�

	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();

	inventory() {};
	~inventory() {};
};

