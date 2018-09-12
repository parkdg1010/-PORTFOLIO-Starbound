#pragma once
#include "gameNode.h"

class gameObject : public gameNode
{
protected:
	float _x, _y, _z;
	float _angle;
	float _speed;
	float _gravity;

	int _state;
	int _axisX, _axisY;
	int _dir;

	int _curFrameX, _curFrameY;
	int _count;
	int _index;
	RECT _hitBox;

	bool _isActive;

	image* _mapPixel;	//스테이지를 여기에 줘야 초기좌표도 좀 찍고 집어던졌을때 맵충돌도 할 수 있을거같다

	Synthesize(float, _hp, Hp)
	Synthesize(float, _damage, Damage)
	Synthesize(float, _armor, Armor)
	Synthesize(int, _price, Price)

public:
	virtual void move() {}
	virtual void collide();
	virtual bool collideStage() { return false; }
	virtual bool collideObject(gameObject* gameObject = NULL);
	virtual void damaged(gameObject* actor) {}

	float getX() { return _x; }
	void setX(float x) { _x = x; }

	float getY() { return _y; }
	void setY(float y) { _y = y; }

	float getZ() { return _z; }
	void setZ(float z) { _z = z; }

	void setPos(float x, float y) { _x = x, _y = y; }

	float getAngle() { return _angle; }
	void setAngle(float angle) { _angle = angle; }

	float getSpeed() { return _speed; }
	void setSpeed(float speed) { _speed = speed; }

	float getGravity() { return _gravity; }
	void setGravity(float gravity) { _gravity = gravity; }

	int getState() { return _state; }
	void setState(int state) { _state = state; }

	int getDir() { return _dir; }
	void setDir(int dir) { _dir = dir; }

	int getCount() { return _count; }
	void setCount(int count) { _count = count; }

	int getIndex() { return _index; }
	void setIndex(int index) { _index = index; }

	RECT getHitBox() { return _hitBox; }
	void setHitBox(RECT hitbox) { _hitBox = hitbox; }

	bool getIsActive() { return _isActive; }
	void setIsActive(bool isActive) { _isActive = isActive; }

	void linkMapPixel(image* pixel) { _mapPixel = pixel; }

	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();

	gameObject() : _mapPixel(NULL) {}
	~gameObject() {}
};

