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
