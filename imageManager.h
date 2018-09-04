#pragma once
#include "singletonBase.h"
#include "image.h"
//=============================================================
//	## imageManager ## (�̹��� �Ŵ���)
//=============================================================
//ADDED �̹����Ŵ������� �ʱ�ȭ,map �����̳ʿ� ���, �������� ���

class imageManager : public singletonBase <imageManager>
{
private:
	//ADDED ������,�������� ��� ���ؼ��� �ڷ���(����������)�� �ʿ��ѵ� �̷� Ÿ���� ���� �ٸ��̸����� �����ؼ� �� �̸����� ����ϰڴ�.
	/*typedef int INT;
	int a;
	INT b;
	vector<int>
	*/
	typedef map<string, image*> mapImageList;				// ������ ���� �̹������
	typedef map<string, image*>::iterator mapImageIter;		// ������ ���� �̹�������� �ݺ���
	
	mapImageList _mImageList;		// ���� �̹���Ŭ������ ���� STL��
	// (typedef���п�) map<string, image*> _mImageList;�� mapImageList _mImageList;�� ���� �ִ�.

public:
	//�̹��� �Ŵ��� �ʱ�ȭ
	HRESULT init();
	//�̹��� �Ŵ��� ����
	void release();

	// �� ��Ʈ������ �ʱ�ȭ
	image* addImage(string strKey, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	// �̹��� ���Ϸ� �ʱ�ȭ (�ַ� ���)
	image* addImage(string strKey, const char* fileName, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	// �̹��� ���Ϸ� �ʱ�ȭ (�ַ� ���), �ʱ�ȭ�Ҷ� ������ ��ġ(float)����
	image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	// ������ �̹��� ���Ϸ� �ʱ�ȭ (�ֻ��)
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = MAGENTA);
	// ������ �̹��� ���Ϸ� �ʱ�ȭ (�ֻ��), �ʱ�ȭ�Ҷ� ������ ��ġ(float)����
	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = MAGENTA);

	// �̹��� Ű������ ã��
	image* findImage(string strKey);
	// �̹��� Ű������ ����
	BOOL deleteImage(string strKey);
	//�̹��� ��ü ����
	BOOL deleteAll ();

// ���� �Է¹��� Ű������ find�ؼ� ����
//=============================================================
//	## �Ϲݷ��� ## 
//=============================================================
	void render(string strKey, HDC hdc, int destX = 0, int destY = 0); //���� ���ϴ� ��ǥ(dest)�� ����
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight); //�̹����� �Ϻκи� ����(��Ʈ���� sour��ǥ�κи�)

//=============================================================
//	## ���ķ��� ## 
//=============================================================
	void alphaRender(string strKey, HDC hdc, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

//=============================================================
//	## �����ӷ��� ## 
//=============================================================
	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

//=============================================================
//	## ��Ʈ��ġ���� ## (�̹��� �����ϸ�)
//=============================================================
	void stretchRender(string strKey, HDC hdc, int destX, int destY, float scale = 1.0f);
	void stretchFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float scale = 1.0f);
//=============================================================
//	## ���������ӷ��� ## (���)
//=============================================================
	void alphaFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

//ADDED : �����Ӹ���Ŀ
//=============================================================
//	## �����Ӹ���Ŀ ## 
//=============================================================
	//void frameMake(image * bmp, int &count, int &index, int frameY1, int frameY2, int cooltime, bool renderDir = false);
	//void frameMake(string strKey, int & count, int & index, int frameY1, int frameY2, int cooltime, bool renderDir = false);
	
	//imageManager();
	//~imageManager();
};
