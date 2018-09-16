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
	_p1FireDelay = 1; //���� �������ڸ��� �ٽ�°� ���ƺ����� 1�� �ʱ�ȭ��
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
		//������Ʈ���� top�� ũ��ٲٸ� �ȴ�.
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
		//�������ְ� �������� ���Ϲٲٱ�
		DELAYCOUNT(_patternDelay, 60);
		if (_patternDelay == 0)
			_activeP = RND->getFromIntTo(1, 3);
		_state = BOSS_MAIN;
		break;
	case BOSS_MAIN:
		_state = BOSS_MAIN;
		pattern1Update();
		break;
	case BOSS_FIRE: //TODO ���°� �ʹ� Ȯ�ٲ�µ� �� ���϶� �ٲ㺸��
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
		int(_y - (_img[_state]->getFrameHeight() >> 1) - CAM->getY()), _img[_state]); //��Ʈ���� *0.5
	
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
		_vbullet->at(i).update(); //���͸� �����Ҵ������� at�� ���� �ε����� �����´� at�� ���ȣ�� ���� �ǹ̷� ���
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
		_vbullet->at(i).render(true); //���͸� �����Ҵ������� at�� ���� �ε����� �����´� at�� ���ȣ�� ���� �ǹ̷� ���
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
	//���� ������ �־ �����ϱ�
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
		DELAYCOUNT(_p1FireDelay, int(_hp * 0.03f));	//ü�°� ����ؼ� �߻������ ���̱�

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

	//TODO ����� ball�� �������� �ٽ� �������ݾ�? ���߿� ��ġ��
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
		//���� �ö���� ���� ������Ʈ
		_boardY += 0.7f;
		_flatBoardPixel->render(_mapPixel->getMemDC(), _x - 400, _y + _img[BOSS_MAIN]->getFrameHeight() * 0.5 - _boardY
			, 0, 0, _flatBoard->getWidth(), _boardY);
		_flatBoardPixel->render(_mapPixel->getMemDC(), _x + 400, _y + _img[BOSS_MAIN]->getFrameHeight() * 0.5 - _boardY
			, 0, 0, _flatBoard->getWidth(), _boardY);
	}
	//���� �� �ö����
	else
	{
		//�� �ö���� ���� ������Ʈ ���ֱ�
		if (_magmaY < _magma->getHeight())
		{
			_magmaY += 0.7f;
			_magmaHitBox = RectMake(0, WINSIZEY - _magma->getHeight(), _mapPixel->getWidth(), WINSIZEY);
		}
		//�� �� �ö����
		else
		{
			_magmaLoopSPD += 2; //��������
			DELAYCOUNT(_p2Duration, 500); //TODO : ���÷��� �ɵ�
			if (_p2Duration == 0)
			{
				//�����ȼ� �����
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
	//���� �ö���� �߶� �����ϱ�
	_flatBoard->render(getMemDC(), _x - 400 - CAM->getX(), _y + _img[BOSS_MAIN]->getFrameHeight() * 0.5 - _boardY - CAM->getY()
		, 0, 0, _flatBoard->getWidth(), _boardY);

	_flatBoard->render(getMemDC(), _x + 400 - CAM->getX(), _y + _img[BOSS_MAIN]->getFrameHeight() * 0.5 - _boardY - CAM->getY()
		, 0, 0, _flatBoard->getWidth(), _boardY);

	if (_boardY >= _flatBoard->getHeight())
	{
		//�� �ö���� �߶� ��������
		RECT temp = { -CAM->getX(), WINSIZEY - _magma->getHeight() - CAM->getY(), _mapPixel->getWidth() - CAM->getX(), WINSIZEY - CAM->getY() }; //ȭ����ǥ�ε� y�� �ٲ�� �ȵǴϱ� ������ǥ�� �ٲ���ȴ�
		_magma->loopRender(getMemDC(), &temp, (int)_magmaLoopSPD, 0); //TODO �߶� �����Ϸ��� ����� �ؾ��ҵ�
	}
}

void kluexbossPh1::pattern3Update()
{
	if (!_iceStart)
	{
		for (int i = 0; i < 3; ++i)
		{
			//������ �ѹ��� 3���� �ణ ������ ��ġ���� ������ �ϴµ�
			//�̸� �浹��Ʈ�� ��Ƶΰ� isActive�� ���� ���� ���������
			_iceActive[RND->getInt(8)] = true;
			//�������� 3���� isActive�� Ȱ���ؼ�
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
		
	//�浹��Ʈ ũ�� �÷��ְ�
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
			//TODO : ���������� ����Ʈ ã�Ƽ� �ֱ�
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
	//TODO isActive�϶��� �浹��Ʈ�� �浹�ؼ� ������ �ް�
}

void kluexbossPh1::pattern3Render()
{
	for (int i = 0; i < 8; ++i)
	{
		//��Ƽ���Ѱ͸� �����ӷ���
		if (_iceActive[i])
		{
			_iceblock->frameRender(getMemDC(), _iceHitBox[i].left - CAM->getX(), 
				_y + _img[BOSS_MAIN]->getFrameHeight() * 0.5 - _iceblock->getFrameHeight() - CAM->getY());
		}
	}
}
