#include "stdafx.h"
#include "spaceShipScene.h"

HRESULT spaceShipScene::init()
{
	_ship = IMAGEMANAGER->findImage("우주선");
	_shipPixel = IMAGEMANAGER->findImage("우주선픽셀");
	_background = IMAGEMANAGER->findImage("우주선배경");
	_teleporter = IMAGEMANAGER->findImage("텔레포터");

	_offsetX = 0;

	_player = SAVEDATA->getPlayer();
	_player->setGravityAccel(0.17f);
	_player->linkMapPixel(_shipPixel);
	_player->init();

	CAMERAMANAGER->init();
	CAMERAMANAGER->setRange(_ship->getWidth(), _ship->getHeight());
	CAMERAMANAGER->setPosition((int)_player->getX(), (int)_player->getY());

	return S_OK;
}

void spaceShipScene::update()
{
	_player->update();
	CAM->videoShooting((int)_player->getX(), (int)_player->getY());
	_offsetX += 2;
}

void spaceShipScene::render()
{
	//TODO : 배경루프렌더 하나 더하기
	RECT back = { 0,0,WINSIZEX, WINSIZEY };
	_background->loopRender(getMemDC(), &back, _offsetX, 0);
	_ship->render(getMemDC(), CAM->getSX(), CAM->getSY(), CAM->getSourX(), CAM->getSourY(), WINSIZEX, WINSIZEY);
	_teleporter->render(getMemDC(), 2568 - CAM->getX(), 720 - CAM->getY());

	_player->render();

	if (_isDebug)
	{
		_shipPixel->render(getMemDC(), CAM->getSX(), CAM->getSY(), CAM->getSourX(), CAM->getSourY(), WINSIZEX, WINSIZEY);
	}
}

void spaceShipScene::release()
{
	SAVEDATA->setPlayer(_player);
}
