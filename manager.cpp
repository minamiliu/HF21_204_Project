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
#include "light.h"
#include "camera.h"
#include "sound.h"
#include "lionGame.h"
#include "zebragame.h"
#include "trashGame.h"
#include "trashGameResult.h"
#include "title.h"
#include "result.h"
#include "fade.h"
#include "scene.h"
#include "stage.h"

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
HWND CManager::m_hWnd = NULL;

int CManager::m_trashGameScore = 0;
int CManager::m_zebraGameScore = 0;
int CManager::m_lionGameScore = 0;
//=============================================================================
//コンストラクタ
//=============================================================================
CManager::CManager()
{
	m_pSceneManager = this;
}

//=============================================================================
//コンストラクタ
//=============================================================================
CManager::CManager(MODE mode)
{
	m_modeNow = mode;
	m_pSceneManager = this;
}
//=============================================================================
//デストラクタ
//=============================================================================
CManager::~CManager()
{
	
}

//=============================================================================
//初期化
//=============================================================================
HRESULT CManager::Init(void)
{
	return S_OK;
}

//=============================================================================
//初期化
//=============================================================================
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
	CLight::Create( D3DXVECTOR3( -0.2f, -0.3f, -0.5f), D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f));
	CLight::Create( D3DXVECTOR3( 0.8f, 0.1f, 0.5f), D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f));
	CLight::Create( D3DXVECTOR3( 0.0f, 1.0f, 0.0f), D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f));
	CLight::SetAllLightOn();

	//カメラの生成
	m_pCamera = new CCamera;
	m_pCamera->Init();

	//サウンド
	m_pSound = new CSound;
	m_pSound->Init( hWnd);

	m_hWnd = hWnd;

	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CManager::Uninit(void)
{
	//オブジェクトの破棄
	CScene::ReleaseAll();
}

//=============================================================================
//更新処理
//=============================================================================
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

	//マウス範囲の制約
	//POINT curPos;
	//ShowCursor(false);
	//GetCursorPos(&curPos);
	//WINDOWINFO windowInfo;
	//GetWindowInfo( m_hWnd, &windowInfo);
	//if(curPos.x > windowInfo.rcClient.right || curPos.x < windowInfo.rcClient.left || curPos.y > windowInfo.rcClient.bottom || curPos.y < windowInfo.rcClient.top)
	//{
	//	SetCursorPos( (windowInfo.rcClient.right + windowInfo.rcClient.left)/2, (windowInfo.rcClient.top + windowInfo.rcClient.bottom)/2);
	//}

}

//=============================================================================
//描画処理
//=============================================================================
void CManager::Draw()
{
	//カメラ設置
	m_pCamera->SetCamera();

	//レンダラーの描画処理
	m_pRenderer->Draw();	
}

//=============================================================================
//シーンの基本部分を生成
//=============================================================================
CManager *CManager::Create( MODE mode, HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	if( m_pSceneManager == NULL)
	{	
		m_pSceneManager = new CManager;
		m_pSceneManager->Init( hInstance, hWnd, bWindow);
	}

	//ゲームデータのロード
	LoadAll();

	//ゲームシーンの生成
	m_modeNext = mode;
	NextModeChange();
	SceneChange();

	return m_pSceneManager;
}

//=============================================================================
//オブジェクトの全体更新処理
//=============================================================================
void CManager::UpdateAll(void)
{
	m_pSceneManager->Update();
}

//=============================================================================
//オブジェクトの全体描画処理
//=============================================================================
void CManager::DrawAll(void)
{
	m_pSceneManager->Draw();
}

//=============================================================================
//シーンの基本部分のリリース
//=============================================================================
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

//=============================================================================
//取得関数リスト
//=============================================================================
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

CSound *CManager::GetSound(void)
{
	return m_pSound;
}

//=============================================================================
//シーンを設置
//=============================================================================
void CManager::NextModeChange(void)
{
	m_modeNow = m_modeNext;
}

//=============================================================================
//フェードのあるシーン設置
//=============================================================================
void CManager::SetNextScene(MODE mode)
{
	if( CFade::isFading() == false)
	{
		m_modeNext = mode;
		CFade::SetFade();
	}
}

//=============================================================================
//シーンの切り替えるが発生する関数
//=============================================================================
void CManager::SceneChange(void)
{
	if( m_modeNext != MODE_NONE && m_modeNow == m_modeNext)
	{
		m_pSceneManager->Uninit();
		m_pSceneManager = NULL;
	}
	else
	{
		return;
	}

	switch(m_modeNext)
	{
	case MODE_TITLE:
		m_pSceneManager = new CTitle;
		break;
		
	case MODE_TRASHGAME:
		m_pSceneManager = new CTrashGame;
		break;

	case MODE_TRASHGAMERESULT:
		m_pSceneManager = new CTrashGameResult;
		break;
		
	case MODE_ZEBRAGAME:
		m_pSceneManager = new CZebraGame;
		break;
		
	case MODE_LIONGAME:
		m_pSceneManager = new CLionGame;
		break;

	case MODE_RESULT:
		m_pSceneManager = new CResult;
		break;

	case MODE_STAGE_START:
		m_pSceneManager = new CStage(CStage::MASU_START);
		break;
	case MODE_STAGE_GORIRA:
		m_pSceneManager = new CStage(CStage::MASU_GORIRA);
		break;
	case MODE_STAGE_ZEBRA:
		m_pSceneManager = new CStage(CStage::MASU_ZEBRA);
		break;
	}
	
	//次のシーンはなしにする
	m_modeNext = MODE_NONE;

	//次のシーンの初期化
	m_pSceneManager->Init();
}

//=============================================================================
//スコアセーブ
//=============================================================================
void CManager::SaveScore(MODE game, int score)
{
	switch(game)
	{
	case MODE_TRASHGAME:
		m_trashGameScore = score;
		break;
	case MODE_ZEBRAGAME:
		m_zebraGameScore = score;
		break;
	case MODE_LIONGAME:
		m_lionGameScore = score;
		break;	
	}
}
//=============================================================================
//スコアロード
//=============================================================================
int CManager::LoadScore(MODE game)
{
	switch(game)
	{
	case MODE_TRASHGAME:
		return m_trashGameScore;
		break;
	case MODE_ZEBRAGAME:
		return m_zebraGameScore;
		break;
	case MODE_LIONGAME:
		return m_lionGameScore;
		break;
	default:
		return 0;
	}
}
//=============================================================================
//モデルやテクスチャを一気にロードする
//=============================================================================
HRESULT CManager::LoadAll(void)
{
	CLionGame::LoadAll();
	return S_OK;
}
