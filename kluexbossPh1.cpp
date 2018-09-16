#include "stdafx.h"
#include "kluexbossPh1.h"
#include "player.h"

HRESULT kluexbossPh1::init()
{
	enemy::init();

	_hp = 2000;

	_pic = IMAGEMANAGER->findImage("BIRDBOSS1");

	_img[BOSS_MAIN] = new animation;
	_img[BOSS_MAIN]->init(_pic->getWidth(), _pic->getHeight(), 13, 3);
	_img[BOSS_MAIN]->setPlayFrame(0, 11, true);
	_img[BOSS_MAIN]->setFPS(1);

	_img[BOSS_FIRE] = new animation;
	_img[BOSS_FIRE]->init(_pic->getWidth(), _pic->getHeight(), 13, 3);
	_img[BOSS_FIRE]->setPlayFrame(13, 24, true);
	_img[BOSS_FIRE]->setFPS(1);

	_img[BOSS_ICE] = new animation;
	_img[BOSS_ICE]->init(_pic->getWidth(), _pic->getHeight(), 13, 3);
	_img[BOSS_ICE]->setPlayFrame(26, 37, true);
	_img[BOSS_ICE]->setFPS(1);

	_hitBox = RectMakeCenter(_x, _y, _img[BOSS_MAIN]->getFrameWidth(), _img[BOSS_MAIN]->getFrameHeight());

	_state = BOSS_MAIN;
	
	_activeP = BOSS_NONE;

	_vbullet = new vector<bullet>;
	bullet blt;
	blt.init(12, 5, 5, WINSIZEX* WINSIZEY, "energycrystalImg");
	for (int i = 0; i < 10; ++i)
	{
		_vbullet->push_back(blt);
	}

	bullet ball;
	ball.init(25, 0, 0, WINSIZEX, "kluexstaffplasmaImg");
	for (int i = 0; i < 5; ++i)
	{
		_vPlasmaBall.push_back(ball);
	}

	_plasmaCount = 0;
	_p1FireDelay = 1; //패턴 시작하자마자 다쏘는걸 막아보려고 1로 초기화함
	_p1FireCount = 0;
	_p1BallDelay = 0;

	_flatBoard = IMAGEMANAGER->findImage("pillarplatformImg");
	_flatBoardPixel = IMAGEMANAGER->findImage("pillarplatformPixelImg");
	_flatBoardPixelErase = IMAGEMANAGER->findImage("pillarplatformPixelEraserImg");
	_magma = IMAGEMANAGER->findImage("firefloorhazardImg");
	_boardY = 0;
	_magmaY = 0;
	_magmaLoopSPD = 0;
	_p2AniCount = 0;
	_p2Duration = 0;

	_iceblock = IMAGEMANAGER->findImage("iceeruptionImg");
	for (int i = 0; i < 8; ++i)
	{
		//업데이트에서 top만 크기바꾸면 된다.
		_iceHitBox[i] = RectMake(_x - _iceblock->getFrameWidth() * 4+ _iceblock->getFrameWidth()*i,
			0 ,_iceblock->getFrameWidth(), _y + _img[BOSS_MAIN]->getFrameHeight() * 0.5);
		_iceActive[i] = false;
	}
	_iceStart = false;

	return S_OK;
}

void kluexbossPh1::update()
{
	switch (_activeP)
	{
	case BOSS_NONE:
		//딜레이주고 랜덤으로 패턴바꾸기
		DELAYCOUNT(_patternDelay, 60);
		if (_patternDelay == 0)
			_activeP = RND->getFromIntTo(1, 3);
		_state = BOSS_MAIN;
		break;
	case BOSS_MAIN:
		_state = BOSS_MAIN;
		pattern1Update();
		break;
	case BOSS_FIRE: //TODO 상태가 너무 확바뀌는데 퀄 높일때 바꿔보자
		_state = BOSS_FIRE;
		pattern2Update();
		break;
	case BOSS_ICE:
		_state = BOSS_ICE;
		pattern3Update();
	}

	_img[_state]->frameUpdate(0.46f);
}

void kluexbossPh1::render()
{
	_pic->aniRender(getMemDC(), int(_x - (_img[_state]->getFrameWidth() >> 1) - CAM->getX()),
		int(_y - (_img[_state]->getFrameHeight() >> 1) - CAM->getY()), _img[_state]); //비트연산 *0.5
	
	switch (_activeP)
	{
	case BOSS_NONE:
		_state = BOSS_MAIN;
		break;
	case BOSS_MAIN:
		pattern1Render();
		break;
	case BOSS_FIRE:
		pattern2Render();
		break;
	case BOSS_ICE:
		pattern3Render();
		break;
	}
}

void kluexbossPh1::release()
{
	for (int i = 0; i < 3; ++i)
	{
		SAFE_DELETE(_img[i]);
	}
}

