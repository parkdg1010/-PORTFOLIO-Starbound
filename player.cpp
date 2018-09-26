#include "stdafx.h"
#include "player.h"
#include "gameStage.h"
#include "enemyManager.h"
#include "warpUI.h"

HRESULT player::init()
{
	initImage();

	_oldX = _oldY = 0;

	_speed = 5.f;

	_jumpCount = 0;

	(_dir == LEFT) ? (_angle = 180) : (_angle = 0);

	_isActive = true;

	_longJumpValue = 0;

	_damagedCount = 0;
	_isDamaged = false;
	_damagedAlpha = 255;

	_gravity = 0;

	if (_inventory == NULL)
	{
		_inventory = new inventory;
		_inventory->init();
	}

	if (_warpUI == NULL)
	{
		_warpUI = new warpUI;
		_warpUI->linkPlayer(this);
		_warpUI->init();
	}

	if (_hpBar == NULL)
	{
		_hpBar = new progressBar;
		_hpBar->init("Texture/character/hpbar", "", 61, 31, 123, 16);
	}

	if (_energyBar == NULL)
	{
		_energyBar = new progressBar;
		_energyBar->init("Texture/character/energybar", "", 61, 49, 123, 16);
	}

	_isWarpOnline = true;

	_stage = NULL;
	_enemyManager = NULL;
	_mapPixel = NULL;

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

		_hpBar->setGauge(_hp, PLAYER_CONST::MAX_HP);
		_hpBar->update();

		_energyBar->setGauge(_energy, PLAYER_CONST::MAX_ENERGY);
		_energyBar->update();

		_inventory->getInvenHP()->setGauge(_hp, PLAYER_CONST::MAX_HP);
		_inventory->update();

		_warpUI->update();

		_weapon = dynamic_cast<weapon*>(_inventory->getCurWeapon());
		if (_weapon != NULL)
		{
			_weapon->setPosition(_x, _y+5, _dir);
			_weapon->setAngle(_handAngle + PI*1.5f);
			_weapon->update();
			if (_stage != NULL)	_weapon->linkMapPixel(_stage->getPixelBuffer());
			else _weapon->linkMapPixel(_mapPixel);
			_weapon->linkEnemyManager(_enemyManager);
		}

		if (_isDamaged)
		{
			DELAYCOUNT(_damagedCount, 20);

			if (_damagedCount % 3 == 0)
				_damagedAlpha = 100;
			else
				_damagedAlpha = 255;

			if (_damagedCount == 0)
			{
				_isDamaged = false;
				_damagedAlpha = 255;
			}
		}
	}
	else
	{
		setPosition(1600, 430, _dir);
		_isActive = true;
	}
}

void player::render()
{
	if (_isActive)
	{
		DELAYCOUNT(_count, 18);
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
			if (_damagedAlpha != 255)
			{
				_img[_state]->alphaFrameRender(getMemDC(), _x - _img[_state]->getFrameWidth()*0.5f - CAM->getX(),
					_y - _img[_state]->getFrameHeight() * 0.5f - CAM->getY(), _curFrameX, _curFrameY, _damagedAlpha);
			}
			else
			{
				_img[_state]->frameRender(getMemDC(), _x - _img[_state]->getFrameWidth()*0.5f - CAM->getX(),
					_y - _img[_state]->getFrameHeight() * 0.5f - CAM->getY(), _curFrameX, _curFrameY);
			}
		}
		else
		{
			//팔 회전각도, 위치조정, 무기타입마다 팔 각도가 다르다
			if (_weapon->getCategory() == TAG_RANGEDWEAPON)
			{
				_handAngle = utl::getAngle(_x, _y, _ptMouse.x + CAM->getX(), _ptMouse.y + CAM->getY());
				_handAngle += (PI * 2.5f);
			}
			else if (_weapon->getCategory() == TAG_MELEEWEAPON)
			{
				switch (dynamic_cast<meleeWeapon*>(_weapon)->getAtkCombo())
				{
				case 0:
					_handAngle = 0;
					break;
				case 1:
					if (_dir == RIGHT)
					{
						if (_handAngle <= PI_2)
							_handAngle += RAD_TO_DEG(15);
					}
					else
					{
						if (_handAngle <= PI*1.5)
							_handAngle += RAD_TO_DEG(375);
					}
					break;
				case 2:
					//
					break;
				case 3:
					break;
				}
			}
			else
			{
				_handAngle = RAD_TO_DEG(10);
			}
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
			
			_hand[RIGHT]->rotateFrameRender(getMemDC(), _x + temp.x - 2 - CAM->getX(), _y + temp.y + 5 - CAM->getY(), 0, _dir, _handAngle);
			if (_damagedAlpha != 255)
			{
				_nohandImg[_state]->alphaFrameRender(getMemDC(), _x - _nohandImg[_state]->getFrameWidth()*0.5f - CAM->getX(),
					_y - _nohandImg[_state]->getFrameHeight() * 0.5f - CAM->getY(), _curFrameX, _curFrameY, _damagedAlpha);
			}
			else
			{
				_nohandImg[_state]->frameRender(getMemDC(), _x - _nohandImg[_state]->getFrameWidth()*0.5f - CAM->getX(),
					_y - _nohandImg[_state]->getFrameHeight() * 0.5f - CAM->getY(), _curFrameX, _curFrameY);
			}
			if(_dir == RIGHT)
				_hand[LEFT]->rotateFrameRender(getMemDC(), _x + temp.x - CAM->getX(), _y + temp.y - CAM->getY(), 0, _dir, _handAngle);
			else
				_hand[LEFT]->rotateFrameRender(getMemDC(), _x + temp.x - CAM->getX(), _y + temp.y - CAM->getY(), 0, _dir, _handAngle);
		}

		if (_weapon != NULL)
		{
			_weapon->render();
		}

		drawUI();
	}
}

