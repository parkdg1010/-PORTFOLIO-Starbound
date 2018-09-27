#include "stdafx.h"
#include "progressBar.h"

HRESULT progressBar::init(const char * frontImageKey, const char * backImageKey, int x, int y, int width, int height)
{
	//체력바 위치 초기화
	_x = x;
	_y = y;
	//체력바 가로, 세로길이 초기화
	_width = width;
	_height = height;
	//체력바 렉트 위치 및 크기 초기화
	_rcProgress = RectMake(x, y, width, height);

	//키값으로 이미지이름(~.bmp)으로 바로 초기화
	char frontImage[128];
	char backImage[128];
	//메모리 깔끔하게 밀어주기
	ZeroMemory(frontImage, sizeof(frontImage));
	ZeroMemory(backImage, sizeof(backImage));
	//~.bmp로 만들기
	//키, 파일이름 IMAGEMANAGER->ADDIMAGE("background", "background.bmp",,,,)
	_stprintf_s(frontImage, "%s.bmp", frontImageKey);
	_stprintf_s(backImage, "%s.bmp", backImageKey);

	//체력바 이미지 초기화
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
	//렌더링 되는 순서에 의해서 렌더가 되니까 피통부터 렌더 시킨다
	if(_progressBarBack != NULL)
		_progressBarBack->render(hdc, _rcProgress.left, _y);
	//앞에 보여지는 체력바 이미지
	if (_progressBarFront != NULL)
	{
		if (_progressBarFront->getMaxFrameX() || _progressBarFront->getMaxFrameY()) //둘중에 하나라도 값이 있으면 프레임이미지다.
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
