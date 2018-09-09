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

	int _objRenderCollideX;						//오브젝트끼리 겹치면 이미지 변경
	char _objShape;								//충돌할 인덱스 x,o,8 형태

	HBRUSH _myBrush;
public:
	void setupWorld();							//스테이지 크기 셋업
	void setBackImage();						//배경이미지 셋업
	void setMap();								//스테이지에 타일입히기
	int setObjFrame(int type, char shape = ' ');//오브젝트 모양변경 o,x,8 //다이아몬드 4방향, 대각선4방향, 8방향 //검사할 타입
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

