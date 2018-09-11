#pragma once
#include "gameObject.h"
#include "gameItem.h"

class gameActor : public gameObject
{
protected:
	float _oldX, _oldY;
	Synthesize(float, _jumpSpeed, JumpSpeed)
public:
	virtual void bltUpdate() {}		//isActive가 비활성 되도 불릿이 사라지지 않게 하기 위해 분리함
	virtual void bltRender() {}		//isActive가 비활성 되도 불릿이 사라지지 않게 하기 위해 분리함
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

