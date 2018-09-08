#include "stdafx.h"
#include "loading.h"
//=============================================================
//	## loadItem ## (�ε������ Ŭ����)
//=============================================================
HRESULT loadItem::init(string keyName, int width, int height, bool isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_0;
	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = keyName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string keyName, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_1;
	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string keyName, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_2;
	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string keyName, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_FRAMEIMAGE_0;
	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string keyName, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_FRAMEIMAGE_1;
	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForSound(string keyName, const char* fileName, bool bgm, bool loop)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_SOUND;
	//���� ����ü �ʱ�ȭ
	_soundResource.keyName = keyName;
	_soundResource.fileName = fileName;
	_soundResource.bgm = bgm;
	_soundResource.loop = loop;

	return S_OK;
}


//=============================================================
//	## loading ## (�ε�Ŭ����)
//=============================================================
HRESULT loading::init(void)
{
	//�ε�ȭ�� ��׶��� �̹��� �ʱ�ȭ
	_background = IMAGEMANAGER->addFrameImage("bgLoadingScene", "Texture/ui/bunny_2048x160_1x8.bmp", 2048, 160, 8, 1); //IMAGEMANAGER->addImage("bgLoadingScene", "bgLoadingScene.bmp", WINSIZEX, WINSIZEY);

	//�ε��� Ŭ���� �ʱ�ȭ
	_loadingBar = new progressBar;
	_loadingBar->init("loadingBarFront", "loadingBarBack", 320, 630, 600, 20);
	_loadingBar->setGauge(0, 0);
	//���� ������ �ʱ�ȭ
	_currentGauge = 0;

	//�ε��� �ۼ�Ʈ �����̹��� �ʱ�ȭ
	_numbers = IMAGEMANAGER->addFrameImage("loadingNumber", "loadingNumber.bmp",400,60,10,1);
	
	//�ۼ�Ʈ ���� �ʱ�ȭ
	_percent = 0;

	_count = 0;

	return S_OK;
}

void loading::release(void)
{
	//�ε��� Ŭ���� ����
	_loadingBar->release();
	SAFE_DELETE(_loadingBar);
}

void loading::update(void)
{
	//�ε��� Ŭ���� ������Ʈ
	_loadingBar->update();
}

void loading::render(void)
{
	//��׶��� ����
	_count = (_count + 1) % 20;
	if (_count == 0) _background->setFrameX(_background->getFrameX() + 1);
	if (_background->getFrameX() >= _background->getMaxFrameX()) _background->setFrameX(0);

	_background->frameRender(getMemDC(), WINSIZEX -250, WINSIZEY - 150);
	//�ε��� Ŭ���� ����
	_loadingBar->render();

	//�ε� �ۼ�Ʈ �̹��� ����
	//�̹��� currentframeX�� �̿��ؼ� 0~9���� ǥ���ϸ� �ǰڴ�.
	//���� �ڸ�
	_numbers->frameRender(getMemDC(), _loadingBar->getRect().right - _numbers->getFrameWidth()*2, _loadingBar->getRect().top - _numbers->getFrameHeight(), (_percent % 100 / 10), 0);
	//���� �ڸ�
	_numbers->frameRender(getMemDC(), _loadingBar->getRect().right - _numbers->getFrameWidth(), _loadingBar->getRect().top - _numbers->getFrameHeight(), (_percent % 100 % 10), 0);

	char fileName[64];
	if (_currentGauge < _vLoadItem.size())
	{
		if (_vLoadItem[_currentGauge]->getLoadingKind() == LOAD_KIND_SOUND)
		{
			sprintf_s(fileName, "Sound\\%s.mp3", _vLoadItem[_currentGauge]->getSoundResource().keyName.c_str()); //c_str ��Ʈ���� const char*������
			TextOut(getMemDC(), _loadingBar->getRect().left + 10, _loadingBar->getRect().bottom + 20, fileName, strlen(fileName));
		}
		else
		{
			sprintf_s(fileName, "Image\\%s.bmp", _vLoadItem[_currentGauge]->getImageResource().keyName.c_str()); //c_str ��Ʈ���� const char*������
			TextOut(getMemDC(), _loadingBar->getRect().left + 10, _loadingBar->getRect().bottom + 20, fileName, strlen(fileName));
		}
	}
}

void loading::loadImage(string keyName, int width, int height, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(keyName, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(keyName, fileName, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(keyName, fileName, x, y, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(keyName, fileName, width, height, frameX, frameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(keyName, fileName, x, y, width, height, frameX, frameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadSound(string keyName, const char * fileName, bool bgm, bool loop)
{
	loadItem* item = new loadItem;
	item->init(keyName, fileName, bgm, loop);
	_vLoadItem.push_back(item);
}

BOOL loading::loadingDone()
{
	//�ε��� �Ϸ��
	if (_currentGauge >= _vLoadItem.size())
	{
		return TRUE; //���� ��ȯ�ϱ� ���� true�� ������
	}

	loadItem* item = _vLoadItem[_currentGauge]; //�̹��� �ε��� ������������ ��������

	//���⿡�� loadItemŬ������ �����͸� ������ addimage, addsound�Ѵ�.
	switch (item->getLoadingKind())
	{
	case LOAD_KIND_IMAGE_0:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.width, img.height, img.trans, img.transColor);
		}
		break;
	case LOAD_KIND_IMAGE_1:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName, img.width, img.height, img.trans, img.transColor);
		}
		break;
	case LOAD_KIND_IMAGE_2:
		{	tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.trans, img.transColor);
		}	
		break;
	case LOAD_KIND_FRAMEIMAGE_0:
		{	tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
		}	
		break;
	case LOAD_KIND_FRAMEIMAGE_1:
		{	tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
		}	
		break;
	case LOAD_KIND_SOUND:
		{
			tagSoundResource bgm = item->getSoundResource();
			SOUNDMANAGER->addSound(bgm.keyName, bgm.fileName, bgm.bgm, bgm.loop);
		}
		break;
	}

	//switch������ �����͸� �ε��ϰ��ϸ� �ε��� ������ ����
	//��������� ����
	_currentGauge++;

	//�ε��ۼ�Ʈ
	_percent = ((float)_currentGauge / _vLoadItem.size() * 100); //int�� ������ / int�� ������ �����ϸ� �Ҽ����� ����������. -> �Ǽ������� ����ȯ �Ͽ� *100 ���� ������ �Ҽ����� �����ش�.

	//�ε��� �̹��� ����
	_loadingBar->setGauge(_currentGauge, _vLoadItem.size());

	return 0;
}


