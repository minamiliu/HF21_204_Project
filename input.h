//=============================================================================
//
// 入力処理 [input.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

/* Keyboard  */
#define	NUM_KEY_MAX		(256)	// キー最大数

/* Mouse  */
#define	NUM_MOUSE_BUTTON_MAX	(8)		// マウスのボタン最大数
#define	MOUSE_BUTTON_LEFT		(0)		// マウスの左ボタン
#define	MOUSE_BUTTON_RIGHT		(1)		// マウスの右ボタン
#define	MOUSE_BUTTON_CENTER		(2)		// マウスの中央ボタン

/* Joypad  */
#define MAX_CONTROLER	(2)			//コントローラ最大数(使う数に応じて変更すること)
#define STICK_RANGE		(65536)		//左０～３２７６７；右３２７６８～６５５３５
#define STICK_DEADZONE	(3000)		//反応しない範囲

#define BUTTON_A		(0)
#define BUTTON_B		(1)
#define BUTTON_X		(2)
#define BUTTON_Y		(3)
#define BUTTON_L1		(4)
#define BUTTON_R1		(5)
#define BUTTON_SELECT	(6)
#define BUTTON_START	(7)
#define BUTTON_L3		(8)
#define BUTTON_R3		(9)

#define LSTICK_UP		(10)	
#define LSTICK_DOWN		(11)	
#define LSTICK_LEFT		(12)	
#define LSTICK_RIGHT	(13)

#define RSTICK_UP		(14)	
#define RSTICK_DOWN		(15)	
#define RSTICK_LEFT		(16)	
#define RSTICK_RIGHT	(17)

//*********************************************************
// 入力クラス
//*********************************************************
class CInput
{
public:
	CInput();
	virtual ~CInput();

	virtual HRESULT Init(HINSTANCE hInst, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;		// ---> 純粋仮想関数化

protected:
	static LPDIRECTINPUT8 m_pDInput;	// DirectInputオブジェクト
	LPDIRECTINPUTDEVICE8 m_pDIDevice;	// Deviceオブジェクト(入力に必要)
};

//*********************************************************
// キーボード入力クラス
//*********************************************************
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();

	HRESULT Init(HINSTANCE hInst, HWND hWnd);
	void Uninit(void);
	void Update(void);

	//キーボード関連
	BOOL GetKeyPress(int nKey);
	BOOL GetKeyTrigger(int nKey);
	BOOL GetKeyRelease(int nKey);
	BOOL GetKeyRepeat(int nKey);
	void FlushKeyTrigger(int nKey);

private:
	BYTE	m_aKeyState[NUM_KEY_MAX];			// キーボードの状態を受け取るワーク
	BYTE	m_aKeyStateTrigger[NUM_KEY_MAX];	// トリガーワーク
	BYTE	m_aKeyStateRelease[NUM_KEY_MAX];	// リリースワーク
	BYTE	m_aKeyStateRepeat[NUM_KEY_MAX];		// リピートワーク
	int		m_aKeyStateRepeatCnt[NUM_KEY_MAX];	// リピートカウンタ
};

//*********************************************************
// マウス入力クラス
//*********************************************************
class CInputMouse : public CInput
{
public:
	CInputMouse();
	~CInputMouse();

	HRESULT Init(HINSTANCE hInst, HWND hWnd);
	void Uninit(void);
	void Update(void);

	// マウス関連
	bool GetMouseLeftPress(void);
	bool GetMouseLeftTrigger(void);
	bool GetMouseLeftRelease(void);

	bool GetMouseRightPress(void);
	bool GetMouseRightTrigger(void);
	bool GetMouseRightRelease(void);

	bool GetMouseCenterPress(void);
	bool GetMouseCenterTrigger(void);
	bool GetMouseCenterRelease(void);

	long GetMouseAxisX(void);
	long GetMouseAxisY(void);
	long GetMouseAxisZ(void);

private:
	DIMOUSESTATE2	m_mouseState;			// マウスの入力情報ワーク
	DIMOUSESTATE2	m_mouseStateTrigger;	// マウスのトリガー情報ワーク
	DIMOUSESTATE2	m_mouseStateRelease;	// マウスのリリース情報ワーク
};

//*********************************************************
// ジョイパッド入力クラス
//*********************************************************
class CInputJoypad : public CInput
{
public:
	CInputJoypad();
	~CInputJoypad();

	HRESULT Init(HINSTANCE hInst, HWND hWnd);
	void Uninit(void);
	void Update(void);

	// ジョイパッド関連
	static BOOL CALLBACK EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef);

	bool GetJoypadTrigger( int padNo, DWORD button );
	bool GetJoypadPress( int padNo, DWORD button );
	long GetJoypadRightAxisX(int padNo);
	long GetJoypadRightAxisY(int padNo);

private:
	DIJOYSTATE				m_joyState[MAX_CONTROLER];				// ジョイパッド情報配列
	DIJOYSTATE				m_joyStatePrev[MAX_CONTROLER];			// ジョイパッド情報配列（直前）
	BYTE					m_joyStateTrigger[MAX_CONTROLER][32];

	static LPDIRECTINPUTDEVICE8	m_pDIDevJoypad[MAX_CONTROLER];		// IDirectInputDevice8インターフェースへのポインタ(ジョイパッド)
	static int					m_nJoypadNum;						// 見つかったジョイパッドの数
};

#endif