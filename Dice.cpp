#include "Dice.h"
#include"Quad.h"
#include"Camera.h"

Dice::~Dice()
{
}

//HRESULT Dice::Initialize()
//{
//	// 頂点情報
////	VERTEX vertices[] =
////	{
////		////1 正面
////		//{ XMVectorSet(-1.0f, 1.0f, -1.0f, 0.0f), {0.0, 0.0, 0.0, 0.0}},// 四角形の頂点（左上）
////		//{ XMVectorSet( 1.0f, 1.0f, -1.0f, 0.0f),	{0.25, 0.0, 0.0, 0.0}},//四角形の頂点（右上）
////		//{ XMVectorSet( 1.0f,-1.0f, -1.0f, 0.0f),	{0.25, 0.5, 0.0, 0.0}},// 四角形の頂点（右下）
////		//{ XMVectorSet(-1.0f,-1.0f, -1.0f, 0.0f), {0.0, 0.5, 0.0, 0.0}},// 四角形の頂点（左下）
////
////		////2下
////		//{ XMVectorSet(-1.0f,  -1.0f, 1.0f, 0.0f), {0.25, 0.0, 0.0, 0.0}},// 四角形の頂点（左上）
////		//{ XMVectorSet(1.0f, -1.0f, 1.0f, 0.0f),	{0.5, 0.0, 0.0, 0.0}},//四角形の頂点（右上）
////		//{ XMVectorSet(1.0f, -1.0f, -1.0f, 0.0f),	 {0.5, 0.5, 0.0, 0.0}},// 四角形の頂点（右下）
////		//{ XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f), {0.25, 0.5, 0.0, 0.0}},// 四角形の頂点（左下）
////
////		////3 左
////		//{ XMVectorSet(-1.0f,  1.0f, 1.0f, 0.0f), {0.5, 0.0, 0.0, 0.0}},// 四角形の頂点（左上）
////		//{ XMVectorSet(-1.0f, 1.0f, -1.0f, 0.0f),	{0.75, 0.0, 0.0, 0.0}},//四角形の頂点（右上）
////		//{ XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f), {0.75, 0.5, 0.0, 0.0}},// 四角形の頂点（右下）
////		//{ XMVectorSet(-1.0f, -1.0f, 1.0f, 0.0f), {0.5, 0.5, 0.0, 0.0}},// 四角形の頂点（左下）
////
////		////4右
////		//{ XMVectorSet(1.0f,  1.0f, -1.0f, 0.0f), {0.75, 0.0, 0.0, 0.0}},// 四角形の頂点（左上）
////		//{ XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f),	{1.0, 0.0, 0.0, 0.0}},//四角形の頂点（右上）
////		//{ XMVectorSet(1.0f, -1.0f, 1.0f, 0.0f), {1.0, 0.5, 0.0, 0.0}},// 四角形の頂点（右下）
////		//{ XMVectorSet(1.0f, -1.0f, -1.0f, 0.0f), {0.75, 0.5, 0.0, 0.0}},// 四角形の頂点（左下）
////
////		////5　上
////		//{ XMVectorSet(-1.0f,  1.0f, 1.0f, 0.0f), {0.0, 0.5, 0.0, 0.0}},// 四角形の頂点（左上）
////		//{ XMVectorSet(1.0f,  1.0f, 1.0f, 0.0f),  {0.25, 0.5, 0.0, 0.0}},//四角形の頂点（右上）
////		//{ XMVectorSet(1.0f, 1.0f, -1.0f, 0.0f),	  {0.25, 1.0, 0.0, 0.0}},// 四角形の頂点（右下）
////		//{ XMVectorSet(-1.0f, 1.0f, -1.0f, 0.0f),   {0.0, 1.0, 0.0, 0.0}},// 四角形の頂点（左下）
////
////		////6　後ろ
////		//{ XMVectorSet(-1.0f,  1.0f, 1.0f, 0.0f), {0.25, 0.5, 0.0, 0.0}},// 四角形の頂点（左上）
////		//{ XMVectorSet(1.0f,  1.0f, 1.0f, 0.0f),  {0.5, 0.5, 0.0, 0.0}},//四角形の頂点（右上）
////		//{ XMVectorSet(1.0f, -1.0f, 1.0f, 0.0f),  {0.5, 1.0, 0.0, 0.0}},// 四角形の頂点（右下）
////		//{ XMVectorSet(-1.0f, -1.0f, 1.0f, 0.0f), {0.25, 1.0, 0.0, 0.0}},// 四角形の頂点（左下）
////
////		 //{ XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.0, 0.0, 0.0, 0.0)},	// 四角形の頂点（左上）, UV
////		//{ XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(1.0, 0.0, 0.0, 0.0)},	// 四角形の頂点（右上）, UV
////		//{ XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),  XMVectorSet(1.0, 1.0, 0.0, 0.0)},	// 四角形の頂点（右下）, UV
////		//{ XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.0, 1.0, 0.0, 0.0)}	// 四角形の頂点（左下）, UV
////		{{ -1.0f,  1.0f, -1.0f },  XMVectorSet(0.0, 0.0, 0.0, 0.0) ,XMVectorSet(0.0f,0.0f,0.0f,0.0f)},
////		{{  1.0f,  1.0f, -1.0f },  XMVectorSet(0.25, 0.0, 0.0, 0.0),XMVectorSet(0.0f,0.0f,0.0f,0.0f)},
////		{{ -1.0f, -1.0f, -1.0f },  XMVectorSet(0.0, 0.5, 0.0, 0.0),XMVectorSet(0.0f, 0.0f, 0.0f,0.0f)},
////		{{  1.0f, -1.0f, -1.0f },  XMVectorSet(0.25, 0.5, 0.0, 0.0),XMVectorSet(0.0f, 0.0f, 0.0f,0.0f)},
////
////		{{ -1.0f,  1.0f,  1.0f },  XMVectorSet(0.25, 0.5, 0.0, 0.0),XMVectorSet(0.0f,  0.0f, 0.0f,1.0f)},
////		{{ -1.0f, -1.0f,  1.0f },  XMVectorSet(0.25, 1.0, 0.0, 0.0),XMVectorSet(0.0f,0.0f,0.0f,1.0f)},
////		{{  1.0f,  1.0f,  1.0f },  XMVectorSet(0.5, 0.5, 0.0, 0.0),XMVectorSet(0.0f,0.0f,0.0f,1.0f)},
////		{{  1.0f, -1.0f,  1.0f },  XMVectorSet(0.5, 1.0, 0.0, 0.0),XMVectorSet(0.0f, 0.0f, 0.0f ,1.0f)},
////
////		{{ -1.0f,  1.0f,  1.0f },  XMVectorSet(0.25, 0.0, 0.0, 0.0),XMVectorSet(-1.0f,  0.0f,  0.0f,0.0f)},
////		{{ -1.0f,  1.0f,  -1.0f },  XMVectorSet(0.5, 0.0, 0.0, 0.0),XMVectorSet(-1.0f,  0.0f,  0.0f,0.0f)},
////		{{ -1.0f, -1.0f,  1.0f },  XMVectorSet(0.25, 0.5, 0.0, 0.0),XMVectorSet(-1.0f, 0.0f,  0.0f,0.0f)},
////		{{ -1.0f, -1.0f,  -1.0f },  XMVectorSet(0.5, 0.5, 0.0, 0.0),XMVectorSet(-1.0f, 0.0f,  0.0f,0.0f)},
////
////		{{  1.0f,  1.0f,  1.0f },  XMVectorSet(0.0, 0.5, 0.0, 0.0),XMVectorSet(1.0f,0.0f,0.0f,0.0f)},
////		{{  1.0f, -1.0f,  1.0f },  XMVectorSet(0.25, 0.5, 0.0, 0.0),XMVectorSet(1.0f,0.0f,0.0f,0.0f)},
////		{{  1.0f,  1.0f,  -1.0f },  XMVectorSet(0.0, 1.0, 0.0, 0.0),XMVectorSet(1.0f,0.0f,0.0f,0.0f)},
////		{{  1.0f, -1.0f,  -1.0f },  XMVectorSet(0.25, 1.0, 0.0, 0.0),XMVectorSet(1.0f,0.0f,0.0f,0.0f)},
////
////		{{ -1.0f,  1.0f,   1.0f },  XMVectorSet(0.5, 0.0, 0.0, 0.0),XMVectorSet(0.0f,1.0f,0.0f,0.0f)},
////		{{ -1.0f,  1.0f,  -1.0f },  XMVectorSet(0.5, 0.5, 0.0, 0.0),XMVectorSet(0.0f,1.0f,0.0f,0.0f)},
////		{{  1.0f,  1.0f,   1.0f },  XMVectorSet(0.75, 0.0, 0.0, 0.0),XMVectorSet(0.0f,1.0f,0.0f,0.0f)},
////		{{  1.0f,  1.0f,  -1.0f },  XMVectorSet(0.75, 0.5, 0.0, 0.0),XMVectorSet(0.0f,1.0f,0.0f,0.0f)},
////
////		{{ -1.0f, -1.0f,  1.0f }, XMVectorSet(0.75, 0.0, 0.0, 0.0),XMVectorSet(0.0f,-1.0f,0.0f,0.0f)},//20
////		{{ -1.0f, -1.0f,  -1.0f }, XMVectorSet(0.75, 0.5, 0.0, 0.0),XMVectorSet(0.0f,-1.0f,0.0f,0.0f)},//21
////		{{  1.0f, -1.0f,  1.0f }, XMVectorSet(1.0, 0.0, 0.0, 0.0),XMVectorSet(0.0f,-1.0f,0.0f,0.0f)},//22
////		{{  1.0f, -1.0f,  -1.0f }, XMVectorSet(1.0, 0.5, 0.0, 0.0),XMVectorSet(0.0f,-1.0f,0.0f,0.0f)},//23
////
////
////	};
////int index[] = {
////		1,0,2, 1,2,3,
////		5,4,6, 5,6,7,
////		9,8,10, 9,10,11,
////		13,12,14, 13,14,15,
////		18,16,17, 18,17,19,
////		20,22,21, 22,23,21,
////	//自分から見た時に指定した回り順に指定する　裏なら反時計回り
////
////		/*0, 1, 2, 3, 2, 1,
////		4, 5, 6, 7, 6, 5,
////		8, 9, 10, 11, 10, 9,
////		12, 13, 14, 15, 14, 13,
////		16, 18, 17, 19, 17, 18,
////		20, 21, 22, 23, 22, 21,*/
////
////};
////
////	//インデックス情報 四角形
////	//int index[] = { 0,2,3, 0,1,2, 4,1,0, 4,5,1, 4,6,7, 4,5,6, 4,3,7, 4,0,3, 1,6,2, 1,5,6, 7,2,3, 7,6,2 };
////	//int index[] = { 0,1,2, 0,2,3, 4,5,6, 4,6,7, 8,9,10,  8,10,11,  12,13,14, 12,14,15,   16,17,18, 16,18,19,   20,21,22, 20,22,23,  };
////
//
//	InitVertexData();
//
//	if (FAILED(CreateVertexBuffer()))
//	{
//		return E_FAIL;
//	}
//
//	InitIndexData();
//
//	if (FAILED(CreateIndexBuffer()))
//	{
//		return E_FAIL;
//	}
//	if (FAILED(CreateConstantBuffer()))
//	{
//		return E_FAIL;
//	}
//
//	return S_OK;
//
//
//	//// 頂点データ用バッファの設定
//	//D3D11_BUFFER_DESC bd_vertex;
//	//bd_vertex.ByteWidth = sizeof(VERTEX) * vertexNum_;
//	//bd_vertex.Usage = D3D11_USAGE_DEFAULT;
//	//bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//	//bd_vertex.CPUAccessFlags = 0;
//	//bd_vertex.MiscFlags = 0;
//	//bd_vertex.StructureByteStride = 0;
//	//D3D11_SUBRESOURCE_DATA data_vertex;
//	//data_vertex.pSysMem = vertices_.data();
//	//hr = Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
//	//if (FAILED(hr))
//	//{
//	//	MessageBox(NULL, L"頂点バッファの作成に失敗", NULL, MB_OK);
//	//	return hr;
//	//}
//
//	//// インデックスバッファを生成する
//	//D3D11_BUFFER_DESC   bd;
//	//bd.Usage = D3D11_USAGE_DEFAULT;
//	//bd.ByteWidth = sizeof(int) * indexNum_;
//	//bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
//	//bd.CPUAccessFlags = 0;
//	//bd.MiscFlags = 0;
//	//D3D11_SUBRESOURCE_DATA InitData;
//	//InitData.pSysMem = index_.data();
//	//InitData.SysMemPitch = 0;
//	//InitData.SysMemSlicePitch = 0;
//	//hr = Direct3D::pDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
//	//if (FAILED(hr))
//	//{
//	//	MessageBox(NULL, L"インデックスバッファの作成に失敗", NULL, MB_OK);
//	//	return hr;
//	//}
//
//	////コンスタントバッファ作成
//	//D3D11_BUFFER_DESC cb;
//	//cb.ByteWidth = sizeof(CONSTANT_BUFFER);
//	//cb.Usage = D3D11_USAGE_DYNAMIC;
//	//cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//	//cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
//	//cb.MiscFlags = 0;
//	//cb.StructureByteStride = 0;
//	//// コンスタントバッファの作成
//	//hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
//	//if (FAILED(hr))
//	//{
//	//	MessageBox(NULL, L"コンスタントバッファの作成に失敗", NULL, MB_OK);
//	//	return hr;
//	//}
//	//pTexture_ = new Texture;
//	//pTexture_->Load("Asset\\dice.png");
//	//return S_OK;
//}

