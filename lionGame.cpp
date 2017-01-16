//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: lionGame.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/17
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "debugproc.h"
#include "lionGame.h"
#include "renderer.h"
#include "input.h"
#include "light.h"
#include "camera.h"
#include "meshField.h"
#include "meshWall.h"
#include "meshRoof.h"
#include "playerX.h"
#include "collision.h"
#include "cubeX.h"
#include "score.h"
#include "enemyX.h"
#include "time.h"
#include "food.h"
#include "shadow.h"
#include "foodIcon.h"
#include "meshDome.h"
#include "effectBG.h"

//============================================
// マクロ定義
//============================================

//============================================
// 静的メンバー変数の初期化
//============================================
//CScore *CLionGame::m_score = NULL;

//============================================
//コンストラクタ
//============================================
CLionGame::CLionGame() : CManager(MODE_LIONGAME)
{
	m_pTime = NULL;
}

CLionGame::~CLionGame()
{
	
}

HRESULT CLionGame::Init(void)
{
	//変数の初期化
	m_state = STATE_NORMAL;

	//カメラの初期化
	m_pCamera->Init();

	//ドーム
	CMeshDome::Create( D3DXVECTOR3( 1000.0f, 0.0f, 750.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 1500.0f, 8, 8);
	CMeshDome::Create( D3DXVECTOR3( 1000.0f, 0.0f, 750.0f), D3DXVECTOR3( D3DX_PI, 0.0f, 0.0f), 1500.0f, 8, 8);

	//床
	CMeshField::Load();
	CMeshField::Create( D3DXVECTOR3( 1000.0f, 0.0f, 750.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 20, 15, 100.0f, 100.0f, CMeshField::TYPE_GREEN);

	//天井
	CMeshRoof::Load();
	CMeshRoof::Create( D3DXVECTOR3( 1000.0f, 300.0f, 750.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 10, 8, 200.0f, 200.0f, CMeshRoof::TYPE_WHITE);

	//ウォール
	CMeshWall::Load();
	CMeshWall::Create( D3DXVECTOR3( 1000.0f, 100.0f, 1500.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 21, 4, 100.0f, 100.0f);
	CMeshWall::Create( D3DXVECTOR3( 1000.0f, 100.0f, 0.0f), D3DXVECTOR3( 0.0f, D3DXToRadian(180.0f), 0.0f), 21, 4, 100.0f, 100.0f);
	CMeshWall::Create( D3DXVECTOR3( 2000.0f, 100.0f, 750.0f), D3DXVECTOR3( 0.0f, D3DXToRadian(90.0f), 0.0f), 16, 4, 100.0f, 100.0f);
	CMeshWall::Create( D3DXVECTOR3( 0.0f, 100.0f, 750.0f), D3DXVECTOR3( 0.0f, D3DXToRadian(-90.0f), 0.0f), 16, 4, 100.0f, 100.0f);
	
	//一番奥 ６個
	CCubeX::Load();
	CCubeX::Create( D3DXVECTOR3( 250.0f, 50.0f, 1100.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 400.0f), CCubeX::TYPE_1X4);
	CCubeX::Create( D3DXVECTOR3( 550.0f, 50.0f, 1100.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 400.0f), CCubeX::TYPE_1X4);
	CCubeX::Create( D3DXVECTOR3( 850.0f, 50.0f, 1100.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 400.0f), CCubeX::TYPE_1X4);
	CCubeX::Create( D3DXVECTOR3(1150.0f, 50.0f, 1100.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 400.0f), CCubeX::TYPE_1X4);
	CCubeX::Create( D3DXVECTOR3(1450.0f, 50.0f, 1100.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 400.0f), CCubeX::TYPE_1X4);
	CCubeX::Create( D3DXVECTOR3(1750.0f, 50.0f, 1100.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 400.0f), CCubeX::TYPE_1X4);
	
	
	CCubeX::Create( D3DXVECTOR3( 250.0f, 50.0f, 600.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 200.0f), CCubeX::TYPE_1X2);
	CCubeX::Create( D3DXVECTOR3( 550.0f, 50.0f, 600.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 200.0f), CCubeX::TYPE_1X2);
	CCubeX::Create( D3DXVECTOR3( 850.0f, 50.0f, 600.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 200.0f), CCubeX::TYPE_1X2);
	CCubeX::Create( D3DXVECTOR3(1150.0f, 50.0f, 600.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 200.0f), CCubeX::TYPE_1X2);
	CCubeX::Create( D3DXVECTOR3(1450.0f, 50.0f, 600.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 200.0f), CCubeX::TYPE_1X2);
	CCubeX::Create( D3DXVECTOR3(1750.0f, 50.0f, 600.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 200.0f), CCubeX::TYPE_1X2);
	
	
	CCubeX::Create( D3DXVECTOR3( 350.0f, 50.0f, 250.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 100.0f), CCubeX::TYPE_1X1);
	CCubeX::Create( D3DXVECTOR3( 650.0f, 50.0f, 250.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 100.0f), CCubeX::TYPE_1X1);
	CCubeX::Create( D3DXVECTOR3( 950.0f, 50.0f, 250.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 100.0f), CCubeX::TYPE_1X1);
	CCubeX::Create( D3DXVECTOR3(1250.0f, 50.0f, 250.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 100.0f), CCubeX::TYPE_1X1);
	CCubeX::Create( D3DXVECTOR3(1550.0f, 50.0f, 250.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 100.0f), CCubeX::TYPE_1X1);
	
	//影
	CShadow::Load();

	//プレイヤー
	CPlayerX::Create( D3DXVECTOR3( 50.0f, 60.0f, 50.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 2.0f, 2.0f, 2.0f), 0.03f);

	//スコア
	//m_score = CScore::Create( D3DXVECTOR3(SCREEN_WIDTH-150, 30.0f, 0.0f), D3DXVECTOR3( 300, 50.0f, 0.0f), 6, RED(1.0f)); 

	//タイム
	m_pTime = CTime::Create( D3DXVECTOR3(SCREEN_WIDTH/2, 100.0f, 0.0f), D3DXVECTOR3(140, 70.0f, 0.0f), 2, 99, true, BLUE(1.0f));

	//敵
	CEnemyX::Load();
	CEnemyX::Create(D3DXVECTOR3(  50, 60.0f, 600.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), CEnemyX::TYPE_000);
	CEnemyX::Create(D3DXVECTOR3( 350, 60.0f, 600.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), CEnemyX::TYPE_000);
	CEnemyX::Create(D3DXVECTOR3( 650, 60.0f, 600.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), CEnemyX::TYPE_000);
	CEnemyX::Create(D3DXVECTOR3( 950, 60.0f, 600.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), CEnemyX::TYPE_000);
	CEnemyX::Create(D3DXVECTOR3(1250, 60.0f, 600.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), CEnemyX::TYPE_000);
	CEnemyX::Create(D3DXVECTOR3(1550, 60.0f, 600.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), CEnemyX::TYPE_000);
	CEnemyX::Create(D3DXVECTOR3(1850, 60.0f, 600.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), CEnemyX::TYPE_000);

	CEnemyX::Create(D3DXVECTOR3(  50, 60.0f, 1000.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), CEnemyX::TYPE_000);
	CEnemyX::Create(D3DXVECTOR3( 350, 60.0f, 1000.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), CEnemyX::TYPE_000);
	CEnemyX::Create(D3DXVECTOR3( 650, 60.0f, 1000.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), CEnemyX::TYPE_000);
	CEnemyX::Create(D3DXVECTOR3( 950, 60.0f, 1000.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), CEnemyX::TYPE_000);
	CEnemyX::Create(D3DXVECTOR3(1250, 60.0f, 1000.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), CEnemyX::TYPE_000);
	CEnemyX::Create(D3DXVECTOR3(1550, 60.0f, 1000.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), CEnemyX::TYPE_000);
	CEnemyX::Create(D3DXVECTOR3(1850, 60.0f, 1000.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), CEnemyX::TYPE_000);

	//スーパーの食材
	CFood::Load();
	CFood::Create(D3DXVECTOR3( 100.0f, 50.0f, 700.0f), D3DXVECTOR2(100.0f, 100.0f), CFood::TYPE_CURRY);
	CFood::Create(D3DXVECTOR3( 400.0f, 50.0f, 700.0f), D3DXVECTOR2(100.0f, 100.0f), CFood::TYPE_EGG);
	CFood::Create(D3DXVECTOR3( 700.0f, 50.0f, 700.0f), D3DXVECTOR2(100.0f, 100.0f), CFood::TYPE_ONION);
	CFood::Create(D3DXVECTOR3(1000.0f, 50.0f, 700.0f), D3DXVECTOR2(100.0f, 100.0f), CFood::TYPE_POTATO);
	CFood::Create(D3DXVECTOR3(1300.0f, 50.0f, 700.0f), D3DXVECTOR2(100.0f, 100.0f), CFood::TYPE_MEAT);

	CFood::Create(D3DXVECTOR3( 100.0f, 50.0f, 1100.0f), D3DXVECTOR2(100.0f, 100.0f), CFood::TYPE_CABBAGE);
	CFood::Create(D3DXVECTOR3( 400.0f, 50.0f, 1100.0f), D3DXVECTOR2(100.0f, 100.0f), CFood::TYPE_MILK);
	CFood::Create(D3DXVECTOR3( 700.0f, 50.0f, 1100.0f), D3DXVECTOR2(100.0f, 100.0f), CFood::TYPE_BANANA);
	CFood::Create(D3DXVECTOR3(1000.0f, 50.0f, 1100.0f), D3DXVECTOR2(100.0f, 100.0f), CFood::TYPE_CARROT);
	CFood::Create(D3DXVECTOR3(1300.0f, 50.0f, 1100.0f), D3DXVECTOR2(100.0f, 100.0f), CFood::TYPE_TOMATO);

	return S_OK;
}

void CLionGame::Uninit()
{
	CManager::Uninit();
}

void CLionGame::Update()
{
	//入力などの更新、各シーンのUpdateの最初に呼び出す
	CManager::Update();

	//Time Up
	if(m_pTime->TimeUp())
	{
		SetNextScene( MODE_RESULT);
	}

	//if(m_pTime->GetTime() == 10 && m_state == STATE_NORMAL)
	//{
	//	//m_pTime->StopTime();
	//	CEffectBG::Create( D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	//	m_state = STATE_SUPER;
	//}


	//スキップシーン
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	if( pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		SetNextScene( MODE_RESULT);
	}

	//シーンが切り替えるところ、各シーンのUpdateの最後に置いとく
	CManager::SceneChange();
}
void CLionGame::Draw()
{
	CManager::Draw();
}

//CScore *CLionGame::GetScore(void)
//{
//	return m_score;
//}