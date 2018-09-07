#include "stdafx.h"
#include "player.h"
#include "gameStage.h"

HRESULT player::init()
{
	_debugBuff = IMAGEMANAGER->addImage("test", 1280, 720, true);

	initImage();

	_oldX = _oldY = 0;

	_speed = 5.f;

	_jumpCount = 0;

	_dir = LEFT;

	(_dir == LEFT) ? (_angle = 180) : (_angle = 0);

	_isActive = true;

	_onGround = true;
	_longJumpValue = 0;

	return S_OK;
}

void player::update()
{
	if (_isActive)
	{
		direction();
		updateHitbox();
		inputKey();
		move();
		collide();
	}
	else
	{
		setPos(1600, 430);
		_isActive = true;
	}
}

void player::render()
{
	if (_isActive)
	{
		_count = (_count + 1) % 18;
		if (_count == 0)
		{
			++_curFrameX;
			if (_curFrameX > _img[_state]->getMaxFrameX())
			{
				_curFrameX = 0;
			}
		}
		_curFrameY = _dir;
		
		if (_weapon == NULL)
		{
			_img[_state]->frameRender(getMemDC(), _x - _img[_state]->getFrameWidth()*0.5 - CAM->getX(),
				_y - _img[_state]->getFrameHeight() * 0.5 - CAM->getY(), _curFrameX, _curFrameY);
		}
		else
		{
			//팔 회전각도, 위치조정
			float tempAngle = utl::getAngle(_x, _y, _ptMouse.x + CAM->getX(), _ptMouse.y + CAM->getY());
			if (KEYMANAGER->isOnceKeyDown(VK_F2))
				cout << tempAngle * 180 / PI << endl;

			if ((PI*0.5 < tempAngle && tempAngle < PI) || -PI < tempAngle && tempAngle < -PI * 0.5)
			{
				tempAngle += PI * 0.5;
			}
			tempAngle -= (PI * 1.75);
			POINT temp = { 0,0 };
			switch (_state)
			{
			case IDLE:
				temp.x = -4;
				temp.y = -3;
				break;
			case WALK:
			case RUN:
				temp.x = -2;
				temp.y = 2 + (_curFrameX % 2);
				break;
			case JUMP:
				temp.x = -3;
				temp.y = -3;
				break;
			case FALL:
				temp.x = -3;
				temp.y = +5;
				break;
			case CLIMB:
				break;
			case DUCK:
				break;
			}
			if (_dir == LEFT)
			{
				temp.x += 7;
				temp.y += 0;
			}
			
			_hand[RIGHT]->rotateFrameRender(getMemDC(), _x + temp.x - 2 - CAM->getX(), _y + temp.y + 5 - CAM->getY(), 0, _dir, tempAngle);
			_nohandImg[_state]->frameRender(getMemDC(), _x - _nohandImg[_state]->getFrameWidth()*0.5 - CAM->getX(),
				_y - _nohandImg[_state]->getFrameHeight() * 0.5 - CAM->getY(), _curFrameX, _curFrameY);
			if(_dir == RIGHT)
				_hand[LEFT]->rotateFrameRender(getMemDC(), _x + temp.x - CAM->getX(), _y + temp.y - CAM->getY(), 0, _dir, tempAngle);
			else
				_hand[LEFT]->rotateFrameRender(getMemDC(), _x + temp.x - CAM->getX(), _y + temp.y - CAM->getY(), 0, _dir, tempAngle);
		}
		//_hair->frameRender(getMemDC(), _x - _img[_state]->getFrameWidth()*0.5 - CAM->getX(), _y - _img[_state]->getFrameHeight() * 0.5 - CAM->getY(), 0, _curFrameY);
		//textMake(getMemDC(), _x - CAM->getX(), _y - CAM->getY(), "X");
		//textMake(getMemDC(), 100, 100, "중력", _gravity);
	}

	if (_isDebug)
	{
		_debugBuff->render(getMemDC());
		textMake(getMemDC(), _x - CAM->getX(), _y - CAM->getY(), "X");
		Sleep(100);
	}
}

void player::release()
{
}

void player::inputKey()
{
	_axisX = NONE;

	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		if (_jumpCount < 2)
		{
			++_jumpCount;
			changeState(JUMP);
		}
		_axisY = UP;
	}
	else if (KEYMANAGER->isStayKeyDown('W'))
	{
		if (_longJumpValue < 7)
		{
			_gravity -= 0.21f;
			_longJumpValue += 0.21f;
		}
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		_axisY = DOWN;
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_axisX = LEFT;

		if (_state != JUMP && _state != FALL)
		{
			changeState(WALK);
		}
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_axisX = RIGHT;

		if (_state != JUMP && _state != FALL)
		{
			changeState(WALK);
		}
	}
}

