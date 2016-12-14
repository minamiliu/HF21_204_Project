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

#include "zebra.h"
#include "gorira.h"
#include "lion.h"
//============================================
// マクロ定義
//============================================
#define TEXTURE_BG "data/TEXTURE/サバンナタイトル用/背景/titleBg.png"

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

	//
	CZebra::Create(D3DXVECTOR3( SCREEN_WIDTH + 600, SCREEN_HEIGHT-250, 0.0f), D3DXVECTOR3(300, 200, 0.0f));
	CGorira::Create(D3DXVECTOR3( SCREEN_WIDTH + 300, SCREEN_HEIGHT-230, 0.0f), D3DXVECTOR3(160, 140, 0.0f));
	CLion::Create(D3DXVECTOR3( SCREEN_WIDTH + 900, SCREEN_HEIGHT-225, 0.0f), D3DXVECTOR3(230, 220, 0.0f));

	return S_OK;
}

void CTitle::Uninit()
{
	CManager::Uninit();
}

void CTitle::Update()
{
	//入力などの更新、各シーンのUpdateの最初に呼び出す
	CManager::Update();

	//CZebra::Update();
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	if( pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		SetNextScene( MODE_TRASHGAME);
	}

	//シーンが切り替えるところ、各シーンのUpdateの最後に置いとく
	CManager::SceneChange();
}
void CTitle::Draw()
{
	CManager::Draw();
	//CZebra::Draw();
}
