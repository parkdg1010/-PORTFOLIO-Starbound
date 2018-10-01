#include "stdafx.h"
#include "bullet.h"

HRESULT bullet::init(float radius, float speed, float damage, float range, const char * imageName)
{
	if (strcmp(imageName, "없음") != 0) //문자열 비교함수 strcmp 
		_image = IMAGEMANAGER->findImage(imageName);
	else
		_image = NULL;
	_radius = radius;
	_speed = speed;
	_range = range;
	_damage = damage;
	_isActive = false;
	_frameDelay = 7;

	_x = _y = _fireX = _fireY = 0;
	_angle = 0;
	_gravity = 0;
	_count = _index = 0;

	_isDirtDrill = false;

	_stage = SAVEDATA->getTiles();
	_tileXY = SAVEDATA->getTileXY();
	_stageBuffer = SAVEDATA->getStageBuffer();

	return S_OK;
}

HRESULT bullet::init(float radius, float speed, float damage, float range, image* image)
{
	if (image != NULL)
		_image = image;
	else
		_image = NULL;

	_radius = radius;
	_speed = speed;
	_range = range;
	_damage = damage;
	_isActive = false;
	_frameDelay = 7;

	_x = _y = _fireX = _fireY = 0;
	_angle = 0;
	_gravity = 0;
	_count = _index = 0;

	_isDirtDrill = false;

	_stage = SAVEDATA->getTiles();
	_tileXY = SAVEDATA->getTileXY();
	_stageBuffer = SAVEDATA->getStageBuffer();

	return S_OK;
}

void bullet::update()
{
	if (!_isActive) return;
		
	_x += _speed * cosf(_angle);
	_y += _speed * -sinf(_angle) + _gravity;
	if (getDistance(_fireX, _fireY, _x, _y) >= _range)
	{
		_isActive = false;
	}
	_hitBox = RectMakeCenter(_x, _y, _radius * 2, _radius * 2);

	if (_image != NULL)
	{
		_count = (_count + 1) % _frameDelay;
		if (_count == 0) ++_index;
		if (_index > _image->getMaxFrameX()) _index = 0;
	}
}

void bullet::render(bool rotate)
{
	if (!_isActive) return;

	if (_image == NULL) Ellipse(getMemDC(), _hitBox.left - CAM->getX(), _hitBox.top - CAM->getY(), _hitBox.right - CAM->getX(),_hitBox.bottom-CAM->getY());
	else if(!rotate) _image->frameRender(getMemDC(), _x-CAM->getX(), _y-CAM->getY(), _index, _dir); //기본렌더
	else _image->rotateFrameRender(getMemDC(), _x - CAM->getX(), _y - CAM->getY(), _index, 0, _angle); //회전렌더
}

void bullet::release()
{
}

void bullet::fire(float fireX, float fireY, float fireAngle, string soundKey)
{
	if (strcmp(soundKey.c_str(), "없음") != 0) //문자열 비교함수 strcmp
		SOUNDMANAGER->play(soundKey, _effectVolume);

	setFireCenter(fireX, fireY);
	_angle = fireAngle;
	_index = 0;
	_isActive = true;
}

bool bullet::collideMap(string pixelImageName)
{
	//벽과 충돌할떄
	if (IMAGEMANAGER->findImage(pixelImageName) == NULL) return false;

	COLORREF color = GetPixel(IMAGEMANAGER->findImage(pixelImageName)->getMemDC(), _x, _y);
	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);
	if (!(r == 255 && g == 0 && b == 255))
	{
		if(_isActive) _isActive = false;
		return true;
	}

	//사거리 벗어남
	float distance = getDistance(_fireX, _fireY, _x, _y);
	if (_range < distance)
	{
		_isActive = false;
	}

	//플레이어랑 충돌도 만들자
	return false;
}

bool bullet::collideMap(image * pixelImage)
{
	//벽과 충돌할떄
	if (pixelImage == NULL) return false;

	COLORREF color = GetPixel(pixelImage->getMemDC(), _x, _y);
	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);
	if (!(r == 255 && g == 0 && b == 255))
	{
		if (_isActive) _isActive = false;

		//땅파기
		if (_isDirtDrill)
		{
			tagTile hitTemp = _stage[int(_y / TILESIZE) * _tileXY.x + int(_x / TILESIZE)];
			tagTile hitAround[8];
			hitAround[0] = _stage[int(_y / TILESIZE) * _tileXY.x + int(_x / TILESIZE) - 1];			//왼쪽
			hitAround[1] = _stage[(int(_y / TILESIZE) - 1) * _tileXY.x + int(_x / TILESIZE)];		//위쪽
			hitAround[2] = _stage[(int(_y / TILESIZE)) * _tileXY.x + int(_x / TILESIZE) + 1];		//오른쪽
			hitAround[3] = _stage[(int(_y / TILESIZE) + 1) * _tileXY.x + int(_x / TILESIZE)];		//아래쪽
			hitAround[4] = _stage[(int(_y / TILESIZE) + 1) * _tileXY.x + int(_x / TILESIZE) - 1];	//왼쪽아래
			hitAround[5] = _stage[(int(_y / TILESIZE) - 1) * _tileXY.x + int(_x / TILESIZE) + 1];	//오른쪽위
			hitAround[6] = _stage[(int(_y / TILESIZE) + 1) * _tileXY.x + int(_x / TILESIZE) + 1];	//오른쪽아래
			hitAround[7] = _stage[(int(_y / TILESIZE) - 1) * _tileXY.x + int(_x / TILESIZE) - 1];	//오른쪽아래

			if (hitTemp.terrain != TR_NONE)
			{
				utl::painting(pixelImage->getMemDC(), hitTemp.rc, MAGENTA);
				utl::painting(_stageBuffer->getMemDC(), hitTemp.rc, MAGENTA);
			}

			for (int i = 0; i < 8; ++i)
			{
				if (hitAround[i].terrain == TR_NONE)
				{
					utl::painting(pixelImage->getMemDC(), hitAround[i].rc, MAGENTA);
					utl::painting(_stageBuffer->getMemDC(), hitAround[i].rc, MAGENTA);
				}
				else if (hitAround[i].terrain == TR_BRICK)
				{

				}
			}
		}

		return true;

	}

	//사거리 벗어남
	float distance = getDistance(_fireX, _fireY, _x, _y);
	if (_range < distance)
	{
		_isActive = false;
	}

	return false;
}

bool bullet::collideActor(gameObject* actor)
{
	if (!_isActive) return false;
	
	if (!actor->getIsActive()) return false;

	RECT temp;

	return IntersectRect(&temp, &actor->getHitBox(), &_hitBox);
}