void player::move()
{
	_oldX = _x;
	_oldY = _y;

	if (_axisX == NONE && _axisY == NONE)
	{
		changeState(IDLE);
	}

	_y += _gravity; //걸을떄 0이 안들어감 계속 충돌
	_gravity += 0.29f; //24, 29, 32 세가지로 나누자

	if (_axisY == UP)
	{
		if (_state == JUMP && _jumpCount < 2)
		{
			_y += _speed * -sinf(PI*0.5);
			updateHitbox();
			_keepWalk = false;
		}
	}

	//_y가 +=_gravity해서 0.5f 더해진 만큼 여유를 주고 FALL검사
	if (_y > _oldY + 0.32f) //이전보다 아래로 떨어져있으면
	{
		if (_state == JUMP)
			_gravity += -sinf(PI*0.5) * _speed; //중력값에서 점프거리를 빼서 자연스런 낙하
		
		if(!_keepWalk)
			changeState(FALL);

		_onGround = false;
	}

	if (_axisY == DOWN)
	{
		//changeStage(DUCK);
		//_y += _speed;
		updateHitbox();
	}
	if (_axisX == LEFT)
	{
		_x += _speed * cosf(PI);
		updateHitbox();
	}
	if (_axisX == RIGHT)
	{
		_x += _speed * cosf(0);
		updateHitbox();
	}
}

void player::collide()
{
	this->collideStage();
	this->collideObject();
}

