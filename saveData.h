#pragma once
#include "singletonBase.h"
#include "tileNode.h"

//�� ��ȯ� ����ϵ��� ����

class player; //��ȣ����, �����͸� ���� �����͸� �������� ��������
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

	//���ϴ� �������� get,set�Լ��� ����� �����͸� ���̺�,�ε�

	saveData() {}
	~saveData() {}
};


//����
//ü�� ����
//if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
//{
//	SAVEDATA->setHp(_currentHp);
//}
////ü�� �ε�
//if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
//{
//	_currentHp = SAVEDATA->getHp();
//}

