#include "stdafx.h"
#include "gameStage.h"
#include "kluexboss.h"
#include "player.h"

HRESULT kluexboss::init()
{
	enemy::init();

	_phase1 = new kluexbossPh1;
	_phase1->setPosition(_x, _y, _dir);
	_phase1->linkPlayer(_player);		//에너미매니저에서 받은 포인터를 그대로 넘겨주기만 하면 되니까 이 cpp는 player를 include할 필요가 없다.
	_phase1->linkMapPixel(_mapPixel);
	_phase1->init();

	_phase2 = new kluexbossPh2;
	_phase2->setPosition(_x, _y, _dir);
	_phase2->linkPlayer(_player);
	_phase2->linkMapPixel(_mapPixel);
	_phase2->init();

	_hpBar = new progressBar;
	_hpBar->init("Texture/enemy/monsters/boss/bosshealthFront", "Texture/enemy/monsters/boss/bosshealthBack", WINSIZEX*0.36f, WINSIZEY*0.8f, 480, 39);

	_deadGravity = 0;
	bullet temp;
	temp.init(3.f, 0, 0, WINSIZEX, "kluexCrystalImg");
	for (int i = 0; i < RND->getFromIntTo(15,5); ++i)
	{
		_deadEffect[0].push_back(temp);
		_deadEffect[0][i].setSpeed(6 + RND->getFloat(2));
	}
	temp.init(3.f, 0, 0, WINSIZEX, "kluexCrystalShardImg");
	for (int i = 0; i < RND->getFromIntTo(15,5); ++i)
	{
		_deadEffect[1].push_back(temp);
		_deadEffect[1][i].setSpeed(4 + RND->getFloat(2));
	}
	temp.init(3.f, 0, 0, WINSIZEX, "kluexStatueShardImg");
	for (int i = 0; i < RND->getFromIntTo(20,10); ++i)
	{
		_deadEffect[2].push_back(temp);
		_deadEffect[2][i].setSpeed(2 + RND->getFloat(2));
	}
	_isDeadEffect = false;

	_currentPhase = _phase1;

	return S_OK;
}

void kluexboss::update()
{
	if (_isStandby)
	{
		_hitBox = _currentPhase->getHitBox();
		//_isActive = _currentPhase->getIsActive();
		_currentPhase->update();
		_hpBar->update();
		_hpBar->setGauge(_currentPhase->getHp(), KLUEX_PH1_CONST::MAX_HP);
		_x = _currentPhase->getX();
		_y = _currentPhase->getY();

		if (!_phase1->getIsActive())
		{
			//죽음이펙트
			if (!_isDeadEffect)
			{
				for (int i = 0; i < 3; ++i)
				{
					for (int j = 0; j < _deadEffect[i].size(); ++j)
					{
						if (_deadEffect[i][j].getIsActive()) continue;

						_deadEffect[i][j].fire(_x, _y, PI_2 + (RND->getFloat(PI_8) - RND->getFloat(PI_8))*2);
					}
				}
				_isDeadEffect = true;
			}

			_deadGravity += 0.3f;
			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < _deadEffect[i].size(); ++j)
				{
					_deadEffect[i][j].update();
					_deadEffect[i][j].setGravity(_deadGravity);

					if (_deadEffect[i][j].getIsActive())
					{
						if (_mapPixel != NULL)
						{
							_deadEffect[i][j].collideMap(_mapPixel);
						}
					}
				}
			}

			if (!_phase2->getIsActive())
			{

			}
			else
			{
			}
		}
		else
		{
		}
	}
	else
	{
		POINT p = { _player->getX(), _player->getY() };
		_rcStandby = RectMakeCenter(_x, _y, WINSIZEX, WINSIZEY);
		if (PtInRect(&_rcStandby, p))
		{
			_isStandby = true;
		}
	}
}

void kluexboss::render()
{
	if (_isStandby)
	{
		_currentPhase->render();
		_hpBar->render(UIMANAGER->getUIDC());

		if (!_phase1->getIsActive())
		{
			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < _deadEffect[i].size(); ++j)
				{
					_deadEffect[i][j].render(true);
				}
			}

			if (!_phase2->getIsActive())
			{

			}
			else
			{
			}
		}
		else
		{
		}
	}
}

void kluexboss::release()
{
	_phase1->release();
	SAFE_DELETE(_phase1);
	_phase2->release();
	SAFE_DELETE(_phase2);
}

void kluexboss::bltUpdate()
{
	if(_isStandby)
		_currentPhase->bltUpdate();
}

void kluexboss::bltRender()
{
	if(_isStandby)
		_currentPhase->bltRender();
}

void kluexboss::move()
{
	if(_isStandby)
		_currentPhase->move();
}

void kluexboss::collide()
{
	if(_isStandby)
		_currentPhase->collide();
}

bool kluexboss::collideObject(gameObject* gameObject)
{
	return _currentPhase->collideObject(gameObject);
}

void kluexboss::damaged(gameObject * actor)
{
	_currentPhase->damaged(actor);
	if (!_phase1->getIsActive())
	{
		//TODO 죽으면 이펙트 or 페이즈2
		SOUNDMANAGER->play("보스죽음", _effectVolume);
		//_phase2->setIsActive(true);
		if (!_phase2->getIsActive())
		{

		}
	}
}

void kluexboss::drawUI()
{
}