bool player::collideStage()
{
	updateHitbox();

	int curTileX, curTileY;
	bool upCollision = false;

	curTileX = _x / TILESIZE;
	curTileY = _y / TILESIZE;

	//맵밖으로 못나가게
	if (_x - PLAYER_CONST::WIDTH * 0.5 < 0)
	{
		_x = PLAYER_CONST::WIDTH * 0.5;
	}

	if (_x + PLAYER_CONST::WIDTH * 0.5 > _stage->getTileX() * TILESIZE)
	{
		_x = _stage->getTileX() * TILESIZE - PLAYER_CONST::WIDTH * 0.5;
	}

	if (_y - PLAYER_CONST::HEIGHT * 0.5 < 0)
	{
		_y = PLAYER_CONST::HEIGHT * 0.5;
	}

	if (_y + PLAYER_CONST::HEIGHT * 0.5 > _stage->getTileY() * TILESIZE)
	{
		_y = _stage->getTileY() * TILESIZE - PLAYER_CONST::HEIGHT * 0.5;
	}

	//위쪽 검사
	RECT temp = { 0,0,0,0 };
	if (_state == JUMP)
	{
		if (_stage->getStage()[(curTileX + (curTileY - 2) * _stage->getTileX())].frontBack == FRONT)
		{
			if (IntersectRect(&temp, &_stage->getStage()[(curTileX + (curTileY - 2) * _stage->getTileX())].rc, &_rcCollision)
				&& _stage->getStage()[(curTileX + (curTileY - 2) * _stage->getTileX())].terrain != TR_NONE)
			{
				_y += (temp.bottom - temp.top) *0.5;
				updateHitbox();
				upCollision = true;
			}
		}
	}

	//아래쪽 검사
	temp = { 0,0,0,0 };
	if (_stage->getStage()[(curTileX + (curTileY+2) * _stage->getTileX())].frontBack == FRONT)
	{
		if (IntersectRect(&temp, &_stage->getStage()[(curTileX + (curTileY + 2) * _stage->getTileX())].rc, &_rcCollision)
			&& _stage->getStage()[(curTileX + (curTileY + 2) * _stage->getTileX())].terrain != TR_NONE)
		{
			if (!_onGround || upCollision)
			{
				_onGround = true;
				_y -= (temp.bottom - temp.top) *0.5;
				updateHitbox();
				_axisY = NONE;
				_jumpCount = 0;
				changeState(IDLE);
			}
			_longJumpValue = 0;
			_gravity = 0;
		}
	}

	//좌우 검사
	if (_axisX == LEFT)
	{
		curTileX = (_x - PLAYER_CONST::WIDTH/2) / TILESIZE;
	}
	if (_axisX == RIGHT)
	{
		curTileX = (_x + PLAYER_CONST::WIDTH / 2) / TILESIZE;
	}

	tileIndex.push_back(curTileX + (curTileY - 1) * _stage->getTileX()); //비어있고
	tileIndex.push_back(curTileX + (curTileY) * _stage->getTileX()); //비어있고
	//tileIndex.push_back(curTileX + (curTileY + 1) * _stage->getTileX()); //채워져있으면 -> 걸어가자

	bool bodyCollision = false;

	for (int i = 0; i < tileIndex.size(); ++i)
	{
		temp = { 0,0,0,0 };
		if (_stage->getStage()[tileIndex[i]].frontBack == FRONT)
		{
			if (IntersectRect(&temp, &_stage->getStage()[tileIndex[i]].rc, &_rcCollision) 
				&& _stage->getStage()[tileIndex[i]].terrain != TR_NONE)
			{
				if (_axisX == LEFT)
				{
					_x += (temp.right - temp.left) * 0.5;
					updateHitbox();
					bodyCollision = true;
				}
				else if(_axisX == RIGHT)
				{
					_x -= (temp.right - temp.left) * 0.5;
					updateHitbox();
					bodyCollision = true;
				}
			}
		}
	}

	if (!bodyCollision && _state == WALK)
	{
		temp = { 0,0,0,0 };
		if (_stage->getStage()[(curTileX + (curTileY + 1) * _stage->getTileX())].frontBack == FRONT)
		{
			if (IntersectRect(&temp, &_stage->getStage()[(curTileX + (curTileY + 1) * _stage->getTileX())].rc, &_rcCollision)
				&& _stage->getStage()[(curTileX + (curTileY + 1) * _stage->getTileX())].terrain != TR_NONE)
			{
				_onGround = true;
				_keepWalk = true;
				_y -= (temp.bottom - temp.top) *0.5;
				updateHitbox();
				_gravity = 0;
			}
		}
	}

	if (_isDebug)
	{
		PatBlt(_debugBuff->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
		HBRUSH _myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
		SelectObject(_debugBuff->getMemDC(), _myBrush);
		for (int i = 0; i < tileIndex.size(); i++)
		{
			Rectangle(_debugBuff->getMemDC(), _stage->getStage()[tileIndex[i]].rc.left - CAM->getX(), _stage->getStage()[tileIndex[i]].rc.top - CAM->getY(), _stage->getStage()[tileIndex[i]].rc.right - CAM->getX(), _stage->getStage()[tileIndex[i]].rc.bottom - CAM->getY());
		}
	}
	
	tileIndex.clear();

	return false;
}

bool player::collideObject(gameObject * gameObject)
{
	return false;
}

void player::damaged(gameObject * actor)
{
	_hp -= actor->getDamage();
}

void player::changeState(STATE state)
{
	if (_state == state) return;

	_state = state;
	
	_curFrameX = 0;
}

void player::updateHitbox()
{
	_hitBox = RectMakeCenter((int)_x, (int)_y, PLAYER_CONST::WIDTH, PLAYER_CONST::HEIGHT);
	_rcCollision = _hitBox;
	_rcCollision.left += 1;
	_rcCollision.right -= 1;
	_rcCollision.top += 1;
	_rcCollision.bottom -= 1;
}

void player::direction()
{
	if (_x > _ptMouse.x + CAM->getX()) _dir = LEFT;
	else if (_x <= _ptMouse.x + CAM->getX()) _dir = RIGHT;
	
	float temp = utl::getAngle(_x, _y, _ptMouse.x + CAM->getX(), _ptMouse.y + CAM->getY());
}

void player::initImage()
{
	_img[IDLE] = IMAGEMANAGER->findImage("PLAYER_IDLE");
	_img[WALK] = IMAGEMANAGER->findImage("PLAYER_RUN");
	_img[RUN] = IMAGEMANAGER->findImage("PLAYER_RUN");
	_img[JUMP] = IMAGEMANAGER->findImage("PLAYER_JUMP");
	_img[FALL] = IMAGEMANAGER->findImage("PLAYER_FALL");
	_img[CLIMB] = IMAGEMANAGER->findImage("");
	_img[DUCK] = IMAGEMANAGER->findImage("");

	_hand[RIGHT] = IMAGEMANAGER->findImage("PLAYER_hand");
	_hand[LEFT] = IMAGEMANAGER->findImage("PLAYER_hand");
	_nohandImg[IDLE] = IMAGEMANAGER->findImage("noHand_PLAYER_IDLE");
	_nohandImg[WALK] = IMAGEMANAGER->findImage("noHand_PLAYER_RUN");
	_nohandImg[RUN] = IMAGEMANAGER->findImage ("noHand_PLAYER_RUN");
	_nohandImg[JUMP] = IMAGEMANAGER->findImage("noHand_PLAYER_JUMP");
	_nohandImg[FALL] = IMAGEMANAGER->findImage("noHand_PLAYER_FALL");
	_nohandImg[CLIMB] = IMAGEMANAGER->findImage("");
	_nohandImg[DUCK] = IMAGEMANAGER->findImage("");
}