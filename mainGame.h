#pragma once
#include "gameNode.h"
#include "loadingScene.h"
#include "startScene.h"
#include "mapToolScene.h"
#include "stageScene.h"
#include "player.h"

class mainGame : public gameNode
{
	player* _player;
public:
	HRESULT init();			//�θ� virtual�̹Ƿ� �ڽ��� �ڵ����� virtual�� �ȴ�.
	void release();
	void update();
	void render();

	mainGame() {}
	~mainGame() {}
};

