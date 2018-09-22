#include "stdafx.h"
#include "meleeWeapon.h"
HRESULT meleeWeapon::init(CATEGORY tag, string name, int rarity, int price, float damage, float armor, image * icon, image * img, image * effect1, image * effect2, image * effect3)
{
	weapon::init(tag, name, rarity, price, damage, armor, icon, img, effect1, effect2, effect3);

	return S_OK;
}

void meleeWeapon::update()
{
}

void meleeWeapon::render()
{
}

void meleeWeapon::release()
{
}
