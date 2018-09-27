#include "stdafx.h"
#include "progressBar.h"

HRESULT progressBar::init(const char * frontImageKey, const char * backImageKey, int x, int y, int width, int height)
{
	//ü�¹� ��ġ �ʱ�ȭ
	_x = x;
	_y = y;
	//ü�¹� ����, ���α��� �ʱ�ȭ
	_width = width;
	_height = height;
	//ü�¹� ��Ʈ ��ġ �� ũ�� �ʱ�ȭ
	_rcProgress = RectMake(x, y, width, height);

	//Ű������ �̹����̸�(~.bmp)���� �ٷ� �ʱ�ȭ
	char frontImage[128];
	char backImage[128];
	//�޸� ����ϰ� �о��ֱ�
	ZeroMemory(frontImage, sizeof(frontImage));
	ZeroMemory(backImage, sizeof(backImage));
	//~.bmp�� �����
	//Ű, �����̸� IMAGEMANAGER->ADDIMAGE("background", "background.bmp",,,,)
	_stprintf_s(frontImage, "%s.bmp", frontImageKey);
	_stprintf_s(backImage, "%s.bmp", backImageKey);

	//ü�¹� �̹��� �ʱ�ȭ
	_progressBarFront = IMAGEMANAGER->addImage(frontImageKey, frontImage, x, y, width, height, true, RGB(255, 0, 255));
	_progressBarBack = IMAGEMANAGER->addImage(backImageKey, backImage, x, y, width, height, true, RGB(255, 0, 255));

	_index = 0;

	return S_OK;
}

void progressBar::release()
{
}

void progressBar::update()
{
	if(_progressBarBack != NULL)
		_rcProgress = RectMake(_x, _y, _progressBarBack->getWidth(), _progressBarBack->getHeight());
	else
		_rcProgress = RectMake(_x, _y, _progressBarFront->getWidth(), _progressBarFront->getHeight());
}

void progressBar::render(HDC hdc)
{
	//������ �Ǵ� ������ ���ؼ� ������ �Ǵϱ� ������� ���� ��Ų��
	if(_progressBarBack != NULL)
		_progressBarBack->render(hdc, _rcProgress.left, _y);
	//�տ� �������� ü�¹� �̹���
	if (_progressBarFront != NULL)
	{
		if (_progressBarFront->getMaxFrameX() || _progressBarFront->getMaxFrameY()) //���߿� �ϳ��� ���� ������ �������̹�����.
		{
			DELAYCOUNT(_delay, 7);
			if (_delay == 0)
			{
				++_index;
				if (_index > _progressBarFront->getMaxFrameY())
					_index = 0;
			}
			_progressBarFront->frameRender(hdc, _rcProgress.left, _y, 0, 0, _width, _progressBarFront->getFrameHeight(), 0, _index);
		}
		else
		{
			_progressBarFront->render(hdc, _rcProgress.left, _y, 0, 0, _width, _progressBarFront->getHeight());
		}
	}
	
}

void progressBar::setGauge(float currentHp, float maxHp)
{
	if(_progressBarBack != NULL)
		_width = (currentHp / maxHp) * _progressBarBack->getWidth();
	else
		_width = (currentHp / maxHp) * _progressBarFront->getWidth();
}