void player::release()
{
}

void player::inputKey()
{
	_axisX = NONE;

	if (KEYMANAGER->isOnceKeyDown(' '))
	{
		if (_jumpCount < 2)
		{
			++_jumpCount;
			changeState(JUMP);
			//점프이펙트
			if (_jumpCount == 1)
			{
				for (int i = 0; i < RND->getFromIntTo(6,3); ++i)
				{
					EFFECTMANAGER->play("JUMP_DUST", _x+RND->getInt(30)-RND->getInt(30), _y+PLAYER_CONST::HEIGHT*0.5f);
				}
			}
		}
		_axisY = UP;
	}
	else if (KEYMANAGER->isStayKeyDown(' '))
	{
		if (_longJumpValue < 7 && (_state == JUMP || _state == FALL))
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

	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		if (!_inventory->getIsActive())
		{
			_inventory->setIsActive(true);
			SOUNDMANAGER->play("인벤토리열기", _effectVolume);
			_warpUI->setIsActive(false);
		}
		else
		{
			_inventory->setIsActive(false);
			SOUNDMANAGER->play("인벤토리닫기", _effectVolume);
		}
	}
	
	//기본은 워프가능상태지만, enemy가 워프감지렉트에 충돌하면 워프가 불가능하게 되어있음
	_isWarpOnline = true;
	if (_enemyManager != NULL)
	{
		RECT temp;
		vector<enemy*> vE = _enemyManager->getEnemy();
		for (int i = 0; i < vE.size(); ++i)
		{
			if (IntersectRect(&temp, &_rcWarpOnline, &vE[i]->getHitBox()))
			{
				_isWarpOnline = false;
			}
		}
	}

	
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		if (_isWarpOnline)
		{
			if (!_warpUI->getIsActive())
			{
				_warpUI->setIsActive(true);
				_inventory->setIsActive(false);
			}
			else
				_warpUI->setIsActive(false);
		}
		else
		{
			_warpUI->setIsActive(false); //warpUI창을 연상태에서 몹을 만나도 닫을수 있게
		}
	}

	if (_weapon != NULL)
	{
		//인벤토리, 워프ui가 닫혀있어야 공격가능
		if (!_inventory->getIsActive() && !_warpUI->getIsActive())
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_weapon->attack();
				if (dynamic_cast<meleeWeapon*>(_weapon))
				{
					dynamic_cast<meleeWeapon*>(_weapon)->setAtkCombo(dynamic_cast<meleeWeapon*>(_weapon)->getAtkCombo() + 1);
				}
			}
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
	_gravity += _gravityAccel;	//24, 29, 32 세가지로 나누자

	if (_axisY == UP)
	{
		if (_state == JUMP && _jumpCount < 2)
		{
			_y += _speed * -sinf(PI*0.5);
			updateHitbox();
		}
	}

	if (_axisY == DOWN)
	{
		if (_state == JUMP)
		{
			changeState(FALL);
			updateHitbox();
		}
	}

	//_y가 +=_gravity해서 0.5f 더해진 만큼 여유를 주고 FALL검사
	if (_y > _oldY + 0.32f) //이전보다 아래로 떨어져있으면
	{
		if (_state == JUMP)
			_gravity += -sinf(PI*0.5) * _speed; //중력값에서 점프거리를 빼서 자연스런 낙하
		
		if(!_keepWalk)
			changeState(FALL);
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
	this->collideStage(_speed);
	this->collideObject();
}

