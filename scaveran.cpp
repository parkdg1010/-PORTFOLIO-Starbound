#include "stdafx.h"
#include "scaveran.h"
#include "player.h"

HRESULT scaveran::init()
{
	enemy::init();

	_speed = 2.4f;
	_hp = 60;
	_damage = 1.f;

	_picR = IMAGEMANAGER->findImage("SCAVERAN_R");
	_picL = IMAGEMANAGER->findImage("SCAVERAN_L");

	for (int i = 0; i < 8; i++)
	{
		_imgR[i] = new animation;
		_imgR[i]->init(_picR->getWidth(), _picR->getHeight(), 7, 5);
		_imgR[i]->setFPS(1);

		_imgL[i] = new animation;
		_imgL[i]->init(_picL->getWidth(), _picL->getHeight(), 7, 5);
		_imgL[i]->setFPS(1);
	}

	_imgR[SCAVERAN_CONST::IDLE]->setPlayFrame(1, 1);
	_imgR[SCAVERAN_CONST::IDLE_BOBUP]->setPlayFrame(3, 5);
	_imgR[SCAVERAN_CONST::IDLE_BOBSIDE]->setPlayFrame(8, 9);
	_imgR[SCAVERAN_CONST::IDLE_BOBDOWN]->setPlayFrame(11, 13);
	_imgR[SCAVERAN_CONST::MOVE]->setPlayFrame(29, 32);
	_imgR[SCAVERAN_CONST::JUMP]->setPlayFrame(29, 32);
	_imgR[SCAVERAN_CONST::FALL]->setPlayFrame(29, 32);
	_imgR[SCAVERAN_CONST::HURT]->setPlayFrame(34, 34);

	_imgL[SCAVERAN_CONST::IDLE]->setPlayFrame(1, 1);
	_imgL[SCAVERAN_CONST::IDLE_BOBUP]->setPlayFrame(3, 5);
	_imgL[SCAVERAN_CONST::IDLE_BOBSIDE]->setPlayFrame(8, 9);
	_imgL[SCAVERAN_CONST::IDLE_BOBDOWN]->setPlayFrame(11, 13);
	_imgL[SCAVERAN_CONST::MOVE]->setPlayFrame(29, 32);
	_imgL[SCAVERAN_CONST::JUMP]->setPlayFrame(29, 32);
	_imgL[SCAVERAN_CONST::FALL]->setPlayFrame(29, 32);
	_imgL[SCAVERAN_CONST::HURT]->setPlayFrame(34, 34);

	_wanderDelay = 0;

	return S_OK;
}

void scaveran::update()
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
	case SCAVERAN_CONST::IDLE:
	case SCAVERAN_CONST::IDLE_BOBUP:
	case SCAVERAN_CONST::IDLE_BOBSIDE:
	case SCAVERAN_CONST::IDLE_BOBDOWN:
	case SCAVERAN_CONST::HURT:
		DELAYCOUNT(_stateDelay, 60);
		if (_stateDelay == 0)
		{
			_state = SCAVERAN_CONST::MOVE;
		}
		break;
	case SCAVERAN_CONST::MOVE:
	case SCAVERAN_CONST::JUMP:
	case SCAVERAN_CONST::FALL:
		move();
		DELAYCOUNT(_stateDelay, 60);
		if (_stateDelay == 0)
		{
			_state = RND->getInt(4);
		}
		//4���� IDLE������ 1���� ��� �����ѵ� ������·� �ٲ�
		break;
	}
	collide();

	_searchingRc = RectMakeCenter((int)_x, (int)_y, 600, 600);
	POINT p = { (LONG)_player->getX(), (LONG)_player->getY() };

	RECT temp;
	if (IntersectRect(&temp, &_hitBox, &_player->getHitBox()))
	{
		_player->damaged(this);
	}

	if (PtInRect(&_searchingRc, p))	_isSearch = true;
	else _isSearch = false;

	if (_dir == RIGHT)
	{
		if (!_imgR[_state]->isPlay())
		{
			_imgR[_state]->start();
		}
		_imgR[_state]->frameUpdate(0.16f);
	}
	else if (_dir == LEFT)
	{
		if (!_imgL[_state]->isPlay())
		{
			_imgL[_state]->start();
		}
		_imgL[_state]->frameUpdate(0.16f);
	}
}

void scaveran::render()
{
	if (_dir == RIGHT)
	{
		_picR->aniRender(getMemDC(), int(_x - (_imgR[_state]->getFrameWidth() >> 1) - CAM->getX()),
			int(_y - 20 - (_imgR[_state]->getFrameHeight() >> 1) - CAM->getY()), _imgR[_state]); //��Ʈ���� *0.5
	}
	else if (_dir == LEFT)
	{
		_picL->aniRender(getMemDC(), int(_x - (_imgL[_state]->getFrameWidth() >> 1) - CAM->getX()),
			int(_y - 20 - (_imgL[_state]->getFrameHeight() >> 1) - CAM->getY()), _imgL[_state]); //��Ʈ���� *0.5
	}
}

void scaveran::release()
{
	for (int i = 0; i < 8; ++i)
	{
		SAFE_DELETE(_imgR[i]);
		SAFE_DELETE(_imgL[i]);
	}
}


