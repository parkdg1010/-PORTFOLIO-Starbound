#pragma once
#include "weapon.h"
class meleeWeapon : public weapon
{
protected:
	int _atkWidth;
	int _atkHeight;
	int _atkDelay; //콤보딜레이 딜레이 안에 공격이 다시 들어와야 콤보공격으로 다음 이펙트가 나온다.
	Synthesize(int, _atkCombo, AtkCombo) //3회 공격
	Synthesize(bool, _effectPlay, EffectPlay)
public:
	virtual HRESULT init(CATEGORY tag = TAG_MELEEWEAPON, string name = "SWORD", int rarity = 0, int price = 0
		, float damage = 0, float armor = 0, image* icon = NULL, image* img = NULL
		, image* effect1 = NULL, image* effect2 = NULL, image* effect3 = NULL);
	virtual void update();
	virtual void render();
	virtual void release();

	virtual void attack() {};

public:
	meleeWeapon() { gameObject::init(); }
	~meleeWeapon() {}
};