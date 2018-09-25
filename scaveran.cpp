#include "stdafx.h"
#include "scaveran.h"
#include "player.h"

HRESULT scaveran::init()
{
	enemy::init();

	_speed = 3;
	_hp = 60;

	_picR = IMAGEMANAGER->findImage("SCAVERAN_R");
	_picL = IMAGEMANAGER->findImage("SCAVERAN_L");

	for (int i = 0; i < 6; i++)
	{
		_imgR[i] = new animation;
		_imgR[i]->init(_picR->getWidth(), _picR->getHeight(), 10, 4);
		_imgR[i]->setFPS(1);

		_imgL[i] = new animation;
		_imgL[i]->init(_picL->getWidth(), _picL->getHeight(), 10, 4);
		_imgL[i]->setFPS(1);
	}

	_imgR[SCAVERAN_CONST::IDLE]->setPlayFrame(1, 1);
	_imgR[SCAVERAN_CONST::IDLE_BOBUP]->setPlayFrame(3, 5);
	_imgR[SCAVERAN_CONST::IDLE_BOBSIDE]->setPlayFrame(8, 9);
	_imgR[SCAVERAN_CONST::IDLE_BOBDOWN]->setPlayFrame(11, 13);
	_imgR[SCAVERAN_CONST::MOVE]->setPlayFrame(29, 32);
	_imgR[SCAVERAN_CONST::HURT]->setPlayFrame(34, 34);

	_imgL[SCAVERAN_CONST::IDLE]->setPlayFrame(1, 1);
	_imgL[SCAVERAN_CONST::IDLE_BOBUP]->setPlayFrame(3, 5);
	_imgL[SCAVERAN_CONST::IDLE_BOBSIDE]->setPlayFrame(8, 9);
	_imgL[SCAVERAN_CONST::IDLE_BOBDOWN]->setPlayFrame(11, 13);
	_imgL[SCAVERAN_CONST::MOVE]->setPlayFrame(29, 32);
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
		DELAYCOUNT(_stateDelay, 60);
		if (_stateDelay == 0)
		{
			_state = RND->getInt(2);
		}
		//평소엔 IDLE과 MOVE를 랜덤하게 오고감
		break;
	case SCAVERAN_CONST::HURT:
		DELAYCOUNT(_stateDelay, 60);
		if (_stateDelay == 0)
		{
			_state = SCAVERAN_CONST::MOVE;
		}
		//데미지 받으면 이상태로 바꾸고 딜레이후 적절한 상태로 변경
		break;
	case SCAVERAN_CONST::MOVE:
		//평소엔 IDLE과 MOVE를 랜덤하게 오고감
		//평소에는 랜덤한 방향으로 움직이다 플레이어가 가까이 다가오면 감지하고 일정거리까지 따라옴
	case SCAVERAN_CONST::JUMP:
		//TODO 앞쪽 픽셀이 너무 높으면 점프함
	case SCAVERAN_CONST::FALL:
		move();
		//허공에서 충돌 안되면 FALL상태
		break;
	case SCAVERAN_CONST::SHOOT:
		bltFire();
		//감지범위에 플레이어가 있으면 멈춰서서 화염방사
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

void scaveran::render()
{
	if (_dir == RIGHT)
	{
		_picR->aniRender(getMemDC(), int(_x - (_imgR[_state]->getFrameWidth() >> 1) - CAM->getX()),
			int(_y - (_imgR[_state]->getFrameHeight() >> 1) - CAM->getY()), _imgR[_state]); //비트연산 *0.5
	}
	else if (_dir == LEFT)
	{
		_picL->aniRender(getMemDC(), int(_x - (_imgL[_state]->getFrameWidth() >> 1) - CAM->getX()),
			int(_y - (_imgL[_state]->getFrameHeight() >> 1) - CAM->getY()), _imgL[_state]); //비트연산 *0.5
	}
}

void scaveran::release()
{
	for (int i = 0; i < 6; ++i)
	{
		SAFE_DELETE(_imgR[i]);
		SAFE_DELETE(_imgL[i]);
	}
}


void scaveran::move()
{
	_oldX = _x;
	_oldY = _y;

	//플레이어 감지
	if (_isSearch)
	{
		float moveAngle = utl::getAnglePL(_x, _y, _player->getX(), _player->getY());
		_x += _speed * cosf(moveAngle);
		updateHitbox();
		//y는 점프해야함
	}
	//감지없이 무브로 들어오면
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

	_y += _gravity; //걸을떄 0이 안들어감 계속 충돌
	_gravity += 0.29f; //24, 29, 32 세가지로 나누자

	if (_state == SCAVERAN_CONST::JUMP)
	{
		_y += _speed * -sinf(PI*0.5);
		updateHitbox();
	}

	//_y가 +=_gravity해서 0.5f 더해진 만큼 여유를 주고 FALL검사
	if (_y > _oldY + 0.32f) //이전보다 아래로 떨어져있으면
	{
		if (_state == SCAVERAN_CONST::JUMP)
			_gravity += -sinf(PI*0.5) * _speed; //중력값에서 점프거리를 빼서 자연스런 낙하

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

	//맵밖으로 못나가게
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

	//_speed값 만큼 벽을 뚫고 나갔을 경우 뚫고나간 현재 위치(x,y,에서 보정한 값)에서 
	// 벽 반대쪽으로 _speed값만을 벽방향으로 1픽셀(i값)씩 검사하면 된다.

	//위쪽 검사
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

	//아래쪽 검사
	//WALK상태 FALL상태에 대해 처리해야함
	if (_state == SCAVERAN_CONST::MOVE) _keepWalk = 15;
	else _keepWalk = 0;

	for (int i = _y + SCAVERAN_CONST::HEIGHT * 0.5f - range; i <= _y + SCAVERAN_CONST::HEIGHT * 0.5f + _keepWalk; ++i)
	{
		color = GetPixel(_mapPixel->getMemDC(), (int)_x, i);
		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		//타일
		if (r == 0 && g == 0 && b == 255)
		{
			_y = i - SCAVERAN_CONST::HEIGHT * 0.5f;
			updateHitbox();
			_gravity = 0;
			if (_state == SCAVERAN_CONST::FALL) _state = SCAVERAN_CONST::IDLE;
			break;
		}
	}

	//왼쪽 검사
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

	//오른쪽 검사
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
	_state = SCAVERAN_CONST::HURT; //데미지 받으면 상태변경
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

