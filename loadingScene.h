#pragma once
#include "gameNode.h"
#include "loading.h"

class loadingScene : public gameNode
{
private:
	loading * _loading;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//�ε��̹��� �Լ�(�̰��� �̹����� ���� �־��)
	void loadingImage();

	void loadingMapToolImage();
	void loadingIntroImage();
	void loadingTiles();
	void loadingObjects();
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

