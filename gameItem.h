#pragma once
#include "gameObject.h"
#include "tileNode.h"

class gameItem : public gameObject
{
	string _name;
	image* _icon;
	image* _img;
	image* _effect[3];
public:
	virtual HRESULT init(ITEM name = ITEM_NONE, int price = 0, float damage = 0, float armor = 0,
		image* icon = NULL, image* img = NULL, image* effect1 = NULL, image* effect2 = NULL, image* effect3 = NULL);
	virtual void update();
	virtual void render();
	virtual void release();

	gameItem() { gameObject::init(); }
	~gameItem() {}
};

class itemFactory
{
public:
	//�̹��� ������ �ʱ�ȭ
	gameItem* createItem(ITEM itemName = ITEM_NONE, int price = 0, float damage = 0, float armor = 0,
		image* icon = NULL, image* img = NULL, image* effect1 = NULL, image* effect2 = NULL, image* effect3 = NULL);
	//�̹���Ű������ �ʱ�ȭ
	gameItem* createItem(ITEM itemName = ITEM_NONE, int price = 0, float damage = 0, float armor = 0,
		string icon = "", string img = "", string effect1 = "", string effect2 = "", string effect3 = "");
};