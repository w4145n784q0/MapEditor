#include "Stage.h"

namespace {
	int blockwidth = 20;
}

Stage::Stage() :pFBX(nullptr)
{
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
	pFBX = new FBX;
	pFBX->Load("Assets/BoxDefault.fbx");
}

void Stage::Update()
{
}

void Stage::Draw()
{
	Transform transform;
	for (int i = 0; i < blockwidth; i++)
	{
		for (int j = 0; j < blockwidth; j++)
		{
			transform.position_.x = j;
			transform.position_.z = i;
			pFBX->Draw(transform);
		}
	}
}

void Stage::Release()
{
	pFBX->Release();
	SAFE_DELETE(pFBX);
}
