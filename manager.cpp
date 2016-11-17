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
#include "game.h"

#include "game.h"
#include "title.h"
#include "result.h"

//============================================
// �}�N����`
//============================================

//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputMouse *CManager::m_pInputMouse = NULL;
CLight *CManager::m_pLight = NULL;
CCamera *CManager::m_pCamera = NULL;
CManager *CManager::m_pSceneNow = NULL;
CManager::TYPE CManager::m_type = TYPE_TITLE;

//============================================
//�R���X�g���N�^
//============================================
CManager::CManager()
{

}

CManager::~CManager()
{
	
}

HRESULT CManager::InitProgram(HINSTANCE hInstance, HWND hWnd, bool bWindow)
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

	return S_OK;
}

HRESULT CManager::Init(void)
{
	return S_OK;
}

void CManager::UninitProgram()
{
	//�I�u�W�F�N�g�̔j��
	CScene::ReleaseAll();

	//���C�g�̔j��
	if( m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

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

	//�����_���[�̔j��
	if( m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
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

	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	if( pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		switch( m_type)
		{
		case TYPE_TITLE:
			m_pSceneNow = SetScene( TYPE_GAME);
			break;

		case TYPE_GAME:
			m_pSceneNow = SetScene( TYPE_RESULT);
			break;

		case TYPE_RESULT:
			m_pSceneNow = SetScene( TYPE_TITLE);
			break;

		}
		m_pSceneNow->Init();
	}
}
void CManager::Draw()
{
	//�J�����ݒu
	m_pCamera->SetCamera();

	//�����_���[�̕`�揈��
	m_pRenderer->Draw();
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

CManager *CManager::SetScene(TYPE type)
{
	m_type = type;

	if(m_pSceneNow)
	{
		m_pSceneNow->Uninit();
	}

	switch(type)
	{
	case TYPE_TITLE:
		m_pSceneNow = new CTitle;
		break;

	case TYPE_GAME:
		m_pSceneNow = new CGame;
		break;

	case TYPE_RESULT:
		m_pSceneNow = new CResult;
		break;

	}

	return m_pSceneNow;
}