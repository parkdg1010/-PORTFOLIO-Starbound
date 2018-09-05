#include "stdafx.h"
#include "gameItem.h"

HRESULT gameItem::init(ITEM name, int price, float damage, float armor,
	image * icon, image * img, image * effect1, image * effect2, image * effect3)
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

gameItem * itemFactory::createItem(ITEM itemName, int price, float damage, float armor,
	image * icon, image * img, image * effect1, image * effect2, image * effect3)
{
	gameItem* item = new gameItem;
	item->init(itemName, price, damage, armor, icon, img, effect1, effect2, effect3);

	return item;
}

gameItem * itemFactory::createItem(ITEM itemName, int price, float damage, float armor, string icon, string img, string effect1, string effect2, string effect3)
{
	gameItem* item = new gameItem;

	image* _icon = IMAGEMANAGER->findImage(icon);
	image* _img = IMAGEMANAGER->findImage(img);
	image* _effect1 = IMAGEMANAGER->findImage(effect1);
	image* _effect2 = IMAGEMANAGER->findImage(effect2);
	image* _effect3 = IMAGEMANAGER->findImage(effect3);

	item->init(itemName, price, damage, armor, _icon, _img, _effect1, _effect2, _effect3);

	return item;
}
