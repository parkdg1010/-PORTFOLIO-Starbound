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
	//������ �⺻
	//�̹��� ������ �ʱ�ȭ
	gameItem * createItem(ITEM itemType = ITEM_NONE, int price = 0, float damage = 0, float armor = 0,
		image* icon = NULL, image* img = NULL, image* effect1 = NULL, image* effect2 = NULL, image* effect3 = NULL);
	//�̹���Ű������ �ʱ�ȭ
	gameItem* createItem(ITEM itemType = ITEM_NONE, int price = 0, float damage = 0, float armor = 0,
		string icon = "", string img = "", string effect1 = "", string effect2 = "", string effect3 = "");
};
