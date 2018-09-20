#pragma once
#include "gameItem.h"

class enemyManager;
class weapon : public gameItem
{
protected:
	image* _effect[3];
	enemyManager* _enemyManager;
public:
	virtual HRESULT init(ITEM name = ITEM_NONE, int price = 0, float damage = 0, float armor = 0,
		image* icon = NULL, image* img = NULL);
	virtual void update();
	virtual void render();
	virtual void release();

	virtual void setup(image* effect1 = NULL, image* effect2 = NULL, image* effect3 = NULL);
	virtual void fire() {};

	void linkEnemyManager(enemyManager* em) { _enemyManager = em; }

	weapon() { gameObject::init(); }
	~weapon() {}
};