#include "stdafx.h"
#include "fennix.h"
#include "player.h"

HRESULT fennix::init()
{
	enemy::init();

	_speed = 2;
	_hp = 100;

	_picR = IMAGEMANAGER->findImage("FENNIX_R");
	_picL = IMAGEMANAGER->findImage("FENNIX_L");

	for (int i = 0; i < 6; i++)
	{
		_imgR[i] = new animation;
		_imgR[i]->init(_picR->getWidth(), _picR->getHeight(), 10, 4);
		_imgR[i]->setFPS(1);

		_imgL[i] = new animation;
		_imgL[i]->init(_picL->getWidth(), _picL->getHeight(), 10, 4);
		_imgL[i]->setFPS(1);
	}

	_imgR[FENNIX_CONST::IDLE]->setPlayFrame(1, 7);
	_imgR[FENNIX_CONST::HURT]->setPlayFrame(9,9);
	_imgR[FENNIX_CONST::MOVE]->setPlayFrame(11,16);
	_imgR[FENNIX_CONST::JUMP]->setPlayFrame(18,19);
	_imgR[FENNIX_CONST::FALL]->setPlayFrame(21,22);
	_imgR[FENNIX_CONST::SHOOT]->setPlayFrame(27,30);

	_imgL[FENNIX_CONST::IDLE]->setPlayFrame(1, 7);
	_imgL[FENNIX_CONST::HURT]->setPlayFrame(9, 9);
	_imgL[FENNIX_CONST::MOVE]->setPlayFrame(11, 16);
	_imgL[FENNIX_CONST::JUMP]->setPlayFrame(18, 19);
	_imgL[FENNIX_CONST::FALL]->setPlayFrame(21, 22);
	_imgL[FENNIX_CONST::SHOOT]->setPlayFrame(27, 30);

	_vBullet = new vector<bullet>;
	bullet blt;
	blt.init(24, 2, 3, 400, "flameImg");
	for (int i = 0; i < 30; ++i)
	{
		blt.setFrameDelay(28);
		_vBullet->push_back(blt);
	}

	_fireDelay = 0;
	_wanderDelay = 0;

	return S_OK;
}

void fennix::update()
{
	if (_isSearch)
	{
		if (_player->getX() > _x)
		{
			_dir = RIGHT;
		}
		else
		{
			_dir = LEFT;
		}
	}

	switch (_state)
	{
	case FENNIX_CONST::IDLE:
		DELAYCOUNT(_stateDelay, 60);
		if (_stateDelay == 0)
		{
			_state = RND->getInt(2);
		}
		//��ҿ� IDLE�� MOVE�� �����ϰ� ����
		break;
	case FENNIX_CONST::HURT:
		//������ ������ �̻��·� �ٲٰ� �������� ������ ���·� ����
		break;
	case FENNIX_CONST::MOVE:
		//��ҿ� IDLE�� MOVE�� �����ϰ� ����
		//��ҿ��� ������ �������� �����̴� �÷��̾ ������ �ٰ����� �����ϰ� �����Ÿ����� �����
	case FENNIX_CONST::JUMP:
		//���� �ȼ��� �ʹ� ������ ������
	case FENNIX_CONST::FALL:
		move();
		//������� �浹 �ȵǸ� FALL����
		break;
	case FENNIX_CONST::SHOOT:
		bltFire();
		//���������� �÷��̾ ������ ���缭�� ȭ�����
		break;
	}
	collide();

	_searchingRc = RectMakeCenter((int)_x, (int)_y, 600, 600);
	_fireRc = RectMakeCenter((int)_x, (int)_y, 320, 320);
	POINT p = { (LONG)_player->getX(), (LONG)_player->getY() };

	if (PtInRect(&_searchingRc, p) && !_isFire)	_isSearch = true;
	else _isSearch = false;
	if (PtInRect(&_fireRc, p)) _isFire = true;
	else _isFire = false;

	if (_dir == RIGHT)
	{
		if (!_imgR[_state]->isPlay())
		{
			_imgR[_state]->start();
		}
		_imgR[_state]->frameUpdate(0.12f);
	}
	else if (_dir == LEFT)
	{
		if (!_imgL[_state]->isPlay())
		{
			_imgL[_state]->start();
		}
		_imgL[_state]->frameUpdate(0.12f);
	}
}

