//=============================================================================
//
// ���͏��� [input.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	COUNT_WAIT_REPEAT	(20)	// ���s�[�g�҂�����

//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************
LPDIRECTINPUT8			CInput::m_pDInput = NULL;						// DirectInput�I�u�W�F�N�g
int						CInputJoypad::m_nJoypadNum = 0;					// ���������W���C�p�b�h�̐�
LPDIRECTINPUTDEVICE8	CInputJoypad::m_pDIDevJoypad[MAX_CONTROLER] = {};

//=============================================================================
// CInput�R���X�g���X�^
//=============================================================================
CInput::CInput()
{
	m_pDIDevice = NULL;
}

//=============================================================================
// CInput�f�X�g���X�^
//=============================================================================
CInput::~CInput()
{
}

//=============================================================================
// ���͏����̏���������
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr = S_FALSE;

	// DirectInput�I�u�W�F�N�g�̍쐬
	if(!m_pDInput)
	{
		hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
									IID_IDirectInput8, (void**)&m_pDInput, NULL);
	}

	return hr;
}

//=============================================================================
// ���͏����̍X�V����
//=============================================================================
#if 0	// ---> �������z�֐���
HRESULT CInput::Update(void)
{
	return S_OK;
}
#endif

//=============================================================================
// ���͏����̏I������
//=============================================================================
void CInput::Uninit(void)
{
	if(m_pDIDevice)
	{// �f�o�C�X�I�u�W�F�N�g�̊J��
		m_pDIDevice->Unacquire();

		m_pDIDevice->Release();
		m_pDIDevice = NULL;
	}

	if(m_pDInput)
	{// DirectInput�I�u�W�F�N�g�̊J��
		m_pDInput->Release();
		m_pDInput = NULL;
	}
}

//=============================================================================
// CInputKeyboard�R���X�g���X�^
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
	// �e���[�N�̃N���A
	ZeroMemory(m_aKeyState, sizeof m_aKeyState);
	ZeroMemory(m_aKeyStateTrigger, sizeof m_aKeyStateTrigger);
	ZeroMemory(m_aKeyStateRelease, sizeof m_aKeyStateRelease);
	ZeroMemory(m_aKeyStateRepeat, sizeof m_aKeyStateRepeat);
	ZeroMemory(m_aKeyStateRepeatCnt, sizeof m_aKeyStateRepeatCnt);
}

//=============================================================================
// CInputKeyboard�f�X�g���X�^
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{
}

//=============================================================================
// �L�[�{�[�h�̏���������
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	// ���͏����̏�����
	CInput::Init(hInst, hWnd);

	// �f�o�C�X�I�u�W�F�N�g���쐬
	hr = m_pDInput->CreateDevice(GUID_SysKeyboard, &m_pDIDevice, NULL);
	if(FAILED(hr) || m_pDIDevice == NULL)
	{
		MessageBox(hWnd, "�L�[�{�[�h���˂��I", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	hr = m_pDIDevice->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = m_pDIDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// m_pDIDevice�A�N�Z�X�����l��(���͐���J�n)
	m_pDIDevice->Acquire();

	return hr;
}

//=============================================================================
// �L�[�{�[�h���͏����̊J��
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	// ���͏����̊J��
	CInput::Uninit();
}

//=============================================================================
// �L�[�{�[�h�̍X�V����
//=============================================================================
void CInputKeyboard::Update(void)
{
	HRESULT hr;
	BYTE aKeyState[NUM_KEY_MAX];

	if(!m_pDIDevice)
	{
		return;
	}

	// �f�o�C�X����f�[�^���擾
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
// �L�[�{�[�h�f�[�^�擾(�v���X)
//=============================================================================
BOOL CInputKeyboard::GetKeyPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? TRUE: FALSE;
}

//=============================================================================
// �L�[�{�[�h�f�[�^�擾(�g���K�[)
//=============================================================================
BOOL CInputKeyboard::GetKeyTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? TRUE: FALSE;
}

