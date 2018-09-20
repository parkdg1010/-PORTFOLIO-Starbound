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
	progressBar* _hpBar;		//인벤체력바
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
	void closePanel();							//패널 닫기

	void ctrlPanelUpdate();						//패널, 패널단추 업데이트
	void ctrlPanelMove();						//드래그로 패널옮기기
	void ctrlPanelRender();						//패널, 패널단추 렌더

	void tabButtonSet();						//탭 하이라이팅 끄기(회색으로)

	void tabChange();							//패널탭 변경
	void iconRender(image* sample, int X, int Y, int rarity);	//패널에 샘플렌더

	void curTabIconRender();					//탭에따라 버튼에 아이콘 바꿔주기
	void itemUse();								//아이템 사용,장착
	void curItemOff();							//장착아이템 해제
	void equipItemRender();						//장착한 아이템 렌더

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

