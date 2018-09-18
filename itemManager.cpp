#include "stdafx.h"
#include "itemManager.h"

//아이템 팩토리
gameItem* itemFactory::createItem(ITEM itemName, int price, float damage, float armor,
	image* icon, image * img, image* effect1, image* effect2, image* effect3)
{
	gameItem* item = NULL;

	switch (itemName)
	{
	case ITEM_NONE:
		item = new gameItem;
		break;
	case ITEM_SPACESWORD:
		item = new meleeWeapon;
		dynamic_cast<meleeWeapon*>(item)->setup(effect1, effect2, effect3);
		break;
	case ITEM_SHOTGUN01:
		item = new shotgun01;
		dynamic_cast<shotgun01*>(item)->setup(effect1, effect2, effect3);
		break;
	}

	item->init();

	return item;
}

gameItem* itemFactory::createItem(ITEM itemName, int price, float damage, float armor, string icon, string img,
	string effect1, string effect2, string effect3)
{
	gameItem* item = NULL;

	image* _icon = IMAGEMANAGER->findImage(icon);
	image* _img = IMAGEMANAGER->findImage(img);
	image* _effect1 = IMAGEMANAGER->findImage(effect1);
	image* _effect2 = IMAGEMANAGER->findImage(effect2);
	image* _effect3 = IMAGEMANAGER->findImage(effect3);

	switch (itemName)
	{
	case ITEM_NONE:
		item = new gameItem;
		break;
	case ITEM_SPACESWORD:
		item = new meleeWeapon;
		dynamic_cast<meleeWeapon*>(item)->setup(_effect1, _effect2, _effect3);
		break;
	case ITEM_SHOTGUN01:
		item = new shotgun01;
		dynamic_cast<shotgun01*>(item)->setup(_effect1, _effect2, _effect3);
		break;
	}

	item->init(itemName, price, damage, armor, _icon, _img);

	return item;
}
