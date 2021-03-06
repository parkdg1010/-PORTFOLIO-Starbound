#include "stdafx.h"
#include "gameStage.h"
#include "player.h"
#include "enemyManager.h"

HRESULT gameStage::init()
{
	initImage();

	if (_enemyFac == NULL)
		_enemyFac = new enemyFactory;

	_treeLightsCount = _treeLightsIdx = _ornatetorchCount = _ornatetorchIdx = 0;

	return S_OK;
}

void gameStage::update()
{
	DELAYCOUNT(_treeLightsCount, 15);
	if (_treeLightsCount == 0)	_treeLightsIdx = RND->getInt(2);
	DELAYCOUNT(_ornatetorchCount, 22);
	if (_ornatetorchCount == 0) _ornatetorchIdx = RND->getInt(4);
}

void gameStage::render()
{
	//이유는 모르겠으나 이 브러시가 픽셀버퍼를 건드려서 충돌이 안되는 버그가 발생했다.
	/*HBRUSH myBrush = CreateSolidBrush(RGB(135, 206, 235));
	RECT rc = { 0,0,WINSIZEX,WINSIZEY };
	FillRect(getMemDC(), &rc, myBrush);*/

	stageRender();
	stageObjectFrameRender();

	if(_isDebug)
		_pixelBuffer->render(getMemDC(), CAM->getSX(), CAM->getSY(), CAM->getSourX(), CAM->getSourY(), WINSIZEX, WINSIZEY);
		// 화면의 sx,sy 좌표부터 그리기 시작해서 소스의 sourX, sourY점부터 WINSIZEX, WINSIZEY 범위만큼 그림
}

void gameStage::release()
{
	_stageBuffer->release();
	SAFE_DELETE(_stageBuffer);

	_pixelBuffer->release();
	SAFE_DELETE(_pixelBuffer);

	SAFE_DELETE(_enemyFac);
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

	loadStageBuffer();

	switch (_stageNum)
	{
	case 1:	
		SOUNDMANAGER->playBgm("집", _soundVolume);
		break;
	case 2:
		SOUNDMANAGER->playBgm("던전", _soundVolume);
		break;
	}
}

void gameStage::loadStageBuffer()
{
	_stageBuffer = new image;
	_stageBuffer->init(_tileX * TILESIZE, _tileY * TILESIZE, true, MAGENTA);

	_pixelBuffer = new image;
	_pixelBuffer->init(_tileX * TILESIZE, _tileY * TILESIZE, true, MAGENTA);

	HBRUSH myBrush = CreateSolidBrush(MAGENTA);
	HBRUSH oldBrush = (HBRUSH)SelectObject(_stageBuffer->getMemDC(), myBrush);
	HBRUSH oldBrush2 = (HBRUSH)SelectObject(_pixelBuffer->getMemDC(), myBrush);

	Rectangle(_stageBuffer->getMemDC(), -10, -10, _tileX * TILESIZE, _tileY * TILESIZE);
	Rectangle(_pixelBuffer->getMemDC(), -10, -10, _tileX * TILESIZE, _tileY * TILESIZE);

	SelectObject(_stageBuffer->getMemDC(), oldBrush);
	SelectObject(_pixelBuffer->getMemDC(), oldBrush2);

	DeleteObject(myBrush);
	DeleteObject(oldBrush);
	DeleteObject(oldBrush2);

	for (int i = 0; i < _tileX * _tileY; ++i)
	{
		if (_stage[i].terrain != TR_NONE)
		{
			_tiles[_stage[i].terrain + _stage[i].frontBack]->frameRender(_stageBuffer->getMemDC(),
				_stage[i].rc.left - 10,
				_stage[i].rc.top - 10,
				_stage[i].terrainFrameX,
				_stage[i].terrainFrameY);
			if (_stage[i].frontBack == FRONT)
			{
				_pixelTiles->frameRender(_pixelBuffer->getMemDC(), _stage[i].rc.left - 10,
					_stage[i].rc.top - 10, 0, 0);
			}
		}
		//발판 픽셀버퍼만들기
		if (_stage[i].object == OBJECT_FF_WOOD)
		{
			//계단은 대각선으로
			if (_stage[i].objFrameX == 1 || _stage[i].objFrameX == 2) // 1,2번은 픽셀2번 3,4번은 픽셀3번
			{
				_pixelTiles->frameRender(_pixelBuffer->getMemDC(), _stage[i].rc.left - 10,
					_stage[i].rc.top - 10, 2, 0);
			}
			else if (_stage[i].objFrameX == 3 || _stage[i].objFrameX == 4)
			{
				_pixelTiles->frameRender(_pixelBuffer->getMemDC(), _stage[i].rc.left - 10,
					_stage[i].rc.top - 10, 3, 0);
			}
			//발판은 일자로
			else
			{
				_pixelTiles->frameRender(_pixelBuffer->getMemDC(), _stage[i].rc.left - 10,
					_stage[i].rc.top - 10, 1, 0);
			}
		}

		//액터 타입,위치 넘겨주기
		if (_stage[i].actor != ACTOR_NONE)
		{
			POINTf pos;
			if (_stage[i].actor == ACTOR_ENEMY)
			{
				//타일사이즈 절반씩 더해서 중앙맞춤
				pos = { i % _tileX * TILESIZE + TILESIZE * 0.5f, i / _tileX * TILESIZE + TILESIZE * 0.5f };
				enemy* temp = _enemyFac->createEnemy(_stage[i].enemy, pos);
				_enemyManager->addEnemy(temp);
			}
			else if (_stage[i].actor == ACTOR_NPC)
			{

			}
		}
	}

	SAVEDATA->setTiles(_stage);
	SAVEDATA->setTileXY(_tileX, _tileY);
	SAVEDATA->setStageBuffer(_stageBuffer);
}

