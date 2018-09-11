#pragma once
#include "gameActor.h"

//부모클래스 => 이놈을 상속받아서 보스, 일반몬스터등을 만든다
class enemy : public gameActor
{
private:
	//랜덤으로 총알 발사 쿨타임 주기
	int _fireCount;
	int _rndFireCount;

public:
	virtual void move();
	virtual void collide();
	virtual bool collideStage() { return false; }
	virtual bool collideObject(gameObject* gameObject = NULL);
	virtual void damaged(gameObject* actor);

	virtual HRESULT init(POINTf position, int dir);
	virtual void update();
	virtual void render();
	virtual void release();

	bool bulletCountFire();

	enemy() { gameObject::init(); }
	virtual ~enemy() {}
};

