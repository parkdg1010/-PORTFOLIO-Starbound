#pragma once
#include "gameNode.h"
class endingScene : public gameNode
{
	int _index;
	int _count;
	int _alpha;
public:
	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();

	endingScene() {}
	~endingScene() {}
};

