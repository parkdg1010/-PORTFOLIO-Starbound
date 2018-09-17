#pragma once
#include "enemy.h"

namespace FENNIX_CONST
{
	const int WIDTH = 88;
	const int HEIGHT = 58;
	enum STATE
	{
		IDLE,
		MOVE,
		HURT,
		JUMP,
		FALL,
		SHOOT
	};
}

class fennix : public enemy
{
private:
	animation* _imgR[6];
	animation* _imgL[6];

	int _stateDelay;
	RECT _searchingRc;	//찾으면 접근
	RECT _fireRc;		//찾으면 발사
	bool _isSearch;
	bool _isFire;
	
	int _keepWalk;
	int _wanderDelay;
	int _wanderDirection;
	int _fireDelay;

public:
	virtual void bltFire();
	virtual void bltUpdate();
	virtual void bltRender();
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

	fennix() {}
	~fennix() {}
};

