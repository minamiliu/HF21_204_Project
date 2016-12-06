//=============================================================================
//
// 入力処理 [input.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	COUNT_WAIT_REPEAT	(20)	// リピート待ち時間

//*****************************************************************************
// 静的変数
//*****************************************************************************
LPDIRECTINPUT8			CInput::m_pDInput = NULL;						// DirectInputオブジェクト
int						CInputJoypad::m_nJoypadNum = 0;					// 見つかったジョイパッドの数
LPDIRECTINPUTDEVICE8	CInputJoypad::m_pDIDevJoypad[MAX_CONTROLER] = {};

//=============================================================================
// CInputコンストラスタ
//=============================================================================
CInput::CInput()
{
	m_pDIDevice = NULL;
}

//=============================================================================
// CInputデストラスタ
//=============================================================================
CInput::~CInput()
{
}

//=============================================================================
// 入力処理の初期化処理
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr = S_FALSE;

	// DirectInputオブジェクトの作成
	if(!m_pDInput)
	{
		hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
									IID_IDirectInput8, (void**)&m_pDInput, NULL);
	}

	return hr;
}

//=============================================================================
// 入力処理の更新処理
//=============================================================================
#if 0	// ---> 純粋仮想関数化
HRESULT CInput::Update(void)
{
	return S_OK;
}
#endif

//=============================================================================
// 入力処理の終了処理
//=============================================================================
void CInput::Uninit(void)
{
	if(m_pDIDevice)
	{// デバイスオブジェクトの開放
		m_pDIDevice->Unacquire();

		m_pDIDevice->Release();
		m_pDIDevice = NULL;
	}

	if(m_pDInput)
	{// DirectInputオブジェクトの開放
		m_pDInput->Release();
		m_pDInput = NULL;
	}
}

//=============================================================================
// CInputKeyboardコンストラスタ
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
	// 各ワークのクリア
	ZeroMemory(m_aKeyState, sizeof m_aKeyState);
	ZeroMemory(m_aKeyStateTrigger, sizeof m_aKeyStateTrigger);
	ZeroMemory(m_aKeyStateRelease, sizeof m_aKeyStateRelease);
	ZeroMemory(m_aKeyStateRepeat, sizeof m_aKeyStateRepeat);
	ZeroMemory(m_aKeyStateRepeatCnt, sizeof m_aKeyStateRepeatCnt);
}

//=============================================================================
// CInputKeyboardデストラスタ
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{
}

//=============================================================================
// キーボードの初期化処理
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	// 入力処理の初期化
	CInput::Init(hInst, hWnd);

	// デバイスオブジェクトを作成
	hr = m_pDInput->CreateDevice(GUID_SysKeyboard, &m_pDIDevice, NULL);
	if(FAILED(hr) || m_pDIDevice == NULL)
	{
		MessageBox(hWnd, "キーボードがねぇ！", "警告！", MB_ICONWARNING);
		return hr;
	}

	// データフォーマットを設定
	hr = m_pDIDevice->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "キーボードのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
		return hr;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = m_pDIDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr))
	{
		MessageBox(hWnd, "キーボードの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
		return hr;
	}

	// m_pDIDeviceアクセス権を獲得(入力制御開始)
	m_pDIDevice->Acquire();

	return hr;
}

//=============================================================================
// キーボード入力処理の開放
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	// 入力処理の開放
	CInput::Uninit();
}

