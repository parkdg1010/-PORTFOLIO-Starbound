#pragma once
#include "enemy.h"

enum tagFENNIXSTATE
{
	FENNIX_IDLE,
	FENNIX_HURT,
	FENNIX_MOVE,
	FENNIX_JUMP,
	FENNIX_FALL,
	FENNIX_SHOOT
};
class fennix : public enemy
{
	animation* _imgR[6];
	animation* _imgL[6];
public:
	virtual void bltUpdate();
	virtual void bltRender();
	virtual void move();
	virtual void collide();
	virtual bool collideStage() { return false; }
	virtual bool collideObject(gameObject* gameObject = NULL);
	virtual void damaged(gameObject* actor);

	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();

	fennix() {}
	~fennix() {}
};

