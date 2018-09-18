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

	virtual void setup() {}

	gameItem() { gameObject::init(); }
	~gameItem() {}
};