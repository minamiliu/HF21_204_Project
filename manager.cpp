//============================================
//
// タイトル:	 CL25課題
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
#include "scene2D.h"
#include "input.h"
#include "player2D.h"
#include "light.h"
#include "camera.h"
#include "scene3D.h"

//============================================
// マクロ定義
//============================================

//============================================
// 静的メンバー変数の初期化
//============================================
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputMouse *CManager::m_pInputMouse = NULL;
CLight *CManager::m_pLight = NULL;
CCamera *CManager::m_pCamera = NULL;

//============================================
//コンストラクタ
//============================================
CManager::CManager()
{

}

CManager::~CManager()
{
	
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
	m_pLight = new CLight;
	m_pLight->Init();

	//カメラの生成
	m_pCamera = new CCamera;
	m_pCamera->Init();

	//オブジェクトの生成(3Dポリゴン)
	CScene3D::Create( D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 10, 10, 100.0f, 100.0f);

	//オブジェクトの生成(2Dポリゴン)
	CPlayer2D::Create( D3DXVECTOR3( 200.0f, 300.0f, 0.0f), D3DXVECTOR3(300.0f, 300.0f, 0.0f));

	return S_OK;
}

void CManager::Uninit()
{
	//オブジェクトの破棄
	CScene2D::ReleaseAll();

	//ライトの破棄
	if( m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

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
