#include "stdafx.h"
#include "gameNode.h"

//=============================================================
//	## �ʱ�ȭ ## init(void)
//=============================================================
HRESULT gameNode::init()
{
	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		SetTimer(_hWnd, 1, 10, NULL);		//Ÿ�̸� �ʱ�ȭ // 10/1000�� ���� Ÿ�̸� 1��
		KEYMANAGER->init();					//Ű�Ŵ��� �ʱ�ȭ
		RND->init();						//������� �ʱ�ȭ
		IMAGEMANAGER->init();				//�̹����Ŵ��� �ʱ�ȭ
		SAVEDATA->init();					//���̺굥���� �ʱ�ȭ
		TXTDATA->init();					//TXT������ �ʱ�ȭ
		INIDATA->init();					//INI������ �ʱ�ȭ
		SCENEMANAGER->init();				//���Ŵ��� �ʱ�ȭ
		TIMEMANAGER->init();				//Ÿ�ӸŴ��� �ʱ�ȭ
		SOUNDMANAGER->init();				//����Ŵ��� �ʱ�ȭ
		EFFECTMANAGER->init();				//����Ʈ�Ŵ��� �ʱ�ȭ
		CAMERAMANAGER->init();				//ī�޶�Ŵ��� �ʱ�ȭ
		//RENDERMANAGER->init();				//�����Ŵ��� �ʱ�ȭ
		//UIMANAGER->init();					//ui�Ŵ��� �ʱ�ȭ
	}

	return S_OK;
}

//=============================================================
//	## ���� ## release(void)
//=============================================================
void gameNode::release()
{
	if (_managerInit)
	{
		//Ÿ�̸� ����
		KillTimer(_hWnd, 1);				//1��Ÿ�̸� ����
		//Ű�Ŵ��� �̱��� ����
		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();
		//������� �̱��� ����
		RND->release();
		RND->releaseSingleton();
		//�̹����Ŵ��� �̱��� ����
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		//���̺굥���� �̱��� ����
		SAVEDATA->release();
		SAVEDATA->releaseSingleton();
		//TXT������ �̱��� ����
		TXTDATA->release();
		TXTDATA->releaseSingleton();
		//INI������ �̱��� ����
		INIDATA->release();
		INIDATA->releaseSingleton();
		//���Ŵ��� �̱��� ����
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();
		//Ÿ�ӸŴ��� �̱��� ����
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();
		//����Ŵ��� �̱��� ����
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();
		//����Ʈ�Ŵ��� �̱��� ����
		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();
		CAMERAMANAGER->release();
		CAMERAMANAGER->releaseSingleton();
		//UIMANAGER->release();
		//UIMANAGER->releaseSingleton();
		//RENDERMANAGER->release();
		//RENDERMANAGER->releaseSingleton();
	}

	//DC ����
	ReleaseDC(_hWnd, _hdc);
}

//=============================================================
//	## ������Ʈ ## update(void)
//=============================================================
void gameNode::update()
{
	//���ΰ�ħ (���߿� ���� Ÿ�̸Ӹ� ���� �Ŀ��� ������� �ʴ´�)
	//������۸� ���� ������� �ʴ´�(true => false)
	InvalidateRect(_hWnd, NULL, FALSE);
	//���ΰ�ħ���ִ� �Լ� - ���ͳ��ͽ��÷ξ��� F5�� ����
}

//=============================================================
//	## ���� ## render(HDC hdc)
//=============================================================
void gameNode::render() //�̹����Ŵ����� �߰��ϸ鼭 HDC�Ű����� ����
{
}

//=============================================================
//	## �������ν��� ##
//=============================================================
LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;			//�ڵ�DC 			
	PAINTSTRUCT ps;		//����Ʈ����ü	

	switch (iMessage)
	{
	case WM_TIMER:
		this->update();
		break;
	case WM_PAINT:							//��¿� ���� ������ ����Ѵ�(����, �׸�, ������� ȭ�鿡 ���̴� ����)
		hdc = BeginPaint(hWnd, &ps);
		this->render();						//�̹��� �Ŵ����� �߰��ϸ鼭 HDC�Ű����� ����
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:		
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;
	case WM_MOUSEWHEEL:
		_ptWheel = (SHORT)HIWORD(wParam);
		break;
	case WM_KEYDOWN:						//Ű���� Ű�� �������� �޼��� �߻�
		switch (wParam)
		{
		case VK_ESCAPE:						//esc Ű�� ������ ȭ������
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:		
		PostQuitMessage(0);
		return 0;
	}

	//������ ���ν������� ó������ ���� ������ �޼����� ó�����ش�
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}