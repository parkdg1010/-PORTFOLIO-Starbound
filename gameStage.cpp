#include "stdafx.h"
#include "gameStage.h"
#include "player.h"

HRESULT gameStage::init()
{
	initImage();
	_stageNum = 1;

	return S_OK;
}

void gameStage::update()
{
}

void gameStage::render()
{
	stageRender();
}

void gameStage::release()
{
}

void gameStage::saveStage()
{
	char temp[128];
	vector<string> vStr;
	sprintf_s(temp, "%d,%d,%d,%d,%d,%d", _tileX, _tileY, _curBackTop, _curBackBot, (int)(_player->getX()), (int)(_player->getY()));
	vStr.push_back(temp);
	TXTDATA->txtSave("Map/stage.world", vStr);

	HANDLE file;
	DWORD write;

	file = CreateFile("Map/stage.map", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, _stage, sizeof(tagTile) * _tileX * _tileY, &write, NULL);

	CloseHandle(file);
}

void gameStage::loadStage()
{
	string name = "Map/stage" + to_string(_stageNum) + ".world";

	vector<string> vStr;
	vStr = TXTDATA->txtLoad(name.c_str());
	_tileX = atoi(vStr[0].c_str());
	_tileY = atoi(vStr[1].c_str());
	_curBackTop = atoi(vStr[2].c_str());
	_curBackBot = atoi(vStr[3].c_str());

	if (_stage != NULL) _stage = NULL;
	_stage = new tagTile[_tileX * _tileY];

	HANDLE file;
	DWORD read;

	name = "Map/stage" + to_string(_stageNum) + ".map";

	file = CreateFile(name.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _stage, sizeof(tagTile) * _tileX * _tileY, &read, NULL);

	CloseHandle(file);

	CAMERAMANAGER->setRange(_tileX * TILESIZE, _tileY * TILESIZE);
	CAMERAMANAGER->setPosition((int)_player->getX(), (int)_player->getY());
}

