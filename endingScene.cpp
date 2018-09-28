#include "stdafx.h"
#include "endingScene.h"

HRESULT endingScene::init()
{
	//����
	IMAGEMANAGER->addFrameImage("����", "Texture/ending/ending_1280x4320_1x6.bmp", 1280, 4320, 1, 6);
	IMAGEMANAGER->addImage("������ũ��", "Texture/ending/endingScreen.bmp", 1280, 720);
	_alpha = 0;

	SOUNDMANAGER->stop("����");

	SAFE_DELETE(cursor);
	
	return S_OK;
}

void endingScene::update()
{
	if (_index == 3)
	{
		if (!SOUNDMANAGER->isPlaySound("����"))
			SOUNDMANAGER->playBgm("����", _soundVolume);
	}
}

void endingScene::render()
{
	if (_alpha < 255)
		_alpha += 1;
	DELAYCOUNT(_count, 200);
	if (_count == 0)
	{
		++_index;
		if(_alpha < 255)
			_alpha = 0;
	}
	if (_index > IMAGEMANAGER->findImage("����")->getMaxFrameY())
	{
		_index = IMAGEMANAGER->findImage("����")->getMaxFrameY();
		_alpha = 255;
	}
	IMAGEMANAGER->render("������ũ��", getMemDC(), 0, 0);
	IMAGEMANAGER->alphaFrameRender("����", getMemDC(), 0, 0, 1, _index, _alpha);
}

void endingScene::release()
{
}