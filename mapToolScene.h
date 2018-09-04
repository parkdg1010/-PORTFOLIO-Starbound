#pragma once
#include "gameNode.h"
#include "tileNode.h"

class mapToolScene : public gameNode
{
private:
	int _tileX, _tileY; //스테이지 타일갯수
	tagTile* _stage; //스테이지
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
	void setupWorld();							//스테이지 크기 셋업
	void setMap();								//스테이지에 타일입히기
	void save();
	void load();
	void minimize();							//패널 최소화

	void ctrlPanelUpdate();						//패널, 패널단추 업데이트
	void ctrlPanelMove();						//드래그로 패널옮기기
	void ctrlPanelRender();						//패널, 패널단추 렌더

	void cameraMove();							//카메라이동 WASD

	void tabButtonSet();						//탭 하이라이팅 끄기(회색으로)

	void tabChange();							//패널탭 변경
	void tabTileSetup();						//currentTab에 따라 샘플타일 변경
	void sampleRender(image* sample, int X, int Y);	//패널에 샘플렌더

	void tileColorChange();						//타일색상 변경

	void stageRender();							//스테이지 렌더
	void curtileMouseRender();					//선택한 타일 마우스에 렌더
	void curTabIconRender();					//탭에따라 버튼에 아이콘 바꿔주기

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

