#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## 초기화 ## init()
//=============================================================
HRESULT mainGame::init()
{
	gameNode::init(TRUE);
	//이곳에서 초기화를 한다
	SCENEMANAGER->addScene("로딩화면", new loadingScene);
	SCENEMANAGER->addScene("맵툴", new mapToolScene);
	SCENEMANAGER->addScene("시작", new startScene);
	SCENEMANAGER->addScene("인게임", new stageScene);
	SCENEMANAGER->addScene("우주선", new spaceShipScene);

	SCENEMANAGER->loadScene("로딩화면");

	cursor = IMAGEMANAGER->addFrameImage("CURSOR", "Texture/ui/cursor_32x22_2x1.bmp", 32, 22, 2, 1);
	ShowCursor(false);

	_player = new player;
	SAVEDATA->setPlayer(_player);

	return S_OK;
}

//=============================================================
//	## 해제 ## release()
//=============================================================
void mainGame::release()
{
	gameNode::release();

	_player->release();
	SAFE_DELETE(_player);
}

//=============================================================
//	## 업데이트 ## update()
//=============================================================
void mainGame::update()
{
	gameNode::update();

	UIMANAGER->clear();

	//씬매니져 업데이트
	SCENEMANAGER->update();

	//사운드매니져 업데이트
	SOUNDMANAGER->update();

	//이펙트매니져 업데이트
	EFFECTMANAGER->update();
}

//=============================================================
//	## 렌더 ## render()
//=============================================================
void mainGame::render() //이제 이미지매니저를 추가했고 gameNode를 수정해서 HDC매개변수 가져올 필요가 없다.
{
	//흰색 빈 비트맵(이것도 렌더에 그냥 둘것!!)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
//=============================================================
	_isDebug = KEYMANAGER->isToggleKey(VK_F1); //모든 클래스 디버그모드 시작

	//씬매니져 렌더
	SCENEMANAGER->render();

	//이펙트매니져 렌더
	EFFECTMANAGER->render();

	UIMANAGER->render(getMemDC());
	if(cursor != NULL) cursor->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, cursorFrameX, cursorFrameY);

	//토글키는 디버깅용으로 많이 사용한다
	if (_isDebug)
	{
		//타임매니져 렌더
		TIMEMANAGER->render(getMemDC());
		TextOut(getMemDC(), 0, 60, "디버그 모드", strlen("디버그 모드"));
	}

//=============================================================	
	//백버퍼의 내용을 HDC에 그린다 (이것도 렌더에 그냥 둘것!!)
	this->getBackBuffer()->render(getHDC());
}