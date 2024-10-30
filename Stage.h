#pragma once
#include"FBX.h"
#include<string>
#include<vector>

namespace {
    const int tablesize = 20;
}

using std::ifstream;
using std::vector;

class Stage
{
    FBX* pFBXarray[5];
    
    struct Data
    {
        int height;
        int type;
    };
    Data table[20][20];
    int selectMode;//地形を上げるか下げるか変えるか
    int selectType;//地形の種類
    vector<string> TableMapData;//tableの中身を保存
    vector<char> TableData;

    //保存
    void Save();

    //開く
    void Open();

    //開いたデータを読み込む
    void OpenFileStage();

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

    //ウィンドウ（ダイアログ）プロシージャをwinmainから持ってきたもの
    LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
};

