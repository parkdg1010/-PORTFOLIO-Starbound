#include "stdafx.h"
#include "gameActor.h"

HRESULT gameActor::init()
{
	return S_OK;
}

void gameActor::update()
{
}

void gameActor::render()
{
	
}

void gameActor::release()
{
}

void gameActor::collide()
{
	this->collideStage();
	this->collideObject();
}

bool gameActor::collideObject(gameObject * gameObject)
{
	RECT temp;

	return IntersectRect(&temp, &gameObject->getHitBox(), &_hitBox);
}