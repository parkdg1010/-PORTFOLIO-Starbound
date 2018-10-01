#pragma once
#include "rangedWeapon.h"
class drillgun : public rangedWeapon
{
public:
	virtual HRESULT init(CATEGORY tag = TAG_RANGEDWEAPON, string name = "GUN", int rarity = 0, int price = 0
		, float damage = 0, float armor = 0, image* icon = NULL, image* img = NULL
		, image* effect1 = NULL, image* effect2 = NULL, image* effect3 = NULL);
	virtual void update();
	virtual void render();
	virtual void release();

	virtual void attack();

	drillgun() {}
	~drillgun() {}
};

