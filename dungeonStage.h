#pragma once
#include "gameStage.h"
class dungeonStage : public gameStage
{
public:
	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();

	dungeonStage() {}
	~dungeonStage() {}
};

