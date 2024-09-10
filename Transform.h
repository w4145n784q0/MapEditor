#pragma once
#include <DirectXMath.h>

using namespace DirectX;

//位置、向き、拡大率などを管理するクラス
class Transform
{
	XMMATRIX matTranslate_;	//移動行列
	XMMATRIX matRotate_;	//回転行列	
	XMMATRIX matScale_;	//拡大行列
	//worldマトリクスはこの三つをかけたもの 掛け算の順番はSRT

public:
	XMFLOAT3 position_;	//位置 平行移動
	XMFLOAT3 rotate_;	//回転　回転
	XMFLOAT3 scale_;	//拡大縮小率　スケーリング

	//コンストラクタ
	Transform();

	//デストラクタ
	~Transform();

	//各行列の計算
	void Calculation();

	//ワールド行列を取得
	XMMATRIX GetWorldMatrix();
	XMMATRIX GetNormalMatrix();
};