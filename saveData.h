#pragma once
#include "singletonBase.h"
#include "tileNode.h"

//씬 전환등에 사용하도록 하자

class player; //상호참조, 포인터를 통해 데이터를 가져오고 내보내자
//class gameStage;

class saveData : public singletonBase <saveData>
{
private:
	HANDLE _saveHandle;
	DWORD _result;
	//float _hp;
	char _data[128];

	player* _player;

	tagTile* _tiles;
	POINT _tileXY;
	image* _stageBuffer;
public:
	HRESULT init();
	void release();

	//int getHp() { return _hp; }
	//void setHp(int hp) { _hp = hp; }

	player* getPlayer() { return _player; }
	void setPlayer(player* p) { _player = p; }

	tagTile* getTiles() { return _tiles; }
	void setTiles(tagTile* t) { _tiles = t; }

	POINT getTileXY() { return _tileXY; }
	void setTileXY(int x, int y) { _tileXY.x = x; _tileXY.y = y; }

	image* getStageBuffer() { return _stageBuffer; }
	void setStageBuffer(image* buffer) { _stageBuffer = buffer; }

	//원하는 데이터의 get,set함수를 만들어 데이터를 세이브,로드

	saveData() {}
	~saveData() {}
};


//예시
//체력 저장
//if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
//{
//	SAVEDATA->setHp(_currentHp);
//}
////체력 로드
//if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
//{
//	_currentHp = SAVEDATA->getHp();
//}

