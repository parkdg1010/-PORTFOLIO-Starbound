#pragma once
#include "weapon.h"
class rangedWeapon : public weapon
{
protected:
	image * _effect[3];
public:
	virtual HRESULT init(ITEM name = ITEM_NONE, int price = 0, float damage = 0, float armor = 0,
		image* icon = NULL, image* img = NULL, image* effect1 = NULL, image* effect2 = NULL, image* effect3 = NULL);
	virtual void update();
	virtual void render();
	virtual void release();

public:
	rangedWeapon() { gameObject::init(); }
	~rangedWeapon() {}
};