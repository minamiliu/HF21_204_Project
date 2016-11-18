//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: result.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/17
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "result.h"
#include "input.h"
#include "scene2D.h"


//============================================
// マクロ定義
//============================================
#define TEXTURE_BG "data/TEXTURE/resultBG.jpg"

//============================================
// 静的メンバー変数の初期化
//============================================


//============================================
//コンストラクタ
//============================================
CResult::CResult() : CManager(TYPE_RESULT)
{

}

CResult::~CResult()
{
	
}

HRESULT CResult::Init(void)
{
	//オブジェクトの生成(2Dポリゴン)
	CScene2D::Create( D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), TEXTURE_BG);

	return S_OK;
}

void CResult::Uninit()
{
	CManager::Uninit();
}

void CResult::Update()
{
	CManager::Update();

	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	if( pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		SetScene( TYPE_TITLE);
	}
}
void CResult::Draw()
{
	CManager::Draw();
}
