//�C���N���[�h
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
#include"resource.h"//�_�C�A���O��ID��`�ɕK�v


//�����J
#pragma comment(lib,"d3d11.lib")

Stage* pStage;
Controller* pController;

namespace{
//�萔�錾
const wchar_t* WIN_CLASS_NAME = L"SampleGame";//�E�B���h�E�N���X��
const wchar_t* APP_GAME = L"�T���v���Q�[��";//�A�v���P�[�V������
const int WINDOW_WIDTH = 800;//�E�B���h�E��
const int WINDOW_HEIGHT = 600;//�E�B���h�E�̍���
}

//�v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);


//�G���g���[�|�C���g
//hinstance�@�C���X�^���X�n���h��
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
  //�E�B���h�E�N���X�i�݌v�}�j���쐬
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);             //���̍\���̂̃T�C�Y
    wc.hInstance = hInstance;                   //�C���X�^���X�n���h��
    wc.lpszClassName = WIN_CLASS_NAME;            //�E�B���h�E�N���X��
    wc.lpfnWndProc = WndProc;                   //�E�B���h�E�v���V�[�W��
    wc.style = CS_VREDRAW | CS_HREDRAW;         //�X�^�C���i�f�t�H���g�j
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //�A�C�R��
    wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //�������A�C�R��
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //�}�E�X�J�[�\��
    wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); //���j���[�i�Ȃ��j
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //�w�i�i���j
    RegisterClassEx(&wc);  //�N���X��o�^

    //�E�B���h�E�T�C�Y�̌v�Z
    //(�\���̈��WINDOW_WIDTH * WINDOW_HEIGHT�Ɏw�肷�邽�߂̌v�Z)
    RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, TRUE);
    int winW = winRect.right - winRect.left;     //�E�B���h�E��
    int winH = winRect.bottom - winRect.top;     //�E�B���h�E����

  //�E�B���h�E���쐬
    HWND hWnd = CreateWindow(
        WIN_CLASS_NAME,         //�E�B���h�E�N���X�� ��̃N���X���Ɠ���
        APP_GAME,     //�^�C�g���o�[�ɕ\��������e
        WS_OVERLAPPEDWINDOW, //�X�^�C���i���ʂ̃E�B���h�E�j
        CW_USEDEFAULT,       //�\���ʒu���i���܂����j
        CW_USEDEFAULT,       //�\���ʒu��i���܂����j
        winW,                 //�E�B���h�E��
        winH,                 //�E�B���h�E����
        NULL,                //�e�E�C���h�E�i�Ȃ��j
        NULL,                //���j���[�i�Ȃ��j
        hInstance,           //�C���X�^���X
        NULL                 //�p�����[�^�i�Ȃ��j
    );

  //�E�B���h�E��\��
    ShowWindow(hWnd, nCmdShow);

    //IDD_DIALOG��������܂���ƌ���ꂽ��
    HWND hDlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1),hWnd, (DLGPROC)DialogProc);

    //Direct3D������
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

    //DirectInput�̏�����
    Input::Initialize(hWnd);

    pStage = new Stage;
    pStage->Initialize();

    pController = new Controller;
    pController->Initialize();


    

    if (FAILED(hr))
    {
        MessageBox(NULL, L"Quad�̏��������s", NULL, MB_OK);
        return 0;
    }

    if (FAILED(hr2))
    {
        MessageBox(NULL, L"Quad�̏��������s", NULL, MB_OK);
        return 0;
    }

  //���b�Z�[�W���[�v�i�����N����̂�҂j
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        //���b�Z�[�W����
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        //���b�Z�[�W�Ȃ�
        else
        {
            //�J�����̍X�V
            Camera::Update();

            //
            pStage->Update();
            //�Q�[���̏���
            Direct3D::BeginDraw();

            //���͏��̍X�V
            Input::Update();

            //�R���g���[���[
            pController->Update();

            pStage->Draw();
           // XMMATRIX mat = XMMatrixIdentity();
            //XMMATRIX mat = XMMatrixScaling(1 / 2.0f, 1 / 2.0f, 1.0f);
            //pSprite->Draw(mat);
            //��]
            //static float rot = 0.0;
            //rot += 0.001;
            ////�p�x�����W�A���ɂ���Ȃ� XMConvertToRadians
            ////���W�A�����p�x�ɂ���Ȃ�XMCOnvertToDegrees
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
            //�P�ʍs��@������1�Ɠ���
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

            //�`�揈��
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


//�E�B���h�E�v���V�[�W���i�������������ɂ�΂��֐��j
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);  //�v���O�����I��
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
        SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)L"�f�t�H���g");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)L"�����K");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)L"��");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)L"��");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)L"��");
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