//=============================================================================
// �L�[�{�[�h�f�[�^�擾(�����[�X)
//=============================================================================
BOOL CInputKeyboard::GetKeyRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? TRUE: FALSE;
}

//=============================================================================
// �L�[�{�[�h�f�[�^�擾(���s�[�g)
//=============================================================================
BOOL CInputKeyboard::GetKeyRepeat(int nKey)
{
	return (m_aKeyStateRepeat[nKey] & 0x80) ? TRUE: FALSE;
}

//=============================================================================
// �L�[�{�[�h�f�[�^�폜(�g���K�[)
//=============================================================================
void CInputKeyboard::FlushKeyTrigger(int nKey)
{
	m_aKeyStateTrigger[nKey] = 0;
}

//=============================================================================
// CInputMouse�R���X�g���X�^
//=============================================================================
CInputMouse::CInputMouse()
{

}

//=============================================================================
// CInputMouse�f�X�g���X�^
//=============================================================================
CInputMouse::~CInputMouse()
{
}

//=============================================================================
// �}�E�X�̏�����
//=============================================================================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;

	// ���͏����̏�����
	CInput::Init(hInstance, hWnd);

	// �f�o�C�X�I�u�W�F�N�g���쐬
	hr = m_pDInput->CreateDevice(GUID_SysMouse, &m_pDIDevice, NULL);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�}�E�X���˂��I", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	hr = m_pDIDevice->SetDataFormat(&c_dfDIMouse2);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�}�E�X�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = m_pDIDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�}�E�X�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �f�o�C�X�̃v���p�e�B��ݒ�
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
			MessageBox(hWnd, "�}�E�X�̃f�o�C�X�̃v���p�e�B��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
			return hr;
		}
	}

	// �}�E�X�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDIDevice->Acquire();

	return S_OK;
}

//=============================================================================
// �}�E�X�̏I������
//=============================================================================
void CInputMouse::Uninit(void)
{
	// ���͏����̊J��
	CInput::Uninit();
}

//=============================================================================
// �}�E�X�̍X�V����
//=============================================================================
void CInputMouse::Update(void)
{
	DIMOUSESTATE2 mouseState;

	// �f�o�C�X����f�[�^���擾
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
		// �}�E�X�ւ̃A�N�Z�X�����l��(���͐���J�n)
		m_pDIDevice->Acquire();
	}
}

//=============================================================================
// �}�E�X�f�[�^�擾(���v���X)
//=============================================================================
bool CInputMouse::GetMouseLeftPress(void)
{
	return (m_mouseState.rgbButtons[MOUSE_BUTTON_LEFT] & 0x80) ? true: false;
}

//=============================================================================
// �}�E�X�f�[�^�擾(���g���K�[)
//=============================================================================
bool CInputMouse::GetMouseLeftTrigger(void)
{
	return (m_mouseStateTrigger.rgbButtons[MOUSE_BUTTON_LEFT] & 0x80) ? true: false;
}

//=============================================================================
// �}�E�X�f�[�^�擾(�������[�X)
//=============================================================================
bool CInputMouse::GetMouseLeftRelease(void)
{
	return (m_mouseStateRelease.rgbButtons[MOUSE_BUTTON_LEFT] & 0x80) ? true: false;
}

//=============================================================================
// �}�E�X�f�[�^�擾(�E�v���X)
//=============================================================================
bool CInputMouse::GetMouseRightPress(void)
{
	return (m_mouseState.rgbButtons[MOUSE_BUTTON_RIGHT] & 0x80) ? true: false;
}

//=============================================================================
// �}�E�X�f�[�^�擾(�E�g���K�[)
//=============================================================================
bool CInputMouse::GetMouseRightTrigger(void)
{
	return (m_mouseStateTrigger.rgbButtons[MOUSE_BUTTON_RIGHT] & 0x80) ? true: false;
}

