#include "stdafx.h"
#include "fennix.h"

HRESULT fennix::init()
{
	enemy::init();

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

	_imgR[FENNIX_IDLE]->setPlayFrame(1, 7);
	_imgR[FENNIX_HURT]->setPlayFrame(9,9);
	_imgR[FENNIX_MOVE]->setPlayFrame(11,16);
	_imgR[FENNIX_JUMP]->setPlayFrame(18,19);
	_imgR[FENNIX_FALL]->setPlayFrame(21,22);
	_imgR[FENNIX_SHOOT]->setPlayFrame(27,30);

	_imgL[FENNIX_IDLE]->setPlayFrame(1, 7);
	_imgL[FENNIX_HURT]->setPlayFrame(9, 9);
	_imgL[FENNIX_MOVE]->setPlayFrame(11, 16);
	_imgL[FENNIX_JUMP]->setPlayFrame(18, 19);
	_imgL[FENNIX_FALL]->setPlayFrame(21, 22);
	_imgL[FENNIX_SHOOT]->setPlayFrame(27, 30);

	return S_OK;
}

void fennix::update()
{
	switch (_state)
	{
	case FENNIX_IDLE:
		//��ҿ� IDLE�� MOVE�� �����ϰ� ����
		break;
	case FENNIX_HURT:
		//������ ������ �̻��·� �ٲٰ� �������� ������ ���·� ����
		break;
	case FENNIX_MOVE:
		//��ҿ� IDLE�� MOVE�� �����ϰ� ����
		//��ҿ��� ������ �������� �����̴� �÷��̾ ������ �ٰ����� �����ϰ� �����Ÿ����� �����
		break;
	case FENNIX_JUMP:
		//���� �ȼ��� �ʹ� ������ ������
		break;
	case FENNIX_FALL:
		//������� �浹 �ȵǸ� FALL����
		break;
	case FENNIX_SHOOT:
		//���������� �÷��̾ ������ ���缭�� ȭ�����
		break;
	}

	if (_dir == RIGHT)
	{
		if (!_imgR[_state]->isPlay())
		{
			_imgR[_state]->start();
		}
		_imgR[_state]->frameUpdate(0.46f);
	}
	else if (_dir == LEFT)
	{
		if (!_imgL[_state]->isPlay())
		{
			_imgL[_state]->start();
		}
		_imgL[_state]->frameUpdate(0.46f);
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

void fennix::bltUpdate()
{
	//ȭ�����
}

void fennix::bltRender()
{
	//ȭ�����
}

void fennix::move()
{

}

void fennix::collide()
{

}

bool fennix::collideObject(gameObject * gameObject)
{
	return false;
}

void fennix::damaged(gameObject * actor)
{
}