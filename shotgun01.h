#pragma once
#include "rangedWeapon.h"

class shotgun01 : public rangedWeapon
{
public:
	virtual HRESULT init(ITEM name = ITEM_NONE, int price = 0, float damage = 0, float armor = 0,
		image* icon = NULL, image* img = NULL);
	virtual void update();
	virtual void render();
	virtual void release();

	virtual void setup(image* effect1 = NULL, image* effect2 = NULL, image* effect3 = NULL);
	virtual void fire();

	shotgun01() {}
	~shotgun01() {}
};

