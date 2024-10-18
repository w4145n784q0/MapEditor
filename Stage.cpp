#include "Stage.h"
#include"Input.h"
#include"Camera.h"
#include"Direct3D.h"
#include"resource.h"

namespace {
	int blockwidth = 20;
	int blockheight = 20;
}

Stage::Stage() :pFBXarray(),selectMode(0),selectType(0)
{
	for (int i = 0; i < blockheight; i++)
	{
		for (int j = 0; j < blockwidth; j++)
		{
			table[i][j].height = 1;
			table[i][j].type = 0;
		}
	}
	table[0][0].height = 5;
	table[0][9].height = 3;
	table[5][2].type = 3;
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
	/*pFBX = new FBX;
	pFBX->Load("Assets/BoxDefault.fbx");*/

	/*pFBXarray[0] = new FBX;
	pFBXarray[0]->Load("Assets/BoxDefault.fbx");
	pFBXarray[1] = new FBX;
	pFBXarray[1]->Load("Assets/BoxBrick.fbx");
	pFBXarray[2] = new FBX;
	pFBXarray[2]->Load("Assets/BoxSand.fbx");
	pFBXarray[3] = new FBX;
	pFBXarray[3]->Load("Assets/BoxWater.fbx");
	pFBXarray[4] = new FBX;
	pFBXarray[4]->Load("Assets/BoxGrass.fbx");*/

	string fileName[] = { "BoxDefault","BoxBrick","BoxSand"
		,"BoxWater","BoxGrass" };
	for (int i = 0; i < 5; i++)
	{
		string path = "Assets/" + fileName[i] + ".fbx";
		pFBXarray[i] = new FBX;
		pFBXarray[i]->Load(path);
	}
}

void Stage::Update()
{
	if (Input::IsMouseButtonDown(0))
	{
		XMMATRIX matView = Camera::GetViewMatrix();//�r���[�s��
		XMMATRIX matProj = Camera::GetProjectionMatrix();//�v���W�F�N�V�����s��

		float w = Direct3D::WINDOW_WIDTH/2;
		float h = Direct3D::WINDOW_HEIGHT/2;

		XMMATRIX vp = //�r���[�|�[�g�s��
		{
			w, 0, 0, 0,
			0, -h, 0, 0,
			0, 0, 1, 0,//z��1����Ȃ��Ɖ������Ȃ��s��Ƃ��Ă��������Ȃ�
			w, h, 0, 1, // ���̍s���ړ����iDirectX�̏ꍇ�j
			//
		};

		XMMATRIX invView = XMMatrixInverse(nullptr, matView);//�r���[�s��i�̋t�s��j
		XMMATRIX invProj = XMMatrixInverse(nullptr, matProj);//�v���W�F�N�V�����s��i�̋t�s��j
		XMMATRIX invVP = XMMatrixInverse(nullptr, vp);//�r���[�|�[�g�s��i�̋t�s��j

		XMVECTOR mouseFrontPos = Input::GetMousePosition();//�}�E�X�̈ʒu���Ƃ���XMvector��
		XMFLOAT3 MousePos;//�X�N���[�����W������XMfloat
		XMStoreFloat3(&MousePos, mouseFrontPos);//MousePos��mouseFrontPos�̒l��XMFLOAT�ɕϊ����ē����

		MousePos.z = 0;
		mouseFrontPos = XMLoadFloat3(&MousePos);//MousePos���x�N�g���ɕϊ� �J�������猩����͈͂ň�Ԍ��̖ʂ��擾

		MousePos.z = 1;//��ԉ����Ƃ�
		XMVECTOR mouseBackPos = XMLoadFloat3(&MousePos);//�}�E�X�̈ʒu���x�N�g����
		
		mouseFrontPos = XMVector3TransformCoord(mouseFrontPos, invVP * invProj * invView);
		mouseBackPos = XMVector3TransformCoord(mouseBackPos, invVP * invProj * invView);

		RayCastData data;
		XMStoreFloat4(&data.start, mouseFrontPos);
		XMStoreFloat4(&data.dir, mouseBackPos - mouseFrontPos);

		for (int x = 0; x < blockwidth; x++)
		{
			for (int z = 0; z < blockwidth; z++)
			{
				for (int y = 0; y < table[x][z].height; y++)
				{
					Transform trans;
					trans.position_.x = x;
					trans.position_.y = y;
					trans.position_.z = z;

					int type = table[x][z].type;
					pFBXarray[type]->RayCast(data, trans);
					if (data.hit == true)
					{
						switch (selectMode)
						{
						case 0:
							table[x][z].height++;
							break;
						case 1:
							if (table[x][z].height > 1)
							{
								table[x][z].height--;
							}
							break;
						case 2:
							table[x][z].type = selectType;
							break;
						default:
							break;
						}
						
						return;
					}
				}
			}
		}
	}
}
/*  
        XMFLOAT3 mousePosBack = Input::GetMousePosition();
        mousePosBack.z = 0.0f;
        XMFLOAT3 mousePosFront = Input::GetMousePosition();
        mousePosFront.z = 1.0f;

        //�@�@mousePosFront���x�N�g���ɕϊ�
        XMVECTOR vMouseFront = XMLoadFloat3(&mousePosFront); // �J�������猩����͈͂ň�Ԍ��̖ʂ��擾
        //�����ŕϊ�����(�O) 
        // �@��invVP�AinvPrj�AinvView��������
        vMouseFront = XMVector3TransformCoord(vMouseFront, invVP * invProj * invView);
        //�B�@mousePosBack���x�N�g���ɕϊ�
        XMVECTOR vMouseBack = XMLoadFloat3(&mousePosBack);
        //�C�@�B��invVP�AinvPrj�AinvView��������
        vMouseBack = XMVector3TransformCoord(vMouseBack, invVP * invProj * invView);
 
        RayCastDeta data;
        XMStoreFloat3(&data.start, vMouseFront);
        XMStoreFloat3(&data.dir, vMouseBack - vMouseFront);*/

void Stage::Draw()
{
	
	/*for (int i = 0; i < blockwidth; i++)
	{
		for (int j = 0; j < blockwidth; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				transform.position_.y = k;
				transform.position_.x = j;
				transform.position_.z = i;
				pFBX->Draw(transform);
			}
			
		}
	}*/

	for (int x = 0; x < blockwidth; x++)
	{
		for (int z = 0; z < blockwidth; z++)
		{
			for (int y = 0; y < table[x][z].height; y++)
			{
				//�\���ʒu���ς���Ă��邾��
				Transform transform;
				transform.position_.x = x;
				transform.position_.y = y;
				transform.position_.z = z;
				
				int type = table[x][z].type;
				pFBXarray[type]->Draw(transform);
			}

		}
	}

}

void Stage::Release()
{
	for (int i = 0; i < 5; i++)
	{
		pFBXarray[i]->Release();
		SAFE_DELETE(pFBXarray[i]);
	}

}

//�_�C�A���O�v���V�[�W��(�����̊֐��ɂ���)
BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
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
		SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_SETCURSEL, 0, 0);
		break;

	case WM_COMMAND:
		switch (LOWORD(wp))
		{
		case IDC_RADIO_UP:
			selectMode = 0;
			break;
		case IDC_RADIO_DOWN:
			selectMode = 1;
			break;
		case IDC_RADIO_CHANGE:
			selectMode = 2;
			break;
		case IDC_COMBO3:
			selectType = (int)SendMessage(GetDlgItem(hDlg,IDC_COMBO3), CB_GETCURSEL, 0, 0);
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
	}

	return FALSE;
}