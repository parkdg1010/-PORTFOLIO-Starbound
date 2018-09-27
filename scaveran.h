#pragma once
#include "enemy.h"

namespace SCAVERAN_CONST
{
	const int WIDTH = 113;
	const int HEIGHT = 54;
	enum STATE
	{
		IDLE,
		IDLE_BOBUP,
		IDLE_BOBSIDE,
		IDLE_BOBDOWN,
		MOVE,
		JUMP,
		FALL,
		HURT
	};
}

class scaveran : public enemy
{
	animation* _imgR[8];
	animation* _imgL[8];

	int _stateDelay;
	RECT _searchingRc;	//찾으면 접근
	bool _isSearch;

	int _keepWalk;
	int _wanderDelay;
	int _wanderDirection;

	int _soundDelay;
public:
	virtual void move();
	virtual void collide();
	virtual bool collideStage(int range);
	virtual bool collideObject(gameObject* gameObject = NULL);
	virtual void damaged(gameObject* actor);

	void updateHitbox();

	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();

	scaveran() {}
	~scaveran() {}
};

