#pragma once
#include "enemy.h"
enum tagKLUEXSTATE
{
	MAIN,
	FIRE,
	ICE
};
class kluexbossPh1 : public enemy
{
	image* _pic;
	animation* _img[3];

	vector<bullet> _vPlasmaBall;
	int _plasmaCount;
	int _p1FireDelay; //¹ß»çµô·¹ÀÌ
	int _p1FireCount; //¹ß»çÈ½¼ö

public:
	virtual void bltUpdate();
	virtual void bltRender();
	virtual void move();
	virtual void collide();
	virtual bool collideStage() { return false; }
	virtual bool collideObject(gameObject* gameObject = NULL);
	virtual void damaged(gameObject* actor);
	virtual void drawUI();

	virtual HRESULT init(POINTf pos, int dir);
	virtual void update();
	virtual void render();
	virtual void release();

	kluexbossPh1() {}
	~kluexbossPh1() {}
};