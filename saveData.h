#pragma once
#include "singletonBase.h"

//�� ��ȯ� ����ϵ��� ����

class player; //��ȣ����, �����͸� ���� �����͸� �������� ��������

class saveData : public singletonBase <saveData>
{
private:
	HANDLE _saveHandle;
	DWORD _result;
	//float _hp;
	char _data[128];

	player* _player;
public:
	HRESULT init();
	void release();

	//int getHp() { return _hp; }
	//void setHp(int hp) { _hp = hp; }

	player* getPlayer() { return _player; }
	void setPlayer(player* p) { _player = p; }

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