//void Dice::Draw()
//{
//	Direct3D::SetShader(SHADER_TYPE::SHADER_3D);
//
//	CONSTANT_BUFFER cb;
//	cb.matWVP = XMMatrixTranspose(Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
//
//	D3D11_MAPPED_SUBRESOURCE pdata;
//	Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
//	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る
//	Direct3D::pContext->Unmap(pConstantBuffer_, 0);	//再開
//
//	//頂点バッファ
//	UINT stride = sizeof(VERTEX);
//	UINT offset = 0;
//	Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);
//
//	// インデックスバッファーをセット
//	stride = sizeof(int);
//	offset = 0;
//	Direct3D::pContext->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);
//
//	//コンスタントバッファ
//	Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
//	Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用
//
//	//サンプラーとシェーダーリソースビューをシェーダにセット
//	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
//	Direct3D::pContext->PSSetSamplers(0, 1, &pSampler);
//
//	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
//	Direct3D::pContext->PSSetShaderResources(0, 1, &pSRV);
//	//
//
//	Direct3D::pContext->DrawIndexed(36, 0, 0); //四角形
//}

//void Dice::Draw(Transform& transform)
//{	
//	Direct3D::SetShader(SHADER_TYPE::SHADER_3D);
//	transform.Calculation();
//
//	PassDataToCB(transform.GetWorldMatrix());
//
//	SetBufferToPipeline();
//
//	Direct3D::pContext->DrawIndexed(index_.size(), 0, 0);
//
//
//	
//	
//
////	Direct3D::pContext->DrawIndexed(36, 0, 0); //四角形
//}

