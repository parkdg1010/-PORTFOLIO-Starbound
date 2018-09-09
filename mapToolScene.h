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
	
	int _saveCount;

	image* _tileIcon, *_objectIcon, *_itemIcon;
	vector<image*> _tiles;
	image* _woodencrate1, *_treelights, *_ornatetorch;
	image* _flatform;
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

	int _objRenderCollideX;						//������Ʈ���� ��ġ�� �̹��� ����
	char _objShape;								//�浹�� �ε��� x,o,8 ����

	HBRUSH _myBrush;
public:
	void setupWorld();							//�������� ũ�� �¾�
	void setBackImage();						//����̹��� �¾�
	void setMap();								//���������� Ÿ��������
	int setObjFrame(int type, char shape = ' ');//������Ʈ ��纯�� o,x,8 //���̾Ƹ�� 4����, �밢��4����, 8���� //�˻��� Ÿ��
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

