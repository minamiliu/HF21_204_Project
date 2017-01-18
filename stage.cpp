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
#include "stage.h"
#include "stagePlayer.h"
#include "stageBg.h"
//============================================
// マクロ定義
//============================================
#define TEXTURE_BG "data/TEXTURE/ステージ用/bg.jpg"
#define TEXTURE_START "data/TEXTURE/ステージ用/start.png"
#define TEXTURE_MASU "data/TEXTURE/ステージ用/masu.png"
#define TEXTURE_GOMIBOX "data/TEXTURE/ゴミ箱(灰色).png"
#define TEXTURE_GOMI "data/TEXTURE/ゴミ.png"
//============================================
// 静的メンバー変数の初期化
//============================================

//各マスの位置
D3DXVECTOR3 CStage::pos[MASU_MAX] = 
{
	D3DXVECTOR3( SCREEN_WIDTH*1/5, SCREEN_HEIGHT*3/4, 0.0f),//スタート位置
	D3DXVECTOR3( SCREEN_WIDTH*2/5, SCREEN_HEIGHT*2/4, 0.0f),//ゴミ捨て
	D3DXVECTOR3( SCREEN_WIDTH*3/5, SCREEN_HEIGHT*3/4, 0.0f),//片付け
	D3DXVECTOR3( SCREEN_WIDTH*4/5, SCREEN_HEIGHT*2/4, 0.0f)	//買い物
};

CStage::MASU_TYPE CStage::m_stageNow = MASU_START;
//============================================
//コンストラクタ
//============================================
CStage::CStage()// : CManager(MODE_STAGE)
{
	
}
CStage::CStage(MASU_TYPE type)
{
	m_stageNow = type;
}

CStage::~CStage()
{
	
}

HRESULT CStage::Init(void)
{

	//オブジェクトの生成(2Dポリゴン)
	//背景
	//CScene2D::Create( D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), TEXTURE_BG);
	CStageBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	//スタート
	CScene2D::Create( pos[MASU_START], D3DXVECTOR3(300, 120, 0.0f), TEXTURE_START);

	//ゴミ捨てゲーム
	CScene2D::Create( pos[MASU_GORIRA], D3DXVECTOR3(300, 120, 0.0f), TEXTURE_MASU);

	CScene2D::Create( D3DXVECTOR3( SCREEN_WIDTH*2/5, SCREEN_HEIGHT*2/4-120, 0.0f), D3DXVECTOR3(200, 120, 0.0f), TEXTURE_GOMIBOX);
	CScene2D::Create( D3DXVECTOR3( SCREEN_WIDTH*2/5-50, SCREEN_HEIGHT*2/4-170, 0.0f), D3DXVECTOR3(70, 50, 0.0f), TEXTURE_GOMI);
	//片付けゲーム
	CScene2D::Create( pos[MASU_ZEBRA], D3DXVECTOR3(300, 120, 0.0f), TEXTURE_MASU);
	//買い物ゲーム
	CScene2D::Create( pos[MASU_LION], D3DXVECTOR3(300, 120, 0.0f), TEXTURE_MASU);

	switch(m_stageNow)
	{
	case MASU_START:
		CStagePlayer::Create(	D3DXVECTOR3(pos[MASU_START].x,pos[MASU_START].y-50,0),//スタート位置
							D3DXVECTOR3(pos[MASU_GORIRA].x,pos[MASU_GORIRA].y-50,0),//ゴール位置
							D3DXVECTOR3(100, 100, 0.0f)
						);
		break;
	case MASU_GORIRA:
		CStagePlayer::Create(	D3DXVECTOR3(pos[MASU_GORIRA].x,pos[MASU_GORIRA].y-50,0),//スタート位置
							D3DXVECTOR3(pos[MASU_ZEBRA].x,pos[MASU_ZEBRA].y-50,0),//ゴール位置
							D3DXVECTOR3(100, 100, 0.0f)
						);
		break;
	case MASU_ZEBRA:
		CStagePlayer::Create(	D3DXVECTOR3(pos[MASU_ZEBRA].x,pos[MASU_ZEBRA].y-50,0),//スタート位置
							D3DXVECTOR3(pos[MASU_LION].x,pos[MASU_LION].y-50,0),//ゴール位置
							D3DXVECTOR3(100, 100, 0.0f)
						);
		break;
	}
	return S_OK;
}

void CStage::Uninit()
{
	CManager::Uninit();
}

void CStage::Update()
{
	//入力などの更新、各シーンのUpdateの最初に呼び出す
	CManager::Update();


	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	if( pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		switch(m_stageNow)
		{
		case MASU_START:
			SetNextScene( MODE_TRASHGAME);
			break;
		case MASU_GORIRA:
			SetNextScene( MODE_ZEBRAGAME);
			break;
		case MASU_ZEBRA:
			SetNextScene( MODE_LIONGAME);
			break;
		}
	}

	//シーンが切り替えるところ、各シーンのUpdateの最後に置いとく
	CManager::SceneChange();
}
void CStage::Draw()
{
	CManager::Draw();
}