//void Dice::Release()
//{
//}

//HRESULT Dice::CreateVertexBuffer()
//{
//	HRESULT hr;
//	// 頂点データ用バッファの設定
//	D3D11_BUFFER_DESC bd_vertex;
//	bd_vertex.ByteWidth = sizeof(VERTEX) * vertexNum_;
//	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
//	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//	bd_vertex.CPUAccessFlags = 0;
//	bd_vertex.MiscFlags = 0;
//	bd_vertex.StructureByteStride = 0;
//	D3D11_SUBRESOURCE_DATA data_vertex;
//	data_vertex.pSysMem = vertices_.data();
//	hr = Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
//
//	if (FAILED(hr))
//	{
//		MessageBox(NULL, L"頂点バッファの作成に失敗", NULL, MB_OK);
//		return hr;
//	}
//	return S_OK;
//}

//HRESULT Dice::CreateIndexBuffer()
//{
//	HRESULT hr;
//	// インデックスバッファを生成する
//	D3D11_BUFFER_DESC   bd;
//	bd.Usage = D3D11_USAGE_DEFAULT;
//	bd.ByteWidth = sizeof(int) * indexNum_;
//	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
//	bd.CPUAccessFlags = 0;
//	bd.MiscFlags = 0;
//
//	D3D11_SUBRESOURCE_DATA InitData;
//	InitData.pSysMem = index_.data();
//	InitData.SysMemPitch = 0;
//	InitData.SysMemSlicePitch = 0;
//	hr = Direct3D::pDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
//	if (FAILED(hr))
//	{
//		MessageBox(NULL, L"インデックスバッファの作成に失敗", NULL, MB_OK);
//		return hr;
//	}
//	return S_OK;
//}

