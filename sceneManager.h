#pragma once
#include "singletonBase.h"
//=============================================================
//	## sceneManager ## (�� �Ŵ���)
//=============================================================

//�̱����� ��ӹ��� ���̵��� static���� ����� ���⶧���� (���� �޸𸮰���)
//�Ϲ�Ŭ������ ���ӳ�带 ����Ϸ��� �ϸ� ������

//���ӳ�� Ŭ���� ���漱��
class gameNode;

class sceneManager : public singletonBase <sceneManager>
{
private:
	typedef map<string, gameNode*> mSceneList;
	typedef map<string, gameNode*>::iterator miSceneList;

private:
	mSceneList _mSceneList;		//������ ��(ȭ��)���� ��Ƶ� ��
	gameNode* _currentScene;	//�����

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//���߰�
	gameNode* addScene(string sceneName, gameNode* scene);
	//������ (�ش�� �ε�)
	HRESULT loadScene(string sceneName);

	//���� �� �ʱ�ȭ
	HRESULT initScene();

	sceneManager() : _currentScene(NULL) {}
	~sceneManager() {}
};

//����
/*���߰�*/
//SCENEMANAGER->addScene("�ȼ��浹", new pixelCollision);
//SCENEMANAGER->addScene("�׽�Ʈ��", new sceneTest);

/*����� ����*/
//SCENEMANAGER->loadScene("�׽�Ʈ��");
