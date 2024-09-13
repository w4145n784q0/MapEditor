//インクルード
#include <Windows.h>
#include"Direct3D.h"
#include<tchar.h>
#include"Camera.h"
#include"Input.h"
#include"Controller.h"

#include"Transform.h"
#include"FBX.h"
#include"assert.h"
#include"Stage.h"
#include"resource.h"//ダイアログのID定義に必要


//リンカ
#pragma comment(lib,"d3d11.lib")

Stage* pStage;
Controller* pController;

namespace{
//定数宣言
const wchar_t* WIN_CLASS_NAME = L"SampleGame";//ウィンドウクラス名
const wchar_t* APP_GAME = L"サンプルゲーム";//アプリケーション名
const int WINDOW_WIDTH = 800;//ウィンドウ幅
const int WINDOW_HEIGHT = 600;//ウィンドウの高さ
}

//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);


//エントリーポイント
//hinstance　インスタンスハンドル
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
  //ウィンドウクラス（設計図）を作成
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);             //この構造体のサイズ
    wc.hInstance = hInstance;                   //インスタンスハンドル
    wc.lpszClassName = WIN_CLASS_NAME;            //ウィンドウクラス名
    wc.lpfnWndProc = WndProc;                   //ウィンドウプロシージャ
    wc.style = CS_VREDRAW | CS_HREDRAW;         //スタイル（デフォルト）
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //アイコン
    wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //小さいアイコン
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //マウスカーソル
    wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); //メニュー（なし）
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //背景（白）
    RegisterClassEx(&wc);  //クラスを登録

    //ウィンドウサイズの計算
    //(表示領域をWINDOW_WIDTH * WINDOW_HEIGHTに指定するための計算)
    RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, TRUE);
    int winW = winRect.right - winRect.left;     //ウィンドウ幅
    int winH = winRect.bottom - winRect.top;     //ウィンドウ高さ

  //ウィンドウを作成
    HWND hWnd = CreateWindow(
        WIN_CLASS_NAME,         //ウィンドウクラス名 上のクラス名と同じ
        APP_GAME,     //タイトルバーに表示する内容
        WS_OVERLAPPEDWINDOW, //スタイル（普通のウィンドウ）
        CW_USEDEFAULT,       //表示位置左（おまかせ）
        CW_USEDEFAULT,       //表示位置上（おまかせ）
        winW,                 //ウィンドウ幅
        winH,                 //ウィンドウ高さ
        NULL,                //親ウインドウ（なし）
        NULL,                //メニュー（なし）
        hInstance,           //インスタンス
        NULL                 //パラメータ（なし）
    );

  //ウィンドウを表示
    ShowWindow(hWnd, nCmdShow);

    //IDD_DIALOGが見つかりませんと言われたら
    HWND hDlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1),hWnd, (DLGPROC)DialogProc);

    //Direct3D初期化
    HRESULT hr =  Direct3D::Initialize(winW, winH, hWnd);
    if (FAILED(hr))
    {
        return 0;
    }

    HRESULT hr2 = Direct3D::Initialize(winW, winH, hWnd);
    if (FAILED(hr))
    {
        return 0;
    }

    Camera::Initialize();

    //DirectInputの初期化
    Input::Initialize(hWnd);

    pStage = new Stage;
    pStage->Initialize();

    pController = new Controller;
    pController->Initialize();


    

    if (FAILED(hr))
    {
        MessageBox(NULL, L"Quadの初期化失敗", NULL, MB_OK);
        return 0;
    }

    if (FAILED(hr2))
    {
        MessageBox(NULL, L"Quadの初期化失敗", NULL, MB_OK);
        return 0;
    }

  //メッセージループ（何か起きるのを待つ）
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        //メッセージあり
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        //メッセージなし
        else
        {
            //カメラの更新
            Camera::Update();

            //
            pStage->Update();
            //ゲームの処理
            Direct3D::BeginDraw();

            //入力情報の更新
            Input::Update();

            //コントローラー
            pController->Update();

            pStage->Draw();
           // XMMATRIX mat = XMMatrixIdentity();
            //XMMATRIX mat = XMMatrixScaling(1 / 2.0f, 1 / 2.0f, 1.0f);
            //pSprite->Draw(mat);
            //回転
            //static float rot = 0.0;
            //rot += 0.001;
            ////角度をラジアンにするなら XMConvertToRadians
            ////ラジアンを角度にするならXMCOnvertToDegrees
            //XMMATRIX rmat = XMMatrixRotationX(rot);
            //rmat = rmat * XMMatrixRotationY(XMConvertToRadians(45.0));
            //
            //static float factor = 0.0;
            //factor += 0.001;
            //float scale = 1.5 + sin(factor);
            ////XMMATRIX smat = XMMatrixScaling(scale, scale, scale);
           // XMMATRIX tmat = XMMatrixTranslation(2.0 * sin(factor), 0, 0);
          //  XMMATRIX mat = smat * rmat * tmat;
           // XMMATRIX tmat = XMMatrixTranslation(3.0*cos(factor), 1.5*sin(factor), 0.0f);
            //単位行列　数字の1と同じ
         //   XMMATRIX mat = XMMatrixIdentity();
            //mat = rmat /** tmat*/;
            ////qu->Draw(mat);
            //di->Draw(mat);

            if (Input::IsKeyUp(DIK_ESCAPE))
            {
                static int cnt = 0;
                cnt++;
                if (cnt >= 3)
                {
                    PostQuitMessage(0);
                }
            }

            if (Input::IsMouseButtonUp(0))
            {
               // PostQuitMessage(0);
            }

            /*Transform trs;

            static float rot = 0;
            trs.scale_ = { 0.5,0.5,0.5 };
           
            trs.rotate_.y = rot * 0.5;
            rot = rot + 0.1;*/

            //t.position_.x += 0.5;
          //  t.scale_ = { 0.2,0.2,0.2 };
            //fbx.Draw(t);
           // d->Draw(trs);
            //qu->Draw(t);
            //qu->Draw(trs);
            //pSprite->Draw(t);

            //描画処理
            Direct3D::EndDraw();

        }
    }

   // SAFE_DELETE(qu);
    //SAFE_DELETE(d);
    //SAFE_DELETE(pSprite);
    pStage->Release();
    SAFE_DELETE(pStage);
    Input::Release();
    Direct3D::Release();
	return 0;
}


//ウィンドウプロシージャ（何かあった時によばれる関数）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);  //プログラム終了
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

BOOL CALLBACK DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_INITDIALOG:
        //HWND  h = GetDlgItem(hDlg, IDC_RADIO_UP);
        SendMessage(GetDlgItem(hDlg, IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);
        SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)L"デフォルト");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)L"レンガ");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)L"草");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)L"砂");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)L"水");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_SETCURSEL, 1, 0);
        break;

    case WM_COMMAND:
        switch (LOWORD(wp))
        {
        case IDC_RADIO_UP:
            break;
        case IDC_RADIO_DOWN:
            break;
        case IDC_RADIO_CHANGE:
            break;
        case ID_MENU_NEW:
            break;
        case ID_MENU_OPEN:
            break;
        case ID_MENU_SAVE:
            break;
        default:
            break;
        }
    case WM_MOUSEMOVE:
        Input::SetMousePosition(LOWORD(lp), HIWORD(lp));
        return 0;

    }

  
    return FALSE;
}