#include "stdafx.h"
#include "itemManager.h"

//아이템 팩토리
gameItem* itemFactory::createItem(CATEGORY tag, string name, int rarity, int price, float damage, float armor,
	image* icon, image * img, image* effect1, image* effect2, image* effect3)
{
	gameItem* item = NULL;

	switch (tag)
	{
	case TAG_USEABLE:
		item = new gameItem;
		item->init(tag, name, rarity, price, damage, armor, icon, img);
		break;
	case TAG_MELEEWEAPON:
		item = new spaceSword;
		dynamic_cast<spaceSword*>(item)->init(tag, name, rarity, price, damage, armor, icon, img, effect1, effect2, effect3);
		break;
	case TAG_RANGEDWEAPON:
		item = new shotgun01;
		dynamic_cast<shotgun01*>(item)->init(tag, name, rarity, price, damage, armor, icon, img, effect1, effect2, effect3);
		break;
	case TAG_PLASMAGUN:
		item = new plasmagun;
		dynamic_cast<plasmagun*>(item)->init(tag, name, rarity, price, damage, armor, icon, img, effect1, effect2, effect3);
		break;
	}

	return item;
}

gameItem* itemFactory::createItem(CATEGORY tag, string name, int rarity, int price, float damage, float armor, string icon, string img,
	string effect1, string effect2, string effect3)
{
	gameItem* item = NULL;

	image* _icon = IMAGEMANAGER->findImage(icon);
	image* _img = IMAGEMANAGER->findImage(img);
	image* _effect1 = IMAGEMANAGER->findImage(effect1);
	image* _effect2 = IMAGEMANAGER->findImage(effect2);
	image* _effect3 = IMAGEMANAGER->findImage(effect3);

	switch (tag)
	{
	case TAG_USEABLE:
		item = new gameItem;
		item->init(tag, name, rarity, price, damage, armor, _icon, _img);
		break;
	case TAG_MELEEWEAPON:
		item = new spaceSword;
		dynamic_cast<spaceSword*>(item)->init(tag, name, rarity, price, damage, armor, _icon, _img, _effect1, _effect2, _effect3);
		break;
	case TAG_RANGEDWEAPON:
		item = new shotgun01;
		dynamic_cast<shotgun01*>(item)->init(tag, name, rarity, price, damage, armor, _icon, _img, _effect1, _effect2, _effect3);
		break;
	case TAG_PLASMAGUN:
		item = new plasmagun;
		dynamic_cast<plasmagun*>(item)->init(tag, name, rarity, price, damage, armor, _icon, _img, _effect1, _effect2, _effect3);
		item->setCategory(TAG_RANGEDWEAPON);
		break;
	}

	return item;
}