//=============================================================================
// �}�E�X�f�[�^�擾(�E�����[�X)
//=============================================================================
bool CInputMouse::GetMouseRightRelease(void)
{
	return (m_mouseStateRelease.rgbButtons[MOUSE_BUTTON_RIGHT] & 0x80) ? true: false;
}

//=============================================================================
// �}�E�X�f�[�^�擾(�����v���X)
//=============================================================================
bool CInputMouse::GetMouseCenterPress(void)
{
	return (m_mouseState.rgbButtons[MOUSE_BUTTON_CENTER] & 0x80) ? true: false;
}

//=============================================================================
// �}�E�X�f�[�^�擾(�����g���K�[)
//=============================================================================
bool CInputMouse::GetMouseCenterTrigger(void)
{
	return (m_mouseStateTrigger.rgbButtons[MOUSE_BUTTON_CENTER] & 0x80) ? true: false;
}

//=============================================================================
// �}�E�X�f�[�^�擾(���������[�X)
//=============================================================================
bool CInputMouse::GetMouseCenterRelease(void)
{
	return (m_mouseStateRelease.rgbButtons[MOUSE_BUTTON_CENTER] & 0x80) ? true: false;
}

//=============================================================================
// �}�E�X�f�[�^�擾(�w���ړ�)
//=============================================================================
long CInputMouse::GetMouseAxisX(void)
{
	return m_mouseState.lX;
}

//=============================================================================
// �}�E�X�f�[�^�擾(�x���ړ�)
//=============================================================================
long CInputMouse::GetMouseAxisY(void)
{
	return m_mouseState.lY;
}

//=============================================================================
// �}�E�X�f�[�^�擾(�y���ړ�)
//=============================================================================
long CInputMouse::GetMouseAxisZ(void)
{
	return m_mouseState.lZ;
}

//=============================================================================
// CInputMouse�R���X�g���X�^
//=============================================================================
CInputJoypad::CInputJoypad()
{
	// �e���[�N�̃N���A
	ZeroMemory(m_joyState, sizeof m_joyState);
	ZeroMemory(m_joyStatePrev, sizeof m_joyStatePrev);
	ZeroMemory(m_joyStateTrigger, sizeof m_joyStateTrigger);
}

//=============================================================================
// CInputMouse�f�X�g���X�^
//=============================================================================
CInputJoypad::~CInputJoypad()
{
}

//=============================================================================
// �W���C�p�b�h�̏�����
//=============================================================================
HRESULT CInputJoypad::Init(HINSTANCE hInstance, HWND hWnd)
{
	int nLoop;


	// ������
	for(nLoop = 0; nLoop < MAX_CONTROLER; nLoop++)
		m_pDIDevJoypad[nLoop] = NULL;

	// �f�o�C�X�I�u�W�F�N�g���쐬(�ڑ�����Ă���W���C�p�b�h��񋓂���)
	if(FAILED(m_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoyCallback, NULL, DIEDFL_ATTACHEDONLY)))
		return E_FAIL;

	// �W���C�p�b�h�̐���������
	for(nLoop = 0; nLoop < MAX_CONTROLER; nLoop++)
	{
		// �W���C�p�b�h���Ȃ��ꍇ�͂�����΂�
		if(m_pDIDevJoypad[nLoop] == NULL)
			continue;

		// �f�[�^�t�H�[�}�b�g�̐ݒ�
		if(FAILED(m_pDIDevJoypad[nLoop]->SetDataFormat(&c_dfDIJoystick)))
			return E_FAIL;

		// �������x���̐ݒ�
		if(FAILED(m_pDIDevJoypad[nLoop]->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
			return E_FAIL;

		// �f�o�C�X�ւ̓��͐���J�n
		m_pDIDevJoypad[nLoop]->Acquire();	
	}

	return S_OK;
}

//=============================================================================
// �W���C�p�b�h�₢���킹�p�R�[���o�b�N�֐�
//=============================================================================
BOOL CALLBACK CInputJoypad::EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef)
{
	DIDEVCAPS	diDevCaps;			// �f�o�C�X���

	// �W���C�p�b�h�p�f�o�C�X�I�u�W�F�N�g���쐬
	if(FAILED(m_pDInput->CreateDevice(lpddi->guidInstance, &m_pDIDevJoypad[m_nJoypadNum], NULL)))
		return DIENUM_CONTINUE;		// �񋓂𑱂���

	// �W���C�p�b�h�̔\�͂𒲂ׂ�
	diDevCaps.dwSize = sizeof(DIDEVCAPS);
	if(FAILED(m_pDIDevJoypad[m_nJoypadNum]->GetCapabilities(&diDevCaps)))
	{
		if(m_pDIDevJoypad[m_nJoypadNum])
			m_pDIDevJoypad[m_nJoypadNum]->Release();
		m_pDIDevJoypad[m_nJoypadNum] = NULL;
		return DIENUM_CONTINUE;		// �񋓂𑱂���
	}

	// �K�萔�ɒB������I��
	m_nJoypadNum++;
	if(m_nJoypadNum == MAX_CONTROLER)
		return DIENUM_STOP;			// �񋓂��I������
	else
		return DIENUM_CONTINUE;		// �񋓂𑱂���
}

