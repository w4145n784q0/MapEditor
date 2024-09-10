#include "Input.h"


namespace Input
{
	//外からアクセスするならヘッダにこれを追加
	LPDIRECTINPUT8   pDInput = nullptr;

	//キーボード
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;
	BYTE keyState[256] = { 0 };
	BYTE prevKeyState[256] = { 0 };    //前フレームでの各キーの状態
	

		//マウス
	LPDIRECTINPUTDEVICE8	pMouseDevice_;	//デバイスオブジェクト
	DIMOUSESTATE mouseState_;				//マウスの状態
	DIMOUSESTATE prevMouseState_;			//前フレームのマウスの状態
	XMVECTOR mousePosition;//マウスの位置

	void Initialize(HWND hWnd)
	{
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);
		
		//キーボード
		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);//デバイスのオブジェクト作成
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard);//キーボードであることを定義
		pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);//他の実行中のアプリに対する優先度
	
		//マウス
		pDInput->CreateDevice(GUID_SysMouse, &pMouseDevice_, nullptr);
		pMouseDevice_->SetDataFormat(&c_dfDIMouse);
		pMouseDevice_->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	}

	void Update()
	{
		

		//キーボード
		memcpy(prevKeyState, keyState, size_t(256));
		pKeyDevice->Acquire();//かくのがマナーみたいなもの（キーボードを見失うことがある。。？）
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);//その瞬間の全キーの状態を読む

		//マウス
		pMouseDevice_->Acquire();
		memcpy(&prevMouseState_, &mouseState_, sizeof(mouseState_));
		pMouseDevice_->GetDeviceState(sizeof(mouseState_), &mouseState_);

	}

	/////////////////////////////　キーボード情報取得　//////////////////////////////////
	bool IsKey(int keyCode)
	{
		if (keyState[keyCode] & 0x80)//128
		{
			return true;
		}
		return false;
	}

	bool IsKeyDown(int keyCode)
	{
		//今は押してて、前回は押してない
		if ((keyState[keyCode] & 0x80) && keyState[keyCode] != prevKeyState[keyCode])
		{
			return true;
		}
		return false;
	}

	bool IsKeyUp(int keyCode)
	{
		if ((prevKeyState[keyCode] & 0x80) && keyState[keyCode] != prevKeyState[keyCode])
		{
			return true;
		}
		return false;
	}
	/////////////////////////////　キーボード情報取得　//////////////////////////////////

	/////////////////////////////　マウス情報取得　//////////////////////////////////

	//マウスのボタンが押されているか調べる
	bool IsMouseButton(int buttonCode)
	{
		//押してる
		if (mouseState_.rgbButtons[buttonCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	//マウスのボタンを今押したか調べる（押しっぱなしは無効）
	bool IsMouseButtonDown(int buttonCode)
	{
		//今は押してて、前回は押してない
		if (IsMouseButton(buttonCode) && !(prevMouseState_.rgbButtons[buttonCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	//マウスのボタンを今放したか調べる
	bool IsMouseButtonUp(int buttonCode)
	{
		//今押してなくて、前回は押してる
		if (!IsMouseButton(buttonCode) && prevMouseState_.rgbButtons[buttonCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	XMVECTOR GetMousePosition()
	{
		return mousePosition;
	}

	void SetMousePosition(int x, int y)
	{
		mousePosition = XMVectorSet((float)x, (float)y, 0, 0);
	}

	/////////////////////////////　マウス情報取得　//////////////////////////////////


	void Release()
	{
		SAFE_RELEASE(pMouseDevice_);
		SAFE_RELEASE(pKeyDevice);
		SAFE_RELEASE(pDInput);
	}
}