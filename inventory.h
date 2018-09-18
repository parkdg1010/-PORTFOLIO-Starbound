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
	void minimize();							//패널 닫기

	void ctrlPanelUpdate();						//패널, 패널단추 업데이트
	void ctrlPanelMove();						//드래그로 패널옮기기
	void ctrlPanelRender();						//패널, 패널단추 렌더

	void tabButtonSet();						//탭 하이라이팅 끄기(회색으로)

	void tabChange();							//패널탭 변경
	void sampleRender(image* sample, int X, int Y);	//패널에 샘플렌더

	void curTabIconRender();					//탭에따라 버튼에 아이콘 바꿔주기

	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();

	inventory() {};
	~inventory() {};
};