//HRESULT Dice::CreateConstantBuffer()
//{
//	HRESULT hr;
//	//コンスタントバッファ作成
//	D3D11_BUFFER_DESC cb;
//	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
//	cb.Usage = D3D11_USAGE_DYNAMIC;
//	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
//	cb.MiscFlags = 0;
//	cb.StructureByteStride = 0;
//
//	// コンスタントバッファの作成
//	hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
//	if (FAILED(hr))
//	{
//		MessageBox(NULL, L"コンスタントバッファの作成に失敗", NULL, MB_OK);
//		return hr;
//	}
//
//	pTexture_ = new Texture;
//	pTexture_->Load("Asset\\dice.png");
//
//	return S_OK;
//}

//HRESULT Dice::LoadTexture()
//{
//	return E_NOTIMPL;
//}

void Dice::InitVertexData()
{
	vertices_ =
	{
		{{ -1.0f,  1.0f, -1.0f },  XMVectorSet(0.0, 0.0, 0.0, 0.0) ,XMVectorSet(0.0f,0.0f,0.0f,0.0f)},
		{{  1.0f,  1.0f, -1.0f },  XMVectorSet(0.25, 0.0, 0.0, 0.0),XMVectorSet(0.0f,0.0f,0.0f,0.0f)},
		{{ -1.0f, -1.0f, -1.0f },  XMVectorSet(0.0, 0.5, 0.0, 0.0),XMVectorSet(0.0f, 0.0f, 0.0f,0.0f)},
		{{  1.0f, -1.0f, -1.0f },  XMVectorSet(0.25, 0.5, 0.0, 0.0),XMVectorSet(0.0f, 0.0f, 0.0f,0.0f)},

		{{ -1.0f,  1.0f,  1.0f },  XMVectorSet(0.25, 0.5, 0.0, 0.0),XMVectorSet(0.0f,  0.0f, 0.0f,1.0f)},
		{{ -1.0f, -1.0f,  1.0f },  XMVectorSet(0.25, 1.0, 0.0, 0.0),XMVectorSet(0.0f,0.0f,0.0f,1.0f)},
		{{  1.0f,  1.0f,  1.0f },  XMVectorSet(0.5, 0.5, 0.0, 0.0),XMVectorSet(0.0f,0.0f,0.0f,1.0f)},
		{{  1.0f, -1.0f,  1.0f },  XMVectorSet(0.5, 1.0, 0.0, 0.0),XMVectorSet(0.0f, 0.0f, 0.0f ,1.0f)},

		{{ -1.0f,  1.0f,  1.0f },  XMVectorSet(0.25, 0.0, 0.0, 0.0),XMVectorSet(-1.0f,  0.0f,  0.0f,0.0f)},
		{{ -1.0f,  1.0f,  -1.0f },  XMVectorSet(0.5, 0.0, 0.0, 0.0),XMVectorSet(-1.0f,  0.0f,  0.0f,0.0f)},
		{{ -1.0f, -1.0f,  1.0f },  XMVectorSet(0.25, 0.5, 0.0, 0.0),XMVectorSet(-1.0f, 0.0f,  0.0f,0.0f)},
		{{ -1.0f, -1.0f,  -1.0f },  XMVectorSet(0.5, 0.5, 0.0, 0.0),XMVectorSet(-1.0f, 0.0f,  0.0f,0.0f)},

		{{  1.0f,  1.0f,  1.0f },  XMVectorSet(0.0, 0.5, 0.0, 0.0),XMVectorSet(1.0f,0.0f,0.0f,0.0f)},
		{{  1.0f, -1.0f,  1.0f },  XMVectorSet(0.25, 0.5, 0.0, 0.0),XMVectorSet(1.0f,0.0f,0.0f,0.0f)},
		{{  1.0f,  1.0f,  -1.0f },  XMVectorSet(0.0, 1.0, 0.0, 0.0),XMVectorSet(1.0f,0.0f,0.0f,0.0f)},
		{{  1.0f, -1.0f,  -1.0f },  XMVectorSet(0.25, 1.0, 0.0, 0.0),XMVectorSet(1.0f,0.0f,0.0f,0.0f)},

		{{ -1.0f,  1.0f,   1.0f },  XMVectorSet(0.5, 0.0, 0.0, 0.0),XMVectorSet(0.0f,1.0f,0.0f,0.0f)},
		{{ -1.0f,  1.0f,  -1.0f },  XMVectorSet(0.5, 0.5, 0.0, 0.0),XMVectorSet(0.0f,1.0f,0.0f,0.0f)},
		{{  1.0f,  1.0f,   1.0f },  XMVectorSet(0.75, 0.0, 0.0, 0.0),XMVectorSet(0.0f,1.0f,0.0f,0.0f)},
		{{  1.0f,  1.0f,  -1.0f },  XMVectorSet(0.75, 0.5, 0.0, 0.0),XMVectorSet(0.0f,1.0f,0.0f,0.0f)},

		{{ -1.0f, -1.0f,  1.0f }, XMVectorSet(0.75, 0.0, 0.0, 0.0),XMVectorSet(0.0f,-1.0f,0.0f,0.0f)},//20
		{{ -1.0f, -1.0f,  -1.0f }, XMVectorSet(0.75, 0.5, 0.0, 0.0),XMVectorSet(0.0f,-1.0f,0.0f,0.0f)},//21
		{{  1.0f, -1.0f,  1.0f }, XMVectorSet(1.0, 0.0, 0.0, 0.0),XMVectorSet(0.0f,-1.0f,0.0f,0.0f)},//22
		{{  1.0f, -1.0f,  -1.0f }, XMVectorSet(1.0, 0.5, 0.0, 0.0),XMVectorSet(0.0f,-1.0f,0.0f,0.0f)},//23

	};
	vertexNum_ = vertices_.size();
}

