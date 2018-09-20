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
		item->init(itemName, price, damage, armor, icon, img);
		break;
	case ITEM_SPACESWORD:
		item = new meleeWeapon;
		item->init(itemName, price, damage, armor, icon, img);
		dynamic_cast<meleeWeapon*>(item)->setup(effect1, effect2, effect3);
		break;
	case ITEM_SHOTGUN01:
		item = new shotgun01;
		item->init(itemName, price, damage, armor, icon, img);	//setup에서 데미지받기위해 그전에 init
		dynamic_cast<shotgun01*>(item)->setup(effect1, effect2, effect3);
		break;
	}

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
		item->init(itemName, price, damage, armor, _icon, _img);
		break;
	case ITEM_SPACESWORD:
		item = new meleeWeapon;
		item->init(itemName, price, damage, armor, _icon, _img);
		dynamic_cast<meleeWeapon*>(item)->setup(_effect1, _effect2, _effect3);
		break;
	case ITEM_SHOTGUN01:
		item = new shotgun01;
		item->init(itemName, price, damage, armor, _icon, _img);
		dynamic_cast<shotgun01*>(item)->setup(_effect1, _effect2, _effect3);
		break;
	}

	return item;
}
