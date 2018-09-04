#pragma once
#include "gameObject.h"
class gameItem : public gameObject
{
	image* _icon;
	image* _img;
	image* _effect[3];
public:
	virtual HRESULT init(int price, float damage, float armor, image* icon = NULL, image* img = NULL, image* effect1 = NULL, image* effect2 = NULL, image* effect3 = NULL);
	virtual void update();
	virtual void render();
	virtual void release();

	gameItem() { gameObject::init(); }
	~gameItem() {}
};

