#pragma once
#include "gameActor.h"
#include "inventory.h"

namespace PLAYER_CONST
{
	const int WIDTH = 64;
	const int HEIGHT = 128;
}

class gameStage;
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

	tagSKILL _skill[3];
	weapon* _weapon;

	int _keepWalk;						//계단 내려가기
	float _longJumpValue;				//점프높이 제한

	float _handAngle;					//손 각도

	gameStage* _stage;					//스테이지 상호참조

	Synthesize(inventory*, _inventory, Inventory)
	Synthesize(int, _jumpCount, JumpCount)			//이단점프
	Synthesize(float, _dashSpeed, DashSpeed)		//대쉬속도
	//Synthesize(weapon*, _weapon, Weapon)			//무기 //비어있으면 아무것도 안함 채워져있으면 손도 바꾸고 무기도 렌더

public:
	virtual void move();
	virtual void collide();
	virtual bool collideStage(int range);
	virtual bool collideObject(gameObject* gameObject = NULL);
	virtual void damaged(gameObject* actor);

	void inputKey();
	void changeState(STATE state);
	void updateHitbox();
	void direction();

	virtual void drawUI();

	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();

	void initImage();

	void linkStage(gameStage* stage) { _stage = stage; }

	player() { gameObject::init(); _weapon = NULL; }
	~player() {}
};

