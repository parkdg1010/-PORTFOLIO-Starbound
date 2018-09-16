#include "stdafx.h"
#include "gameStage.h"
#include "kluexboss.h"

HRESULT kluexboss::init()
{
	enemy::init();

	_phase1 = new kluexbossPh1;
	_phase1->setPosition(_x, _y);
	_phase1->linkPlayer(_player);		//���ʹ̸Ŵ������� ���� �����͸� �״�� �Ѱ��ֱ⸸ �ϸ� �Ǵϱ� �� cpp�� player�� include�� �ʿ䰡 ����.
	_phase1->linkMapPixel(_mapPixel);
	_phase1->init();

	_phase2 = new kluexbossPh2;
	_phase2->setPosition(_x, _y);
	_phase2->linkPlayer(_player);
	_phase2->linkMapPixel(_mapPixel);
	_phase2->init();

	_currentPhase = _phase1;

	return S_OK;
}

void kluexboss::update()
{
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