void kluexbossPh1::bltUpdate()
{
	for (int i = 0; i < _vbullet->size(); ++i)
	{
		_vbullet->at(i).update(); //벡터를 동적할당했을때 at을 통해 인덱스를 가져온다 at이 대괄호와 같은 의미로 사용
		if (_mapPixel != NULL)
		{
			_vbullet->at(i).collideMap(_mapPixel);
		}
	}
}

void kluexbossPh1::bltRender()
{
	for (int i = 0; i < _vbullet->size(); ++i)
	{
		_vbullet->at(i).render(true); //벡터를 동적할당했을때 at을 통해 인덱스를 가져온다 at이 대괄호와 같은 의미로 사용
	}
}

void kluexbossPh1::move()
{
}

void kluexbossPh1::collide()
{
}

bool kluexbossPh1::collideObject(gameObject * gameObject)
{
	return false;
}

void kluexbossPh1::damaged(gameObject * actor)
{
}

void kluexbossPh1::drawUI()
{
}

void kluexbossPh1::pattern1Update()
{
	//구슬 딜레이 넣어서 생성하기
	DELAYCOUNT(_p1BallDelay, 60);
	if (_p1BallDelay == 0)
	{
		if (_plasmaCount < _vPlasmaBall.size())
		{
			_img[_state]->start();
			if (!_vPlasmaBall[_plasmaCount].getIsActive())
			{
				_vPlasmaBall[_plasmaCount].fire(_x + 200 * cosf(_plasmaCount *PI*0.25f), _y + 200 * -sinf(_plasmaCount *PI*0.25f),
					utl::getAnglePL(_vPlasmaBall[_plasmaCount].getX(), _vPlasmaBall[_plasmaCount].getY(), _player->getX(), _player->getY()));
				++_plasmaCount;
			}
		}
	}

	if (_plasmaCount >= _vPlasmaBall.size())
	{
		DELAYCOUNT(_p1FireDelay, int(_hp * 0.03f));	//체력과 비례해서 발사딜레이 줄이기

		if (_p1FireDelay == 0 && _p1FireCount < 20)
		{
			for (int i = 0; i < _vbullet->size(); ++i)
			{
				if (_vbullet->at(i).getIsActive()) continue;

				int temp = RND->getInt(5);

				EFFECTMANAGER->play("red_Pulse_Cannon_Explosion", (int)_vPlasmaBall[temp].getX(), (int)_vPlasmaBall[temp].getY());
				_vbullet->at(i).fire(_vPlasmaBall[temp].getX(), _vPlasmaBall[temp].getY(),
					utl::getAnglePL(_vPlasmaBall[temp].getX(), _vPlasmaBall[temp].getY(), _player->getX(), _player->getY()));
				++_p1FireCount;
				break;
			}
		}

		if (_p1FireCount >= 20)
		{
			for (int i = 0; i < _vPlasmaBall.size(); ++i)
			{
				_vPlasmaBall[i].setIsActive(false);
			}
			_plasmaCount = 0;
			_p1FireCount = 0;
			_activeP = BOSS_NONE;
		}
	}

	for (int i = 0; i < _vPlasmaBall.size(); ++i)
	{
		_vPlasmaBall[i].setAngle(utl::getAnglePL(_vPlasmaBall[i].getX(), _vPlasmaBall[i].getY(), _player->getX(), _player->getY()));
		_vPlasmaBall[i].update();
	}

	//TODO 쏘고나면 ball이 없어지고 다시 생성되잖아? 나중에 고치자
}

void kluexbossPh1::pattern1Render()
{
	for (int i = 0; i < _vPlasmaBall.size(); ++i)
	{
		_vPlasmaBall[i].render(true);
	}
}

void kluexbossPh1::pattern2Update()
{
	DELAYCOUNT(_p2AniCount, 120);
	if (_p2AniCount == 0)
	{
		_img[_state]->start();
	}
	
	if (_boardY < _flatBoard->getHeight())
	{
		//발판 올라오기 높이 업데이트
		_boardY += 0.7f;
		_flatBoardPixel->render(_mapPixel->getMemDC(), _x - 400, _y + _img[BOSS_MAIN]->getFrameHeight() * 0.5 - _boardY
			, 0, 0, _flatBoard->getWidth(), _boardY);
		_flatBoardPixel->render(_mapPixel->getMemDC(), _x + 400, _y + _img[BOSS_MAIN]->getFrameHeight() * 0.5 - _boardY
			, 0, 0, _flatBoard->getWidth(), _boardY);
	}
	//발판 다 올라오면
	else
	{
		//불 올라오기 높이 업데이트 해주기
		if (_magmaY < _magma->getHeight())
		{
			_magmaY += 0.7f;
			_magmaHitBox = RectMake(0, WINSIZEY - _magma->getHeight(), _mapPixel->getWidth(), WINSIZEY);
		}
		//불 다 올라오면
		else
		{
			_magmaLoopSPD += 2; //루프렌더
			DELAYCOUNT(_p2Duration, 500); //TODO : 더늘려도 될듯
			if (_p2Duration == 0)
			{
				//발판픽셀 지우기
				_flatBoardPixelErase->render(_mapPixel->getMemDC(), _x + 400, _y + _img[BOSS_MAIN]->getFrameHeight() * 0.5 - _flatBoard->getHeight()
					, 0, 0, _flatBoard->getWidth(), _flatBoard->getHeight());
				_flatBoardPixelErase->render(_mapPixel->getMemDC(), _x - 400, _y + _img[BOSS_MAIN]->getFrameHeight() * 0.5 - _flatBoard->getHeight()
					, 0, 0, _flatBoard->getWidth(), _flatBoard->getHeight());
				_magmaY = 0;
				_boardY = 0;
				_magmaLoopSPD = 0;
				_activeP = BOSS_NONE;
			}
		}
	}
}

