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
#include "game.h"

#include "game.h"
#include "title.h"
#include "result.h"

//============================================
// マクロ定義
//============================================

//============================================
// 静的メンバー変数の初期化
//============================================
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputMouse *CManager::m_pInputMouse = NULL;
CCamera *CManager::m_pCamera = NULL;

CManager *CManager::m_pSceneManager = NULL;
CManager::TYPE CManager::m_type = TYPE_NONE;

//============================================
//コンストラクタ
//============================================
CManager::CManager()
{
	m_pSceneManager = this;
}

CManager::CManager(TYPE type)
{
	m_type = type;
	m_pSceneManager = this;
}

CManager::~CManager()
{
	
}

HRESULT CManager::InitProgram(HINSTANCE hInstance, HWND hWnd, bool bWindow)
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

	return S_OK;
}

HRESULT CManager::Init(void)
{
	return S_OK;
}

void CManager::UninitProgram()
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

	//レンダラーの破棄
	if( m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
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
	if( m_type != type)
	{
		m_pSceneManager->Uninit();
		m_pSceneManager = NULL;
	}

	switch(type)
	{
	case TYPE_TITLE:
		m_pSceneManager = new CTitle;
		break;

	case TYPE_GAME:
		m_pSceneManager = new CGame;
		break;

	case TYPE_RESULT:
		m_pSceneManager = new CResult;
		break;

	}

	m_pSceneManager->Init();

	return m_pSceneManager;
}

void CManager::CheckScene( CManager **ppManager)
{
	if( *ppManager != m_pSceneManager)
	{
		*ppManager = m_pSceneManager;
	}
}