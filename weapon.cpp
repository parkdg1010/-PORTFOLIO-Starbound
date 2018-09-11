#include "stdafx.h"
#include "weapon.h"

HRESULT weapon::init(ITEM name, int price, float damage, float armor, image * icon, image * img, image * effect1, image * effect2, image * effect3)
{
	switch (name)
	{
	case ITEM_NONE:
		_name = "";
		break;
	case ITEM_SPACESWORD:
		_name = "ASTRO SABRE DELUXE";
		break;
	}
	_price = price;

	_damage = damage;
	_armor = armor;

	_icon = icon;
	_img = img;

	if(effect1 != NULL) _effect[0] = effect1;
	if(effect2 != NULL) _effect[1] = effect2;
	if(effect3 != NULL) _effect[2] = effect3;

	return S_OK;
}

void weapon::update()
{
}

void weapon::render()
{
}

void weapon::release()
{
}
