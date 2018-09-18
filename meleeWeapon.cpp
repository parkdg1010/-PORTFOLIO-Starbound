#include "stdafx.h"
#include "meleeWeapon.h"

HRESULT meleeWeapon::init(ITEM name, int price, float damage, float armor, image * icon, image * img)
{
	weapon::init(name, price, damage, armor, icon, img);

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

void meleeWeapon::setup(image * effect1, image * effect2, image * effect3)
{
	weapon::setup(effect1, effect2, effect3);
}
