#pragma once
#include"FBX.h"
#include<string>


using std::ifstream;
namespace {
    const int tablesize = 20;
}

class Stage
{
    FBX* pFBXarray[5];
    
    struct Data
    {
        int height;
        int type;
    };
    Data table[20][20];
    int selectMode;//�n�`���グ�邩�����邩�ς��邩
    int selectType;//�n�`�̎��

    //�ۑ�
    void Save();

    //�J��
    void Open();

public:
    //�R���X�g���N�^
    Stage();

    //�f�X�g���N�^
    ~Stage();

    //������
    void Initialize() ;

    //�X�V
    void Update() ;

    //�`��
    void Draw() ;

    //�J��
    void Release();

    //�E�B���h�E�i�_�C�A���O�j�v���V�[�W����winmain���玝���Ă�������
    LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
};

