//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: trashGameResult.cpp
// 作成者:		 HAL東京ゲーム学科　山家啓介
// 作成日:       2016/12/13
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "score.h"
#include "trashGameResult.h"
#include "scene2D.h"
//============================================
// マクロ定義
//============================================
#define TEXTURE_BGPOLYGON "data/TEXTURE/rendering003-16.png"

//============================================
// 静的メンバー変数の初期化
//============================================
CScore *CTrashGameResult::m_pScore;
int CTrashGameResult::m_nTrashGameResultCnt = 0;
//============================================
//コンストラクタ
//============================================
CTrashGameResult::CTrashGameResult() : CManager(MODE_TRASHGAMERESULT)
{
	m_nTrashGameResultCnt = 0;
}

CTrashGameResult::~CTrashGameResult()
{
	
}

HRESULT CTrashGameResult::Init(void)
{ 
	//m_pCamera->Init();
	
	//オブジェクトの生成(3Dポリゴン)
	//CScene3D::Create( D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 10, 10, 100.0f, 100.0f);

	//オブジェクトの生成(Xfile)
	//CPlayerX::Create( D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f), 5.0f);

	//背景
	CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f),D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f),TEXTURE_BGPOLYGON);
	//スコア
	m_pScore = CScore::Create(D3DXVECTOR3(640, 360.0f, 0.0f), D3DXVECTOR3(600.0f, 100.0f, 0.0f), 6, RED(1.0f));
	return S_OK;
}

void CTrashGameResult::Uninit()
{
	CManager::Uninit();
}

void CTrashGameResult::Update()
{
	CManager::Update();

	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	if( pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		SetNextScene( MODE_ZEBRAGAME);
	}

	//シーンが切り替えるところ、各シーンのUpdateの最後に置いとく
	CManager::SceneChange();
}

void CTrashGameResult::Draw()
{
	CManager::Draw();
}


int CTrashGameResult::GetTrashGameResultCnt(void)
{
	return m_nTrashGameResultCnt;
}