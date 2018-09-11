#include "stdafx.h"
#include "gameItem.h"

HRESULT gameItem::init(ITEM name, int price, float damage, float armor,
	image * icon, image * img)
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

//아이템 팩토리
gameItem * itemFactory::createItem(ITEM itemName, int price, float damage, float armor,
	image * icon, image * img)
{
	gameItem* item = new gameItem;
	item->init(itemName, price, damage, armor, icon, img);

	return item;
}

gameItem * itemFactory::createItem(ITEM itemName, int price, float damage, float armor, string icon, string img)
{
	gameItem* item = new gameItem;

	image* _icon = IMAGEMANAGER->findImage(icon);
	image* _img = IMAGEMANAGER->findImage(img);

	item->init(itemName, price, damage, armor, _icon, _img);

	return item;
}
