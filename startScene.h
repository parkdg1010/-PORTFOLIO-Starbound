#pragma once
#include "gameNode.h"

class player;
class startScene : public gameNode
{
private:
	image* _ui[4];
	RECT _rcUi[4];
	int _buttonLight[4];
	image* _space;
	image* _star;
	image* _earth;
	image* _logo;
	float _angle;
	bool _soundOption;

	player* _player;
public:
	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();

	void buttonLighting(int index);

	startScene() {}
	~startScene() {}
};

