#pragma once

//=============================================================
//	## namespace MY_UTIL ##
//=============================================================

//=============================================================
//	## 자주 사용하는 상수 ##
//=============================================================
#define MAGENTA		RGB(255,0,255)
#define PI		    3.14159265358979323846f

#define PI_2		PI *0.5   //2로나눔
#define PI_4		PI *0.25  //4로 나눔
#define PI_8		PI *0.125 //8로 나눔

//ADDED 매크로 함수
#define DELAYCOUNT(count, delay) {count = (count +1) % delay;} //딜레이
#define RAD_TO_DEG(angle) angle *0.017453292519943295769f // 호도를 각도로
#define MID(p1,p2) (p1+p2)*0.5 //두 점의 중점

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
	POINT getRectCenter(RECT rc);
};

namespace utl = MY_UTIL;

