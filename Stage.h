#pragma once
#include"FBX.h"
#include<string>
class Stage
{
    FBX* pFBX;
    FBX* pFBXarray[5];
    //int table[20][20];
    
    struct Data
    {
        int height;
        int type;
    };
    Data table[20][20];

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

    //ダイアログプロシージャをwinmainから持ってきたもの
    BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
};

