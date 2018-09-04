#include "stdafx.h"
#include "txtData.h"

HRESULT txtData::init(void)
{
	return S_OK;
}

void txtData::release(void)
{
}

//���̺�
void txtData::txtSave(const char * fileName, vector<string> vStr)
{
	HANDLE file;
	DWORD write;
	char str[128];
	ZeroMemory(str, sizeof(str));

	strcpy_s(str,sizeof(str), vectorArrayCombine(vStr)); //���ڿ� ����

	file = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, str, 128, &write, NULL);

	CloseHandle(file);
}
//������ ���ڿ��� ��ģ��.
char * txtData::vectorArrayCombine(vector<string> vArray)
{
	//100,200,1...

	char str[128];
	ZeroMemory(str, sizeof(str));

	for (int i = 0; i < vArray.size(); i++)
	{
		strcat_s(str, vArray[i].c_str()); //c_str() => ���ڿ��� char�� (�迭)������ �ٲ��� //���ڿ� ��ħ
		//str1 = "������", str2 = "���ٻ�"
		//strcat(str1, str2) => str1 = "�����ٸ��ٻ�";
		if (i + 1 < vArray.size())
		{
			strcat_s(str, ","); //������ ������ ������ �����Ͱ��� ���̿� ,�� �ٿ� ��������.
		}
		//str1 => ������,���ٻ�
	}

	return str;
}

//�ε�
vector<string> txtData::txtLoad(const char * fileName)
{
	HANDLE file;
	DWORD read;
	char str[128];
	ZeroMemory(str, sizeof(str));

	file = CreateFile(fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, str, 128, &read, NULL);

	CloseHandle(file);

	return charArraySeparation(str);
}

vector<string> txtData::charArraySeparation(char charArray[])
{
	vector<string> vArray;
	const char* separation = ",";
	char* context = NULL;
	char* token;

	token = strtok_s(charArray, separation, &context); //���ڿ� �и�
	vArray.push_back(token);
	//a,b,c,d...
	while (NULL != (token = strtok_s(NULL, separation, &context)))
	{
		vArray.push_back(token);
	}

	return vArray;
}
