#pragma once
#include"FBX.h"
class Stage
{
    FBX* pFBX;
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
};

