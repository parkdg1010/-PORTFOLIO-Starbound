#pragma once
#include "gameObject.h"
#include "tileNode.h"

class gameItem : public gameObject
{
protected:
	string _name;		//������ �̸�
	image* _icon;		//�κ��丮 ������
	image* _img;		//������ �⺻�̹���
public:
	virtual HRESULT init(ITEM name = ITEM_NONE, int price = 0, float damage = 0, float armor = 0,
		image* icon = NULL, image* img = NULL);
	virtual void update();
	virtual void render();
	virtual void release();

	gameItem() { gameObject::init(); }
	~gameItem() {}
};

class itemFactory
{
public:
	//������ �⺻
	//�̹��� ������ �ʱ�ȭ
	gameItem* createItem(ITEM itemType = ITEM_NONE, int price = 0, float damage = 0, float armor = 0,
		image* icon = NULL, image* img = NULL);
	//�̹���Ű������ �ʱ�ȭ
	gameItem* createItem(ITEM itemType = ITEM_NONE, int price = 0, float damage = 0, float armor = 0,
		string icon = "", string img = "");
};