void scaveran::move()
{
	_oldX = _x;
	_oldY = _y;

	//�÷��̾� ����
	if (_isSearch)
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
		_x += (_speed - 0.5f) * cosf(PI * _wanderDirection);
	}

	_y += _gravity; //������ 0�� �ȵ� ��� �浹
	_gravity += 0.29f; //24, 29, 32 �������� ������

	if (_state == SCAVERAN_CONST::JUMP)
	{
		_y += _speed * -sinf(PI*0.5);
		updateHitbox();
	}

	//_y�� +=_gravity�ؼ� 0.5f ������ ��ŭ ������ �ְ� FALL�˻�
	if (_y > _oldY + 0.32f) //�������� �Ʒ��� ������������
	{
		if (_state == SCAVERAN_CONST::JUMP)
			_gravity += -sinf(PI*0.5) * _speed; //�߷°����� �����Ÿ��� ���� �ڿ����� ����

		if (!_keepWalk)
			_state = SCAVERAN_CONST::FALL;
	}
}

void scaveran::collide()
{
	collideStage((int)_speed);
}

bool scaveran::collideStage(int range)
{
	updateHitbox();

	bool upCollision = false;
	COLORREF color;
	int r, g, b;

	//�ʹ����� ��������
	if (_x - SCAVERAN_CONST::WIDTH * 0.5f < 0)
	{
		_x = SCAVERAN_CONST::WIDTH * 0.5f;
	}

	if (_x + SCAVERAN_CONST::WIDTH * 0.5f > _mapPixel->getWidth())
	{
		_x = _mapPixel->getWidth() - SCAVERAN_CONST::WIDTH * 0.5f;
	}

	if (_y - SCAVERAN_CONST::HEIGHT * 0.5f < 0)
	{
		_y = SCAVERAN_CONST::HEIGHT * 0.5f;
	}

	if (_y + SCAVERAN_CONST::HEIGHT * 0.5 > _mapPixel->getHeight())
	{
		_y = _mapPixel->getHeight() - SCAVERAN_CONST::HEIGHT * 0.5f;
	}

	//_speed�� ��ŭ ���� �հ� ������ ��� �հ��� ���� ��ġ(x,y,���� ������ ��)���� 
	// �� �ݴ������� _speed������ ���������� 1�ȼ�(i��)�� �˻��ϸ� �ȴ�.

	//���� �˻�
	for (int i = _y - SCAVERAN_CONST::HEIGHT * 0.5f + range; i >= _y - SCAVERAN_CONST::HEIGHT * 0.5f; --i)
	{
		color = GetPixel(_mapPixel->getMemDC(), (int)_x, i);
		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		if (r == 0 && g == 0 && b == 255)
		{
			_y = i + SCAVERAN_CONST::HEIGHT * 0.5f;
			updateHitbox();
			upCollision = true;
			break;
		}
	}

	//�Ʒ��� �˻�
	//WALK���� FALL���¿� ���� ó���ؾ���
	if (_state == SCAVERAN_CONST::MOVE) _keepWalk = 15;
	else _keepWalk = 0;

	for (int i = _y + SCAVERAN_CONST::HEIGHT * 0.5f - range; i <= _y + SCAVERAN_CONST::HEIGHT * 0.5f + _keepWalk; ++i)
	{
		color = GetPixel(_mapPixel->getMemDC(), (int)_x, i);
		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		//Ÿ��
		if (r == 0 && g == 0 && b == 255)
		{
			_y = i - SCAVERAN_CONST::HEIGHT * 0.5f;
			updateHitbox();
			_gravity = 0;
			if (_state == SCAVERAN_CONST::FALL) _state = SCAVERAN_CONST::IDLE;
			break;
		}
	}

	//���� �˻�
	for (int i = _x - SCAVERAN_CONST::WIDTH * 0.5f + range; i >= _x - SCAVERAN_CONST::WIDTH * 0.5f; --i)
	{
		color = GetPixel(_mapPixel->getMemDC(), i, (int)_y);
		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		if (r == 0 && g == 0 && b == 255)
		{
			_x = i + SCAVERAN_CONST::WIDTH * 0.5f;
			updateHitbox();
			break;
		}
	}

	//������ �˻�
	for (int i = _x + SCAVERAN_CONST::WIDTH * 0.5f - range; i <= _x + SCAVERAN_CONST::WIDTH * 0.5f; ++i)
	{
		color = GetPixel(_mapPixel->getMemDC(), i, (int)_y);
		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		if (r == 0 && g == 0 && b == 255)
		{
			_x = i - SCAVERAN_CONST::WIDTH * 0.5f;
			updateHitbox();
			break;
		}
	}

	return false;
}

bool scaveran::collideObject(gameObject * gameObject)
{
	return false;
}

void scaveran::damaged(gameObject * actor)
{
	_hp -= actor->getDamage();
	_state = SCAVERAN_CONST::HURT; //������ ������ ���º���
	if (_hp <= 0)
	{
		_hp = 0;
		_isActive = false;
	}
}

void scaveran::updateHitbox()
{
	_hitBox = RectMakeCenter((int)_x, (int)_y, SCAVERAN_CONST::WIDTH, SCAVERAN_CONST::HEIGHT);
}

