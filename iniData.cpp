#include "stdafx.h"
#include "iniData.h"

HRESULT iniData::init()
{
	return S_OK;
}

void iniData::release(void)
{
	for (int i = 0; i < _vIniData.size(); ++i)
	{
		delete[] _vIniData[i].value;
	}
}
//ini������ �����͵��� ���Ϳ� �߰� ����,Ű,��
void iniData::addData(const char * section, const char * key, const char * value)
{
	//ini������ ����ü ������ �ʱ�ȭ
	tagIniData data;
	data.section = (char*)section;
	data.key = (char*)key;
	//data.value = (char*)value;

	int len = strlen(value);
	char * temp = new char[len + 1];
	for (int i = 0; i < len; ++i)
	{
		temp[i] = value[i];
	}
	temp[len] = '\0';
	data.value = temp;

	//���Ϳ� ini������ ����ü ���
	_vIniData.push_back(data);
}
//fileName.ini ���Ϸ� ����
void iniData::saveINI(const char * fileName)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf_s(str, "\\%s.ini", fileName);
	GetCurrentDirectory(256, dir);
	//user/�ڼ���/~~/windowApi/fileName.ini
	strcat_s(dir, str);

	for (int i = 0; i < _vIniData.size(); i++)
	{
		WritePrivateProfileString(_vIniData[i].section, _vIniData[i].key, _vIniData[i].value, dir);
	}
}
//���ڿ��� ������ �ε�
char * iniData::loadDataString(const char * fileName, const char * section, const char * key)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf_s(str, "\\%s.ini", fileName);
	GetCurrentDirectory(256, dir);
	//user/�ڼ���/~~/windowApi/fileName.ini
	strcat_s(dir, str);
	//dir = �ҷ��� ini������ ���

	char data[64] = { NULL }; //�ҷ��� �����͸� ������ ���� data�� ��´� (����)
	GetPrivateProfileString(section, key, "NOT_FOUND", data, 64, dir);

	return data; // �ҷ��� ������ ��ȯ
}
//������ ������ �ε�
int iniData::loadDataInteger(const char * fileName, const char * section, const char * key)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf_s(str, "\\%s.ini", fileName);
	GetCurrentDirectory(256, dir);
	//user/�ڼ���/~~/windowApi/fileName.ini
	strcat_s(dir, str);

	return GetPrivateProfileInt(section, key, 0, dir);
}
//�Ǽ��� ������ �ε�
float iniData::loadDataFloat(const char * fileName, const char * section, const char * key)
{
	return (atof)(loadDataString(fileName, section, key)); //atof ���ڿ��� �Ǽ��� ��ȯ�Ѵ�.
}
