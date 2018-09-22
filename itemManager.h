#pragma once
#include "gameNode.h"
#include "inventory.h"

class itemManager : public gameNode
{
public:
	itemManager() {};
	~itemManager() {};
};

class itemFactory
{
public:
	//아이템 기본
	//이미지 변수로 초기화
	gameItem * createItem(CATEGORY tag = TAG_USEABLE, string name = "NONE", int rarity = 0, int price = 0, float damage = 0, float armor = 0,
		image* icon = NULL, image* img = NULL, image* effect1 = NULL, image* effect2 = NULL, image* effect3 = NULL);
	//이미지키값으로 초기화
	gameItem* createItem(CATEGORY tag = TAG_USEABLE, string name = "NONE", int rarity = 0, int price = 0, float damage = 0, float armor = 0,
		string icon = "", string img = "", string effect1 = "", string effect2 = "", string effect3 = "");
};
