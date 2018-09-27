#pragma once
#include "gameNode.h"
//=============================================================
//	## progressBar ## (���α׷����� = ü�¹�)
//=============================================================

class progressBar : public gameNode
{
private:
	RECT _rcProgress;			//ü�¹� ��Ʈ
	int _x, _y;					//ü�¹� ��ġ��ǥ
	float _width;				//ü�¹� ���α���
	float _height;				//ü�¹� ���α���
								
	image* _progressBarFront;	//ü�¹� �� �̹���
	image* _progressBarBack;	//ü�¹� �� �̹���

	int _delay;					//���̹��� �����ӵ�����
	int _index;

public:
	//ü�¹� �ʱ�ȭ(���̹���Ű, ���̹���Ű, x, y, ���α���, ���α���)
	HRESULT init(const char* frontImageKey, const char* backImageKey, int x, int y, int width, int height);
	void release();
	void update();
	void render(HDC hdc);

	//ü�¹� ������ �����ϱ�
	void setGauge(float currentHp, float maxHp);

	//ü�¹� ��ġ ��ǥ �����ϱ�
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }
	void setPosition(int x, int y) { _x = x; _y = y; }
	//ü�¹� ��Ʈ ��������
	RECT getRect() { return _rcProgress; }

	void setFrontImg(image* barFront) { _progressBarFront = barFront; }
	void setBackImg(image* barBack) { _progressBarBack = barBack; }

	progressBar() {}
	~progressBar() {}
};

