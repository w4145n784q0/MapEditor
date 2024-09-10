#pragma once
#include <dInput.h>
#include"Transform.h"

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")

//SAFE_RELEASE�͕ʂ̃N���X�Ő錾���Ă��Ă������Ő錾���Ȃ��Ǝg���Ȃ�
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

class Controller
{
	Transform transform;
	XMFLOAT3 tar;

public:
	//�R���X�g���N�^
	Controller();

	//�f�X�g���N�^
	~Controller();

	//������
	void Initialize();

	//�X�V
	void Update();

	//�J��
	void Release();

	Transform GetTransform() { return transform; }
};

