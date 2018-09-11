#pragma once
#include "gameActor.h"

//�θ�Ŭ���� => �̳��� ��ӹ޾Ƽ� ����, �Ϲݸ��͵��� �����
class enemy : public gameActor
{
private:
	//�������� �Ѿ� �߻� ��Ÿ�� �ֱ�
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

