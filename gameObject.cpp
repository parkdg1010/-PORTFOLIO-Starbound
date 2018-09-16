#include "stdafx.h"
#include "gameObject.h"
#include "stageScene.h"

HRESULT gameObject::init()
{
	_angle = 0;
	_speed = 0;
	_gravity = 0;

	_axisX = NONE;
	_axisY = NONE;

	_curFrameX = 0;
	_curFrameY = 0;
	_count = 0;
	_index = 0;
	_hitBox = { 0,0,0,0 };
	_hp = 0;
	_damage = 0;
	_armor = 0;
	_price = 0;

	return S_OK;
}

void gameObject::update()
{
}

void gameObject::render()
{
}

void gameObject::release()
{
}

void gameObject::collide()
{
	this->collideStage();
	this->collideObject();
}

bool gameObject::collideObject(gameObject * gameObject)
{
	RECT temp;

	return IntersectRect(&temp, &gameObject->getHitBox(), &_hitBox);
}