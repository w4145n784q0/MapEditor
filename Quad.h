#pragma once
#include "Direct3D.h"
#include <DirectXMath.h>
#include "Texture.h"
#include "Transform.h"
#include <vector>

using namespace DirectX;

//コンスタントバッファー:　アプリ側から、シェーダーに毎フレーム渡したい情報
struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
	XMMATRIX	matW;
};

//頂点情報
struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
	XMVECTOR normal; //ノーマル追加（法線ベクトル）
};

class Quad
{
protected:
	int vertexNum_;
	std::vector<VERTEX> vertices_;
	int indexNum_;//インデックス数
	std::vector<int> index_;//インデックス情報

	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;    //インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ

	Texture* pTexture_;
public:
	Quad();
	virtual ~Quad();
	HRESULT Initialize();
	//void Draw();
	void Draw(Transform& transform);
	void Release();

private:
	virtual void InitVertexData();
	HRESULT CreateVertexBuffer();
	virtual void InitIndexData();
	HRESULT CreateIndexBuffer();
	HRESULT CreateConstantBuffer();
	HRESULT LoadTexture();

	//---------Draw関数から呼ばれる関数---------
	void PassDataToCB(Transform& transform);	//コンスタントバッファに各種情報を渡す
	void SetBufferToPipeline();
};