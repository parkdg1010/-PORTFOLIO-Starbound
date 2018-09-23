#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## �ʱ�ȭ ## init()
//=============================================================
HRESULT mainGame::init()
{
	gameNode::init(TRUE);
	//�̰����� �ʱ�ȭ�� �Ѵ�
	SCENEMANAGER->addScene("�ε�ȭ��", new loadingScene);
	SCENEMANAGER->addScene("����", new mapToolScene);
	SCENEMANAGER->addScene("����", new startScene);
	SCENEMANAGER->addScene("�ΰ���", new stageScene);
	SCENEMANAGER->addScene("���ּ�", new spaceShipScene);

	SCENEMANAGER->loadScene("�ε�ȭ��");

	cursor = IMAGEMANAGER->addFrameImage("CURSOR", "Texture/ui/cursor_32x22_2x1.bmp", 32, 22, 2, 1);
	ShowCursor(false);

	_player = new player;
	SAVEDATA->setPlayer(_player);

	return S_OK;
}

//=============================================================
//	## ���� ## release()
//=============================================================
void mainGame::release()
{
	gameNode::release();

	_player->release();
	SAFE_DELETE(_player);
}

//=============================================================
//	## ������Ʈ ## update()
//=============================================================
void mainGame::update()
{
	gameNode::update();

	UIMANAGER->clear();

	//���Ŵ��� ������Ʈ
	SCENEMANAGER->update();

	//����Ŵ��� ������Ʈ
	SOUNDMANAGER->update();

	//����Ʈ�Ŵ��� ������Ʈ
	EFFECTMANAGER->update();
}

//=============================================================
//	## ���� ## render()
//=============================================================
void mainGame::render() //���� �̹����Ŵ����� �߰��߰� gameNode�� �����ؼ� HDC�Ű����� ������ �ʿ䰡 ����.
{
	//��� �� ��Ʈ��(�̰͵� ������ �׳� �Ѱ�!!)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
//=============================================================
	_isDebug = KEYMANAGER->isToggleKey(VK_F1); //��� Ŭ���� ����׸�� ����

	//���Ŵ��� ����
	SCENEMANAGER->render();

	//����Ʈ�Ŵ��� ����
	EFFECTMANAGER->render();

	UIMANAGER->render(getMemDC());
	if(cursor != NULL) cursor->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, cursorFrameX, cursorFrameY);

	//���Ű�� ���������� ���� ����Ѵ�
	if (_isDebug)
	{
		//Ÿ�ӸŴ��� ����
		TIMEMANAGER->render(getMemDC());
		TextOut(getMemDC(), 0, 60, "����� ���", strlen("����� ���"));
	}

//=============================================================	
	//������� ������ HDC�� �׸��� (�̰͵� ������ �׳� �Ѱ�!!)
	this->getBackBuffer()->render(getHDC());
}