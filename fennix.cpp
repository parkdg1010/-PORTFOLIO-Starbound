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
		//평소엔 IDLE과 MOVE를 랜덤하게 오고감
		break;
	case FENNIX_CONST::HURT:
		//데미지 받으면 이상태로 바꾸고 딜레이후 적절한 상태로 변경
		break;
	case FENNIX_CONST::MOVE:
		//평소엔 IDLE과 MOVE를 랜덤하게 오고감
		//평소에는 랜덤한 방향으로 움직이다 플레이어가 가까이 다가오면 감지하고 일정거리까지 따라옴
	case FENNIX_CONST::JUMP:
		//앞쪽 픽셀이 너무 높으면 점프함
	case FENNIX_CONST::FALL:
		move();
		//허공에서 충돌 안되면 FALL상태
		break;
	case FENNIX_CONST::SHOOT:
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

void fennix::render()
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
	//TODO : 불릿프레임 천천히 돌게하고, 발사딜레이 주기
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
	//화염방사
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
	//화염방사
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

	//플레이어 감지
	if(_isSearch)
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
		_x += (_speed-0.5f) * cosf(PI * _wanderDirection);
	}

	_y += _gravity; //걸을떄 0이 안들어감 계속 충돌
	_gravity += 0.29f; //24, 29, 32 세가지로 나누자

	if (_state == FENNIX_CONST::JUMP)
	{
		_y += _speed * -sinf(PI*0.5);
		updateHitbox();
	}

	//_y가 +=_gravity해서 0.5f 더해진 만큼 여유를 주고 FALL검사
	if (_y > _oldY + 0.32f) //이전보다 아래로 떨어져있으면
	{
		if (_state == FENNIX_CONST::JUMP)
			_gravity += -sinf(PI*0.5) * _speed; //중력값에서 점프거리를 빼서 자연스런 낙하

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

	//맵밖으로 못나가게
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

	//_speed값 만큼 벽을 뚫고 나갔을 경우 뚫고나간 현재 위치(x,y,에서 보정한 값)에서 
	// 벽 반대쪽으로 _speed값만을 벽방향으로 1픽셀(i값)씩 검사하면 된다.

	//위쪽 검사
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

	//아래쪽 검사
	//WALK상태 FALL상태에 대해 처리해야함
	if (_state == FENNIX_CONST::MOVE) _keepWalk = 15;
	else _keepWalk = 0;

	for (int i = _y + FENNIX_CONST::HEIGHT * 0.5f - range; i <= _y + FENNIX_CONST::HEIGHT * 0.5f + _keepWalk; ++i)
	{
		color = GetPixel(_mapPixel->getMemDC(), (int)_x, i);
		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		//타일
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

	//왼쪽 검사
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

	//오른쪽 검사
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
