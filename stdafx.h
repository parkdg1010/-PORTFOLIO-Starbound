// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <Windows.h>

//디버깅용 (주석치면 콘솔창이 사라진다)
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
// C++ 런타임 헤더 파일입니다.
#include <iostream>
// 자주사용하는 STL
#include <string>
#include <vector>
#include <map>

//네임스페이스
#include "util.h"
using namespace MY_UTIL;
using namespace std;

//=============================================================
//	## 내가 만든 헤더파일을 이곳에 추가한다 ##
//=============================================================
#include "commonMacroFunction.h"
#include "keyManager.h"
#include "randomFuntion.h"
#include "image.h"
#include "imageManager.h"
#include "saveData.h"
#include "txtData.h"
#include "iniData.h"
#include "sceneManager.h"
#include "timeManager.h"
#include "soundManager.h"
#include "effectManager.h"

#include "Camera.h"
//#include "RenderManager.h"
#include "UIManager.h"

//=============================================================
//	## 싱글톤을 추가한다 ##
//=============================================================
//ADDED : 싱글톤 : 하나의 객체(인스턴스)만 만들어서 어디서든 접근하기쉽게 만든 클래스
#define KEYMANAGER keyManager::getSingleton()
#define RND randomFuntion::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define SAVEDATA saveData::getSingleton()
#define TXTDATA txtData::getSingleton()
#define INIDATA iniData::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()

#define CAMERAMANAGER Camera::getSingleton()
#define UIMANAGER UIManager::getSingleton()
#define CAM Camera::getSingleton()
//#define RENDERMANAGER RenderManager::getSingleton()
//CHECK 렌더매니저와 UI매니저는 포함된 다른 클래스(actor등)을 만들고 모든 주석을 풀어야함
//=============================================================
//	## 디파인문 ## (윈도우창 초기화)
//=============================================================
#define WINNAME (LPTSTR)(TEXT(" 스타바운드 "))
#define WINSTARTX		100
#define WINSTARTY		0
#define WINSIZEX		1280
#define WINSIZEY		720
#define WINSTYLE		WS_CAPTION | WS_SYSMENU

//=============================================================
//	## 매크로함수 ## (클래스에서 동적할당된 부분 해제)
//=============================================================
#define SAFE_DELETE(p)		{if(p) {delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = NULL;}}

//ADDED 겟셋함수 매크로
#define Synthesize(VarType, VarName, FuncName)                     \
protected:   VarType VarName;                                 \
public:   inline VarType get##FuncName(void) const { return VarName; }   \
public:   inline void set##FuncName(VarType value) { VarName = value; }

//=============================================================
//	## 전역변수 ##
//=============================================================
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;
//ADDED : 디버그모드
extern BOOL			_isDebug;
//ADDED : 마우스휠
extern SHORT		_ptWheel;
//ADDED : 커서,볼륨
extern image*		cursor;
extern int			cursorFrameX;
extern int			cursorFrameY;
extern float		_soundVolume;
extern float		_effectVolume;

typedef struct POINTf
{
	float  x;
	float  y;
};

enum AXIS
{
	RIGHT, LEFT, UP, DOWN, NONE
};