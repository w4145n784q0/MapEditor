#include "Stage.h"
#include"Input.h"
#include"Camera.h"
#include"Direct3D.h"
#include"resource.h"
#include<fstream>
#include<vector>

using std::ifstream;
using std::ofstream;
using std::vector;

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

	string fileName[] = { "BoxDefault","BoxBrick","BoxGrass"
		,"BoxSand","BoxWater" };
	for (int i = 0; i < 5; i++)
	{
		string path = "Assets/" + fileName[i] + ".fbx";
		pFBXarray[i] = new FBX;
		pFBXarray[i]->Load(path);
	}

	//ファイルを読み込む処理↓（途中）------------------------------
	int i = 0;
	vector<string> inputList;
	ifstream file("test.txt");
	string indata;
	if (file.fail()) {
		//PostQuitMessage(0);
	}
	
	while (std::getline(file, indata)) //一行ずつ読み込む
	{
		inputList.push_back(indata);
		getchar();
	}
	//file.close();
	


}

void Stage::Update()
{
	if (Input::IsMouseButtonDown(0))
	{
		XMMATRIX matView = Camera::GetViewMatrix();//ビュー行列
		XMMATRIX matProj = Camera::GetProjectionMatrix();//プロジェクション行列

		float w = Direct3D::WINDOW_WIDTH/2;
		float h = Direct3D::WINDOW_HEIGHT/2;

		XMMATRIX vp = //ビューポート行列
		{
			w, 0, 0, 0,
			0, -h, 0, 0,
			0, 0, 1, 0,//zは1じゃないと何もしない行列としておかしくなる
			w, h, 0, 1, // この行が移動分（DirectXの場合）
			//
		};

		XMMATRIX invView = XMMatrixInverse(nullptr, matView);//ビュー行列（の逆行列）
		XMMATRIX invProj = XMMatrixInverse(nullptr, matProj);//プロジェクション行列（の逆行列）
		XMMATRIX invVP = XMMatrixInverse(nullptr, vp);//ビューポート行列（の逆行列）

		XMVECTOR mouseFrontPos = Input::GetMousePosition();//マウスの位置をとってXMvectorへ
		XMFLOAT3 MousePos;//スクリーン座標を入れるXMfloat
		XMStoreFloat3(&MousePos, mouseFrontPos);//MousePosにmouseFrontPosの値をXMFLOATに変換して入れる

		MousePos.z = 0;
		mouseFrontPos = XMLoadFloat3(&MousePos);//MousePosをベクトルに変換 カメラから見える範囲で一番後ろの面を取得

		MousePos.z = 1;//一番奥をとる
		XMVECTOR mouseBackPos = XMLoadFloat3(&MousePos);//マウスの位置をベクトル化
		
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
				//表示位置が変わっているだけ
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

void Stage::Save()
{
	//名前を付けて保存する
	WCHAR fileName[MAX_PATH] = L"無題.map";  //ファイル名を入れる変数(ワイド文字列)

	//「ファイルを保存」ダイアログの設定
	OPENFILENAME ofn;                         	//名前をつけて保存ダイアログの設定用構造体
	ZeroMemory(&ofn, sizeof(ofn));            	//構造体初期化
	ofn.lStructSize = sizeof(OPENFILENAME);   	//構造体のサイズ
	ofn.lpstrFilter = TEXT("マップデータ(*.map)\0*.map\0")        //─┬ファイルの種類(.txtとか.pngとか拡張子)
		              TEXT("テキストデータ(*.txt)\0*.txt\0")      //─┘最後だけ\0ふたつ
					  TEXT("すべてのファイル(*.*)\0*.*\0\0");     
	ofn.lpstrFile = fileName;               	//ファイル名
	ofn.nMaxFile = MAX_PATH;               	//パスの最大文字数
	ofn.Flags = OFN_OVERWRITEPROMPT;   		//フラグ（同名ファイルが存在したら上書き確認）
	ofn.lpstrDefExt = L"map";                  	//デフォルト拡張子

	//「ファイルを保存」ダイアログ
	BOOL selFile;
	selFile = GetSaveFileName(&ofn);//名前を付けて保存

	//キャンセルしたら中断
	if (selFile == FALSE) return;



	HANDLE hFile;        //ファイルのハンドル 
	hFile = CreateFile(
		L"test.txt",                 //ファイル名(自由)
		GENERIC_WRITE,           //アクセスモード（書き込み用->GENERIC_WRITE）
		0,                      //共有（なし）
		NULL,                   //セキュリティ属性（継承しない）
		CREATE_ALWAYS,           //作成方法->新しくファイルを作る（同名のファイルがあると上書き）
		FILE_ATTRIBUTE_NORMAL,  //属性とフラグ（設定なし）
		NULL);                  //拡張属性（なし）

	DWORD dwBytes = 0;  //書き込み位置
	WriteFile(
		hFile,                   //ファイルハンドル
		"abcd",                  //保存するデータ（文字列）だいたい変数
		(DWORD)(4),   //書き込む文字数 本来はstrlenで変数に指定
		&dwBytes,                //書き込んだサイズを入れる変数
		NULL);

	CloseHandle(hFile);//必ず閉じる
}

void Stage::Open()
{
	WCHAR fileName[MAX_PATH] = L"無題.map";  //ファイル名を入れる変数

	//「ファイルを保存」ダイアログの設定
	OPENFILENAME ofn;                         	//名前をつけて保存ダイアログの設定用構造体
	ZeroMemory(&ofn, sizeof(ofn));            	//構造体初期化
	ofn.lStructSize = sizeof(OPENFILENAME);   	//構造体のサイズ
	ofn.lpstrFilter = TEXT("マップデータ(*.map)\0*.map\0")        //─┬ファイルの種類
					  TEXT("テキストデータ(*.txt)\0*.txt\0")
					  TEXT("すべてのファイル(*.*)\0*.*\0\0");     //─┘
	ofn.lpstrFile = fileName;               	//ファイル名
	ofn.nMaxFile = MAX_PATH;               	//パスの最大文字数
	ofn.Flags = OFN_FILEMUSTEXIST;	//フラグ（同名ファイルが存在したら上書き確認）
	ofn.lpstrDefExt = L"map";                  	//デフォルト拡張子

	//「ファイルを開く」ダイアログ
	BOOL selFile;
	selFile = GetOpenFileName(&ofn);

	//キャンセルしたら中断
	if (selFile == FALSE) return;


	HANDLE hFile;        //ファイルのハンドル
	hFile = CreateFile(
		L"test.txt",                 //ファイル名
		GENERIC_READ,           //アクセスモード（読み込み用->GENERIC_READ）
		0,                      //共有（なし）
		NULL,                   //セキュリティ属性（継承しない）
		OPEN_EXISTING,           //作成方法（その名前のファイルがなければエラー）
		FILE_ATTRIBUTE_NORMAL,  //属性とフラグ（設定なし）
		NULL);                  //拡張属性（なし）

	//ファイルのサイズを取得
	DWORD fileSize = GetFileSize(hFile, NULL);

	//ファイルのサイズ分メモリを確保
	char* data;
	data = new char[fileSize];

	DWORD dwBytes = 0; //読み込み位置

	ReadFile(
		hFile,     //ファイルハンドル
		data,      //データを入れる変数
		fileSize,  //読み込むサイズ
		&dwBytes,  //読み込んだサイズ
		NULL);     //オーバーラップド構造体（今回は使わない）

	CloseHandle(hFile);
}

////ウィンドウプロシージャ(ただの関数にした)
LRESULT Stage::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);  //プログラム終了
		return 0;
	case WM_MOUSEMOVE:
		Input::SetMousePosition(LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_MENU_NEW:

			break;
		case ID_MENU_OPEN:
			Open();
			break;
		case ID_MENU_SAVE:
			Save();
			break;
		}
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//ダイアログプロシージャ(ただの関数にした)
BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		SendMessage(GetDlgItem(hDlg, IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);
		SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)L"デフォルト");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)L"レンガ");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)L"草");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)L"砂");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)L"水");
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
			return TRUE;
			break;
		default:
			break;
		}
	}

	return FALSE;
}