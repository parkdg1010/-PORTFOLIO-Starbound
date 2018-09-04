#pragma once
#include "singletonBase.h"

class gameObject;
class gameActor;
class RenderManager : public singletonBase<RenderManager>
{
private:
	multimap<float, gameActor *> renderList;
	//multimap<float, gameObject *> backgroundList;

public:
	HRESULT init();	// void를 사용해도 됨. HRESULT: 정상적인 종료 여부 등의 여러 값을 가질 수 있음. 제일 많이 사용하는 것이 S_OK(정상 종료), E_FAIL(에러 발생)
	void release();
	void render(HDC hdc);
	void backgroundRender(HDC hdc);

	void addRender(float z, gameActor *name);
	//void addBackground(float z, gameObject *backActor);
	void clearBackground();

	RenderManager() {}
	~RenderManager() {}
};