//=============================================================================
// キーボードの更新処理
//=============================================================================
void CInputKeyboard::Update(void)
{
	HRESULT hr;
	BYTE aKeyState[NUM_KEY_MAX];

	if(!m_pDIDevice)
	{
		return;
	}

	// デバイスからデータを取得
	hr = m_pDIDevice->GetDeviceState(sizeof(aKeyState), aKeyState);
	if(SUCCEEDED(hr))
	{
		for(int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & ~aKeyState[nCntKey];

			m_aKeyStateRepeat[nCntKey] = m_aKeyStateTrigger[nCntKey];

			if(aKeyState[nCntKey])
			{
				m_aKeyStateRepeatCnt[nCntKey]++;
				if(m_aKeyStateRepeatCnt[nCntKey] >= COUNT_WAIT_REPEAT)
				{
					m_aKeyStateRepeat[nCntKey] = aKeyState[nCntKey];
				}
			}
			else
			{
				m_aKeyStateRepeatCnt[nCntKey] = 0;
				m_aKeyStateRepeat[nCntKey] = 0;
			}

			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		m_pDIDevice->Acquire();
	}
}

//=============================================================================
// キーボードデータ取得(プレス)
//=============================================================================
BOOL CInputKeyboard::GetKeyPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? TRUE: FALSE;
}

//=============================================================================
// キーボードデータ取得(トリガー)
//=============================================================================
BOOL CInputKeyboard::GetKeyTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? TRUE: FALSE;
}

//=============================================================================
// キーボードデータ取得(リリース)
//=============================================================================
BOOL CInputKeyboard::GetKeyRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? TRUE: FALSE;
}

//=============================================================================
// キーボードデータ取得(リピート)
//=============================================================================
BOOL CInputKeyboard::GetKeyRepeat(int nKey)
{
	return (m_aKeyStateRepeat[nKey] & 0x80) ? TRUE: FALSE;
}

//=============================================================================
// キーボードデータ削除(トリガー)
//=============================================================================
void CInputKeyboard::FlushKeyTrigger(int nKey)
{
	m_aKeyStateTrigger[nKey] = 0;
}

//=============================================================================
// CInputMouseコンストラスタ
//=============================================================================
CInputMouse::CInputMouse()
{
	ZeroMemory(&m_mouseState, sizeof DIMOUSESTATE2);
	ZeroMemory(&m_mouseStateTrigger, sizeof DIMOUSESTATE2);
	ZeroMemory(&m_mouseStateRelease, sizeof DIMOUSESTATE2);
}

//=============================================================================
// CInputMouseデストラスタ
//=============================================================================
CInputMouse::~CInputMouse()
{
}

//=============================================================================
// マウスの初期化
//=============================================================================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;

	// 入力処理の初期化
	CInput::Init(hInstance, hWnd);

	// デバイスオブジェクトを作成
	hr = m_pDInput->CreateDevice(GUID_SysMouse, &m_pDIDevice, NULL);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "マウスがねぇ！", "警告！", MB_ICONWARNING);
		return hr;
	}

	// データフォーマットを設定
	hr = m_pDIDevice->SetDataFormat(&c_dfDIMouse2);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "マウスのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
		return hr;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = m_pDIDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr))
	{
		MessageBox(hWnd, "マウスの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
		return hr;
	}

	// デバイスのプロパティを設定
	{
		DIPROPDWORD dipdw;

		dipdw.diph.dwSize = sizeof(dipdw);
		dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
		dipdw.diph.dwObj = 0;
		dipdw.diph.dwHow = DIPH_DEVICE;
		dipdw.dwData = DIPROPAXISMODE_REL;

		hr = m_pDIDevice->SetProperty(DIPROP_AXISMODE, &dipdw.diph);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "マウスのデバイスのプロパティを設定できませんでした。", "警告！", MB_ICONWARNING);
			return hr;
		}
	}

	// マウスへのアクセス権を獲得(入力制御開始)
	m_pDIDevice->Acquire();

	return S_OK;
}

//=============================================================================
// マウスの終了処理
//=============================================================================
void CInputMouse::Uninit(void)
{
	// 入力処理の開放
	CInput::Uninit();
}

