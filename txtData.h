#pragma once
#include "singletonBase.h"

//������ �����͵��� ���Ϳ� ��Ƽ� �ؽ�Ʈ ���Ϸ� ������ش�.

class txtData : public singletonBase <txtData>
{
public:
	HRESULT init(void);
	void release(void);

	//���̺�
	void txtSave(const char* fileName, vector<string> vStr);
	char* vectorArrayCombine(vector<string> vArray);
	//1,2,100
	
	//�ε�
	vector<string> txtLoad(const char* fileName);
	vector<string> charArraySeparation(char charArray[]);

	txtData() {}
	~txtData() {}
};

//����
//���̺�
//if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
//{
//	//itoa => ������ ���ڷ� integral to ascii
//	char temp[128];
//	vector<string> vStr;
//	vStr.push_back(itoa(_rocket->getX(), temp, 10));
//	vStr.push_back(itoa(_rocket->getY(), temp, 10));
//	vStr.push_back(itoa(_currentHp, temp, 10));
//
//	TXTDATA->txtSave("save.txt", vStr);
//}
//
//if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
//{
//	vector<string> vStr;
//	vStr = TXTDATA->txtLoad("save.txt");
//	//atoi => ���ڸ� ���ڷ� ascii to integral
//	_rocket->setX(atoi(vStr[0].c_str()));
//	_rocket->setY(atoi(vStr[1].c_str()));
//	_currentHp = (atoi(vStr[2].c_str()));
//}

