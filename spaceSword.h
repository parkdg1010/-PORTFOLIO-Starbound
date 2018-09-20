#pragma once
#include "meleeWeapon.h"
class spaceSword : public meleeWeapon
{
public:
	virtual HRESULT init(ITEM name = ITEM_NONE, int price = 0, float damage = 0, float armor = 0,
		image* icon = NULL, image* img = NULL);
	virtual void update();
	virtual void render();
	virtual void release();

	virtual void setup(image* effect1 = NULL, image* effect2 = NULL, image* effect3 = NULL);
	virtual void attack();

	spaceSword() {}
	~spaceSword() {}
};