//=============================================================================
// マウスの更新処理
//=============================================================================
void CInputMouse::Update(void)
{
	DIMOUSESTATE2 mouseState;

	// デバイスからデータを取得
	if(SUCCEEDED(m_pDIDevice->GetDeviceState(sizeof(mouseState), &mouseState)))
	{
		m_mouseStateTrigger.lX = ((m_mouseState.lX ^ mouseState.lX) & mouseState.lX);
		m_mouseStateTrigger.lY = ((m_mouseState.lY ^ mouseState.lY) & mouseState.lY);
		m_mouseStateTrigger.lZ = ((m_mouseState.lZ ^ mouseState.lZ) & mouseState.lZ);

		m_mouseStateRelease.lX = ((m_mouseState.lX ^ mouseState.lX) & ~mouseState.lX);
		m_mouseStateRelease.lY = ((m_mouseState.lY ^ mouseState.lY) & ~mouseState.lY);
		m_mouseStateRelease.lZ = ((m_mouseState.lZ ^ mouseState.lZ) & ~mouseState.lZ);

		for(int nCntKey = 0; nCntKey < NUM_MOUSE_BUTTON_MAX; nCntKey++)
		{
			m_mouseStateTrigger.rgbButtons[nCntKey] = ((m_mouseState.rgbButtons[nCntKey] ^ mouseState.rgbButtons[nCntKey]) & mouseState.rgbButtons[nCntKey]);
			m_mouseStateRelease.rgbButtons[nCntKey] = ((m_mouseState.rgbButtons[nCntKey] ^ mouseState.rgbButtons[nCntKey]) & ~mouseState.rgbButtons[nCntKey]);
		}

		m_mouseState = mouseState;
	}
	else
	{
		// マウスへのアクセス権を獲得(入力制御開始)
		m_pDIDevice->Acquire();
	}
}

//=============================================================================
// マウスデータ取得(左プレス)
//=============================================================================
bool CInputMouse::GetMouseLeftPress(void)
{
	return (m_mouseState.rgbButtons[MOUSE_BUTTON_LEFT] & 0x80) ? true: false;
}

//=============================================================================
// マウスデータ取得(左トリガー)
//=============================================================================
bool CInputMouse::GetMouseLeftTrigger(void)
{
	return (m_mouseStateTrigger.rgbButtons[MOUSE_BUTTON_LEFT] & 0x80) ? true: false;
}

//=============================================================================
// マウスデータ取得(左リリース)
//=============================================================================
bool CInputMouse::GetMouseLeftRelease(void)
{
	return (m_mouseStateRelease.rgbButtons[MOUSE_BUTTON_LEFT] & 0x80) ? true: false;
}

//=============================================================================
// マウスデータ取得(右プレス)
//=============================================================================
bool CInputMouse::GetMouseRightPress(void)
{
	return (m_mouseState.rgbButtons[MOUSE_BUTTON_RIGHT] & 0x80) ? true: false;
}

//=============================================================================
// マウスデータ取得(右トリガー)
//=============================================================================
bool CInputMouse::GetMouseRightTrigger(void)
{
	return (m_mouseStateTrigger.rgbButtons[MOUSE_BUTTON_RIGHT] & 0x80) ? true: false;
}

//=============================================================================
// マウスデータ取得(右リリース)
//=============================================================================
bool CInputMouse::GetMouseRightRelease(void)
{
	return (m_mouseStateRelease.rgbButtons[MOUSE_BUTTON_RIGHT] & 0x80) ? true: false;
}

//=============================================================================
// マウスデータ取得(中央プレス)
//=============================================================================
bool CInputMouse::GetMouseCenterPress(void)
{
	return (m_mouseState.rgbButtons[MOUSE_BUTTON_CENTER] & 0x80) ? true: false;
}

//=============================================================================
// マウスデータ取得(中央トリガー)
//=============================================================================
bool CInputMouse::GetMouseCenterTrigger(void)
{
	return (m_mouseStateTrigger.rgbButtons[MOUSE_BUTTON_CENTER] & 0x80) ? true: false;
}

