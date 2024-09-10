#pragma once
#include"FBX.h"
class Stage
{
    FBX* pFBX;
public:
    //コンストラクタ
    Stage();

    //デストラクタ
    ~Stage();

    //初期化
    void Initialize() ;

    //更新
    void Update() ;

    //描画
    void Draw() ;

    //開放
    void Release();
};

