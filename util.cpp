#include "stdafx.h"
#include "util.h"

float MY_UTIL::getDistance(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = startY - endY;

	return sqrtf(x*x + y * y);
}

float MY_UTIL::getDistance(float _x, float _y)
{
	return sqrt(pow(_x, 2) + pow(_y, 2));
}

float MY_UTIL::getAngle(float startX, float startY, float endX, float endY)
{
	return atan2(startY - endY, endX - startX);
}

float MY_UTIL::getAnglePL(float startX, float startY, float endX, float endY)
{
	float angle = atan2(startY - endY, endX - startX);
	if (angle < 0)
		angle += 2 * PI;	//0보다 작으면 360도 더해서 양수값으로?
	return angle;
}

void MY_UTIL::textMake(HDC dc, int x, int y, const char * name, int value)
{
	char temp[256];
	wsprintf(temp, "%s%d", name, value);
	TextOut(dc, x, y, temp, strlen(temp));
}

void MY_UTIL::textMake(HDC dc, int x, int y, const char * name, float value)
{
	char temp[256];
	_stprintf_s(temp, "%s%f", name, value);
	TextOut(dc, x, y, temp, strlen(temp));
}

void MY_UTIL::textMake(HDC dc, int x, int y, const char* t)
{
	TextOut(dc, x, y, t, strlen(t));
}

int MY_UTIL::getRectArea(RECT rc)
{
	LONG width = rc.right - rc.left;
	LONG height = rc.bottom - rc.top;
	int area = abs(width * height);
	
	return area;
}

POINT MY_UTIL::getRectCenter(RECT rc)
{
	POINT temp;
	temp.x = MID(rc.left, rc.right);
	temp.y = MID(rc.top, rc.bottom);
	return temp;
}
