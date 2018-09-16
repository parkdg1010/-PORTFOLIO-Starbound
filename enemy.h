#pragma once
#include "gameActor.h"
#include "bullet.h"

//부모클래스 => 이놈을 상속받아서 보스, 일반몬스터등을 만든다
class player;						//damaged함수 호출을 위해 상호참조를 해야겠다.
class enemy : public gameActor
{
private:
	//랜덤으로 총알 발사 쿨타임 주기
	int _fireCount;
	int _rndFireCount;
protected:
	image* _picR;
	image* _picL;
	vector<bullet>* _vbullet;
	player* _player;
public:
	virtual void bltUpdate() {}
	virtual void bltRender() {}
	virtual void move();
	virtual void collide();
	virtual bool collideStage() { return false; }
	virtual bool collideObject(gameObject* gameObject = NULL);
	virtual void damaged(gameObject* actor);

	void linkPlayer(player* p) { _player = p; }

	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();

	bool bulletCountFire();

	enemy() { gameObject::init(); }
	virtual ~enemy() {}
};

