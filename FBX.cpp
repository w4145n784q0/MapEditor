#include "FBX.h"
#include "Camera.h"
#include <filesystem>

namespace fs = std::filesystem;

FBX::FBX()
	:pVertexBuffer_(nullptr), pIndexBuffer_(nullptr), pConstantBuffer_(nullptr),
	vertexCount_(-1), polygonCount_(-1)
{
}

//ロードしていろいろ初期化
HRESULT FBX::Load(std::string fileName)
{
	//マネージャを生成
	FbxManager* pFbxManager = FbxManager::Create();

	//インポーターを生成
	FbxImporter* fbxImporter = FbxImporter::Create(pFbxManager, "imp");
	fbxImporter->Initialize(fileName.c_str(), -1, pFbxManager->GetIOSettings());

	//シーンオブジェクトにFBXファイルの情報を流し込む
	FbxScene* pFbxScene = FbxScene::Create(pFbxManager, "fbxscene");
	fbxImporter->Import(pFbxScene);
	fbxImporter->Destroy();

	//メッシュ情報を取得
	FbxNode* rootNode = pFbxScene->GetRootNode();
	FbxNode* pNode = rootNode->GetChild(0);
	FbxMesh* mesh = pNode->GetMesh();

	//各情報の個数を取得
	vertexCount_ = mesh->GetControlPointsCount();	//頂点の数
	polygonCount_ = mesh->GetPolygonCount();	//ポリゴンの数
	materialCount_ = pNode->GetMaterialCount();

	fs::path cPath, basePath;
	cPath = fs::current_path();
	basePath = cPath;
	string subDir("Assets");
	//Assetsフォルダまでのフルパスを生成する
	fs::path subPath(cPath.string() + "\\" + subDir);
	assert(fs::exists(subPath));
	//カレントディレクトリを移動
	fs::current_path(subPath);

	InitVertex(mesh);
	InitIndex(mesh);
	InitConstantBuffer();
	InitMaterial(pNode);

	//カレントパスをもとどおりにもどす
	fs::current_path(basePath);

	//マネージャ解放
	pFbxManager->Destroy();
	return S_OK;
}


void FBX::InitVertex(fbxsdk::FbxMesh* mesh)
{
	//頂点情報を入れる配列
	//VERTEX* vertices = new VERTEX[vertexCount_];
	std::vector<VERTEX> vertices(vertexCount_);
	//全ポリゴン
	for (DWORD poly = 0; poly < polygonCount_; poly++)//dword　microsoftで使われる型　とても大きい
	{
		//3頂点分
		for (int vertex = 0; vertex < 3; vertex++)
		{
			//調べる頂点の番号
			int index = mesh->GetPolygonVertex(poly, vertex);

			//頂点の位置
			FbxVector4 pos = mesh->GetControlPointAt(index);
			vertices[index].position = XMVectorSet((float)pos[0], (float)pos[1], (float)pos[2], 0.0f);

			//頂点に割り当てられたUV
			FbxLayerElementUV* pUV = mesh->GetLayer(0)->GetUVs();
			int uvIndex = mesh->GetTextureUVIndex(poly, vertex, FbxLayerElement::eTextureDiffuse);
			FbxVector2  uv = pUV->GetDirectArray().GetAt(uvIndex);
			vertices[index].uv = XMVectorSet((float)(uv.mData[0]), (float)(1.0f - uv.mData[1]), 0.0f, 0.0f);//変更した
		
			//頂点の法線
			FbxVector4 Normal;
			mesh->GetPolygonVertexNormal(poly, vertex, Normal);	//ｉ番目のポリゴンの、ｊ番目の頂点の法線をゲット
			vertices[index].normal = XMVectorSet((float)Normal[0], (float)Normal[1], (float)Normal[2], 0.0f);
		
		}

	}
	// 頂点バッファ作成
	//（自分でやって）
	//頂点バッファ
	HRESULT hr;
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(VERTEX) * vertexCount_;
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices.data();
	hr = Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"頂点バッファの作成に失敗しました", L"エラー", MB_OK);
	}
}

