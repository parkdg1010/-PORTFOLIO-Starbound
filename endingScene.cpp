#include "stdafx.h"
#include "endingScene.h"

HRESULT endingScene::init()
{
	//엔딩
	IMAGEMANAGER->addFrameImage("엔딩", "Texture/ending/ending_1280x4320_1x6.bmp", 1280, 4320, 1, 6);
	IMAGEMANAGER->addImage("엔딩스크린", "Texture/ending/endingScreen.bmp", 1280, 720);
	_alpha = 0;

	SOUNDMANAGER->stop("던전");

	SAFE_DELETE(cursor);
	
	return S_OK;
}

void endingScene::update()
{
	if (_index == 3)
	{
		if (!SOUNDMANAGER->isPlaySound("엔딩"))
			SOUNDMANAGER->playBgm("엔딩", _soundVolume);
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
	if (_index > IMAGEMANAGER->findImage("엔딩")->getMaxFrameY())
	{
		_index = IMAGEMANAGER->findImage("엔딩")->getMaxFrameY();
		_alpha = 255;
	}
	IMAGEMANAGER->render("엔딩스크린", getMemDC(), 0, 0);
	IMAGEMANAGER->alphaFrameRender("엔딩", getMemDC(), 0, 0, 1, _index, _alpha);
}

void endingScene::release()
{
}