//=============================================================================
// �W���C�p�b�h�̏I������
//=============================================================================
void CInputJoypad::Uninit(void)
{
	for(int nLoop = 0; nLoop < MAX_CONTROLER; nLoop++)
	{
		SAFE_RELEASE(m_pDIDevJoypad[nLoop]);
	}	
}

//=============================================================================
// �W���C�p�b�h�̍X�V����
//=============================================================================
void CInputJoypad::Update(void)
{
	int nLoop;
	
	for(nLoop = 0; nLoop < MAX_CONTROLER; nLoop++)
	{
		// ���O�W���C�p�b�h���̃o�b�N�A�b�v
		m_joyStatePrev[nLoop] = m_joyState[nLoop];

		if(m_pDIDevJoypad[nLoop])
		{
			// �f�o�C�X����f�[�^���擾
			if(FAILED(m_pDIDevJoypad[nLoop]->GetDeviceState(sizeof(DIJOYSTATE), &m_joyState[nLoop])))
				m_pDIDevJoypad[nLoop]->Acquire();
		}
		

		// �g���K�[���v�Z
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
// �W���C�p�b�h�f�[�^�擾(�g���K�[)
//=============================================================================
bool CInputJoypad::GetJoypadTrigger( int padNo, DWORD button )
{
	if(m_pDIDevJoypad[padNo] == NULL) return false;
	return (m_joyStateTrigger[padNo][button] & 0x80) ? true: false;
}
//=============================================================================
// �W���C�p�b�h�f�[�^�擾(�v���X)
//=============================================================================
bool CInputJoypad::GetJoypadPress( int padNo, DWORD button )
{
	if(m_pDIDevJoypad[padNo] == NULL) return false;
	return (m_joyState[padNo].rgbButtons[button] & 0x80) ? true: false;
}
//=============================================================================
// �W���C�p�b�h�f�[�^�擾(�w���ړ�)
//=============================================================================
long CInputJoypad::GetJoypadRightAxisX(int padNo)
{
	if(m_pDIDevJoypad[padNo] == NULL) return 0;

	if( abs(m_joyState[padNo].lRx - STICK_RANGE/2) < STICK_DEADZONE) return 0;

	return (m_joyState[padNo].lRx - STICK_RANGE/2) * (long)0.01f;
}
//=============================================================================
// �}�E�X�f�[�^�擾(�x���ړ�)
//=============================================================================
long CInputJoypad::GetJoypadRightAxisY(int padNo)
{
	if(m_pDIDevJoypad[padNo] == NULL) return 0;

	if( abs(m_joyState[padNo].lRy - STICK_RANGE/2) < STICK_DEADZONE) return 0;

	return (m_joyState[padNo].lRy - STICK_RANGE/2) * (long)0.01f;
}
