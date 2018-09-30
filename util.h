#pragma once

//=============================================================
//	## namespace MY_UTIL ##
//=============================================================

//=============================================================
//	## ���� ����ϴ� ��� ##
//=============================================================
#define MAGENTA		RGB(255,0,255)
#define PI		    3.14159265358979323846f

#define PI_2		PI *0.5   //2�γ���
#define PI_4		PI *0.25  //4�� ����
#define PI_8		PI *0.125 //8�� ����

//ADDED ��ũ�� �Լ�
#define DELAYCOUNT(count, delay) {count = (count +1) % delay;} //������
#define RAD_TO_DEG(angle) angle *0.017453292519943295769f // ȣ���� ������
#define MID(p1,p2) (p1+p2)*0.5 //�� ���� ����

namespace MY_UTIL
{
	// �� �� ������ �Ÿ�
	float getDistance(float startX, float startY, float endX, float endY);
	float getDistance(float _x, float _y);
	// �� �� ������ ����
	float getAngle(float startX, float startY, float endX, float endY);
	//+�θ� �� �� ������ ����
	float getAnglePL(float startX, float startY, float endX, float endY);

	void textMake(HDC dc, int x, int y, const char* name, int value); //���ڸ� ������ ������� ���ڸ� ������ ���� ��� �Ǽ��� ������ �Ǽ� ���
	void textMake(HDC dc, int x, int y, const char* name, float value);
	void textMake(HDC dc, int x, int y, const char* name);

	int getRectArea(RECT rc);
	POINT getRectCenter(RECT rc);
};

namespace utl = MY_UTIL;

