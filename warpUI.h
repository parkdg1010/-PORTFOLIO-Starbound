#pragma once
#include "gameObject.h"
enum WARPTAB
{
	DUNGEON,
	SHIP,
	HOME
};

class player;									//플레이어의 위치를 바꾸기 위해 상호참조했다.
class warpUI : public gameObject
{
private:
	HDC _uiDC;
	image* _warpUI;
	image* _warpButton;
	image* _warp[3];

	RECT _rcUI, _rcButton, _rc[3];
	int _currentTab;
	bool _isCtrlPanelMove;
	POINT _ctrlPanelMove;

	player* _player;
public:
	void ctrlPanelUpdate();						//패널, 패널단추 업데이트
	void ctrlPanelMove();						//드래그로 패널옮기기
	void ctrlPanelRender();						//패널, 패널단추 렌더

	void tabButtonSet();						//버튼 하이라이팅 끄기(흑색으로)

	void tabChange();							//패널탭 변경

	void warpDone();							//워프함

	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();

	void linkPlayer(player* p) { _player = p; }

	warpUI() {}
	~warpUI() {}
};

