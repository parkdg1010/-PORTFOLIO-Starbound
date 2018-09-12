#include "stdafx.h"
#include "gameStage.h"
#include "kluexboss.h"

HRESULT kluexboss::init(POINTf pos, int dir)
{
	enemy::init(pos, dir);

	_phase1 = new kluexbossPh1;
	_phase1->init(pos, dir);

	_phase2 = new kluexbossPh2;
	_phase2->init(pos, dir);

	_currentPhase = _phase1;

	return S_OK;
}

void kluexboss::update()
{
	_currentPhase->linkMapPixel(_mapPixel);
	_currentPhase->setPlayerHitBox(_playerHitBox);
	_currentPhase->setPlayerX(_playerX);
	_currentPhase->setPlayerY(_playerY);

	_currentPhase->update();
}

void kluexboss::render()
{
	_currentPhase->render();
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