void Dice::InitIndexData()
{
	index_ = { 
		1,0,2, 1,2,3,
		5,4,6, 5,6,7,
		9,8,10, 9,10,11,
		13,12,14, 13,14,15,
		18,16,17, 18,17,19,
		20,22,21, 22,23,21, };
	indexNum_ = index_.size();
}

//void Dice::PassDataToCB(XMMATRIX worldMatrix)
//{
//	CONSTANT_BUFFER cb;
//	cb.matWVP = XMMatrixTranspose(worldMatrix * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
//	cb.matW = XMMatrixTranspose(worldMatrix);
//
//	D3D11_MAPPED_SUBRESOURCE pdata;
//	Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
//	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る
//	Direct3D::pContext->Unmap(pConstantBuffer_, 0);	//再開
//
//}

//void Dice::SetBufferToPipeline()
//{
//	//頂点バッファ
//	UINT stride = sizeof(VERTEX);
//	UINT offset = 0;
//	Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);
//
//	// インデックスバッファーをセット
//	stride = sizeof(int);
//	offset = 0;
//	Direct3D::pContext->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);
//
//	//コンスタントバッファ
//	Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
//	Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用
//
//	//サンプラーとシェーダーリソースビューをシェーダにセット
//	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
//	Direct3D::pContext->PSSetSamplers(0, 1, &pSampler);
//
//	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
//	Direct3D::pContext->PSSetShaderResources(0, 1, &pSRV);
//}
