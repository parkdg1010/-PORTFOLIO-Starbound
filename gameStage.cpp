#include "stdafx.h"
#include "gameStage.h"
#include "player.h"

HRESULT gameStage::init()
{
	initImage();
	_stageNum = 1;

	_treeLightsCount = _treeLightsIdx = _ornatetorchCount = _ornatetorchIdx = 0;

	return S_OK;
}

void gameStage::update()
{
	_treeLightsCount = (_treeLightsCount + 1) % 15;
	if (_treeLightsCount == 0)	_treeLightsIdx = RND->getInt(2); //_treeLights->setFrameX(RND->getInt(2));
	_ornatetorchCount = (_ornatetorchCount + 1) % 22;
	if (_ornatetorchCount == 0) _ornatetorchIdx = RND->getInt(4); //_ornatetorch->setFrameX(RND->getInt(4));
}

void gameStage::render()
{
	stageRender();
	if(_isDebug)
		_pixelBuffer->render(getMemDC(), CAM->getSX(), CAM->getSY(), CAM->getSourX(), CAM->getSourY(), WINSIZEX, WINSIZEY); 
		// ȭ���� sx,sy ��ǥ���� �׸��� �����ؼ� �ҽ��� sourX, sourY������ WINSIZEX, WINSIZEY ������ŭ �׸�
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

	loadStageBuffer();

	CAMERAMANAGER->setRange(_tileX * TILESIZE, _tileY * TILESIZE);
	CAMERAMANAGER->setPosition((int)_player->getX(), (int)_player->getY());
}

void gameStage::loadStageBuffer()
{
	_stageBuffer = IMAGEMANAGER->addImage("STAGE_BUFFER", _tileX * TILESIZE, _tileY * TILESIZE, true, MAGENTA);
	_pixelBuffer = IMAGEMANAGER->addImage("PIXEL_BUFFER", _tileX * TILESIZE, _tileY * TILESIZE, true, MAGENTA);

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
				_stage[i].rc.left - 10 - CAM->getX(),
				_stage[i].rc.top - 10 - CAM->getY(),
				_stage[i].terrainFrameX,
				_stage[i].terrainFrameY);
			if (_stage[i].frontBack == FRONT)
			{
				_pixelTiles->frameRender(_pixelBuffer->getMemDC(), _stage[i].rc.left - 10 - CAM->getX(),
					_stage[i].rc.top - 10 - CAM->getY(), 0, 0);
			}
		}
		//���� �ȼ����۸����
		if (_stage[i].object == OBJECT_FF_WOOD)
		{
			//����� �밢������
			if (_stage[i].objFrameX)
			{
				_pixelTiles->frameRender(_pixelBuffer->getMemDC(), _stage[i].rc.left - 10 - CAM->getX(),
					_stage[i].rc.top - 10 - CAM->getY(), 2, 0);
			}
			//������ ���ڷ�
			else
			{
				_pixelTiles->frameRender(_pixelBuffer->getMemDC(), _stage[i].rc.left - 10 - CAM->getX(),
					_stage[i].rc.top - 10 - CAM->getY(), 1, 0);
			}
		}
	}
}

void gameStage::initImage()
{
	//TODO : Ÿ���߰�
	//Ÿ��
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

	//����
	_flatform = IMAGEMANAGER->findImage("FLATFORM_WOOD");

	_pixelTiles = IMAGEMANAGER->findImage("TILE_PIXEL");

	//������Ʈ
	_woodencrate1 = IMAGEMANAGER->findImage("��������1");
	_treeLights = IMAGEMANAGER->findImage("Ʈ������");
	_ornatetorch = IMAGEMANAGER->findImage("��ĵ�");

	//������
	_item = IMAGEMANAGER->findImage("���ְ�");

	//���
	_backGroundTop[0] = IMAGEMANAGER->findImage("���Top0");
	_backGroundTop[1] = IMAGEMANAGER->findImage("���Top1");
	_backGroundTop[2] = IMAGEMANAGER->findImage("���Top2");
	_backGroundTop[3] = IMAGEMANAGER->findImage("���Top3");
	_backGroundTop[4] = IMAGEMANAGER->findImage("���Top4");

	_backGroundBot[0] = IMAGEMANAGER->findImage("���Bot0");
	_backGroundBot[1] = IMAGEMANAGER->findImage("���Bot1");
	_backGroundBot[2] = IMAGEMANAGER->findImage("���Bot2");
	_backGroundBot[3] = IMAGEMANAGER->findImage("���Bot3");
}

void gameStage::stageRender()
{
	if (_stage != NULL)
	{
		//��׶��� ����
		RECT temp = { 0, -CAM->getY(), WINSIZEX, WINSIZEY - CAM->getY() }; //ȭ����ǥ�ε� y�� �ٲ�� �ȵǴϱ� ������ǥ�� �ٲ���ȴ�
		_backGroundTop[_curBackTop]->loopRender(getMemDC(), &temp, (int)_player->getX(), 0);
		temp = { -CAM->getX(), WINSIZEY - CAM->getY(),TILESIZE * _tileX - CAM->getX() + 200, TILESIZE * _tileY - CAM->getY() };
		_backGroundBot[_curBackBot]->loopRender(getMemDC(), &temp, 0, 0);

		//�������� Ÿ��
		//int startX = (_player->getX() - WINSIZEX / 2) / TILESIZE - 2;
		//int startY = (_player->getY() - WINSIZEY / 2) / TILESIZE - 2;
		//int endX = (_player->getX() + WINSIZEX / 2) / TILESIZE + 2;
		//int endY = (_player->getY() + WINSIZEY / 2) / TILESIZE + 2;

		//�������� ����
		_stageBuffer->render(getMemDC(), CAM->getSX(), CAM->getSY(), CAM->getSourX(), CAM->getSourY(), WINSIZEX, WINSIZEY); //ī�޶� ����ũ�� �̹����� CAM->getSX(), CAM->getSY()

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
					//TODO : ������Ʈ ����
					//CHECK : ������ �ϴ°� ���ٰ����� �� ���� ����� �����غ���
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

