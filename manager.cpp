//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: manager.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/01
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "player2D.h"
#include "light.h"
#include "camera.h"
#include "scene3D.h"
#include "playerX.h"
#include "sound.h"

#include "game.h"
#include "title.h"
#include "result.h"
#include "fade.h"

//============================================
// �}�N����`
//============================================

//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputMouse *CManager::m_pInputMouse = NULL;
CSound *CManager::m_pSound = NULL;
CCamera *CManager::m_pCamera = NULL;

CManager *CManager::m_pSceneManager = NULL;
CManager::MODE CManager::m_modeNow = MODE_NONE;
CManager::MODE CManager::m_modeNext = MODE_NONE;

//============================================
//�R���X�g���N�^
//============================================
CManager::CManager()
{
	m_pSceneManager = this;
}

CManager::CManager(MODE mode)
{
	m_modeNow = mode;
	m_pSceneManager = this;
}

CManager::~CManager()
{
	
}

HRESULT CManager::Init(void)
{
	return S_OK;
}

HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// �����_���[�̐���
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, bWindow);

	//�L�[�{�[�h�̐���
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);

	//�}�E�X�̐���
	m_pInputMouse = new CInputMouse;
	m_pInputMouse->Init(hInstance, hWnd);

	//���C�g�̐���
	CLight::Create( D3DXVECTOR3( 0.2f, -0.6f, 0.8f), D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f));
	CLight::Create( D3DXVECTOR3( -0.2f, -0.3f, -0.5f), D3DXCOLOR( 0.75f, 0.75f, 0.75f, 1.0f));
	CLight::Create( D3DXVECTOR3( 0.8f, 0.1f, 0.5f), D3DXCOLOR( 0.15f, 0.15f, 0.15f, 1.0f));
	CLight::SetAllLightOn();

	//�J�����̐���
	m_pCamera = new CCamera;
	m_pCamera->Init();

	//�T�E���h
	m_pSound = new CSound;
	m_pSound->Init( hWnd);

	return S_OK;
}

void CManager::Uninit(void)
{
	//�I�u�W�F�N�g�̔j��
	CScene::ReleaseAll();
}

void CManager::Update()
{
	//�����_���[�̍X�V����
	m_pRenderer->Update();

	//�L�[�{�[�h�̍X�V����
	m_pInputKeyboard->Update();

	//�}�E�X�̍X�V����
	m_pInputMouse->Update();

	//�J�����̍X�V����
	m_pCamera->Update();

}
void CManager::Draw()
{
	//�J�����ݒu
	m_pCamera->SetCamera();

	//�����_���[�̕`�揈��
	m_pRenderer->Draw();	
}


CManager *CManager::Create( MODE mode, HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	if( m_pSceneManager == NULL)
	{	
		m_pSceneManager = new CManager;
		m_pSceneManager->Init( hInstance, hWnd, bWindow);
	}

	m_pSceneManager = SetScene( mode);

	return m_pSceneManager;
}

void CManager::UpdateAll(void)
{
	m_pSceneManager->Update();
}

void CManager::DrawAll(void)
{
	m_pSceneManager->Draw();
}

void CManager::Release(void)
{
	//�I�u�W�F�N�g�̔j��
	CScene::ReleaseAll();

	//���C�g�̔j��
	CLight::ReleaseAll();

	//�J�����̔j��
	if( m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}

	//�L�[�{�[�h�̔j��
	if( m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	//�}�E�X�̔j��
	if( m_pInputMouse != NULL)
	{
		m_pInputMouse->Uninit();
		delete m_pInputMouse;
		m_pInputMouse = NULL;
	}

	//�T�E���h�̔j��
	if( m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}

	//�����_���[�̔j��
	if( m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//���ȉ��
	if(m_pSceneManager != NULL)
	{
		m_pSceneManager->Uninit();
		delete m_pSceneManager;
		m_pSceneManager = NULL;
		return;
	}

}

CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}

CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

CInputMouse *CManager::GetInputMouse(void)
{
	return m_pInputMouse;
}

CCamera *CManager::GetCamera(void)
{
	return m_pCamera;
}

CManager *CManager::SetScene(MODE mode)
{
	if( m_modeNow != mode && m_modeNow != NULL)
	{
		m_pSceneManager->Uninit();
		m_pSceneManager = NULL;
	}

	switch(mode)
	{
	case MODE_TITLE:
		m_pSceneManager = new CTitle;
		break;

	case MODE_GAME:
		m_pSceneManager = new CGame;
		break;

	case MODE_RESULT:
		m_pSceneManager = new CResult;
		break;

	}

	m_pSceneManager->Init();

	return m_pSceneManager;
}

CManager::MODE CManager::GetNextScene(void)
{
	return m_modeNext;
}

void CManager::SetNextScene(MODE mode)
{
	m_modeNext = mode;
	CFade::SetFade();
}

//=============================================================================
//
//=============================================================================
CSound *CManager::GetSound(void)
{
	return m_pSound;
}