//=============================================================================
//
// ���͏��� [input.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

/* Keyboard  */
#define	NUM_KEY_MAX		(256)	// �L�[�ő吔

/* Mouse  */
#define	NUM_MOUSE_BUTTON_MAX	(8)		// �}�E�X�̃{�^���ő吔
#define	MOUSE_BUTTON_LEFT		(0)		// �}�E�X�̍��{�^��
#define	MOUSE_BUTTON_RIGHT		(1)		// �}�E�X�̉E�{�^��
#define	MOUSE_BUTTON_CENTER		(2)		// �}�E�X�̒����{�^��

/* Joypad  */
#define MAX_CONTROLER	(2)			//�R���g���[���ő吔(�g�����ɉ����ĕύX���邱��)
#define STICK_RANGE		(65536)		//���O�`�R�Q�V�U�V�G�E�R�Q�V�U�W�`�U�T�T�R�T
#define STICK_DEADZONE	(3000)		//�������Ȃ��͈�

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
// ���̓N���X
//*********************************************************
class CInput
{
public:
	CInput();
	virtual ~CInput();

	virtual HRESULT Init(HINSTANCE hInst, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;		// ---> �������z�֐���

protected:
	static LPDIRECTINPUT8 m_pDInput;	// DirectInput�I�u�W�F�N�g
	LPDIRECTINPUTDEVICE8 m_pDIDevice;	// Device�I�u�W�F�N�g(���͂ɕK�v)
};

//*********************************************************
// �L�[�{�[�h���̓N���X
//*********************************************************
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();

	HRESULT Init(HINSTANCE hInst, HWND hWnd);
	void Uninit(void);
	void Update(void);

	//�L�[�{�[�h�֘A
	BOOL GetKeyPress(int nKey);
	BOOL GetKeyTrigger(int nKey);
	BOOL GetKeyRelease(int nKey);
	BOOL GetKeyRepeat(int nKey);
	void FlushKeyTrigger(int nKey);

private:
	BYTE	m_aKeyState[NUM_KEY_MAX];			// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
	BYTE	m_aKeyStateTrigger[NUM_KEY_MAX];	// �g���K�[���[�N
	BYTE	m_aKeyStateRelease[NUM_KEY_MAX];	// �����[�X���[�N
	BYTE	m_aKeyStateRepeat[NUM_KEY_MAX];		// ���s�[�g���[�N
	int		m_aKeyStateRepeatCnt[NUM_KEY_MAX];	// ���s�[�g�J�E���^
};

//*********************************************************
// �}�E�X���̓N���X
//*********************************************************
class CInputMouse : public CInput
{
public:
	CInputMouse();
	~CInputMouse();

	HRESULT Init(HINSTANCE hInst, HWND hWnd);
	void Uninit(void);
	void Update(void);

	// �}�E�X�֘A
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
	DIMOUSESTATE2	m_mouseState;			// �}�E�X�̓��͏�񃏁[�N
	DIMOUSESTATE2	m_mouseStateTrigger;	// �}�E�X�̃g���K�[��񃏁[�N
	DIMOUSESTATE2	m_mouseStateRelease;	// �}�E�X�̃����[�X��񃏁[�N
};

//*********************************************************
// �W���C�p�b�h���̓N���X
//*********************************************************
class CInputJoypad : public CInput
{
public:
	CInputJoypad();
	~CInputJoypad();

	HRESULT Init(HINSTANCE hInst, HWND hWnd);
	void Uninit(void);
	void Update(void);

	// �W���C�p�b�h�֘A
	static BOOL CALLBACK EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef);

	bool GetJoypadTrigger( int padNo, DWORD button );
	bool GetJoypadPress( int padNo, DWORD button );
	long GetJoypadRightAxisX(int padNo);
	long GetJoypadRightAxisY(int padNo);

private:
	DIJOYSTATE				m_joyState[MAX_CONTROLER];				// �W���C�p�b�h���z��
	DIJOYSTATE				m_joyStatePrev[MAX_CONTROLER];			// �W���C�p�b�h���z��i���O�j
	BYTE					m_joyStateTrigger[MAX_CONTROLER][32];

	static LPDIRECTINPUTDEVICE8	m_pDIDevJoypad[MAX_CONTROLER];		// IDirectInputDevice8�C���^�[�t�F�[�X�ւ̃|�C���^(�W���C�p�b�h)
	static int					m_nJoypadNum;						// ���������W���C�p�b�h�̐�
};

#endif