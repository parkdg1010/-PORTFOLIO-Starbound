#pragma once
#include "enemy.h"
class kluexbossPh2 : public enemy
{
public:
	virtual void bltUpdate();
	virtual void bltRender();
	virtual void move();
	virtual void collide();
	virtual bool collideStage() { return false; }
	virtual bool collideObject(gameObject* gameObject = NULL);
	virtual void damaged(gameObject* actor);
	virtual void drawUI();

	virtual HRESULT init(POINTf pos, int dir);
	virtual void update();
	virtual void render();
	virtual void release();

	kluexbossPh2() {}
	~kluexbossPh2() {}
};