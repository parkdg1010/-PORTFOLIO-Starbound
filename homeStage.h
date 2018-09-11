#pragma once
#include "gameStage.h"
class homeStage : public gameStage
{
	int _treeLightsCount, _treeLightsIdx, _ornatetorchCount, _ornatetorchIdx;
public:
	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();

	homeStage() {}
	~homeStage() {}
};

