#include "stdafx.h"
#include "dungeonStage.h"

HRESULT dungeonStage::init()
{
	gameStage::init();

	_stageNum = 2;

	return S_OK;
}

void dungeonStage::update()
{
	gameStage::update();
}

void dungeonStage::render()
{
	gameStage::render();
}

void dungeonStage::release()
{
	gameStage::release();
}