void fennix::render()
{
	if (_dir == RIGHT)
	{
		_picR->aniRender(getMemDC(), int(_x - (_imgR[_state]->getFrameWidth() >> 1) - CAM->getX()),
			int(_y - (_imgR[_state]->getFrameHeight() >> 1) - CAM->getY()), _imgR[_state]); //��Ʈ���� *0.5
	}
	else if (_dir == LEFT)
	{
		_picL->aniRender(getMemDC(), int(_x - (_imgL[_state]->getFrameWidth() >> 1) - CAM->getX()),
			int(_y - (_imgL[_state]->getFrameHeight() >> 1) - CAM->getY()), _imgL[_state]); //��Ʈ���� *0.5
	}
}

void fennix::release()
{
	for (int i = 0; i < 6; ++i)
	{
		SAFE_DELETE(_imgR[i]);
		SAFE_DELETE(_imgL[i]);
	}
}

void fennix::bltFire()
{
	//TODO : �Ҹ������� õõ�� �����ϰ�, �߻������ �ֱ�
	if (_isFire)
	{
		DELAYCOUNT(_fireDelay, 12);
		if (_fireDelay == 0)
		{
			for (int i = 0; i < _vBullet->size(); ++i)
			{
				if (_vBullet->at(i).getIsActive()) continue;

				//EFFECTMANAGER->play("red_Pulse_Cannon_Explosion", (int)_vPlasmaBall[temp].getX(), (int)_vPlasmaBall[temp].getY());
				_vBullet->at(i).fire(_x, _y, utl::getAnglePL(_x, _y, _player->getX(), _player->getY()));
				break;
			}
		}
	}
	else
	{
		_state = FENNIX_CONST::IDLE;
	}
}

void fennix::bltUpdate()
{
	//ȭ�����
	for (int i = 0; i < _vBullet->size(); ++i)
	{
		_vBullet->at(i).update();
		if (_mapPixel != NULL)
		{
			_vBullet->at(i).collideMap(_mapPixel);
		}
	}
}

void fennix::bltRender()
{
	//ȭ�����
	for (int i = 0; i < _vBullet->size(); ++i)
	{
		_vBullet->at(i).render(true);
	}
}

void fennix::move()
{
	if (_isFire)
	{
		_state = FENNIX_CONST::SHOOT;
		return;
	}

	_oldX = _x;
	_oldY = _y;

	//�÷��̾� ����
	if(_isSearch)
	{
		float moveAngle = utl::getAnglePL(_x, _y, _player->getX(), _player->getY());
		_x += _speed * cosf(moveAngle);
		updateHitbox();
		//y�� �����ؾ���
	}
	//�������� ����� ������
	else
	{
		DELAYCOUNT(_wanderDelay, 180);
		if (_wanderDelay == 0)
		{
			_wanderDirection = RND->getInt(2);
		}
		if (_wanderDirection == 0) _dir = RIGHT;
		else _dir = LEFT;
		_x += (_speed-0.5f) * cosf(PI * _wanderDirection);
	}

	_y += _gravity; //������ 0�� �ȵ� ��� �浹
	_gravity += 0.29f; //24, 29, 32 �������� ������

	if (_state == FENNIX_CONST::JUMP)
	{
		_y += _speed * -sinf(PI*0.5);
		updateHitbox();
	}

	//_y�� +=_gravity�ؼ� 0.5f ������ ��ŭ ������ �ְ� FALL�˻�
	if (_y > _oldY + 0.32f) //�������� �Ʒ��� ������������
	{
		if (_state == FENNIX_CONST::JUMP)
			_gravity += -sinf(PI*0.5) * _speed; //�߷°����� �����Ÿ��� ���� �ڿ����� ����

		if (!_keepWalk)
			_state = FENNIX_CONST::FALL;
	}
}

