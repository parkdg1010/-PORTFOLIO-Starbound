#pragma once
#include "gameActor.h"
#include "bullet.h"

//�θ�Ŭ���� => �̳��� ��ӹ޾Ƽ� ����, �Ϲݸ��͵��� �����
class player;						//damaged�Լ� ȣ���� ���� ��ȣ������ �ؾ߰ڴ�.
class enemy : public gameActor
{
private:
	//�������� �Ѿ� �߻� ��Ÿ�� �ֱ�
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

