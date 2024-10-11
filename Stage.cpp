#include "Stage.h"
#include"Input.h"
#include"Camera.h"
#include"Direct3D.h"

namespace {
	int blockwidth = 20;
	int blockheight = 20;
}

Stage::Stage() :pFBX(nullptr)
{
	for (int i = 0; i < blockheight; i++)
	{
		for (int j = 0; j < blockwidth; j++)
		{
			table[i][j].height = 1;
			table[i][j].type = 0;
		}
	}
	table[0][0].height = 5;
	table[0][9].height = 3;
	table[5][2].type = 3;
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
	/*pFBX = new FBX;
	pFBX->Load("Assets/BoxDefault.fbx");*/

	/*pFBXarray[0] = new FBX;
	pFBXarray[0]->Load("Assets/BoxDefault.fbx");
	pFBXarray[1] = new FBX;
	pFBXarray[1]->Load("Assets/BoxBrick.fbx");
	pFBXarray[2] = new FBX;
	pFBXarray[2]->Load("Assets/BoxSand.fbx");
	pFBXarray[3] = new FBX;
	pFBXarray[3]->Load("Assets/BoxWater.fbx");
	pFBXarray[4] = new FBX;
	pFBXarray[4]->Load("Assets/BoxGrass.fbx");*/

	string fileName[] = { "BoxDefault","BoxBrick","BoxSand"
		,"BoxWater","BoxGrass" };
	for (int i = 0; i < 5; i++)
	{
		string path = "Assets/" + fileName[i] + ".fbx";
		pFBXarray[i] = new FBX;
		pFBXarray[i]->Load(path);
	}
}

void Stage::Update()
{
	RayCastData data;
	data.start = XMFLOAT4(0, 5, 0, 0);
	data.dir = XMFLOAT4(0, -1, 0, 0);

	Transform trans;
	trans.position_.x = 1;

	pFBXarray[0]->RayCast(data,trans);

	if (Input::IsMouseButtonDown(0))
	{
		XMMATRIX matView = Camera::GetViewMatrix();//ビュー行列
		XMMATRIX matProj = Camera::GetProjectionMatrix();//プロジェクション行列

		float w = Direct3D::WINDOW_WIDTH/2;
		float h = Direct3D::WINDOW_HEIGHT/2;

		XMMATRIX vp = //ビューポート行列
		{
			w, 0, 0, 0,
			0, -h, 0, 0,
			0, 0, 0, 0,
			w, h, 0, 0, // この行が移動分（DirectXの場合）
		};

		XMMATRIX invView = XMMatrixInverse(nullptr, matView);//ビュー行列（の逆行列）
		XMMATRIX invProj = XMMatrixInverse(nullptr, matProj);//プロジェクション行列（の逆行列）
		XMMATRIX invVP = XMMatrixInverse(nullptr, vp);//ビューポート行列（の逆行列）

		XMVECTOR mouseFrontPos = Input::GetMousePosition();//マウスの位置をとってXMvectorへ
		XMFLOAT3 MousePos;//スクリーン座標を入れるXMfloat
		XMStoreFloat3(&MousePos, mouseFrontPos);//MousePosにmouseFrontPosの値をXMFLOATに変換して入れる
		MousePos.z = 0;
		mouseFrontPos = XMLoadFloat3(&MousePos);//MousePosをベクトルに変換

		MousePos.z = 1;//一番奥をとる
		XMVECTOR mouseBackPos = XMLoadFloat3(&MousePos);//マウスの位置をベクトル化
		
		mouseFrontPos = XMVector3TransformCoord(mouseFrontPos, invVP * invProj * invView);
		mouseBackPos = XMVector3TransformCoord(mouseBackPos, invVP * invProj * invView);
	}
}

void Stage::Draw()
{
	Transform transform;
	/*for (int i = 0; i < blockwidth; i++)
	{
		for (int j = 0; j < blockwidth; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				transform.position_.y = k;
				transform.position_.x = j;
				transform.position_.z = i;
				pFBX->Draw(transform);
			}
			
		}
	}*/

	for (int x = 0; x < blockwidth; x++)
	{
		for (int z = 0; z < blockwidth; z++)
		{
			for (int y = 0; y < table[x][z].height; y++)
			{
				//表示位置が変わっているだけ
				transform.position_.x = x;
				transform.position_.y = y;
				transform.position_.z = z;
				
				int type = table[x][z].type;
				pFBXarray[type]->Draw(transform);
			}

		}
	}

}

void Stage::Release()
{
	for (int i = 0; i < 5; i++)
	{
		pFBXarray[i]->Release();
		SAFE_DELETE(pFBXarray[i]);
	}

}
