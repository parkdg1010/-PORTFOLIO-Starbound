#pragma once
#include "enemy.h"
namespace KLUEX_PH1_CONST
{
	const int WIDTH = 300;
	const int HEIGHT = 280;
	const int MAX_HP = 2000;
	enum STATE
	{
		MAIN,
		FIRE,
		ICE,
		NONE
	};
}

class kluexbossPh1 : public enemy
{
private:
	animation* _img[3];

	//���Ϻ�ȯ
	int _activeP;
	int _patternDelay;
	//����1 ����
	vector<bullet> _vPlasmaBall;
	int _plasmaCount;
	int _p1BallDelay; //�� ���� ������
	int _p1FireDelay; //�߻������
	int _p1FireCount; //�߻�Ƚ��

	//����2 ����
	image* _flatBoard;
	image* _flatBoardPixel;
	image* _flatBoardPixelErase;
	image* _magma;
	RECT _magmaHitBox;
	float _boardY;
	float _magmaY;
	int _magmaLoopSPD;
	int _p2AniCount;
	int _p2Duration;

	//����3 ����
	image* _iceblock;
	RECT _iceHitBox[8];
	bool _iceActive[8];
	bool _iceStart;
	int _iceframeCount;
	int _p3Duration;

public:
	virtual void bltUpdate();
	virtual void bltRender();
	virtual void move();
	virtual void collide();
	virtual bool collideStage(int range) { return false; }
	virtual bool collideObject(gameObject* gameObject = NULL);
	virtual void damaged(gameObject* actor);
	virtual void drawUI();

	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();

	void pattern1Update();
	void pattern1Render();

	void pattern2Update();
	void pattern2Render();

	void pattern3Update();
	void pattern3Render();

	kluexbossPh1() {}
	~kluexbossPh1() {}
};