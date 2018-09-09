#include "stdafx.h"
#include "mapToolScene.h"
HRESULT mapToolScene::init()
{
	initImage();

	_currentTab = CTRL_SIZINGTAB;

	_isMinimize = false;
	_isCtrlPanelMove = false;
	_ctrlPanelX = WINSIZEX - 280;
	_ctrlPanelY = WINSIZEY/2;
	ctrlPanelUpdate();

	_tileX = _tileY = 0;
	_stage = NULL;

	ZeroMemory(&_currentTile, sizeof(tagCurrentTile));
	_currentTile.frontBack = FRONT;
	
	initCamera();

	_lButtonDown = false;

	_randomTile = true;

	_curBackTop = BACKTOP_0;
	_curBackBot = BACKBOT_0;

	_saveCount = 0;

	initBrush();

	return S_OK;
}

void mapToolScene::update()
{
	if (!_lButtonDown) _oldMouse = _ptMouse; //키를 누르지 않으면 옛날좌표를 계속 저장

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (!_isMinimize)
		{
			//탭변경
			tabChange();
			//currentTab에 따라 샘플타일 변경
			tabTileSetup();
			//세이브
			save();
			//로드
			load();
		}

		//최소화
		minimize();

		_lButtonDown = true;
	}

	if (KEYMANAGER->isOnceKeyDown(' '))
	{
		if (!_isMinimize)
		{
			_isMinimize = true;
		}
		else
		{
			_isMinimize = false;
		}
	}

	_cameraSpeed = 4;
	if (KEYMANAGER->isToggleKey(VK_CAPITAL))
	{
		_cameraSpeed = 10;
	}

	_randomTile = true;
	if (KEYMANAGER->isStayKeyDown(VK_LCONTROL))
	{
		_randomTile = false;
	}

	_currentTile.frontBack = (TERRAIN_FRONTBACK)KEYMANAGER->isToggleKey(VK_LSHIFT);

	//타일색상 변경
	tileColorChange();
	//카메라무브
	cameraMove();

	//패널 옮기기
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (!_isMinimize)
		{
			ctrlPanelMove();
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		if (_isCtrlPanelMove)
		{
			_isCtrlPanelMove = false;
		}
		_lButtonDown = false;
	}

	if (_lButtonDown)
	{
		setMap();
	}

	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (_saveCount > 0)
			_saveCount--;
	}
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		if (_saveCount < 9)
			_saveCount++;
	}

	if(!_isMinimize) ctrlPanelUpdate();
	else _rcTaskBar = RectMake(0, WINSIZEY - 35, 134, 35);

	CAMERAMANAGER->videoShooting((int)_cameraLens.x, (int)_cameraLens.y);
}

void mapToolScene::render()
{
	//스테이지 렌더
	stageRender();

	//선택한 타일 마우스에 보이게
	curtileMouseRender();

	if (!_isMinimize)
	{
		//패널 렌더
		ctrlPanelRender();

		//탭에따라 버튼에 이미지타입 바꿔주기
		curTabIconRender();
	}
	else
	{
		_taskBar->frameRender(getMemDC(), _rcTaskBar.left, _rcTaskBar.top, 0, 0);
	}

	//드래그 범위 보여주기
	if (_isMinimize || !PtInRect(&_rcCtrlPanel, _ptMouse))
	{
		if (_lButtonDown)
		{
			RectangleLine(getMemDC(), _dragRc.left - CAM->getX(), _dragRc.top - CAM->getY(),
				_dragRc.right - CAM->getX(), _dragRc.bottom - CAM->getY(), RGB(0, 200, 0));

			_drag->alphaRender(getMemDC(), _dragRc.left - CAM->getX(), _dragRc.top - CAM->getY()
				, 0, 0, _dragRc.right - _dragRc.left, _dragRc.bottom - _dragRc.top, 100);
		}
	}

	if (_isDebug)
	{
		textMake(getMemDC(), _cameraLens.x - CAM->getX(), _cameraLens.y - CAM->getY(), "X");
		textMake(getMemDC(), 200, 100, "x", (_cameraLens.x) / TILESIZE);
		textMake(getMemDC(), 200, 120, "y", (_cameraLens.y) / TILESIZE);
	}
}

