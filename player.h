#pragma once
#include "gameActor.h"
#include "inventory.h"

namespace PLAYER_CONST
{
	const int WIDTH = 64;
	const int HEIGHT = 128;
	const float MAX_HP = 200;
	const float MAX_ENERGY = 200;
}

class gameStage;		//스테이지 픽셀충돌을 하기위해 상호참조
class enemyManager;		//에너미 상호작용을 위해 상호참조
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

	image* _portraitUI;					//화면ui
	progressBar* _hpBar;				//화면 체력바
	progressBar* _energyBar;			//화면 기력바
	tagSKILL _skill[3];
	weapon* _weapon;					//무기 //비어있으면 아무것도 안함 채워져있으면 손도 바꾸고 무기도 렌더

	int _keepWalk;						//계단 내려가기
	float _longJumpValue;				//점프높이 제한

	int _invincibleCount;				//무적시간
	int _invincible;					//무적임	//0이면 무적 1면 무적시간 2이면 무적끝으로 하자

	float _handAngle;					//손 각도

	gameStage* _stage;					//스테이지 상호참조
	enemyManager* _enemyManager;		//에너미매니저 상호참조

	Synthesize(inventory*, _inventory, Inventory)
	Synthesize(int, _jumpCount, JumpCount)			//이단점프
	Synthesize(float, _dashSpeed, DashSpeed)		//대쉬속도
	Synthesize(float, _energy, Energy)				//기력

public:
	virtual void move();
	virtual void collide();
	virtual bool collideStage(int range);
	virtual bool collideObject(gameObject* gObject = NULL);
	virtual void damaged(gameObject* actor);
	virtual void damaged(float damage);

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
	void linkEnemyManager(enemyManager* EM) { _enemyManager = EM; }

	player() { gameObject::init(); _weapon = NULL; }
	~player() {}
};

