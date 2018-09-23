#include "stdafx.h"
#include "spaceShipScene.h"

HRESULT spaceShipScene::init()
{
	_ship = IMAGEMANAGER->findImage("���ּ�");
	_shipPixel = IMAGEMANAGER->findImage("���ּ��ȼ�");
	_background = IMAGEMANAGER->findImage("���ּ����");
	_teleporter = IMAGEMANAGER->findImage("�ڷ�����");

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
	//TODO : ���������� �ϳ� ���ϱ�
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