//=============================================================================
// マウスデータ取得(中央リリース)
//=============================================================================
bool CInputMouse::GetMouseCenterRelease(void)
{
	return (m_mouseStateRelease.rgbButtons[MOUSE_BUTTON_CENTER] & 0x80) ? true: false;
}

//=============================================================================
// マウスデータ取得(Ｘ軸移動)
//=============================================================================
long CInputMouse::GetMouseAxisX(void)
{
	return m_mouseState.lX;
}

//=============================================================================
// マウスデータ取得(Ｙ軸移動)
//=============================================================================
long CInputMouse::GetMouseAxisY(void)
{
	return m_mouseState.lY;
}

//=============================================================================
// マウスデータ取得(Ｚ軸移動)
//=============================================================================
long CInputMouse::GetMouseAxisZ(void)
{
	return m_mouseState.lZ;
}

//=============================================================================
// CInputMouseコンストラスタ
//=============================================================================
CInputJoypad::CInputJoypad()
{
	// 各ワークのクリア
	ZeroMemory(m_joyState, sizeof m_joyState);
	ZeroMemory(m_joyStatePrev, sizeof m_joyStatePrev);
	ZeroMemory(m_joyStateTrigger, sizeof m_joyStateTrigger);
}

//=============================================================================
// CInputMouseデストラスタ
//=============================================================================
CInputJoypad::~CInputJoypad()
{
}

//=============================================================================
// ジョイパッドの初期化
//=============================================================================
HRESULT CInputJoypad::Init(HINSTANCE hInstance, HWND hWnd)
{
	int nLoop;


	// 初期化
	for(nLoop = 0; nLoop < MAX_CONTROLER; nLoop++)
		m_pDIDevJoypad[nLoop] = NULL;

	// デバイスオブジェクトを作成(接続されているジョイパッドを列挙する)
	if(FAILED(m_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoyCallback, NULL, DIEDFL_ATTACHEDONLY)))
		return E_FAIL;

	// ジョイパッドの数だけ処理
	for(nLoop = 0; nLoop < MAX_CONTROLER; nLoop++)
	{
		// ジョイパッドがない場合はすっ飛ばす
		if(m_pDIDevJoypad[nLoop] == NULL)
			continue;

		// データフォーマットの設定
		if(FAILED(m_pDIDevJoypad[nLoop]->SetDataFormat(&c_dfDIJoystick)))
			return E_FAIL;

		// 協調レベルの設定
		if(FAILED(m_pDIDevJoypad[nLoop]->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
			return E_FAIL;

		// デバイスへの入力制御開始
		m_pDIDevJoypad[nLoop]->Acquire();	
	}

	return S_OK;
}

//=============================================================================
// ジョイパッド問い合わせ用コールバック関数
//=============================================================================
BOOL CALLBACK CInputJoypad::EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef)
{
	DIDEVCAPS	diDevCaps;			// デバイス情報

	// ジョイパッド用デバイスオブジェクトを作成
	if(FAILED(m_pDInput->CreateDevice(lpddi->guidInstance, &m_pDIDevJoypad[m_nJoypadNum], NULL)))
		return DIENUM_CONTINUE;		// 列挙を続ける

	// ジョイパッドの能力を調べる
	diDevCaps.dwSize = sizeof(DIDEVCAPS);
	if(FAILED(m_pDIDevJoypad[m_nJoypadNum]->GetCapabilities(&diDevCaps)))
	{
		if(m_pDIDevJoypad[m_nJoypadNum])
			m_pDIDevJoypad[m_nJoypadNum]->Release();
		m_pDIDevJoypad[m_nJoypadNum] = NULL;
		return DIENUM_CONTINUE;		// 列挙を続ける
	}

	// 規定数に達したら終了
	m_nJoypadNum++;
	if(m_nJoypadNum == MAX_CONTROLER)
		return DIENUM_STOP;			// 列挙を終了する
	else
		return DIENUM_CONTINUE;		// 列挙を続ける
}