void mapToolScene::release()
{
	releaseBrush();
}

//이미지 초기화
void mapToolScene::initImage()
{
	_ctrlPanel = IMAGEMANAGER->findImage("맵툴UI");
	_saveButton = IMAGEMANAGER->findImage("맵세이브UI");
	_loadButton = IMAGEMANAGER->findImage("맵로드UI");
	_minimizeButton = IMAGEMANAGER->findImage("맵툴최소화");
	_taskBar = IMAGEMANAGER->findImage("맵툴표시줄");
	_worldButton = IMAGEMANAGER->findImage("크기태그");
	_tilesButton = IMAGEMANAGER->findImage("지형태그");
	_itemButton = IMAGEMANAGER->findImage("아이템태그");
	_objectButton = IMAGEMANAGER->findImage("오브젝트태그");
	_enemyButton = IMAGEMANAGER->findImage("에너미태그");
	_drag = IMAGEMANAGER->findImage("드래그");

	//샘플
	_tileIcon = IMAGEMANAGER->findImage("타일아이콘");
	_objectIcon = IMAGEMANAGER->findImage("오브젝트아이콘");
	_itemIcon = IMAGEMANAGER->findImage("아이템아이콘");

	//TODO : 타일추가
	//타일
	image* tileType;
	vector<string> keyname = { "TILE_BRICK","BACKTILE_BRICK", "TILE_COBBLEBRICK", "BACKTILE_COBBLEBRICK", 
		"TILE_CONCRETE", "BACKTILE_CONCRETE", "TILE_DARKWOOD", "BACKTILE_DARKWOOD", "TILE_DIRT", 
		"BACKTILE_DIRT", "TILE_FULLWOOD1", "BACKTILE_FULLWOOD1", "TILE_FULLWOOD2", "BACKTILE_FULLWOOD2", 
		"TILE_LOG", "BACKTILE_LOG", "TILE_PETALBLOCK", "BACKTILE_PETALBLOCK", "TILE_ROOF", "BACKTILE_ROOF"};
	for (int i = 0; i < keyname.size(); ++i)
	{
		tileType = IMAGEMANAGER->findImage(keyname[i]);
		_tiles.push_back(tileType);
	}

	//오브젝트
	_woodencrate1 = IMAGEMANAGER->findImage("나무상자1");
	_treelights = IMAGEMANAGER->findImage("트리전구");

	//아이템
	_item = IMAGEMANAGER->findImage("우주검");

	//배경
	_backGroundTop[0] = IMAGEMANAGER->findImage("배경Top0");
	_backGroundTop[1] = IMAGEMANAGER->findImage("배경Top1");
	_backGroundTop[2] = IMAGEMANAGER->findImage("배경Top2");
	_backGroundTop[3] = IMAGEMANAGER->findImage("배경Top3");
	_backGroundTop[4] = IMAGEMANAGER->findImage("배경Top4");

	_backGroundBot[0] = IMAGEMANAGER->findImage("배경Bot0");
	_backGroundBot[1] = IMAGEMANAGER->findImage("배경Bot1");
	_backGroundBot[2] = IMAGEMANAGER->findImage("배경Bot2");
	_backGroundBot[3] = IMAGEMANAGER->findImage("배경Bot3");
}

//카메라 초기화
void mapToolScene::initCamera()
{
	_cameraLens = { WINSIZEX / 2, WINSIZEY / 2 };
	CAMERAMANAGER->init();
	CAMERAMANAGER->setRange(3000, 3000);
	CAMERAMANAGER->setPosition((int)_cameraLens.x, (int)_cameraLens.y);
	_cameraSpeed = 4;
}

void mapToolScene::initBrush()
{
	_myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	SelectObject(getMemDC(), _myBrush);
}

void mapToolScene::releaseBrush()
{
	DeleteObject(_myBrush);
}

