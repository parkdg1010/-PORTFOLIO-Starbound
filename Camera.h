#pragma once
#include "singletonBase.h"
class Camera : public singletonBase<Camera>
{
private:
	int maxWidth, maxHeight;
	int x, y, oldX, oldY;
	int sX, sY, shakingPower;

	int destX, destY;
	float speed;

	int count, delay, delayCount;

public:
	void setRange(int width, int height) { maxWidth = width; maxHeight = height; }
	void setPosition(int _x, int _y) { x = _x; y = _y; }
	void setShakeInfo(int shakingTime, int _shakingPower) { count = shakingTime; shakingPower = _shakingPower; }
	void videoShooting(int _x, int _y, float _speed = 0);
	void videoShooting();

	int getMaxWidth() { return maxWidth; }
	int getMaxHeight() { return maxHeight; }
	int getX() { return x - sX; }		//기본(진동포함)
	int getY() { return y - sY; }		//기본(진동포함)
	int getSourX() { return x; }		//배경용
	int getSourY() { return y; }		//배경용
	int getSX() { return sX; }
	int getSY() { return sY; }

	HRESULT init();
	void release();

	Camera() {}
	~Camera() {}
};

