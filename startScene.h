#pragma once
#include "gameNode.h"

class player;
class startScene : public gameNode
{
private:
	image* _ui[4];
	RECT _rcUi[4];
	int _buttonLight[4];
	image* _space;
	image* _star;
	image* _earth;
	image* _logo;
	float _angle;
	
	bool _soundOption;
	image* _numbers;
	image* _soundUI;
	image* _soundButton;
	image* _soundLeft;
	image* _soundRight;

	RECT _rcSoundUI;
	RECT _rcSoundButton;
	int _buttonFrame;
	RECT _rcSoundNum[3];
	RECT _rcSoundArrow[2];
	int _soundArrowFrame[2];
	RECT _rcEffectNum[3];
	RECT _rcEffectArrow[2];
	int _effectArrowFrame[2];

	player* _player;
public:

	void buttonLighting(int index);

	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();

	void initImage();

	void soundOptionUpdate();
	void soundOptionRender();

	startScene() {}
	~startScene() {}
};

