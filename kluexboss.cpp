#include "stdafx.h"
#include "gameStage.h"
#include "kluexboss.h"

HRESULT kluexboss::init()
{
	enemy::init();

	_phase1 = new kluexbossPh1;
	_phase1->setPosition(_x, _y, _dir);
	_phase1->linkPlayer(_player);		//에너미매니저에서 받은 포인터를 그대로 넘겨주기만 하면 되니까 이 cpp는 player를 include할 필요가 없다.
	_phase1->linkMapPixel(_mapPixel);
	_phase1->init();

	_phase2 = new kluexbossPh2;
	_phase2->setPosition(_x, _y, _dir);
	_phase2->linkPlayer(_player);
	_phase2->linkMapPixel(_mapPixel);
	_phase2->init();

	_hpBar = new progressBar;
	_hpBar->init("Texture/enemy/monsters/boss/bosshealthFront", "Texture/enemy/monsters/boss/bosshealthBack", WINSIZEX*0.36f, WINSIZEY*0.8f, 480, 39);

	_currentPhase = _phase1;

	return S_OK;
}

void kluexboss::update()
{
	_hitBox = _currentPhase->getHitBox();
	_isActive = _currentPhase->getIsActive();
	_currentPhase->update();
	_hpBar->update();
	_hpBar->setGauge(_currentPhase->getHp(), KLUEX_PH1_CONST::MAX_HP);
}

void kluexboss::render()
{
	_currentPhase->render();
	_hpBar->render(UIMANAGER->getUIDC());
}

void kluexboss::release()
{
	_phase1->release();
	SAFE_DELETE(_phase1);
	_phase2->release();
	SAFE_DELETE(_phase2);
}

void kluexboss::bltUpdate()
{
	_currentPhase->bltUpdate();
}

void kluexboss::bltRender()
{
	_currentPhase->bltRender();
}

void kluexboss::move()
{
	_currentPhase->move();
}

void kluexboss::collide()
{
	_currentPhase->collide();
}

bool kluexboss::collideObject(gameObject* gameObject)
{
	return _currentPhase->collideObject(gameObject);
}

void kluexboss::damaged(gameObject * actor)
{
	_currentPhase->damaged(actor);
}

void kluexboss::drawUI()
{
}