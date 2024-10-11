#pragma once
#include"Direct3D.h"
#include <DirectXMath.h>
#include"Texture.h"
#include<vector>
#include"Transform.h"
#include<filesystem>

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"

#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")
//マルチデバッグがmtならMDのところをMTにする

//classの外にかく
struct RayCastData
{
	XMFLOAT4 start;
	XMFLOAT4 dir;
	bool hit;
	float dist;
};

class FBX
{
private:

		//マテリアル
	struct MATERIAL
	{
		Texture* pTexture;
	};

	struct CONSTANT_BUFFER {
		XMMATRIX	matWVP;//ワールドビュープロジェクション
		XMMATRIX    matNormal;//法線ベクトルの変換用
	};

	//頂点情報
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
		XMVECTOR normal;//法線ベクトル　ノーマル追加
	};
	std::vector<VERTEX> vertices;//頂点データ
	std::vector<int> *index;//インデックスデータ

	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer** pIndexBuffer_; //インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ
	/*std::vector<MATERIAL>pMaterialBuffer;*/
	std::vector <MATERIAL> pMaterialList_;
	std::vector<int>indexCount_;

	int vertexCount_;	//頂点数
	int polygonCount_;	//ポリゴン数
	int materialCount_;	//マテリアルの個数
	void InitVertex(fbxsdk::FbxMesh* mesh);//頂点バッファ準備
	void InitIndex(fbxsdk::FbxMesh* mesh);//インデックスバッファ準備
	void InitConstantBuffer();//コンスタントバッファ準備
	void InitMaterial(fbxsdk::FbxNode* pNode);
	
public:
	FBX();
	HRESULT Load(std::string fileName);
	void    Draw(Transform& transform);
	void    Release();
	void RayCast(RayCastData& rayData, Transform& transform);//参照でポインタのように扱える
};

