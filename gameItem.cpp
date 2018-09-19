#include "stdafx.h"
#include "gameItem.h"

HRESULT gameItem::init(ITEM name, int price, float damage, float armor,
	image * icon, image * img, int rarity)
{
	switch (name)
	{
	case ITEM_NONE:
		_name = "";
		break;
	case ITEM_SPACESWORD:
		_name = "ASTRO SABRE DELUXE";
		break;
	case ITEM_SHOTGUN01:
		_name = "SHOT GUN";
		break;
	}
	_price = price;

	_damage = damage;
	_armor = armor;

	_icon = icon;
	_img = img;

	_rarity = rarity;

	return S_OK;
}


void gameItem::update()
{
}

void gameItem::render()
{
}

void gameItem::release()
{
}