#pragma once
#include "gameObject.h"

class bullet : public gameObject
{
protected:
	image* _image;		// �Ҹ��̹���
	//image* _pixelMap;	// �ȼ��� �޾ƿ��� (���ӿ�����Ʈ�� ����)
	float _radius;		// �Ҹ� ������
	float _range;		// �Ҹ���Ÿ�
	int _frameDelay;	// ������ ������

	float _fireX, _fireY;
public:
	virtual HRESULT init(float radius, float speed, float damage, float range, const char* imageName = "����");
	//�Ҹ�������, �ӵ�, ���ݷ�, ��Ÿ�, �̹���Ű�� �̹���Ű���� �ȳ����� Ellipse�� �׷��� �߻����ش�.
	virtual void update();
	//��Ƽ����¸� ����
	virtual void render(bool rotate = false);
	//����, rotate�� true�� ������Ʈ�����Ѵ�.
	virtual void release();

	virtual void fire(float fireX, float fireY, float fireAngle, string soundKey = "����");
	//�߻��Ҷ� ����Ű������ �����Ű�� �߻���ġ ���ϰ� �߻簢��(ȣ��) ���� for�� continue�� ���ó����

	virtual bool collideMap(string pixelImageName);		//������ �浹�� �ϱ����� �ȼ��̹���Ű���� �Ѱ��ְ� ����
	virtual bool collideMap(image * pixelImage);		//������ �浹�� �ϱ����� �ȼ��̹���Ű���� �Ѱ��ְ� ����

	virtual bool collideActor(gameObject* actor);		
	//true�� �浹�̰� false�� �浹�ƴ�, ������ �ൿ(�����ֱ�)�� ��Ȱ���� ����� Ŭ�������� ����

	//void setPixelMap(image* pixelMap) { _pixelMap = pixelMap; }
	void setFrameDelay(int delay) { _frameDelay = delay; }

	float getRange() { return _range; }

	float getEffectAngle() { return getAnglePL(_x, _y, _fireX, _fireY); }
	//angle���� ����θ� ǥ���ϱ����� getAnglePL�� ���

	void setIsActive(bool isActive) { _isActive = isActive; }
	void setFireCenter(float fireX, float fireY) { _fireX = fireX; _fireY = fireY; _x = fireX; _y = fireY; }

	bullet() {}
	~bullet() {}
};

