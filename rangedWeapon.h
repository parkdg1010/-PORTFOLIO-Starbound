#pragma once
#include "weapon.h"
#include "bullet.h"
class rangedWeapon : public weapon
{
protected:
	vector<bullet>* _vBullet;
	float _fireX, _fireY;
public:
	virtual HRESULT init(CATEGORY tag = TAG_RANGEDWEAPON, string name = "GUN", int rarity = 0, int price = 0
		, float damage = 0, float armor = 0, image* icon = NULL, image* img = NULL
		, image* effect1 = NULL, image* effect2 = NULL, image* effect3 = NULL);
	virtual void update();
	virtual void render();
	virtual void release();

	virtual void attack() {};
	vector<bullet>* getVBullet() { return _vBullet; }

public:
	rangedWeapon() { gameObject::init(); _vBullet = NULL; }
	~rangedWeapon() {}
};
