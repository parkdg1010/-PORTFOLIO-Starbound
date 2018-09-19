#pragma once
#include "gameObject.h"
#include "tileNode.h"

class gameItem : public gameObject
{
protected:
	Synthesize(string, _name, Name) //������ �̸�
	Synthesize(image*, _icon, Icon) //�κ��丮 ������
	Synthesize(image*, _img, Img)	//������ �⺻�̹���
	Synthesize(int, _rarity, Rarity)//���

public:
	virtual HRESULT init(ITEM name = ITEM_NONE, int price = 0, float damage = 0, float armor = 0,
		image* icon = NULL, image* img = NULL, int rarity = 0);
	virtual void update();
	virtual void render();
	virtual void release();

	virtual void setup() {}

	virtual void use() {}	//������ ���

	gameItem() { gameObject::init(); }
	~gameItem() {}
};