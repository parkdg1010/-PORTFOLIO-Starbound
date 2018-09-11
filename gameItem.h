#pragma once
#include "gameObject.h"
#include "tileNode.h"

class gameItem : public gameObject
{
protected:
	string _name;		//아이템 이름
	image* _icon;		//인벤토리 아이콘
	image* _img;		//아이템 기본이미지
public:
	virtual HRESULT init(ITEM name = ITEM_NONE, int price = 0, float damage = 0, float armor = 0,
		image* icon = NULL, image* img = NULL);
	virtual void update();
	virtual void render();
	virtual void release();

	gameItem() { gameObject::init(); }
	~gameItem() {}
};

class itemFactory
{
public:
	//아이템 기본
	//이미지 변수로 초기화
	gameItem* createItem(ITEM itemType = ITEM_NONE, int price = 0, float damage = 0, float armor = 0,
		image* icon = NULL, image* img = NULL);
	//이미지키값으로 초기화
	gameItem* createItem(ITEM itemType = ITEM_NONE, int price = 0, float damage = 0, float armor = 0,
		string icon = "", string img = "");
};