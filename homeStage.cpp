#include "stdafx.h"
#include "homeStage.h"

HRESULT homeStage::init()
{
	gameStage::init();

	_stageNum = 1;
	_treeLightsCount = _treeLightsIdx = _ornatetorchCount = _ornatetorchIdx = 0;

	return S_OK;
}

void homeStage::update()
{
	gameStage::update();

	_treeLightsCount = (_treeLightsCount + 1) % 15;
	if (_treeLightsCount == 0)	_treeLightsIdx = RND->getInt(2);
	_ornatetorchCount = (_ornatetorchCount + 1) % 22;
	if (_ornatetorchCount == 0) _ornatetorchIdx = RND->getInt(4);
}

void homeStage::render()
{
	gameStage::render();

	int startX = (CAM->getX()) / TILESIZE - 2;
	int startY = (CAM->getY()) / TILESIZE - 2;
	int endX = (CAM->getX() + WINSIZEX) / TILESIZE + 2;
	int endY = (CAM->getY() + WINSIZEY) / TILESIZE + 2;

	if (startX < 0) startX = 0;
	if (startY < 0) startY = 0;
	if (endX >= _tileX) endX = _tileX;
	if (endY >= _tileY) endY = _tileY;

	for (int i = startY; i < endY; ++i)
	{
		for (int j = startX; j < endX; ++j)
		{
			image* curRender = NULL;
			switch (_stage[i * _tileX + j].object)
			{
			case OBJECT_WOODENCRATE1:
				curRender = _woodencrate1;
				break;
			case OBJECT_TREELIGHTS:
				_treeLights->frameRender(getMemDC(),
					_stage[i*_tileX + j].rc.left - 10 - CAM->getX(),
					_stage[i*_tileX + j].rc.top - 10 - CAM->getY(), _treeLightsIdx, _stage[i*_tileX + j].objFrameY);
				break;
			case OBJECT_ORNATETORCH:
				_ornatetorch->frameRender(getMemDC(),
					_stage[i*_tileX + j].rc.left - 10 - CAM->getX(),
					_stage[i*_tileX + j].rc.top - 10 - CAM->getY(), _ornatetorchIdx, _stage[i*_tileX + j].objFrameY);
				break;
			case OBJECT_FF_WOOD:
				curRender = _flatform;
				break;
				//TODO : 오브젝트 렌더
				//CHECK : 일일이 하는건 에바같은데 더 나은 방법을 생각해보자
			}
			if (curRender != NULL)
				curRender->frameRender(getMemDC(),
					_stage[i*_tileX + j].rc.left - 10 - CAM->getX(),
					_stage[i*_tileX + j].rc.top - 10 - CAM->getY(),
					_stage[i*_tileX + j].objFrameX,
					_stage[i*_tileX + j].objFrameY);
		}
	}
}

void homeStage::release()
{
	gameStage::release();
}
