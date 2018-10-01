#include "stdafx.h"
#include "bullet.h"

HRESULT bullet::init(float radius, float speed, float damage, float range, const char * imageName)
{
	if (strcmp(imageName, "����") != 0) //���ڿ� ���Լ� strcmp 
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
	else if(!rotate) _image->frameRender(getMemDC(), _x-CAM->getX(), _y-CAM->getY(), _index, _dir); //�⺻����
	else _image->rotateFrameRender(getMemDC(), _x - CAM->getX(), _y - CAM->getY(), _index, 0, _angle); //ȸ������
}

void bullet::release()
{
}

void bullet::fire(float fireX, float fireY, float fireAngle, string soundKey)
{
	if (strcmp(soundKey.c_str(), "����") != 0) //���ڿ� ���Լ� strcmp
		SOUNDMANAGER->play(soundKey, _effectVolume);

	setFireCenter(fireX, fireY);
	_angle = fireAngle;
	_index = 0;
	_isActive = true;
}

bool bullet::collideMap(string pixelImageName)
{
	//���� �浹�ҋ�
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

	//��Ÿ� ���
	float distance = getDistance(_fireX, _fireY, _x, _y);
	if (_range < distance)
	{
		_isActive = false;
	}

	//�÷��̾�� �浹�� ������
	return false;
}

bool bullet::collideMap(image * pixelImage)
{
	//���� �浹�ҋ�
	if (pixelImage == NULL) return false;

	COLORREF color = GetPixel(pixelImage->getMemDC(), _x, _y);
	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);
	if (!(r == 255 && g == 0 && b == 255))
	{
		if (_isActive) _isActive = false;

		//���ı�
		if (_isDirtDrill)
		{
			tagTile hitTemp = _stage[int(_y / TILESIZE) * _tileXY.x + int(_x / TILESIZE)];
			tagTile hitAround[8];
			hitAround[0] = _stage[int(_y / TILESIZE) * _tileXY.x + int(_x / TILESIZE) - 1];			//����
			hitAround[1] = _stage[(int(_y / TILESIZE) - 1) * _tileXY.x + int(_x / TILESIZE)];		//����
			hitAround[2] = _stage[(int(_y / TILESIZE)) * _tileXY.x + int(_x / TILESIZE) + 1];		//������
			hitAround[3] = _stage[(int(_y / TILESIZE) + 1) * _tileXY.x + int(_x / TILESIZE)];		//�Ʒ���
			hitAround[4] = _stage[(int(_y / TILESIZE) + 1) * _tileXY.x + int(_x / TILESIZE) - 1];	//���ʾƷ�
			hitAround[5] = _stage[(int(_y / TILESIZE) - 1) * _tileXY.x + int(_x / TILESIZE) + 1];	//��������
			hitAround[6] = _stage[(int(_y / TILESIZE) + 1) * _tileXY.x + int(_x / TILESIZE) + 1];	//�����ʾƷ�
			hitAround[7] = _stage[(int(_y / TILESIZE) - 1) * _tileXY.x + int(_x / TILESIZE) - 1];	//�����ʾƷ�

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

	//��Ÿ� ���
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
