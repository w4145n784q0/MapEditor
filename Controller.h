#pragma once
#include <dInput.h>
#include"Transform.h"

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")

//SAFE_RELEASEは別のクラスで宣言していてもここで宣言しないと使えない
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

class Controller
{
	Transform transform;
	XMFLOAT3 tar;

public:
	//コンストラクタ
	Controller();

	//デストラクタ
	~Controller();

	//初期化
	void Initialize();

	//更新
	void Update();

	//開放
	void Release();

	Transform GetTransform() { return transform; }
};

