#pragma once
#include "enemy.h"
#include "progressBar.h"
#include "kluexbossPh1.h"
#include "kluexbossPh2.h"

class kluexboss : public enemy
{
private:
	enemy* _currentPhase;
	enemy* _phase1;
	enemy* _phase2;

	bool _isPhase2;
	int _deadCount;

	progressBar* _hpBar;
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

	kluexboss() { gameObject::init(); };
	~kluexboss() {};
};

