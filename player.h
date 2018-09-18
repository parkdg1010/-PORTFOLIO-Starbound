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
		IDLE, WALK, RUN, JUMP, FALL, CLIMB, DUCK //������
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

	int _keepWalk;						//��� ��������
	float _longJumpValue;				//�������� ����

	float _handAngle;					//�� ����

	gameStage* _stage;					//�������� ��ȣ����

	inventory* _inventory;

	Synthesize(int, _jumpCount, JumpCount)			//�̴�����
	Synthesize(float, _dashSpeed, DashSpeed)		//�뽬�ӵ�
	Synthesize(weapon*, _weapon, Weapon)			//���� //��������� �ƹ��͵� ���� ä���������� �յ� �ٲٰ� ���⵵ ����

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