//=============================================================================
// ジョイパッドの終了処理
//=============================================================================
void CInputJoypad::Uninit(void)
{
	for(int nLoop = 0; nLoop < MAX_CONTROLER; nLoop++)
	{
		SAFE_RELEASE(m_pDIDevJoypad[nLoop]);
	}	
}

//=============================================================================
// ジョイパッドの更新処理
//=============================================================================
void CInputJoypad::Update(void)
{
	int nLoop;
	
	for(nLoop = 0; nLoop < MAX_CONTROLER; nLoop++)
	{
		// 直前ジョイパッド情報のバックアップ
		m_joyStatePrev[nLoop] = m_joyState[nLoop];

		if(m_pDIDevJoypad[nLoop])
		{
			// デバイスからデータを取得
			if(FAILED(m_pDIDevJoypad[nLoop]->GetDeviceState(sizeof(DIJOYSTATE), &m_joyState[nLoop])))
				m_pDIDevJoypad[nLoop]->Acquire();
		}
		

		// トリガー情報計算
		for( int i = 0; i < 32; i++ )
		{
			if( m_joyState[nLoop].rgbButtons[i] & 0x80 && 
				!(m_joyStatePrev[nLoop].rgbButtons[i] & 0x80) )
			{
				m_joyStateTrigger[nLoop][i] = 0x80;
			} else {
				m_joyStateTrigger[nLoop][i] = 0x00;
			}
		}

		if(m_joyState[nLoop].lY - STICK_RANGE/2 < -STICK_RANGE/4) m_joyStateTrigger[nLoop][LSTICK_UP] = 0x80;
		if(m_joyState[nLoop].lY - STICK_RANGE/2 >  STICK_RANGE/4) m_joyStateTrigger[nLoop][LSTICK_DOWN] = 0x80;
		if(m_joyState[nLoop].lX - STICK_RANGE/2 < -STICK_RANGE/4) m_joyStateTrigger[nLoop][LSTICK_LEFT] = 0x80;
		if(m_joyState[nLoop].lX - STICK_RANGE/2 >  STICK_RANGE/4) m_joyStateTrigger[nLoop][LSTICK_RIGHT] = 0x80;

	}
}
//=============================================================================
// ジョイパッドデータ取得(トリガー)
//=============================================================================
bool CInputJoypad::GetJoypadTrigger( int padNo, DWORD button )
{
	if(m_pDIDevJoypad[padNo] == NULL) return false;
	return (m_joyStateTrigger[padNo][button] & 0x80) ? true: false;
}
//=============================================================================
// ジョイパッドデータ取得(プレス)
//=============================================================================
bool CInputJoypad::GetJoypadPress( int padNo, DWORD button )
{
	if(m_pDIDevJoypad[padNo] == NULL) return false;
	return (m_joyState[padNo].rgbButtons[button] & 0x80) ? true: false;
}
//=============================================================================
// ジョイパッドデータ取得(Ｘ軸移動)
//=============================================================================
long CInputJoypad::GetJoypadRightAxisX(int padNo)
{
	if(m_pDIDevJoypad[padNo] == NULL) return 0;

	if( abs(m_joyState[padNo].lRx - STICK_RANGE/2) < STICK_DEADZONE) return 0;

	return (m_joyState[padNo].lRx - STICK_RANGE/2) * (long)0.01f;
}
//=============================================================================
// マウスデータ取得(Ｙ軸移動)
//=============================================================================
long CInputJoypad::GetJoypadRightAxisY(int padNo)
{
	if(m_pDIDevJoypad[padNo] == NULL) return 0;

	if( abs(m_joyState[padNo].lRy - STICK_RANGE/2) < STICK_DEADZONE) return 0;

	return (m_joyState[padNo].lRy - STICK_RANGE/2) * (long)0.01f;
}
