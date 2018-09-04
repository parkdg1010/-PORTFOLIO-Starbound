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
	HRESULT init();	// void�� ����ص� ��. HRESULT: �������� ���� ���� ���� ���� ���� ���� �� ����. ���� ���� ����ϴ� ���� S_OK(���� ����), E_FAIL(���� �߻�)
	void release();
	void render(HDC hdc);
	void backgroundRender(HDC hdc);

	void addRender(float z, gameActor *name);
	//void addBackground(float z, gameObject *backActor);
	void clearBackground();

	RenderManager() {}
	~RenderManager() {}
};