void FBX::InitIndex(fbxsdk::FbxMesh* mesh)
{
	pIndexBuffer_ = new ID3D11Buffer * [materialCount_];
	//int* index = new int[polygonCount_ * 3];
	indexCount_ = std::vector<int>(materialCount_);
	std::vector<int> index(polygonCount_ * 3);

	for (int i = 0; i < materialCount_; i++)
	{
		int count = 0;
		//全ポリゴン
		//index.clear();
		for (DWORD poly = 0; poly < polygonCount_; poly++)
		{
			FbxLayerElementMaterial* mtl = mesh->GetLayer(0)->GetMaterials();
			int mtlId = mtl->GetIndexArray().GetAt(poly);
			if (mtlId == i) {
				//3頂点分
				for (DWORD vertex = 0; vertex < 3; vertex++)
				{
					index[count] = mesh->GetPolygonVertex(poly, vertex);
					count++;
				}
			}
		}
		indexCount_[i] = count;
		//	（ここもデータサイズを指定するところだけ注意）
		D3D11_BUFFER_DESC   bd;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(int) * polygonCount_ * 3;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = index.data();
		InitData.SysMemPitch = 0;
		InitData.SysMemSlicePitch = 0;

		HRESULT hr;
		hr = Direct3D::pDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer_[i]);
		if (FAILED(hr))
		{
			MessageBox(NULL, L"インデックスバッファの作成に失敗しました", L"エラー", MB_OK);
		}
	}
}

void FBX::InitConstantBuffer()
{
	//Quadと一緒
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// コンスタントバッファの作成
	HRESULT hr;
	hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"コンスタントバッファの作成に失敗しました", L"エラー", MB_OK);
	}
}

void FBX::InitMaterial(fbxsdk::FbxNode* pNode)
{
	pMaterialList_ = std::vector<MATERIAL>(materialCount_);
	for (int i = 0; i < materialCount_; i++)
	{
		//i番目のマテリアル情報を取得
		FbxSurfaceMaterial* pMaterial = pNode->GetMaterial(i);

		//テクスチャ情報
		FbxProperty  lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);

		//テクスチャの数数
		int fileTextureCount = lProperty.GetSrcObjectCount<FbxFileTexture>();

		//テクスチャあり
		if (fileTextureCount > 0)
		{
			FbxFileTexture* textureInfo = lProperty.GetSrcObject<FbxFileTexture>(0);
			const char* textureFilePath = textureInfo->GetRelativeFileName();
			fs::path texFile(textureFilePath);
			//ここで存在チェックが必要（あとでやろう）
			if (fs::is_regular_file(texFile))
			{
				pMaterialList_[i].pTexture = new Texture;
				pMaterialList_[i].pTexture->Load(texFile.string());
			}
			else
			{
				//Error must be handled here
			}

		}
		//テクスチャ無し
		else
		{
			//this part are witten after
			pMaterialList_[i].pTexture = nullptr;
		}


	}
}



void FBX::Draw(Transform& transform)
{
	//Quadをアレンジ
	Direct3D::SetShader(SHADER_3D);
	transform.Calculation();

	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(transform.GetWorldMatrix() * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
	cb.matNormal = XMMatrixTranspose(transform.GetNormalMatrix());
	// インデックスバッファーをセット
	for (int i = 0; i < materialCount_; i++) {
		D3D11_MAPPED_SUBRESOURCE pdata;
		Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
		memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る

		Direct3D::pContext->Unmap(pConstantBuffer_, 0);	//再開

		//頂点バッファ、インデックスバッファ、コンスタントバッファをパイプラインにセット
		//頂点バッファ
		UINT stride = sizeof(VERTEX);
		UINT offset = 0;
		Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);



		stride = sizeof(int);
		offset = 0;
		Direct3D::pContext->IASetIndexBuffer(pIndexBuffer_[i], DXGI_FORMAT_R32_UINT, 0);


		//コンスタントバッファ
		Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
		Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用

		if (!(pMaterialList_[i].pTexture == nullptr)) {
			//サンプラーとシェーダーリソースビューをシェーダにセット
			ID3D11SamplerState* pSampler = pMaterialList_[i].pTexture->GetSampler();
			Direct3D::pContext->PSSetSamplers(0, 1, &pSampler);

			ID3D11ShaderResourceView* pSRV = pMaterialList_[i].pTexture->GetSRV();
			Direct3D::pContext->PSSetShaderResources(0, 1, &pSRV);

		}
		//描画
		Direct3D::pContext->DrawIndexed(indexCount_[i], 0, 0);
	}
}

void FBX::Release()
{
}