//스테이지 크기선택
void mapToolScene::setupWorld()
{	
	//맵사이즈 설정
	if (PtInRect(&_rcButton[0], _ptMouse))
	{
		if (_stage == NULL)
		{
			_tileX = 500;
			_tileY = 500;
		}
	}
	if (PtInRect(&_rcButton[1], _ptMouse))
	{
		if (_stage == NULL)
		{
			_tileX = 300;
			_tileY = 300;
		}
	}
	if (PtInRect(&_rcButton[2], _ptMouse))
	{
		if (_stage == NULL)
		{
			_tileX = 100;
			_tileY = 100;
		}
	}
	//설정한대로 맵만들기 //스테이지 가로,세로가 0이 아닌 조건이 있어야 ptInRect조건없이도 정상작동함
	if (_tileX != 0 && _tileY != 0 && _stage == NULL)
	{
		_stage = new tagTile[_tileX * _tileY];
		for (int i = 0; i < _tileX * _tileY; ++i)
		{
			_stage[i].rc = RectMake(TILESIZE * (i % _tileX), TILESIZE * (i / _tileX), TILESIZE, TILESIZE);
			_stage[i].terrain = TR_DIRT;
			_stage[i].frontBack = FRONT;
			_stage[i].object = OBJECT_NONE;
			_stage[i].terrainFrameX = RND->getInt(5);
			_stage[i].terrainFrameY = 0;
			_stage[i].objFrameX = 0;
			_stage[i].objFrameY = 0;
		}
		CAMERAMANAGER->setRange(_tileX * TILESIZE, _tileY * TILESIZE);
		_cameraLens.x = _tileX * TILESIZE / 2;
		_cameraLens.y = WINSIZEY / 2;
		//CAMERAMANAGER->videoShooting((int)_cameraLens.x, (int)_cameraLens.y);
	}
	//맵지우기
	if (PtInRect(&_rcButton[3], _ptMouse))
	{
		_stage = NULL;
		_tileX = 0;
		_tileY = 0;
	}
}

void mapToolScene::setBackImage()
{
	//top백그라운드
	for (int i = 0; i < 5; ++i)
	{
		if (PtInRect(&_rcButton[i], _ptMouse))
		{
			_curBackTop = i; //BACKTOP_0, BACKTOP_1, BACKTOP_2, BACKTOP_3, BACKTOP_4
		}
	}
	//bot백그라운드
	for (int i = 0; i < 4; ++i)
	{
		if (PtInRect(&_rcButton[10+i], _ptMouse))
		{
			_curBackBot = i; // BACKBOT_0, BACKBOT_1, BACKBOT_2, BACKBOT_3
		}
	}
}

//스테이지 타일입히기
void mapToolScene::setMap()
{
	if (!_isMinimize && PtInRect(&_rcCtrlPanel, _ptMouse))
	{
		return;
	}

	int left = min(_oldMouse.x, _ptMouse.x);
	int top = min(_oldMouse.y, _ptMouse.y);
	int right = max(_oldMouse.x, _ptMouse.x);
	int bottom = max(_oldMouse.y, _ptMouse.y);

	_dragRc = { left + CAM->getX(), top + CAM->getY(), right + CAM->getX(), bottom + CAM->getY() };

	RECT tempRc;
	POINT mouse = { _ptMouse.x + CAM->getX(), _ptMouse.y + CAM->getY() };

	int startX = (_cameraLens.x - WINSIZEX / 2) / TILESIZE - 2;
	int startY = (_cameraLens.y - WINSIZEY / 2) / TILESIZE - 2;
	int endX = (_cameraLens.x + WINSIZEX / 2) / TILESIZE + 2;
	int endY = (_cameraLens.y + WINSIZEY / 2) / TILESIZE + 2;

	if (startX < 0) startX = 0;
	if (startY < 0) startY = 0;
	if (endX >= _tileX) endX = _tileX;
	if (endY >= _tileY) endY = _tileY;

	for (int i = startY; i < endY; ++i)
	{
		for (int j = startX; j < endX; ++j)
		{
			if (_stage != NULL)
			{
				if (_currentTab == CTRL_TERRAINTAB)
				{
					if (IntersectRect(&tempRc, &_dragRc, &_stage[i * _tileX + j].rc))
					{
						_stage[i * _tileX + j].terrain = _currentTile.terrainType;
						_stage[i * _tileX + j].frontBack = _currentTile.frontBack;
						if(_randomTile) _stage[i * _tileX + j].terrainFrameX = RND->getInt(5);
						else _stage[i * _tileX + j].terrainFrameX = _currentTile.frameX;
						_stage[i * _tileX + j].terrainFrameY = _currentTile.frameY;
					}
				}
				if (_currentTab == CTRL_ITEMTAB)
				{
					//TODO : 아이템
				}
				if (_currentTab == CTRL_OBJECTTAB)
				{
					if(PtInRect(&_stage[i * _tileX + j].rc, mouse))
					{
						_stage[i * _tileX + j].object = _currentTile.objectType;
						_stage[i * _tileX + j].objFrameX = _currentTile.frameX;
						_stage[i * _tileX + j].objFrameY = _currentTile.frameY;
					}
				}
				if (_currentTab == CTRL_ENEMYTAB)
				{
					//TODO : spawner마크를 깔아주고 좌표만 저장해서 인게임에 넘겨주자
				}
				if (_currentTab == CTRL_ERASER)
				{
					if (IntersectRect(&tempRc, &_dragRc, &_stage[i * _tileX + j].rc))
					{
						_stage[i * _tileX + j].object = OBJECT_NONE;
						_stage[i * _tileX + j].terrain = TR_NONE;
						_stage[i * _tileX + j].frontBack = FRONT;
						_stage[i * _tileX + j].terrainFrameX = 0;
						_stage[i * _tileX + j].terrainFrameY = 0;
					}
				}
			}
		}
	}
}

