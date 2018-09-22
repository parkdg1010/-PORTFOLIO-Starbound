#include "stdafx.h"
#include "weapon.h"
HRESULT weapon::init(CATEGORY tag, string name, int rarity, int price, float damage, float armor, image * icon, image * img, image * effect1, image * effect2, image * effect3)
{
	gameItem::init(tag, name, rarity, price, damage, armor, icon, img);

	if(effect1 != NULL)
		_effect[0] = effect1;
	if(effect2 != NULL)
		_effect[1] = effect2;
	if(effect3 != NULL)
		_effect[2] = effect3;

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
