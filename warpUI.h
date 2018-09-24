#pragma once
#include "gameObject.h"
class warpUI : public gameObject
{
private:
	HDC _uiDC;
	image* _warpUI;
	image* _warpButton;
	image* _warpShip;
	image* _warpHome;
	image* _warpDungeon;

	RECT _rcUI, _rcButton, _rcShip, _rcHome, _rcDungeon;
	bool _isCtrlPanelMove;
	POINT _ctrlPanelMove;

public:
	void ctrlPanelUpdate();						//패널, 패널단추 업데이트
	void ctrlPanelMove();						//드래그로 패널옮기기
	void ctrlPanelRender();						//패널, 패널단추 렌더

	void tabButtonSet();						//버튼 하이라이팅 끄기(흑색으로)

	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();

	warpUI() {}
	~warpUI() {}
};

