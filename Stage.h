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

    //�_�C�A���O�v���V�[�W����winmain���玝���Ă�������
    BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
};