void gameStage::initImage()
{
	//TODO : 타일추가
	//타일
	_brick[FRONT] = IMAGEMANAGER->findImage("TILE_BRICK");
	_cobbleBrick[FRONT] = IMAGEMANAGER->findImage("TILE_COBBLEBRICK");
	_concrete[FRONT] = IMAGEMANAGER->findImage("TILE_CONCRETE");
	_darkwood[FRONT] = IMAGEMANAGER->findImage("TILE_DARKWOOD");
	_dirt[FRONT] = IMAGEMANAGER->findImage("TILE_DIRT");
	_fullwood1[FRONT] = IMAGEMANAGER->findImage("TILE_FULLWOOD1");
	_fullwood2[FRONT] = IMAGEMANAGER->findImage("TILE_FULLWOOD2");
	_log[FRONT] = IMAGEMANAGER->findImage("TILE_LOG");
	_petalblock[FRONT] = IMAGEMANAGER->findImage("TILE_PETALBLOCK");
	_rooftile[FRONT] = IMAGEMANAGER->findImage("TILE_ROOF");

	_brick[BACK] = IMAGEMANAGER->findImage("BACKTILE_BRICK");
	_cobbleBrick[BACK] = IMAGEMANAGER->findImage("BACKTILE_COBBLEBRICK");
	_concrete[BACK] = IMAGEMANAGER->findImage("BACKTILE_CONCRETE");
	_darkwood[BACK] = IMAGEMANAGER->findImage("BACKTILE_DARKWOOD");
	_dirt[BACK] = IMAGEMANAGER->findImage("BACKTILE_DIRT");
	_fullwood1[BACK] = IMAGEMANAGER->findImage("BACKTILE_FULLWOOD1");
	_fullwood2[BACK] = IMAGEMANAGER->findImage("BACKTILE_FULLWOOD2");
	_log[BACK] = IMAGEMANAGER->findImage("BACKTILE_LOG");
	_petalblock[BACK] = IMAGEMANAGER->findImage("BACKTILE_PETALBLOCK");
	_rooftile[BACK] = IMAGEMANAGER->findImage("BACKTILE_ROOF");

	//오브젝트
	_woodencrate1 = IMAGEMANAGER->findImage("나무상자1");

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

void gameStage::stageRender()
{
	if (_stage != NULL)
	{
		//백그라운드 렌더
		RECT temp = { 0, -CAM->getY(), WINSIZEX, WINSIZEY - CAM->getY() }; //화면좌표인데 y는 바뀌면 안되니까 절대좌표로 바꿔버렸다
		_backGroundTop[_curBackTop]->loopRender(getMemDC(), &temp, (int)_player->getX(), 0);
		temp = { -CAM->getX(), WINSIZEY - CAM->getY(),TILESIZE * _tileX - CAM->getX() + 200, TILESIZE * _tileY - CAM->getY() };
		_backGroundBot[_curBackBot]->loopRender(getMemDC(), &temp, 0, 0);

		//스테이지 타일
		//int startX = (_player->getX() - WINSIZEX / 2) / TILESIZE - 2;
		//int startY = (_player->getY() - WINSIZEY / 2) / TILESIZE - 2;
		//int endX = (_player->getX() + WINSIZEX / 2) / TILESIZE + 2;
		//int endY = (_player->getY() + WINSIZEY / 2) / TILESIZE + 2;

		int startX = (CAM->getX()) / TILESIZE - 2;
		int startY = (CAM->getY()) / TILESIZE - 2;
		int endX = (CAM->getX() + WINSIZEX) / TILESIZE + 2;
		int endY = (CAM->getY() + WINSIZEY) / TILESIZE + 2;

		if (startX < 0) startX = 0;
		if (startY < 0) startY = 0;
		if (endX >= _tileX) endX = _tileX;
		if (endY >= _tileY) endY = _tileY;

		for (int i = startY; i < endY; ++i)
		{
			for (int j = startX; j < endX; ++j)
			{
				image* curRender = NULL;
				//TODO : 타일추가
				switch (_stage[i*_tileX + j].terrain)
				{
				case TR_BRICK:
					curRender = _brick[_stage[i*_tileX + j].frontBack];
					break;
				case TR_COBBLEBRICK:
					curRender = _cobbleBrick[_stage[i*_tileX + j].frontBack];
					break;
				case TR_CONCRETE:
					curRender = _concrete[_stage[i*_tileX + j].frontBack];
					break;
				case TR_DARKWOOD:
					curRender = _darkwood[_stage[i*_tileX + j].frontBack];
					break;
				case TR_DIRT:
					curRender = _dirt[_stage[i*_tileX + j].frontBack];
					break;
				case TR_FULLWOOD1:
					curRender = _fullwood1[_stage[i*_tileX + j].frontBack];
					break;
				case TR_FULLWOOD2:
					curRender = _fullwood2[_stage[i*_tileX + j].frontBack];
					break;
				case TR_LOG:
					curRender = _log[_stage[i*_tileX + j].frontBack];
					break;
				case TR_PETALBLOCK:
					curRender = _petalblock[_stage[i*_tileX + j].frontBack];
					break;
				case TR_ROOF:
					curRender = _rooftile[_stage[i*_tileX + j].frontBack];
					break;
				}
				if (curRender != NULL)
					curRender->frameRender(getMemDC(),
						_stage[i*_tileX + j].rc.left - 10 - CAM->getX(),
						_stage[i*_tileX + j].rc.top - 10 - CAM->getY(),
						_stage[i*_tileX + j].terrainFrameX,
						_stage[i*_tileX + j].terrainFrameY);
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
			HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
			HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);
			for (int i = startY; i < endY; ++i)
			{
				for (int j = startX; j < endX; ++j)
				{
					Rectangle(getMemDC(), _stage[i*_tileX + j].rc.left - CAM->getX(), _stage[i*_tileX + j].rc.top - CAM->getY(),
						_stage[i*_tileX + j].rc.right - CAM->getX(), _stage[i*_tileX + j].rc.bottom - CAM->getY());
				}
			}
			SelectObject(getMemDC(), oldBrush);
		}
	}
}

