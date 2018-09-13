#pragma once
#include "gameNode.h"
#include "loading.h"

class loadingScene : public gameNode
{
private:
	loading * _loading;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//�ε��̹��� �Լ�(�̰��� �̹����� ���� �־��)
	void loadingImage();

	void loadingMapToolImage();
	void loadingIntroImage();
	void loadingTiles();
	void loadingObjects();
	void loadingEffectImage();
	void loadingItem();
	void loadingPlayer();
	void loadingMonster();

	//�ε����� �Լ�(�̰��� ���带 ���� �־��)
	void loadingSound();
	//�ε�����Ʈ �Լ�
	void loadingEffect();

	loadingScene() {}
	~loadingScene() {}
};

