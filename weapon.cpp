#include "stdafx.h"
#include "weapon.h"

HRESULT weapon::init(ITEM name, int price, float damage, float armor, image * icon, image * img)
{
	gameItem::init(name, price, damage, armor, icon, img);

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

void weapon::setup(image * effect1, image * effect2, image * effect3)
{
	if (effect1 != NULL) _effect[0] = effect1;
	if (effect2 != NULL) _effect[1] = effect2;
	if (effect3 != NULL) _effect[2] = effect3;
}
