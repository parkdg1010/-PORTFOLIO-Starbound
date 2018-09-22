#pragma once
#include "gameObject.h"
#include "tileNode.h"

class gameItem : public gameObject
{
protected:
	Synthesize(string, _name, Name)				//아이템 이름
	Synthesize(image*, _icon, Icon)				//인벤토리 아이콘
	Synthesize(image*, _img, Img)				//아이템 기본이미지
	Synthesize(int, _rarity, Rarity)			//레어도
	Synthesize(CATEGORY, _category, Category)	//카테고리

public:
	virtual HRESULT init(CATEGORY tag = TAG_USEABLE, string name = "NONE", int rarity = 0, int price = 0, 
		float damage = 0, float armor = 0, image* icon = NULL, image* img = NULL);
	virtual void update();
	virtual void render();
	virtual void release();

	virtual void setup() {}

	virtual void use() {}	//아이템 사용

	gameItem() { gameObject::init(); }
	~gameItem() {}
};