void mapToolScene::save()
{
	if (PtInRect(&_rcSave, _ptMouse))
	{
		char temp[128];
		vector<string> vStr;
		sprintf_s(temp, "%d,%d,%d,%d,%d,%d", _tileX, _tileY, _curBackTop, _curBackBot, _cameraLens.x, _cameraLens.y);
		vStr.push_back(temp);

		string name = "Map/stage" + to_string(_saveCount) + ".world";
		TXTDATA->txtSave(name.c_str(), vStr);

		HANDLE file;
		DWORD write;

		name = "Map/stage" + to_string(_saveCount) + ".map";
		
		file = CreateFile(name.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL, NULL);
		WriteFile(file, _stage, sizeof(tagTile) * _tileX * _tileY, &write, NULL);

		CloseHandle(file);
	}
}

void mapToolScene::load()
{
	if (PtInRect(&_rcLoad, _ptMouse))
	{
		string name = "Map/stage" + to_string(_saveCount) + ".world";

		vector<string> vStr;
		vStr = TXTDATA->txtLoad(name.c_str());
		_tileX = atoi(vStr[0].c_str());
		_tileY = atoi(vStr[1].c_str());
		_curBackTop = atoi(vStr[2].c_str());
		_curBackBot = atoi(vStr[3].c_str());
		_cameraLens.x = atoi(vStr[4].c_str());
		_cameraLens.y = atoi(vStr[5].c_str());

		if(_stage != NULL) _stage = NULL;
		_stage = new tagTile[_tileX * _tileY];

		HANDLE file;
		DWORD read;

		name = "Map/stage" + to_string(_saveCount) + ".map";

		file = CreateFile(name.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(file, _stage, sizeof(tagTile) * _tileX * _tileY, &read, NULL);

		CloseHandle(file);

		CAMERAMANAGER->setRange(_tileX * TILESIZE, _tileY * TILESIZE);
		CAMERAMANAGER->setPosition((int)_cameraLens.x, (int)_cameraLens.y);
	}
}

//최소화
void mapToolScene::minimize()
{
	if (PtInRect(&_rcMinimize, _ptMouse))
	{
		_isMinimize = true;
	}

	if (PtInRect(&_rcTaskBar, _ptMouse))
	{
		_isMinimize = false;
	}
}

//패널 위치
void mapToolScene::ctrlPanelUpdate()
{
	_rcCtrlPanel = RectMakeCenter(_ctrlPanelX, _ctrlPanelY, 503, 486);
	_rcSave = RectMakeCenter(_rcCtrlPanel.left + 200, _rcCtrlPanel.top + 35, 134, 35);
	_rcLoad = RectMakeCenter(_rcCtrlPanel.left + 350, _rcCtrlPanel.top + 35, 134, 35);
	_rcMinimize = RectMakeCenter(_rcCtrlPanel.left + 455, _rcCtrlPanel.top + 35, 44, 35);
	_rcWorld = RectMakeCenter(_rcCtrlPanel.left + 57, _rcCtrlPanel.top + 114, 65, 38);
	_rcTile = RectMakeCenter(_rcCtrlPanel.left + 124, _rcCtrlPanel.top + 114, 65, 38);
	_rcItem = RectMakeCenter(_rcCtrlPanel.left + 192, _rcCtrlPanel.top + 114, 65, 38);
	_rcObject = RectMakeCenter(_rcCtrlPanel.left + 259, _rcCtrlPanel.top + 114, 65, 38);
	_rcEnemy = RectMakeCenter(_rcCtrlPanel.left + 327, _rcCtrlPanel.top + 114, 65, 38);
	_rcErase = RectMakeCenter(_rcCtrlPanel.left + 452, _rcCtrlPanel.top + 113, 39, 39);
	for (int i = 0; i < 60; ++i)
	{
		_rcButton[i] = RectMakeCenter(_rcCtrlPanel.left + 35 + 48 * (i % 10), _rcCtrlPanel.top + 171 + 48 * (i / 10), 40, 40);
	}
}

//패널 드래그
void mapToolScene::ctrlPanelMove()
{
	//컨트롤 패널을 클릭하면
	if (PtInRect(&_rcCtrlPanel, _ptMouse))
	{
		//패널무브가 아니면
		if (!_isCtrlPanelMove)
		{
			//마우스 위치랑 패널의 중점 거리를 저장
			_ctrlPanelMove.x = _ctrlPanelX - _ptMouse.x;
			_ctrlPanelMove.y = _ctrlPanelY - _ptMouse.y;
			_isCtrlPanelMove = true;
		}
	}

	if (_isCtrlPanelMove)
	{
		//저장한 거리만큼 보정해서 클릭한 곳을 끌고가게
		_ctrlPanelX = _ptMouse.x + _ctrlPanelMove.x;
		_ctrlPanelY = _ptMouse.y + _ctrlPanelMove.y;
	}
}

//패널 렌더
void mapToolScene::ctrlPanelRender()
{
	_ctrlPanel->render(getMemDC(), _rcCtrlPanel.left, _rcCtrlPanel.top);
	_saveButton->frameRender(getMemDC(), _rcSave.left, _rcSave.top);
	_loadButton->frameRender(getMemDC(), _rcLoad.left, _rcLoad.top);
	_minimizeButton->frameRender(getMemDC(), _rcMinimize.left, _rcMinimize.top);
	_worldButton->frameRender(getMemDC(), _rcWorld.left, _rcWorld.top);
	_tilesButton->frameRender(getMemDC(), _rcTile.left, _rcTile.top);
	_itemButton->frameRender(getMemDC(), _rcItem.left, _rcItem.top);
	_objectButton->frameRender(getMemDC(), _rcObject.left, _rcObject.top);
	_enemyButton->frameRender(getMemDC(), _rcEnemy.left, _rcEnemy.top);
	IMAGEMANAGER->render("빈패드", getMemDC(), _rcCtrlPanel.left + 9, _rcCtrlPanel.top + 9);
	IMAGEMANAGER->frameRender("숫자", getMemDC(), _rcCtrlPanel.left + 10, _rcCtrlPanel.top + 10, _saveCount, 0);
}

//카메라무브
void mapToolScene::cameraMove()
{
	//카메라 스크롤
	if (_cameraLens.y > WINSIZEY/2 && KEYMANAGER->isStayKeyDown('W'))
	{
		_cameraLens.y -= _cameraSpeed;
	}
	if (_cameraLens.y < _tileY * TILESIZE - WINSIZEY/2 && KEYMANAGER->isStayKeyDown('S'))
	{
		_cameraLens.y += _cameraSpeed;
	}
	if (_cameraLens.x > WINSIZEX/2 && KEYMANAGER->isStayKeyDown('A'))
	{
		_cameraLens.x -= _cameraSpeed;
	}
	if (_cameraLens.x < _tileX * TILESIZE - WINSIZEX/2 && KEYMANAGER->isStayKeyDown('D'))
	{
		_cameraLens.x += _cameraSpeed;
	}
}

//탭버튼 하이라이팅 끄기
void mapToolScene::tabButtonSet()
{
	_worldButton->setFrameX(0);
	_tilesButton->setFrameX(0);
	_itemButton->setFrameX(0);
	_objectButton->setFrameX(0);
	_enemyButton->setFrameX(0);
}

//샘플타일 렌더
void mapToolScene::sampleRender(image* sample, int X, int Y)
{
	sample->frameRender(getMemDC(), _rcButton[Y * 10 + X].left + 2, _rcButton[Y * 10 + X].top + 2, X, Y);
}

//타일탭 변경
void mapToolScene::tabChange()
{
	if (PtInRect(&_rcWorld, _ptMouse))
	{
		_currentTab = CTRL_SIZINGTAB;
		tabButtonSet();
		_worldButton->setFrameX(2);
	}
	if (PtInRect(&_rcTile, _ptMouse))
	{
		_currentTab = CTRL_TERRAINTAB;
		tabButtonSet();
		_tilesButton->setFrameX(2);
	}
	if (PtInRect(&_rcItem, _ptMouse))
	{
		_currentTab = CTRL_ITEMTAB;
		tabButtonSet();
		_itemButton->setFrameX(2);
	}
	if (PtInRect(&_rcObject, _ptMouse))
	{
		_currentTab = CTRL_OBJECTTAB;
		tabButtonSet();
		_objectButton->setFrameX(2);
	}
	if (PtInRect(&_rcEnemy, _ptMouse))
	{
		_currentTab = CTRL_ENEMYTAB;
		tabButtonSet();
		_enemyButton->setFrameX(2);
	}
	if (PtInRect(&_rcErase, _ptMouse))
	{
		_currentTab = CTRL_ERASER;
		tabButtonSet();
	}
}

//curTab에 따라 샘플타일 변경
void mapToolScene::tabTileSetup()
{
	//맵사이즈탭
	if (_currentTab == CTRL_SIZINGTAB)
	{
		//맵사이즈 설정
		setupWorld();
	}
	//지형탭
	else if (_currentTab == CTRL_TERRAINTAB)
	{
		if (PtInRect(&_rcButton[0], _ptMouse))
		{
			_currentTile.terrainType = TR_BRICK;
			_currentTile.frameX = RND->getInt(5);
			_currentTile.frameY = 0;
		}
		if (PtInRect(&_rcButton[1], _ptMouse))
		{
			_currentTile.terrainType = TR_COBBLEBRICK;
			_currentTile.frameX = RND->getInt(5);
			_currentTile.frameY = 0;
		}
		if (PtInRect(&_rcButton[2], _ptMouse))
		{
			_currentTile.terrainType = TR_CONCRETE;
			_currentTile.frameX = RND->getInt(5);
			_currentTile.frameY = 0;
		}
		if (PtInRect(&_rcButton[3], _ptMouse))
		{
			_currentTile.terrainType = TR_DARKWOOD;
			_currentTile.frameX = RND->getInt(5);
			_currentTile.frameY = 0;
		}
		if (PtInRect(&_rcButton[4], _ptMouse))
		{
			_currentTile.terrainType = TR_DIRT;
			_currentTile.frameX = RND->getInt(5);
			_currentTile.frameY = 0;
		}
		if (PtInRect(&_rcButton[5], _ptMouse))
		{
			_currentTile.terrainType = TR_FULLWOOD1;
			_currentTile.frameX = RND->getInt(5);
			_currentTile.frameY = 0;
		}
		if (PtInRect(&_rcButton[6], _ptMouse))
		{
			_currentTile.terrainType = TR_FULLWOOD2;
			_currentTile.frameX = RND->getInt(5);
			_currentTile.frameY = 0;
		}
		if (PtInRect(&_rcButton[7], _ptMouse))
		{
			_currentTile.terrainType = TR_LOG;
			_currentTile.frameX = RND->getInt(5);
			_currentTile.frameY = 0;
		}
		if (PtInRect(&_rcButton[8], _ptMouse))
		{
			_currentTile.terrainType = TR_PETALBLOCK;
			_currentTile.frameX = RND->getInt(5);
			_currentTile.frameY = 0;
		}
		if (PtInRect(&_rcButton[9], _ptMouse))
		{
			_currentTile.terrainType = TR_ROOF;
			_currentTile.frameX = RND->getInt(5);
			_currentTile.frameY = 0;
		}
		//TODO : 타일추가
	}
	//아이템탭
	else if (_currentTab == CTRL_ITEMTAB)
	{
		if (PtInRect(&_rcButton[0], _ptMouse))
		{
			_currentTile.itemType = ITEM_SPACESWORD;
		}
	}
	//오브젝트탭
	else if (_currentTab == CTRL_OBJECTTAB)
	{
		//배경이미지 선택
		setBackImage();

		//오브젝트 선택
		if (PtInRect(&_rcButton[20], _ptMouse))
		{
			_currentTile.objectType = OBJECT_WOODENCRATE1;
			_currentTile.frameX = RND->getInt(2);
			_currentTile.frameY = 0;
		}

		if (PtInRect(&_rcButton[30], _ptMouse))
		{
			_currentTile.objectType = OBJECT_TREELIGHTS;
			_currentTile.frameX = RND->getInt(2);
			_currentTile.frameY = 0;
		}
	}
	//에너미탭
	else if (_currentTab == CTRL_ENEMYTAB)
	{

	}
	else if (_currentTab == CTRL_ERASER)
	{
		_currentTile.terrainType = TR_NONE;
		_currentTile.objectType = OBJECT_NONE;
		_currentTile.frameX = 0;
		_currentTile.frameY = 0;
	}
}

//타일 색상바꾸기
void mapToolScene::tileColorChange()
{
	//휠로 색상바꾸기
	if (_ptWheel > 0)
	{
		if (_currentTile.frameY < 8) ++_currentTile.frameY;
		_ptWheel = 0;
	}
	else if (_ptWheel < 0)
	{
		if (_currentTile.frameY > 0) --_currentTile.frameY;
		_ptWheel = 0;
	}
}

//스테이지 랜더
void mapToolScene::stageRender()
{
	if (_stage != NULL)
	{
		//백그라운드 렌더
		RECT temp = { 0, -CAM->getY(), WINSIZEX, WINSIZEY - CAM->getY() }; //화면좌표인데 y는 바뀌면 안되니까 절대좌표로 바꿔버렸다
		_backGroundTop[_curBackTop]->loopRender(getMemDC(), &temp, _cameraLens.x, 0);
		temp = { -CAM->getX(), WINSIZEY - CAM->getY(),TILESIZE * _tileX - CAM->getX() + 200, TILESIZE * _tileY - CAM->getY() };
		_backGroundBot[_curBackBot]->loopRender(getMemDC(), &temp, 0, 0);

		//스테이지 타일
		int startX = (_cameraLens.x - WINSIZEX/2) / TILESIZE - 2;
		int startY = (_cameraLens.y - WINSIZEY/2) / TILESIZE - 2;
		int endX = (_cameraLens.x + WINSIZEX/2) / TILESIZE + 2;
		int endY = (_cameraLens.y + WINSIZEY/2) / TILESIZE + 2;

		/*startX = (CAM->getX()) / TILESIZE - 2;
		startY = (CAM->getY()) / TILESIZE - 2;
		endX = (CAM->getX() + WINSIZEX) / TILESIZE + 2;
		endY = (CAM->getY() + WINSIZEY) / TILESIZE + 2;*/

		//스테이지 렌더
		if (startX < 0) startX = 0;
		if (startY < 0) startY = 0;
		if (endX >= _tileX) endX = _tileX;
		if (endY >= _tileY) endY = _tileY;

		for (int i = startY; i < endY; ++i)
		{
			for (int j = startX; j < endX; ++j)
			{
				if (_stage[i*_tileX + j].terrain != TR_NONE)
				{
					_tiles[_stage[i*_tileX + j].terrain + _stage[i*_tileX + j].frontBack]->frameRender(getMemDC(),
						_stage[i*_tileX + j].rc.left - 10 - CAM->getX(),
						_stage[i*_tileX + j].rc.top - 10 - CAM->getY(),
						_stage[i*_tileX + j].terrainFrameX,
						_stage[i*_tileX + j].terrainFrameY);
				}
			}
		}

		for (int i = startY; i < endY; ++i)
		{
			for (int j = startX; j < endX; ++j)
			{
				image* curRender = NULL;
				switch (_stage[i * _tileX + j].object)
				{
				case OBJECT_WOODENCRATE1:
					curRender = _woodencrate1;
					break;
				case OBJECT_TREELIGHTS:
					curRender = _treelights;
					break;
					//TODO : 오브젝트 렌더
				}
				if (curRender != NULL)
					curRender->frameRender(getMemDC(),
						_stage[i*_tileX + j].rc.left - 10 - CAM->getX(),
						_stage[i*_tileX + j].rc.top - 10 - CAM->getY(),
						_stage[i*_tileX + j].objFrameX,
						_stage[i*_tileX + j].objFrameY);
			}
		}

		if (KEYMANAGER->isToggleKey('1'))
		{
			for (int i = startY; i < endY; ++i)
			{
				for (int j = startX; j < endX; ++j)
				{
					Rectangle(getMemDC(), _stage[i*_tileX + j].rc.left - CAM->getX(), _stage[i*_tileX + j].rc.top - CAM->getY(),
						_stage[i*_tileX + j].rc.right - CAM->getX(), _stage[i*_tileX + j].rc.bottom - CAM->getY());
				}
			}
		}
	}
}
//선택한 타일 마우스에 렌더
void mapToolScene::curtileMouseRender()
{
	if (_currentTab == CTRL_TERRAINTAB)
	{
		if(_currentTile.terrainType != TR_NONE)
			_tiles[_currentTile.terrainType + _currentTile.frontBack]->frameRender(getMemDC(), _ptMouse.x + 10, _ptMouse.y + 10, _currentTile.frameX, _currentTile.frameY);
	}
	else if (_currentTab == CTRL_ITEMTAB)
	{
		if (_currentTile.itemType != ITEM_NONE)
		{
			image* curRender = NULL;
			switch (_currentTile.itemType)
			{
			case ITEM_SPACESWORD:
				curRender = _item;
				break;
			}
			if (curRender != NULL)
				curRender->render(getMemDC(), _ptMouse.x + 10, _ptMouse.y + 10);
		}
	}
	else if (_currentTab == CTRL_OBJECTTAB)
	{
		if (_currentTile.objectType != OBJECT_NONE)
		{
			image* curRender = NULL;
			switch (_currentTile.objectType)
			{
			case OBJECT_WOODENCRATE1:
				curRender = _woodencrate1;
				break;
			case OBJECT_TREELIGHTS:
				curRender = _treelights;
				break;
			}
			if (curRender != NULL)
				curRender->frameRender(getMemDC(), _ptMouse.x + 10, _ptMouse.y + 10, _currentTile.frameX, _currentTile.frameY);
		}
	}
}

//샘플아이콘
void mapToolScene::curTabIconRender()
{
	if (_currentTab == CTRL_SIZINGTAB)
	{
		IMAGEMANAGER->render("큰월드", getMemDC(), _rcButton[0].left + 2, _rcButton[0].top + 2);
		IMAGEMANAGER->render("중간월드", getMemDC(), _rcButton[1].left + 2, _rcButton[1].top + 2);
		IMAGEMANAGER->render("작은월드", getMemDC(), _rcButton[2].left + 2, _rcButton[2].top + 2);
		IMAGEMANAGER->render("월드삭제", getMemDC(), _rcButton[3].left + 2, _rcButton[3].top + 2);
	}
	else if (_currentTab == CTRL_TERRAINTAB)
	{
		for (int i = 0; i < 6; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				sampleRender(_tileIcon, j, i);
			}
		}
	}
	else if (_currentTab == CTRL_ITEMTAB)
	{
		for (int i = 0; i < 6; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				sampleRender(_itemIcon, j, i);
			}
		}
	}
	else if (_currentTab == CTRL_OBJECTTAB)
	{
		for (int i = 0; i < 6; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				sampleRender(_objectIcon, j, i);
			}
		}
	}
	else if (_currentTab == CTRL_ENEMYTAB)
	{

	}
}