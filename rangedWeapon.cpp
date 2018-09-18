#include "stdafx.h"
#include "rangedWeapon.h"

HRESULT rangedWeapon::init(ITEM name, int price, float damage, float armor, image * icon, image * img)
{
	weapon::init(name, price, damage, armor, icon, img);

	return S_OK;
}

void rangedWeapon::update()
{
}

void rangedWeapon::render()
{
}

void rangedWeapon::release()
{
}

void rangedWeapon::setup(image * effect1, image * effect2, image * effect3)
{
	weapon::setup(effect1, effect2, effect3);
}