bool player::collideStage(int range)
{
	updateHitbox();

	bool upCollision = false;
	COLORREF color;
	int r, g, b;

	if (_stage != NULL)
	{
		//맵밖으로 못나가게
		if (_x - PLAYER_CONST::WIDTH * 0.5f < 0)
		{
			_x = PLAYER_CONST::WIDTH * 0.5f;
		}

		if (_x + PLAYER_CONST::WIDTH * 0.5f > _stage->getTileX() * TILESIZE)
		{
			_x = _stage->getTileX() * TILESIZE - PLAYER_CONST::WIDTH * 0.5f;
		}

		if (_y - PLAYER_CONST::HEIGHT * 0.5f < 0)
		{
			_y = PLAYER_CONST::HEIGHT * 0.5f;
		}

		if (_y + PLAYER_CONST::HEIGHT * 0.5f > _stage->getTileY() * TILESIZE)
		{
			_y = _stage->getTileY() * TILESIZE - PLAYER_CONST::HEIGHT * 0.5f;
		}

		//_speed값 만큼 벽을 뚫고 나갔을 경우 뚫고나간 현재 위치(x,y,에서 보정한 값)에서 
		// 벽 반대쪽으로 _speed값만을 벽방향으로 1픽셀(i값)씩 검사하면 된다.

		//위쪽 검사
		for (int i = _y - PLAYER_CONST::HEIGHT * 0.5f + range; i >= _y - PLAYER_CONST::HEIGHT * 0.5f; --i)
		{
			color = GetPixel(_stage->getPixelBuffer()->getMemDC(), _x, i);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 0 && g == 0 && b == 255)
			{
				_y = i + PLAYER_CONST::HEIGHT * 0.5f;
				updateHitbox();
				upCollision = true;
				break;
			}
		}

		//아래쪽 검사
		//WALK상태 FALL상태에 대해 처리해야함
		if (_state == WALK) _keepWalk = 15;
		else _keepWalk = 0;

		for (int i = _y + PLAYER_CONST::HEIGHT * 0.5f - range; i <= _y + PLAYER_CONST::HEIGHT * 0.5f + _keepWalk; ++i)
		{
			color = GetPixel(_stage->getPixelBuffer()->getMemDC(), _x, i);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			//타일
			if (r == 0 && g == 0 && b == 255)
			{
				_y = i - PLAYER_CONST::HEIGHT * 0.5f;
				updateHitbox();
				_gravity = 0;
				if (_state == FALL)
					changeState(IDLE);
				_axisY = NONE;
				_longJumpValue = 0;
				_jumpCount = 0;
				break;
			}
			//발판
			else if (r == 0 && g == 255 && b == 0)
			{
				if (_axisY == DOWN && _state == FALL)
				{
					_longJumpValue = 8;
					_jumpCount = 1;
				}
				else
				{
					_y = i - PLAYER_CONST::HEIGHT * 0.5f;
					updateHitbox();
					_gravity = 0;
					if (_state == FALL)
						changeState(IDLE);
					_axisY = NONE;
					_longJumpValue = 0;
					_jumpCount = 0;
					break;
				}
			}
		}

		//왼쪽 검사
		for (int i = _x - PLAYER_CONST::WIDTH * 0.5f + range; i >= _x - PLAYER_CONST::WIDTH * 0.5f; --i)
		{
			color = GetPixel(_stage->getPixelBuffer()->getMemDC(), i, _y);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 0 && g == 0 && b == 255)
			{
				_x = i + PLAYER_CONST::WIDTH * 0.5f;
				updateHitbox();
				break;
			}
		}

		//오른쪽 검사
		for (int i = _x + PLAYER_CONST::WIDTH * 0.5f - range; i <= _x + PLAYER_CONST::WIDTH * 0.5f; ++i)
		{
			color = GetPixel(_stage->getPixelBuffer()->getMemDC(), i, _y);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 0 && g == 0 && b == 255)
			{
				_x = i - PLAYER_CONST::WIDTH * 0.5f;
				updateHitbox();
				break;
			}
		}
	}
	else if (_mapPixel != NULL)
	{
		//위쪽 검사
		for (int i = _y - PLAYER_CONST::HEIGHT * 0.5f + range; i >= _y - PLAYER_CONST::HEIGHT * 0.5f; --i)
		{
			color = GetPixel(_mapPixel->getMemDC(), _x, i);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 0 && g == 0 && b == 255)
			{
				_y = i + PLAYER_CONST::HEIGHT * 0.5f;
				updateHitbox();
				upCollision = true;
				break;
			}
		}

		//아래쪽 검사
		//WALK상태 FALL상태에 대해 처리해야함
		if (_state == WALK) _keepWalk = 15;
		else _keepWalk = 0;

		for (int i = _y + PLAYER_CONST::HEIGHT * 0.5f - range; i <= _y + PLAYER_CONST::HEIGHT * 0.5f + _keepWalk; ++i)
		{
			color = GetPixel(_mapPixel->getMemDC(), _x, i);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			//타일
			if (r == 0 && g == 0 && b == 255)
			{
				_y = i - PLAYER_CONST::HEIGHT * 0.5f;
				updateHitbox();
				_gravity = 0;
				if (_state == FALL)
					changeState(IDLE);
				_axisY = NONE;
				_longJumpValue = 0;
				_jumpCount = 0;
				break;
			}
			//발판
			else if (r == 0 && g == 255 && b == 0)
			{
				if (_axisY == DOWN && _state == FALL)
				{
					_longJumpValue = 8;
					_jumpCount = 1;
				}
				else
				{
					_y = i - PLAYER_CONST::HEIGHT * 0.5f;
					updateHitbox();
					_gravity = 0;
					if (_state == FALL)
						changeState(IDLE);
					_axisY = NONE;
					_longJumpValue = 0;
					_jumpCount = 0;
					break;
				}
			}
		}

		//왼쪽 검사
		for (int i = _x - PLAYER_CONST::WIDTH * 0.5f + range; i >= _x - PLAYER_CONST::WIDTH * 0.5f; --i)
		{
			color = GetPixel(_mapPixel->getMemDC(), i, _y);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 0 && g == 0 && b == 255)
			{
				_x = i + PLAYER_CONST::WIDTH * 0.5f;
				updateHitbox();
				break;
			}
		}

		//오른쪽 검사
		for (int i = _x + PLAYER_CONST::WIDTH * 0.5f - range; i <= _x + PLAYER_CONST::WIDTH * 0.5f; ++i)
		{
			color = GetPixel(_mapPixel->getMemDC(), i, _y);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 0 && g == 0 && b == 255)
			{
				_x = i - PLAYER_CONST::WIDTH * 0.5f;
				updateHitbox();
				break;
			}
		}
	}
	return false;
}

