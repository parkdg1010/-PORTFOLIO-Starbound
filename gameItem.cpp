#include "stdafx.h"
#include "gameItem.h"

HRESULT gameItem::init(CATEGORY tag, string name, int rarity, int price, float damage, float armor,
	image * icon, image * img)
{
	_category = tag;

	_name = name;
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