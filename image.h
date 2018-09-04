#pragma once
#include "animation.h"
//=============================================================
//	## image ## (������ ��� ������Ʈ �ȴ�)
//=============================================================
class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,		// ���ҽ��� �ε�
		LOAD_FILE,				// ���Ϸ� �ε�
		LOAD_EMPTY,				// ���Ʈ�� �ε�
		LOAD_END
	};

	typedef struct tagImage		// Ÿ�� ������ ����ü
	{
		DWORD		redID;					// ���ҽ� ID
		HDC			hMemDC;					// ����۷� ����� �޸�DC
		HBITMAP		hBit;					// ��Ʈ��
		HBITMAP		hOBit;					// �õ��Ʈ��
		float		x;						// �̹��� x��ǥ - ȭ�鿡 ��� ��ġ
		float		y;						// �̹��� y��ǥ - ȭ�鿡 ��� ��ġ
		int			width;					// �̹��� ����ũ��
		int			height;					// �̹��� ����ũ��
		int			currentFrameX;			// ���� ������ x		(�Ѱ� �̹��� ������ �������������� ���ư��°� ����� �ִ�)(��������ź)   
		int			currentFrameY;			// ���� ������ y
		int			maxFrameX;				//�ִ� x������ ����
		int			maxFrameY;				//�ִ� y������ ����
		int			frameWidth;				// 1�����Ӵ� ���α���
		int			frameHeight;			// 1�����Ӵ� ���α���
		BYTE		loadType;				// �̹��� �ε�Ÿ��

		tagImage()					// ����ü ������ -> �ʱ�ȭ
		{
			redID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;	// �±� �̹����� ���� �ǹ� �����͸� �Ѱ��ٶ� LP~�� ����ϸ� �ȴ�

private:
	LPIMAGE_INFO	_imageInfo;		// �̹��� ����
	CHAR*			_fileName;		// �̹��� �̸�
	BOOL			_isTrans;		// ���� ����? (����Ÿ)
	COLORREF		_transColor;	// ���� ���� RGB ( ����Ÿ = RGB(255.0.255) )

	LPIMAGE_INFO	_blendImage;	// ���ĺ��� �̹���		���ĺ���
	BLENDFUNCTION	_blendFunc;		// ���ĺ��� ��� 		memDC�� �̹����� blendDC�� �ű�� �װ� hdc�� �ű�

	LPIMAGE_INFO	_stretchImage;	//��Ʈ��ġ�̹���
	LPIMAGE_INFO	_rotateImage;	//������Ʈ�̹���

public:
	image();
	~image();

	// �� ��Ʈ������ �ʱ�ȭ
	HRESULT init(int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	// �� ��Ʈ������ �ʱ�ȭ
	// �̹��� ���ҽ��� �ʱ�ȭ(������)
	HRESULT init(DWORD resID, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0)); // ����Ʈ �Ű�����
																												// �̹��� ���Ϸ� �ʱ�ȭ (�ַ� ���)
	HRESULT init(const char* fileName, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	// �̹��� ���Ϸ� �ʱ�ȭ (�ַ� ���), �ʱ�ȭ�Ҷ� ������ ��ġ(float)����
	HRESULT init(const char* fileName, float x, float y, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	// ������ �̹��� ���Ϸ� �ʱ�ȭ (�ֻ��)
	HRESULT init(const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = MAGENTA);
	// ������ �̹��� ���Ϸ� �ʱ�ȭ (�ֻ��), �ʱ�ȭ�Ҷ� ������ ��ġ(float)����
	HRESULT init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = MAGENTA);

	// ���ĺ��� �ʱ�ȭ
	HRESULT initForAlphaBlend(void);

	//����
	void release(void);

	//=============================================================
	//	## �Ϲݷ��� ## 
	//=============================================================
	void render(HDC hdc, int destX = 0, int destY = 0); //���� ���ϴ� ��ǥ(dest)�� ����
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight); //�̹����� �Ϻκи� ����(��Ʈ���� sour��ǥ�κи�)

	//=============================================================
	//	## ���ķ��� ## 
	//=============================================================
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//=============================================================
	//	## �����ӷ��� ## 
	//=============================================================
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void frameRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, int currentFrameX, int currentFrameY);

	//=============================================================
	//	## �������� ##
	//=============================================================
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	//=============================================================
	//	## ��Ʈ��ġ���� ## (�̹��� �����ϸ�)
	//=============================================================
	void stretchRender(HDC hdc, int destX, int destY, float scale = 1.0f);
	void stretchFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float scale = 1.0f);

	//=============================================================
	//	## ���������ӷ��� ## (made by ���)
	//=============================================================
	void alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	//=============================================================
	//	## ������Ʈ���� ## (�̹��� ȸ��)
	//=============================================================
	void rotateRender(HDC hdc, float centerX, float centerY, float angle);
	void rotateFrameRender(HDC hdc, float centerX, float centerY, float angle);
	void rotateFrameRender(HDC hdc, float centerX, float centerY, int currentFrameX, int currentFrameY, float angle);

	//=============================================================
	//	## �ִϷ��� ## 
	//=============================================================
	void aniRender(HDC hdc, int destX, int destY, animation* ani);
	void aniAlphaRender(HDC hdc, int destX, int destY, animation* ani, BYTE alpha);


	//=============================================================
	//	## inline ## (�ζ��� �Լ��� - ����, ����)
	//=============================================================

	//DC ���
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	//�̹��� x��ǥ
	inline float getX(void) { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x = x; }
	//�̹��� y��ǥ
	inline float getY(void) { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }
	//�̹��� ������ǥ
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}
	//�̹��� ����, ����ũ��
	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }
	//�ٿ�� �ڽ�(�浹�� ��Ʈ)
	inline RECT boundingBox(void)
	{
		RECT rc = { (int)_imageInfo->x, (int)_imageInfo->y, (int)_imageInfo->x + _imageInfo->width,(int)_imageInfo->y + _imageInfo->height };
		return rc;
	}
	inline RECT boundingBoxWithFrame(void)
	{
		RECT rc = { (int)_imageInfo->x, (int)_imageInfo->y, (int)_imageInfo->x + _imageInfo->frameWidth,(int)_imageInfo->y + _imageInfo->frameHeight };
		return rc;
	}

	// ������ x
	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)	//�ƽ��������� �����ʰ����ش�.
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}
	//������ y
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)	//�ƽ��������� �����ʰ����ش�.
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	//�̹��� �������Ӵ� ����, ����ũ��
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	//�ƽ������� ���� x(����), y(����)
	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }


};