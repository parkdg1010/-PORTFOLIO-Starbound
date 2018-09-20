#pragma once
#include "weapon.h"
class meleeWeapon : public weapon
{
protected:
	image* _effect[3];
	int _atkWidth;
	int _atkHeight;
	int _atkCombo; //3회 공격
	int _atkDelay; //콤보딜레이 딜레이 안에 공격이 다시 들어와야 콤보공격으로 다음 이펙트가 나온다.
public:
	virtual HRESULT init(ITEM name = ITEM_NONE, int price = 0, float damage = 0, float armor = 0,
		image* icon = NULL, image* img = NULL);
	virtual void update();
	virtual void render();
	virtual void release();

	virtual void setup(image* effect1 = NULL, image* effect2 = NULL, image* effect3 = NULL);
	virtual void attack() {};

public:
	meleeWeapon() { gameObject::init(); }
	~meleeWeapon() {}
};