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

class gameStage;		//�������� �ȼ��浹�� �ϱ����� ��ȣ����
class enemyManager;		//���ʹ� ��ȣ�ۿ��� ���� ��ȣ����
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

	image* _portraitUI;					//ȭ��ui
	progressBar* _hpBar;				//ȭ�� ü�¹�
	progressBar* _energyBar;			//ȭ�� ��¹�
	tagSKILL _skill[3];
	weapon* _weapon;					//���� //��������� �ƹ��͵� ���� ä���������� �յ� �ٲٰ� ���⵵ ����

	int _keepWalk;						//��� ��������
	float _longJumpValue;				//�������� ����

	int _invincibleCount;				//�����ð�
	int _invincible;					//������	//0�̸� ���� 1�� �����ð� 2�̸� ���������� ����

	float _handAngle;					//�� ����

	gameStage* _stage;					//�������� ��ȣ����
	enemyManager* _enemyManager;		//���ʹ̸Ŵ��� ��ȣ����

	Synthesize(inventory*, _inventory, Inventory)
	Synthesize(int, _jumpCount, JumpCount)			//�̴�����
	Synthesize(float, _dashSpeed, DashSpeed)		//�뽬�ӵ�
	Synthesize(float, _energy, Energy)				//���

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

