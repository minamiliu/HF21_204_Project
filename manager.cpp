//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: manager.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/01
//
//============================================

//============================================
//インクルードファイル
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
// マクロ定義
//============================================

//============================================
// 静的メンバー変数の初期化
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
//コンストラクタ
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
	// レンダラーの生成
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, bWindow);

	//キーボードの生成
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);

	//マウスの生成
	m_pInputMouse = new CInputMouse;
	m_pInputMouse->Init(hInstance, hWnd);

	//ライトの生成
	CLight::Create( D3DXVECTOR3( 0.2f, -0.6f, 0.8f), D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f));
	CLight::Create( D3DXVECTOR3( -0.2f, -0.3f, -0.5f), D3DXCOLOR( 0.75f, 0.75f, 0.75f, 1.0f));
	CLight::Create( D3DXVECTOR3( 0.8f, 0.1f, 0.5f), D3DXCOLOR( 0.15f, 0.15f, 0.15f, 1.0f));
	CLight::SetAllLightOn();

	//カメラの生成
	m_pCamera = new CCamera;
	m_pCamera->Init();

	//サウンド
	m_pSound = new CSound;
	m_pSound->Init( hWnd);

	return S_OK;
}

void CManager::Uninit(void)
{
	//オブジェクトの破棄
	CScene::ReleaseAll();
}

void CManager::Update()
{
	//レンダラーの更新処理
	m_pRenderer->Update();

	//キーボードの更新処理
	m_pInputKeyboard->Update();

	//マウスの更新処理
	m_pInputMouse->Update();

	//カメラの更新処理
	m_pCamera->Update();

}
void CManager::Draw()
{
	//カメラ設置
	m_pCamera->SetCamera();

	//レンダラーの描画処理
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
	//オブジェクトの破棄
	CScene::ReleaseAll();

	//ライトの破棄
	CLight::ReleaseAll();

	//カメラの破棄
	if( m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}

	//キーボードの破棄
	if( m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	//マウスの破棄
	if( m_pInputMouse != NULL)
	{
		m_pInputMouse->Uninit();
		delete m_pInputMouse;
		m_pInputMouse = NULL;
	}

	//サウンドの破棄
	if( m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}

	//レンダラーの破棄
	if( m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//自己解放
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