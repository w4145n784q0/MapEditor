#include "Stage.h"
#include"Input.h"
#include"Camera.h"
#include"Direct3D.h"

namespace {
	int blockwidth = 20;
}

Stage::Stage() :pFBX(nullptr)
{
	for (int i = 0; i < blockwidth; i++)
	{
		for (int j = 0; j < blockwidth; j++)
		{
			table[i][j] = 1;
		}
	}
	table[0][0] = 5;
	table[0][9] = 3;
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
			for (int y = 0; y < table[x][z]; y++)
			{
				transform.position_.x = x;
				transform.position_.y = y;
				transform.position_.z = z;
				pFBX->Draw(transform);
			}

		}
	}

}

void Stage::Release()
{
	pFBX->Release();
	SAFE_DELETE(pFBX);
}
