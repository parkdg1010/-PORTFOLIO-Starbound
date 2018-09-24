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
	void ctrlPanelUpdate();						//�г�, �гδ��� ������Ʈ
	void ctrlPanelMove();						//�巡�׷� �гοű��
	void ctrlPanelRender();						//�г�, �гδ��� ����

	void tabButtonSet();						//��ư ���̶����� ����(�������)

	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();

	warpUI() {}
	~warpUI() {}
};

