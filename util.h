#pragma once

//=============================================================
//	## namespace MY_UTIL ##
//=============================================================

//=============================================================
//	## 자주 사용하는 상수 ##
//=============================================================
#define MAGENTA		RGB(255,0,255)
#define PI		    3.14159265358979323846f

#define PI_2		PI/2
#define PI_4		PI/4
#define PI_8		PI/8

namespace MY_UTIL
{
	// 두 점 사이의 거리
	float getDistance(float startX, float startY, float endX, float endY);
	float getDistance(float _x, float _y);
	// 두 점 사이의 각도
	float getAngle(float startX, float startY, float endX, float endY);
	//+로만 두 점 사이의 각도
	float getAnglePL(float startX, float startY, float endX, float endY);

	void textMake(HDC dc, int x, int y, const char* name, int value); //숫자를 넣으면 숫자출력 문자를 넣으면 문자 출력 실수를 넣으면 실수 출력
	void textMake(HDC dc, int x, int y, const char* name, float value);
	void textMake(HDC dc, int x, int y, const char* name);

	int getRectArea(RECT rc);
};

namespace utl = MY_UTIL;

