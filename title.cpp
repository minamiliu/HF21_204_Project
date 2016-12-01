//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: title.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/17
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "scene2D.h"
#include "sound.h"
#include "time.h"
#include "score.h"


//============================================
// マクロ定義
//============================================
#define TEXTURE_BG "data/TEXTURE/titleBG.jpg"

//============================================
// 静的メンバー変数の初期化
//============================================


//============================================
//コンストラクタ
//============================================
CTitle::CTitle() : CManager(MODE_TITLE)
{
	
}

CTitle::~CTitle()
{
	
}

HRESULT CTitle::Init(void)
{

	//オブジェクトの生成(2Dポリゴン)
	CScene2D::Create( D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), TEXTURE_BG);

	//CSound *pSound = CManager::GetSound();
	//pSound->Play( CSound::SOUND_LABEL_BGM000);

	CTime::Create( D3DXVECTOR3(SCREEN_WIDTH/2, 100.0f, 0.0f), D3DXVECTOR3(200.0f, 100.0f, 0.0f), 2, 99, true, BLUE(1.0f));
	m_score = CScore::Create( D3DXVECTOR3(150, 100.0f, 0.0f), D3DXVECTOR3( 300, 50.0f, 0.0f), 6, RED(1.0f));
	m_score->SetScore(1000);

	return S_OK;
}

void CTitle::Uninit()
{
	//Sceneの破棄
	CManager::Uninit();
}

void CTitle::Update()
{
	//入力などの更新、各シーンのUpdateの最初に呼び出す
	CManager::Update();

	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	if( pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		SetNextScene( MODE_GAME);
	}

	if( pInputKeyboard->GetKeyTrigger(DIK_UP))
	{
		m_score->AddScore(100);
	}
	if( pInputKeyboard->GetKeyTrigger(DIK_DOWN))
	{
		m_score->AddScore(-100);
	}

	//シーンが切り替えるところ、各シーンのUpdateの最後に置いとく
	CManager::SceneChange();
}
void CTitle::Draw()
{
	CManager::Draw();
}
