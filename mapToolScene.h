#pragma once
#include "gameNode.h"
#include "tileNode.h"

class mapToolScene : public gameNode
{
private:
	int _tileX, _tileY; //�������� Ÿ�ϰ���
	tagTile* _stage; //��������
	tagCurrentTile _currentTile;
	CTRL _currentTab;

	image* _ctrlPanel, *_saveButton, *_loadButton, *_minimizeButton, *_taskBar, *_worldButton, *_tilesButton, *_itemButton, *_objectButton, *_enemyButton;
	RECT _rcCtrlPanel, _rcSave, _rcLoad, _rcMinimize, _rcTaskBar, _rcWorld, _rcTile, _rcItem, _rcObject, _rcEnemy, _rcErase;
	float _ctrlPanelX, _ctrlPanelY;
	bool _isMinimize, _isCtrlPanelMove;
	POINT _ctrlPanelMove;
	
	image* _tileIcon, *_objectIcon, *_itemIcon;
	image* _brick[2], *_cobbleBrick[2], *_concrete[2], *_darkwood[2], *_dirt[2];
	image* _fullwood1[2], *_fullwood2[2], *_log[2], *_petalblock[2], *_rooftile[2];
	image* _woodencrate1;
	image* _item;
	RECT _rcButton[60];
	vector<tagTile*> _vItemBox;

	POINT _cameraLens;
	int _cameraSpeed;

	bool _lButtonDown;
	POINT _oldMouse;
	RECT _dragRc;
	image* _drag;

	bool _randomTile;

	image* _backGroundTop[5];
	image* _backGroundBot[5];
	int _curBackTop;
	int _curBackBot;

	HBRUSH _myBrush;
public:
	void setupWorld();							//�������� ũ�� �¾�
	void setMap();								//���������� Ÿ��������
	void save();
	void load();
	void minimize();							//�г� �ּ�ȭ

	void ctrlPanelUpdate();						//�г�, �гδ��� ������Ʈ
	void ctrlPanelMove();						//�巡�׷� �гοű��
	void ctrlPanelRender();						//�г�, �гδ��� ����

	void cameraMove();							//ī�޶��̵� WASD

	void tabButtonSet();						//�� ���̶����� ����(ȸ������)

	void tabChange();							//�г��� ����
	void tabTileSetup();						//currentTab�� ���� ����Ÿ�� ����
	void sampleRender(image* sample, int X, int Y);	//�гο� ���÷���

	void tileColorChange();						//Ÿ�ϻ��� ����

	void stageRender();							//�������� ����
	void curtileMouseRender();					//������ Ÿ�� ���콺�� ����
	void curTabIconRender();					//�ǿ����� ��ư�� ������ �ٲ��ֱ�

	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();

	void initImage();
	void initCamera();
	void initBrush();

	void releaseBrush();

	mapToolScene() {}
	~mapToolScene() {}
};