void fennix::collide()
{
	collideStage((int)_speed);
}

bool fennix::collideStage(int range)
{
	updateHitbox();

	bool upCollision = false;
	COLORREF color;
	int r, g, b;

	//�ʹ����� ��������
	if (_x - FENNIX_CONST::WIDTH * 0.5f < 0)
	{
		_x = FENNIX_CONST::WIDTH * 0.5f;
	}

	if (_x + FENNIX_CONST::WIDTH * 0.5f > _mapPixel->getWidth())
	{
		_x = _mapPixel->getWidth() - FENNIX_CONST::WIDTH * 0.5f;
	}

	if (_y - FENNIX_CONST::HEIGHT * 0.5f < 0)
	{
		_y = FENNIX_CONST::HEIGHT * 0.5f;
	}

	if (_y + FENNIX_CONST::HEIGHT * 0.5 > _mapPixel->getHeight())
	{
		_y = _mapPixel->getHeight() - FENNIX_CONST::HEIGHT * 0.5f;
	}

	//_speed�� ��ŭ ���� �հ� ������ ��� �հ��� ���� ��ġ(x,y,���� ������ ��)���� 
	// �� �ݴ������� _speed������ ���������� 1�ȼ�(i��)�� �˻��ϸ� �ȴ�.

	//���� �˻�
	for (int i = _y - FENNIX_CONST::HEIGHT * 0.5f + range; i >= _y - FENNIX_CONST::HEIGHT * 0.5f; --i)
	{
		color = GetPixel(_mapPixel->getMemDC(), (int)_x, i);
		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		if (r == 0 && g == 0 && b == 255)
		{
			_y = i + FENNIX_CONST::HEIGHT * 0.5f;
			updateHitbox();
			upCollision = true;
			break;
		}
	}

	//�Ʒ��� �˻�
	//WALK���� FALL���¿� ���� ó���ؾ���
	if (_state == FENNIX_CONST::MOVE) _keepWalk = 15;
	else _keepWalk = 0;

	for (int i = _y + FENNIX_CONST::HEIGHT * 0.5f - range; i <= _y + FENNIX_CONST::HEIGHT * 0.5f + _keepWalk; ++i)
	{
		color = GetPixel(_mapPixel->getMemDC(), (int)_x, i);
		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		//Ÿ��
		if (r == 0 && g == 0 && b == 255)
		{
			_y = i - FENNIX_CONST::HEIGHT * 0.5f;
			updateHitbox();
			_gravity = 0;
			if (_state == FENNIX_CONST::FALL) _state = FENNIX_CONST::IDLE;
				//changeState(FENNIX_CONST::IDLE);
			break;
		}
	}

	//���� �˻�
	for (int i = _x - FENNIX_CONST::WIDTH * 0.5f + range; i >= _x - FENNIX_CONST::WIDTH * 0.5f; --i)
	{
		color = GetPixel(_mapPixel->getMemDC(), i, (int)_y);
		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		if (r == 0 && g == 0 && b == 255)
		{
			_x = i + FENNIX_CONST::WIDTH * 0.5f;
			updateHitbox();
			break;
		}
	}

	//������ �˻�
	for (int i = _x + FENNIX_CONST::WIDTH * 0.5f - range; i <= _x + FENNIX_CONST::WIDTH * 0.5f; ++i)
	{
		color = GetPixel(_mapPixel->getMemDC(), i, (int)_y);
		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		if (r == 0 && g == 0 && b == 255)
		{
			_x = i - FENNIX_CONST::WIDTH * 0.5f;
			updateHitbox();
			break;
		}
	}

	return false;
}

bool fennix::collideObject(gameObject * gameObject)
{
	return false;
}

void fennix::damaged(gameObject * actor)
{
}

void fennix::updateHitbox()
{
	_hitBox = RectMakeCenter((int)_x, (int)_y, _picL->getFrameWidth(), _picL->getFrameHeight());
}
