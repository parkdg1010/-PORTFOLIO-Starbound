#pragma once
#include "gameObject.h"
enum WARPTAB
{
	DUNGEON,
	SHIP,
	HOME
};

class player;									//�÷��̾��� ��ġ�� �ٲٱ� ���� ��ȣ�����ߴ�.
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
	void ctrlPanelUpdate();						//�г�, �гδ��� ������Ʈ
	void ctrlPanelMove();						//�巡�׷� �гοű��
	void ctrlPanelRender();						//�г�, �гδ��� ����

	void tabButtonSet();						//��ư ���̶����� ����(�������)

	void tabChange();							//�г��� ����

	void warpDone();							//������

	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();

	void linkPlayer(player* p) { _player = p; }

	warpUI() {}
	~warpUI() {}
};