void kluexbossPh1::pattern2Render()
{
	//발판 올라오기 잘라서 렌더하기
	_flatBoard->render(getMemDC(), _x - 400 - CAM->getX(), _y + _img[BOSS_MAIN]->getFrameHeight() * 0.5 - _boardY - CAM->getY()
		, 0, 0, _flatBoard->getWidth(), _boardY);

	_flatBoard->render(getMemDC(), _x + 400 - CAM->getX(), _y + _img[BOSS_MAIN]->getFrameHeight() * 0.5 - _boardY - CAM->getY()
		, 0, 0, _flatBoard->getWidth(), _boardY);

	if (_boardY >= _flatBoard->getHeight())
	{
		//불 올라오기 잘라서 루프렌더
		RECT temp = { -CAM->getX(), WINSIZEY - _magma->getHeight() - CAM->getY(), _mapPixel->getWidth() - CAM->getX(), WINSIZEY - CAM->getY() }; //화면좌표인데 y는 바뀌면 안되니까 절대좌표로 바꿔버렸다
		_magma->loopRender(getMemDC(), &temp, (int)_magmaLoopSPD, 0); //TODO 잘라서 렌더하려면 고민좀 해야할듯
	}
}

void kluexbossPh1::pattern3Update()
{
	if (!_iceStart)
	{
		for (int i = 0; i < 3; ++i)
		{
			//얼음은 한번에 3개씩 약간 랜덤한 위치에다 만들어야 하는데
			//미리 충돌렉트를 깔아두고 isActive를 각각 따로 만든다음에
			_iceActive[RND->getInt(8)] = true;
			//랜덤으로 3개만 isActive를 활성해서
		}
		_iceStart = true;
	}
	
	DELAYCOUNT(_iceframeCount, 120);
	if (_iceframeCount == 0)
	{
		_iceblock->setFrameX(_iceblock->getFrameX() + 1);
		if (_iceblock->getFrameX() > _iceblock->getMaxFrameX())
		{
			_iceblock->setFrameX(0);
		}
		_img[_state]->start();
	}
		
	//충돌렉트 크기 늘려주고
	for (int i = 0; i < 8; ++i)
	{
		if (_iceActive[i])
		{
			if(_iceblock->getFrameX() == 0)
				_iceHitBox[i].top = _y + _img[BOSS_MAIN]->getFrameHeight() * 0.5 - 31;
			if (_iceblock->getFrameX() == 1)
				_iceHitBox[i].top = _y + _img[BOSS_MAIN]->getFrameHeight() * 0.5 - 58;
			if (_iceblock->getFrameX() == 2)
				_iceHitBox[i].top = _y + _img[BOSS_MAIN]->getFrameHeight() * 0.5 - 124;
			if (_iceblock->getFrameX() == 3)
				_iceHitBox[i].top = _y + _img[BOSS_MAIN]->getFrameHeight() * 0.5 - 168;
		}
	}

	if (_iceblock->getFrameX() == 3)
	{
		DELAYCOUNT(_p3Duration, 500);
		if (_p3Duration == 0)
		{
			//TODO : 얼음꺠지는 이펙트 찾아서 넣기
			_iceStart = false;
			_activeP = BOSS_NONE;
			for (int i = 0; i < 8; ++i)
			{
				_iceActive[i] = false;
				_iceHitBox[i] = RectMake(_x - _iceblock->getFrameWidth() * 4 + _iceblock->getFrameWidth()*i,
					0, _iceblock->getFrameWidth(), _y + _img[BOSS_MAIN]->getFrameHeight() * 0.5);
				_iceblock->setFrameX(0);
			}
		}
	}
	//TODO isActive일때만 충돌렉트랑 충돌해서 데미지 받게
}

void kluexbossPh1::pattern3Render()
{
	for (int i = 0; i < 8; ++i)
	{
		//액티브한것만 프레임렌더
		if (_iceActive[i])
		{
			_iceblock->frameRender(getMemDC(), _iceHitBox[i].left - CAM->getX(), 
				_y + _img[BOSS_MAIN]->getFrameHeight() * 0.5 - _iceblock->getFrameHeight() - CAM->getY());
		}
	}
}
