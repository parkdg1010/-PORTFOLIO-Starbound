#include "stdafx.h"
#include "gameItem.h"

HRESULT gameItem::init(int price, float damage, float armor, image * icon, image * img, image * effect1, image * effect2, image * effect3)
{
	_price = price;
	
	_damage = damage;
	_armor = armor;
	
	_icon = icon;
	_img = img;

	_effect[0] = effect1;
	_effect[1] = effect2;
	_effect[2] = effect3;

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
