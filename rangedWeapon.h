#pragma once
#include "weapon.h"
#include "bullet.h"
class rangedWeapon : public weapon
{
protected:
	image * _effect[3];
	vector<bullet>* _vBullet;
	float _fireX, _fireY;
public:
	virtual HRESULT init(ITEM name = ITEM_NONE, int price = 0, float damage = 0, float armor = 0,
		image* icon = NULL, image* img = NULL);
	virtual void update();
	virtual void render();
	virtual void release();

	virtual void setup(image* effect1 = NULL, image* effect2 = NULL, image* effect3 = NULL);
	virtual void fire() {};
	vector<bullet>* getVBullet() { return _vBullet; }

public:
	rangedWeapon() { gameObject::init(); _vBullet = NULL; }
	~rangedWeapon() {}
};
