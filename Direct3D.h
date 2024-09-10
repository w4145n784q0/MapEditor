#pragma once

#include <d3d11.h>
#include <assert.h>

enum SHADER_TYPE
{
	SHADER_2D,
	SHADER_3D,
	SHADER_MAX
};

//リンカ
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

namespace Direct3D

{
	//初期化
	HRESULT Initialize(int winW, int winH, HWND hWnd);
	//シェーダー準備
	HRESULT InitShader();
	HRESULT InitShader3D(); //simple3D.hlslのための初期化
	HRESULT InitShader2D(); //simple2D.hlslのための初期化

	void SetShader(SHADER_TYPE type);



	//描画開始
	void BeginDraw();
	//描画終了
	void EndDraw();
	//解放
	void Release();

	extern ID3D11Device* pDevice;
	extern ID3D11DeviceContext* pContext;
	extern const int WINDOW_WIDTH;
	extern const int WINDOW_HEIGHT;

};