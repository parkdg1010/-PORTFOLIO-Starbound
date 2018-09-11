#pragma once

//=============================================================
//	## namespace MY_UTIL ##
//=============================================================

//=============================================================
//	## ���� ����ϴ� ��� ##
//=============================================================
#define MAGENTA		RGB(255,0,255)
#define PI		    3.14159265358979323846f

#define PI_2		PI/2
#define PI_4		PI/4
#define PI_8		PI/8

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
};

namespace utl = MY_UTIL;