bool player::collideObject(gameObject * gObject)
{
	return false;
}

void player::damaged(gameObject * actor)
{
	if (!_isDamaged)
	{
		_hp -= actor->getDamage();
		_isDamaged = true;
	}
	//TODO : 데미지받을때 깜빡임
	if (_hp <= 0)
	{
		_hp = 0;
		EFFECTMANAGER->play("PLAYER_DEATH", _x, _y);
		//씬전환해서 우주선으로 가버리자
		setPosition(3350, 750, RIGHT);
		SCENEMANAGER->loadScene("우주선");

		_isActive = false;
		_hp = PLAYER_CONST::MAX_HP;
	}
}

void player::damaged(float damage)
{
	if (!_isDamaged)
	{
		_hp -= damage;
		_isDamaged = true;
	}
	//TODO : 데미지받을때 깜빡임
	if (_hp < 0)
	{
		_hp = 0;
		EFFECTMANAGER->play("PLAYER_DEATH", _x, _y);
		//씬전환해서 우주선으로 가버리자
		setPosition(3350, 750, RIGHT);
		SCENEMANAGER->loadScene("우주선");

		_isActive = false;
		_hp = PLAYER_CONST::MAX_HP;
	}
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

	_rcWarpOnline = RectMakeCenter((int)_x, (int)_y, PLAYER_CONST::WIDTH * 13, PLAYER_CONST::HEIGHT * 3);
}

void player::direction()
{
	if (_x > _ptMouse.x + CAM->getX()) _dir = LEFT;
	else if (_x <= _ptMouse.x + CAM->getX()) _dir = RIGHT;
	
	float temp = utl::getAngle(_x, _y, _ptMouse.x + CAM->getX(), _ptMouse.y + CAM->getY());
}

void player::drawUI()
{
	HDC uiDC = UIMANAGER->getUIDC();
	_inventory->render();
	_portraitUI->render(uiDC);
	_hpBar->render(uiDC);
	_energyBar->render(uiDC);
	_warpUI->render();
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

	_portraitUI = IMAGEMANAGER->findImage("portraitUI");
}