void gameStage::initImage()
{
	//TODO : 타일추가
	//타일
	image* tileType;
	vector<string> keyname = { "TILE_BRICK","BACKTILE_BRICK", "TILE_COBBLEBRICK", "BACKTILE_COBBLEBRICK",
		"TILE_CONCRETE", "BACKTILE_CONCRETE", "TILE_DARKWOOD", "BACKTILE_DARKWOOD", "TILE_DIRT",
		"BACKTILE_DIRT", "TILE_FULLWOOD1", "BACKTILE_FULLWOOD1", "TILE_FULLWOOD2", "BACKTILE_FULLWOOD2",
		"TILE_LOG", "BACKTILE_LOG", "TILE_PETALBLOCK", "BACKTILE_PETALBLOCK", "TILE_ROOF", "BACKTILE_ROOF" };
	for (int i = 0; i < keyname.size(); ++i)
	{
		tileType = IMAGEMANAGER->findImage(keyname[i]);
		_tiles.push_back(tileType);
	}

	//발판
	_flatform = IMAGEMANAGER->findImage("FLATFORM_WOOD");

	_pixelTiles = IMAGEMANAGER->findImage("TILE_PIXEL");

	//오브젝트
	_woodencrate1 = IMAGEMANAGER->findImage("나무상자1");
	_treeLights = IMAGEMANAGER->findImage("트리전구");
	_ornatetorch = IMAGEMANAGER->findImage("장식등");

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

		//스테이지 랜더
		_stageBuffer->render(getMemDC(), CAM->getSX(), CAM->getSY(), CAM->getSourX(), CAM->getSourY(), WINSIZEX, WINSIZEY); //카메라 쉐이크할 이미지에 CAM->getSX(), CAM->getSY()
	}
}

void gameStage::stageObjectFrameRender()
{
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
			switch (_stage[i * _tileX + j].object)
			{
			case OBJECT_WOODENCRATE1:
				curRender = _woodencrate1;
				break;
			case OBJECT_TREELIGHTS:
				_treeLights->frameRender(getMemDC(),
					_stage[i*_tileX + j].rc.left - 10 - CAM->getX(),
					_stage[i*_tileX + j].rc.top - 10 - CAM->getY(), _treeLightsIdx, _stage[i*_tileX + j].objFrameY);
				break;
			case OBJECT_ORNATETORCH:
				_ornatetorch->frameRender(getMemDC(),
					_stage[i*_tileX + j].rc.left - 10 - CAM->getX(),
					_stage[i*_tileX + j].rc.top - 10 - CAM->getY(), _ornatetorchIdx, _stage[i*_tileX + j].objFrameY);
				break;
			case OBJECT_FF_WOOD:
				curRender = _flatform;
				break;
				//TODO : 오브젝트 렌더
				//CHECK : 일일이 하는건 에바같은데 더 나은 방법을 생각해보자
			}
			if (curRender != NULL)
				curRender->frameRender(getMemDC(),
					_stage[i*_tileX + j].rc.left - 10 - CAM->getX(),
					_stage[i*_tileX + j].rc.top - 10 - CAM->getY(),
					_stage[i*_tileX + j].objFrameX,
					_stage[i*_tileX + j].objFrameY);
		}
	}
}

