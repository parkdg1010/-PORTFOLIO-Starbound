#pragma once
#include "weapon.h"
class meleeWeapon : public weapon
{
protected:
	image* _effect[3];
	int _atkWidth;
	int _atkHeight;
	int _atkCombo; //3ȸ ����
	int _atkDelay; //�޺������� ������ �ȿ� ������ �ٽ� ���;� �޺��������� ���� ����Ʈ�� ���´�.
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