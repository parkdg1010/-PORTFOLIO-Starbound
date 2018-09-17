#pragma once
#include "gameObject.h"

class bullet : public gameObject
{
protected:
	image* _image;		// 불릿이미지
	//image* _pixelMap;	// 픽셀맵 받아오기 (게임오브젝트에 포함)
	float _radius;		// 불릿 반지름
	float _range;		// 불릿사거리
	int _frameDelay;	// 프레임 딜레이

	float _fireX, _fireY;
public:
	virtual HRESULT init(float radius, float speed, float damage, float range, const char* imageName = "없음");
	//불릿반지름, 속도, 공격력, 사거리, 이미지키값 이미지키값을 안넣으면 Ellipse를 그려서 발사해준다.
	virtual void update();
	//액티브상태면 무브
	virtual void render(bool rotate = false);
	//렌더, rotate가 true면 로테이트렌더한다.
	virtual void release();

	virtual void fire(float fireX, float fireY, float fireAngle, string soundKey = "없음");
	//발사할때 사운드키값으로 재생시키고 발사위치 정하고 발사각도(호도) 지정 for문 continue는 사용처에서

	virtual bool collideMap(string pixelImageName);		//벽과의 충돌을 하기위해 픽셀이미지키값을 넘겨주게 했음
	virtual bool collideMap(image * pixelImage);		//벽과의 충돌을 하기위해 픽셀이미지키값을 넘겨주게 했음

	virtual bool collideActor(gameObject* actor);		
	//true면 충돌이고 false면 충돌아님, 이후의 행동(피해주기)과 비활성은 사용할 클래스에서 결정

	//void setPixelMap(image* pixelMap) { _pixelMap = pixelMap; }
	void setFrameDelay(int delay) { _frameDelay = delay; }

	float getRange() { return _range; }

	float getEffectAngle() { return getAnglePL(_x, _y, _fireX, _fireY); }
	//angle값을 양수로만 표현하기위해 getAnglePL을 사용

	void setIsActive(bool isActive) { _isActive = isActive; }
	void setFireCenter(float fireX, float fireY) { _fireX = fireX; _fireY = fireY; _x = fireX; _y = fireY; }

	bullet() {}
	~bullet() {}
};

