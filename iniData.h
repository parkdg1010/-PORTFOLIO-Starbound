#pragma once
#include "singletonBase.h"
//=============================================================
//	## iniData ## (INI ������)
//=============================================================
//ini������ ����ü
struct tagIniData
{
	char* section;
	char* key;
	char* value;
};

class iniData : public singletonBase <iniData>
{
private:
	vector<tagIniData> _vIniData;

public:
	HRESULT init();
	void release();

	//������ �߰��ϱ�(����, Ű, ���)
	void addData(const char* section, const char* key, const char* value);
	//���̺�(�����̸�)
	void saveINI(const char* fileName);

	//���ڷ� ���� �ε��ϱ�(�����̸�, ����, Ű)
	char* loadDataString(const char* fileName, const char* section, const char* key);
	//������ ���� �ε��ϱ�(�����̸�, ����, Ű)
	int loadDataInteger(const char* fileName, const char* section, const char* key);
	//�Ǽ��� ���� �ε��ϱ�
	float loadDataFloat(const char* fileName, const char* section, const char* key); // atof ascii to float���� ���ڿ��� �Ǽ��� ����ȯ����.

	iniData() {}
	~iniData() {}
};


//���� Ű�� addData�ϸ� ���� ����ȴ�.

/* ����
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
	//����, Ű, ���
	//[����]
	//���=99
	//����=70
	//[����]
	//�ѽǷ�=20
	//�ڵ���=80
	INIDATA->addData("����", "���", "99");
	INIDATA->addData("����", "����", "70");
	INIDATA->addData("����", "�ѽǷ�", "20");
	INIDATA->addData("����", "�ڵ���", "80");
	//�����̸����� ���̺�
	INIDATA->saveINI("ARVR");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
	int num = INIDATA->loadDataInteger("ARVR", "����", "�ѽǷ�");
	cout << "������ �ѽǷ�: " << num << endl;
	}
*/