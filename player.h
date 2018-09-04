#pragma once
#include "gameActor.h"
#include "gameItem.h"

namespace PLAYER_CONST
{
	const int WIDTH = 64;
	const int HEIGHT = 128;
}

class player : public gameActor
{
private:
	enum STATE
	{
		IDLE, WALK, RUN, JUMP, FALL, CLIMB, DUCK //수구림
	};
	enum tagSKILL
	{
		REGEN_ENERGY, REGEN_HP,		//head
		DASH, SPRINT,				//body
		MULTJUMP, ROCKETJUMP		//foot
	};
	enum tagITEM
	{
		ITEM_WEAPON, ITEM_HEAD, ITEM_BODY, ITEM_BACK, ITEM_FOOT, ITEM_OBJECT
	};
	image* _img[7];
	image* _nohandImg[7];
	image* _hand[2];
	//image* _hair;

	//image* _weapon; //비어있으면 아무것도 안함 채워져있으면 손도 바꾸고 무기도 렌더
	
	gameItem* _weapon;

	tagSKILL _skill[3];

	image* _debugBuff;

	RECT _rcCollision;

	bool _onGround;
	bool _keepWalk;
	float _longJumpValue;

	vector<int> tileIndex;

	Synthesize(int, _jumpCount, JumpCount)
	Synthesize(float, _dashSpeed, DashSpeed)

public:
	virtual void move();
	virtual void collide();
	virtual bool collideStage();
	virtual bool collideObject(gameObject* gameObject = NULL);
	virtual void damaged(gameObject* actor);

	void inputKey();
	void changeState(STATE state);
	void updateHitbox();
	void direction();

	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();

	void initImage();

	player() { gameObject::init(); }
	~player() {}
};

