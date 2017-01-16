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
	m_player = NULL;
}

CLionGame::~CLionGame()
{
	
}

HRESULT CLionGame::Init(void)
{
	//変数の初期化
	m_state = STATE_NORMAL;
	m_nNumCube = 0; //棚の数
	m_nNumWall = 0; //壁の数

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
	m_pMeshWall[m_nNumWall++] = CMeshWall::Create( D3DXVECTOR3( 1000.0f, 100.0f, 1500.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 21, 4, 100.0f, 100.0f);
	m_pMeshWall[m_nNumWall++] = CMeshWall::Create( D3DXVECTOR3( 1000.0f, 100.0f, 0.0f), D3DXVECTOR3( 0.0f, D3DXToRadian(180.0f), 0.0f), 21, 4, 100.0f, 100.0f);
	m_pMeshWall[m_nNumWall++] = CMeshWall::Create( D3DXVECTOR3( 2000.0f, 100.0f, 750.0f), D3DXVECTOR3( 0.0f, D3DXToRadian(90.0f), 0.0f), 16, 4, 100.0f, 100.0f);
	m_pMeshWall[m_nNumWall++] = CMeshWall::Create( D3DXVECTOR3( 0.0f, 100.0f, 750.0f), D3DXVECTOR3( 0.0f, D3DXToRadian(-90.0f), 0.0f), 16, 4, 100.0f, 100.0f);
	
	//一番奥 ６個
	CCubeX::Load();
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3( 250.0f, 50.0f, 1100.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 400.0f), CCubeX::TYPE_1X4);
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3( 550.0f, 50.0f, 1100.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 400.0f), CCubeX::TYPE_1X4);
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3( 850.0f, 50.0f, 1100.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 400.0f), CCubeX::TYPE_1X4);
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3(1150.0f, 50.0f, 1100.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 400.0f), CCubeX::TYPE_1X4);
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3(1450.0f, 50.0f, 1100.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 400.0f), CCubeX::TYPE_1X4);
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3(1750.0f, 50.0f, 1100.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 400.0f), CCubeX::TYPE_1X4);

	//2段目　６個
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3( 250.0f, 50.0f, 600.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 200.0f), CCubeX::TYPE_1X2);
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3( 550.0f, 50.0f, 600.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 200.0f), CCubeX::TYPE_1X2);
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3( 850.0f, 50.0f, 600.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 200.0f), CCubeX::TYPE_1X2);
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3(1150.0f, 50.0f, 600.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 200.0f), CCubeX::TYPE_1X2);
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3(1450.0f, 50.0f, 600.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 200.0f), CCubeX::TYPE_1X2);
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3(1750.0f, 50.0f, 600.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 200.0f), CCubeX::TYPE_1X2);

	//レジ　５個
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3( 350.0f, 50.0f, 250.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 100.0f), CCubeX::TYPE_1X1);
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3( 650.0f, 50.0f, 250.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 100.0f), CCubeX::TYPE_1X1);
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3( 950.0f, 50.0f, 250.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 100.0f), CCubeX::TYPE_1X1);
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3(1250.0f, 50.0f, 250.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 100.0f), CCubeX::TYPE_1X1);
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3(1550.0f, 50.0f, 250.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 100.0f), CCubeX::TYPE_1X1);
	
	//影
	CShadow::Load();

	//プレイヤー
	m_player = CPlayerX::Create( D3DXVECTOR3( 50.0f, 60.0f, 50.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 2.0f, 2.0f, 2.0f), 0.03f);

	//アイテム
	//CItemX::Create( D3DXVECTOR3( -200.0f, 30.0f, -200.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f));
	//CItemX::Create( D3DXVECTOR3( -100.0f, 30.0f, 100.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f));
	//CItemX::Create( D3DXVECTOR3( 100.0f, 30.0f, -100.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f));
	//CItemX::Create( D3DXVECTOR3( 100.0f, 30.0f, 100.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f));

	//スコア
	//m_score = CScore::Create( D3DXVECTOR3(SCREEN_WIDTH-150, 30.0f, 0.0f), D3DXVECTOR3( 300, 50.0f, 0.0f), 6, RED(1.0f)); 

	//タイム
	m_pTime = CTime::Create( D3DXVECTOR3(SCREEN_WIDTH/2, 100.0f, 0.0f), D3DXVECTOR3(140, 70.0f, 0.0f), 2, 11, true, BLUE(1.0f));

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

	//壁との当たり判定
	bool bHit = false;
	D3DXVECTOR3 front = m_player->GetFront();
	D3DXVECTOR3 posP = m_player->GetPosition();
	D3DXVECTOR3 wall_nor;
	for(int cntWall = 0; cntWall < m_nNumWall; cntWall++)
	{
		if( m_pMeshWall[cntWall]->HitCheck( posP,  posP + front, &wall_nor, NULL))
		{
			bHit = true;
			break;
		}
	}

	//キューブとの当たり判定
	bool bHitCube = false;
	int nIDCube = 0;
	for(int cntCube = 0; cntCube < m_nNumCube; cntCube++)
	{
		float len = m_cube[cntCube]->GetDistanceBoxPoint( m_player->GetPosition() + front);
		if( len < 15.0f)
		{
			bHitCube = true;
			bHit = true;
			nIDCube = cntCube;
			break;
		}	
	}



	//当たり判定後のプレイヤー移動
	if( bHit == false)
	{
		m_player->SetPosition( posP + front);
	}
	else
	{
		if( bHitCube == true)
		{
			//レジにいたら
			if( m_cube[nIDCube]->GetType() == CCubeX::TYPE_1X1)
			{
				if( CFood::isAllClear() == true)
				{
					SetNextScene( MODE_RESULT);
				}
			}

			//壁ずり
			D3DXVECTOR3 vecX = D3DXVECTOR3( 1.0f, 0.0f, 0.0f);
			D3DXVECTOR3 vecZ = D3DXVECTOR3( 0.0f, 0.0f, 1.0f);
			CCollision::GetWallScratchVector( &vecX, front, vecX);
			CCollision::GetWallScratchVector( &vecZ, front, vecZ);
			
			if( m_cube[nIDCube]->GetDistanceBoxPoint( m_player->GetPosition() + vecX) >= 15.0f)
			{
				m_player->SetPosition( posP + vecX);
			}
			if( m_cube[nIDCube]->GetDistanceBoxPoint( m_player->GetPosition() + vecZ) >= 15.0f)
			{
				m_player->SetPosition( posP + vecZ);
			}
		}
		else
		{
			bHit = false;

			//前進方向の修正
			CCollision::GetWallScratchVector( &front, front, wall_nor);

			//壁との当たり判定(2回目)
			for(int cntWall = 0; cntWall < m_nNumWall; cntWall++)
			{
				if( m_pMeshWall[cntWall]->HitCheck( posP,  posP + front, &wall_nor, NULL))
				{
					bHit = true;
					break;
				}
			}
			//移動
			if( bHit == false)
			{
				m_player->SetPosition( posP + front);
			}		
		}
	}

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