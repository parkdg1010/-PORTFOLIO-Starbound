#pragma once
#include "gameObject.h"

class gameActor : public gameObject
{
protected:
	float _oldX, _oldY;
	Synthesize(float, _jumpSpeed, JumpSpeed)
public:
	virtual void move() {}
	virtual void collide();
	virtual bool collideStage() { return false; }
	virtual bool collideObject(gameObject* gameObject = NULL);
	virtual void damaged(gameObject* actor) {}

	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();

	gameActor() {}
	~gameActor() {}
};

