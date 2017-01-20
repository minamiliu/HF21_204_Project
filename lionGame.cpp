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
#include "limbX.h"
#include "effect3D.h"
#include "change.h"

//============================================
// マクロ定義
//============================================
#define TEXTURE_LION	"data/TEXTURE/lion.png"
#define TEXTURE_LIONMOM "data/TEXTURE/lionMom.png"
#define TEXTURE_MOM		"data/TEXTURE/player000.png"
#define TEXTURE_MLT		"data/TEXTURE/かける.png"
//============================================
// 静的メンバー変数の初期化
//============================================
CScore *CLionGame::m_pScore = NULL;
CPlayerX *CLionGame::m_pPlayer = NULL;
CScene2D *pTextureMlt = NULL;
CScore *pTextureHd = NULL;
//=============================================================================
//コンストラクタ
//=============================================================================
CLionGame::CLionGame() : CManager(MODE_LIONGAME)
{
	m_pTime = NULL;
	m_pChange = NULL;
	m_pEffectBG = NULL;
}
//=============================================================================
//デストラクタ
//=============================================================================
CLionGame::~CLionGame()
{
	
}
//=============================================================================
//
//=============================================================================
HRESULT CLionGame::Init(void)
{
	//ゲームデータをロード
	LoadAll();

	//変数の初期化
	m_state = STATE_NORMAL;
	m_nCntState = 0;

	//カメラの初期化
	m_pCamera->Init();

	//ステージ設計
	CreateStageLiu();
	//CreateStageUsukura();

	pTextureMlt = NULL;
	pTextureHd = NULL;
	m_nGameCnt = 0;
	return S_OK;
}
//=============================================================================
//
//=============================================================================
void CLionGame::Uninit()
{
	//点数を保存
	CManager::SaveScore( MODE_LIONGAME, m_pScore->GetScore());

	CManager::Uninit();
}
//=============================================================================
//
//=============================================================================
void CLionGame::Update()
{
	//入力などの更新、各シーンのUpdateの最初に呼び出す
	CManager::Update();

	m_nGameCnt++;

	//時間になったら、変身する
	if(m_pTime->GetTime() == 55 && m_state == STATE_NORMAL)
	{
		m_pTime->StopTime();
		//m_pEffectBG = CEffectBG::Create( D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT/2, 0.0f));
		m_pChange = CChange::Create(TEXTURE_MOM, TEXTURE_LION, TEXTURE_LIONMOM);
		m_state = STATE_UPGRADE;
		m_pPlayer->SetState(CPlayerX::STATE_LION); //ライオンに変身
	}

	//状態更新
	switch( m_state)
	{
	case STATE_UPGRADE:
		
		if( m_pChange->GetState() == false)
		{
			m_pChange->Uninit();
			m_state = STATE_LION;
			m_pTime->StopTime();
			m_pTime->SetColor(RED(1.0f));
		}
		break;
	}

	//Time Up
	if(m_pTime->TimeUp())
	{
		SetNextScene( MODE_STAGE_LION);
	}

	//Game Clear or Time Up
	if(m_pPlayer->GetState() == CPlayerX::STATE_GOAL || m_pTime->GetTime() <= 59)
	{
		if(m_pTime->GetTimeFlag() == true)
		{
			m_pTime->StopTime();
		}
		D3DXVECTOR3 timePos = m_pTime->GetPosition();
		D3DXVECTOR3 scorePos = m_pScore->GetPosition();
		if(timePos.y <= 300 && scorePos.y <= 400 )
		{
	//		//スコア
	//m_pScore = CScore::Create( D3DXVECTOR3(150, 100.0f, 0.0f), D3DXVECTOR3( 300, 50.0f, 0.0f), 6, RED(1.0f)); 

	////タイム     timePos != D3DXVECTOR3(SCREEN_WIDTH/2,300,0) || scorePos != D3DXVECTOR3(SCREEN_WIDTH/2,400,0)
	//m_pTime = CTime::Create( D3DXVECTOR3(SCREEN_WIDTH/2, 100.0f, 0.0f), D3DXVECTOR3(150, 100.0f, 0.0f), 2, 99, true, BLUE(1.0f));



			scorePos.x += (SCREEN_WIDTH/2 - 150)/100;
			scorePos.y += (400 - 100)/100;
			m_pScore->SetPosition(scorePos);
			timePos.x += 0;
			timePos.y += (300 - 100)/120;
			m_pTime->SetPosition(timePos);
		}
		else
		{
			if(pTextureMlt == NULL && pTextureHd == NULL)
			{
				pTextureMlt = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH/2 + 150,230,0),D3DXVECTOR3(200,200,0),TEXTURE_MLT);
				pTextureHd = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH/2 + 250,220,0),D3DXVECTOR3(100,100,0),3,YELLOW(1.0));
				pTextureHd->SetScore(100);
				m_nGameCnt = 0;
			}
			if(m_nGameCnt >= 60 && m_nGameCnt % 10 == 0)
			{
				if(m_pTime->GetScore() != 0)
				{
					int time = m_pTime->GetScore();
					time--;
					m_pTime->SetScore(time);
					int score = m_pScore->GetScore();
					score+=100;
					m_pScore->SetScore(score);
				}
			}
		}
		//timePos.x+=10;
		//timePos.y+=10;
		//m_pTime->SetPosition(timePos);

		//m_pTime->SetPosition(D3DXVECTOR3(SCREEN_WIDTH/2,300,0));
		//m_pScore->SetPosition(D3DXVECTOR3(SCREEN_WIDTH/2,400,0));


		//SetNextScene( MODE_STAGE_LION);
	}

#ifdef _DEBUG
	//スキップシーン
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	if( pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		SetNextScene( MODE_STAGE_LION);
	}
#endif

	//シーンが切り替えるところ、各シーンのUpdateの最後に置いとく
	CManager::SceneChange();
}
//=============================================================================
//
//=============================================================================
void CLionGame::Draw()
{
	CManager::Draw();
}
//=============================================================================
//
//=============================================================================
CScore *CLionGame::GetScore(void)
{
	return m_pScore;
}
//=============================================================================
//
//=============================================================================
CPlayerX *CLionGame::GetPlayer(void)
{
	return m_pPlayer;
}
//=============================================================================
//ゲームが立ち上がるとき、一回のみ全部ロードする
//=============================================================================
HRESULT CLionGame::LoadAll(void)
{
	CPlayerX::Load();
	CLimbX::Load();
	CMeshField::Load();
	CMeshWall::Load();
	CMeshRoof::Load();
	CCubeX::Load();
	CShadow::Load();
	CEnemyX::Load();
	CFood::Load();
	CEffect3D::Load();

	return S_OK;
}
//=============================================================================
//
//=============================================================================
void CLionGame::CreateStageLiu(void)
{
	//ドーム
	CMeshDome::Create( D3DXVECTOR3( 1000.0f, 0.0f, 750.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 1500.0f, 8, 8);
	CMeshDome::Create( D3DXVECTOR3( 1000.0f, 0.0f, 750.0f), D3DXVECTOR3( D3DX_PI, 0.0f, 0.0f), 1500.0f, 8, 8);

	//床
	CMeshField::Create( D3DXVECTOR3( 1000.0f, 0.0f, 750.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 20, 15, 100.0f, 100.0f, CMeshField::TYPE_GREEN);

	//天井
	CMeshRoof::Create( D3DXVECTOR3( 1000.0f, 400.0f, 750.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 10, 8, 200.0f, 200.0f, CMeshRoof::TYPE_WHITE);

	//ウォール
	CMeshWall::Create( D3DXVECTOR3( 1000.0f, 200.0f, 1500.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 20, 4, 100.0f, 100.0f);
	CMeshWall::Create( D3DXVECTOR3( 1000.0f, 200.0f, 0.0f), D3DXVECTOR3( 0.0f, D3DXToRadian(180.0f), 0.0f), 20, 4, 100.0f, 100.0f);
	CMeshWall::Create( D3DXVECTOR3( 2000.0f, 200.0f, 750.0f), D3DXVECTOR3( 0.0f, D3DXToRadian(90.0f), 0.0f), 15, 4, 100.0f, 100.0f);
	CMeshWall::Create( D3DXVECTOR3( 0.0f, 200.0f, 750.0f), D3DXVECTOR3( 0.0f, D3DXToRadian(-90.0f), 0.0f), 15, 4, 100.0f, 100.0f);
	
	//一番奥 ６個
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

	//プレイヤー
	m_pPlayer = CPlayerX::Create( D3DXVECTOR3( 50.0f, 60.0f, 50.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 2.0f, 2.0f, 2.0f), 0.03f, CPlayerX::TYPE_HUMAN);

	//スコア
	m_pScore = CScore::Create( D3DXVECTOR3( 150.0f, 30.0f, 0.0f), D3DXVECTOR3( 300, 50.0f, 0.0f), 6, RED(1.0f)); 

	//タイム
	m_pTime = CTime::Create( D3DXVECTOR3(SCREEN_WIDTH/2, 100.0f, 0.0f), D3DXVECTOR3(140, 70.0f, 0.0f), 2, 60, true, BLUE(1.0f));

	//敵
	//CEnemyX::Create(D3DXVECTOR3(  50, 60.0f, 600.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), CEnemyX::TYPE_000);
	//CEnemyX::Create(D3DXVECTOR3( 350, 60.0f, 600.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), CEnemyX::TYPE_000);
	//CEnemyX::Create(D3DXVECTOR3( 650, 60.0f, 600.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), CEnemyX::TYPE_000);
	//CEnemyX::Create(D3DXVECTOR3( 950, 60.0f, 600.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), CEnemyX::TYPE_000);
	//CEnemyX::Create(D3DXVECTOR3(1250, 60.0f, 600.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), CEnemyX::TYPE_000);
	//CEnemyX::Create(D3DXVECTOR3(1550, 60.0f, 600.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), CEnemyX::TYPE_000);
	//CEnemyX::Create(D3DXVECTOR3(1850, 60.0f, 600.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), CEnemyX::TYPE_000);

	CEnemyX::Create(D3DXVECTOR3(  50, 60.0f, 1000.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), CEnemyX::TYPE_000);
	CEnemyX::Create(D3DXVECTOR3( 350, 60.0f, 1000.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), CEnemyX::TYPE_000);
	CEnemyX::Create(D3DXVECTOR3( 650, 60.0f, 1000.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), CEnemyX::TYPE_000);
	CEnemyX::Create(D3DXVECTOR3( 950, 60.0f, 1000.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), CEnemyX::TYPE_000);
	CEnemyX::Create(D3DXVECTOR3(1250, 60.0f, 1000.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), CEnemyX::TYPE_000);
	CEnemyX::Create(D3DXVECTOR3(1550, 60.0f, 1000.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), CEnemyX::TYPE_000);
	CEnemyX::Create(D3DXVECTOR3(1850, 60.0f, 1000.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), CEnemyX::TYPE_000);

	//スーパーの食材
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
}
void CLionGame::CreateStageUsukura(void)
{
	//ドーム
	CMeshDome::Create( D3DXVECTOR3( 1050.0f, 0.0f,1500.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 2000.0f, 8, 8);
	CMeshDome::Create( D3DXVECTOR3( 1050.0f, 0.0f,1500.0f), D3DXVECTOR3( D3DX_PI, 0.0f, 0.0f), 2000.0f, 8, 8);

	//床
	CScene3D::Create( D3DXVECTOR3( 1050.0f, 0.0f,1500.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 21, 30, 100.0f, 100.0f, false);

	//ウォール
	CMeshWall::Create( D3DXVECTOR3( 1050.0f, 100.0f, 3000.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 21, 4, 100.0f, 100.0f);
	CMeshWall::Create( D3DXVECTOR3( 1050.0f, 100.0f, 0.0f), D3DXVECTOR3( 0.0f, D3DXToRadian(180.0f), 0.0f), 21, 4, 100.0f, 100.0f);
	CMeshWall::Create( D3DXVECTOR3( 2100.0f, 100.0f, 1500.0f), D3DXVECTOR3( 0.0f, D3DXToRadian(90.0f), 0.0f), 30, 4, 100.0f, 100.0f);
	CMeshWall::Create( D3DXVECTOR3( 0.0f, 100.0f, 1500.0f), D3DXVECTOR3( 0.0f, D3DXToRadian(-90.0f), 0.0f), 30, 4, 100.0f, 100.0f);
	
	
	//一番奥 ６個
	for(int nCnt = 0 ; nCnt < 4 ; nCnt++)
	{
		CCubeX::Create( D3DXVECTOR3( 450.0f + (400 * nCnt), 50.0f, 800.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 400.0f), CCubeX::TYPE_1X4);
		CCubeX::Create( D3DXVECTOR3( 450.0f + (400 * nCnt), 50.0f, 1500.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 400.0f), CCubeX::TYPE_1X4);
		CCubeX::Create( D3DXVECTOR3( 450.0f + (400 * nCnt), 50.0f, 1900.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 400.0f), CCubeX::TYPE_1X4);
		CCubeX::Create( D3DXVECTOR3( 450.0f + (400 * nCnt), 50.0f, 2300.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 400.0f), CCubeX::TYPE_1X4);
	}
	CCubeX::Create( D3DXVECTOR3( 700.0f , 50.0f, 350.0f), D3DXVECTOR3( 0.0f, D3DXToRadian(90.0f), 0.0f), D3DXVECTOR3( 400.0f, 100.0f, 100.0f), CCubeX::TYPE_1X4);
	CCubeX::Create( D3DXVECTOR3( 1100.0f , 50.0f, 350.0f), D3DXVECTOR3( 0.0f, D3DXToRadian(90.0f), 0.0f), D3DXVECTOR3( 400.0f, 100.0f, 100.0f), CCubeX::TYPE_1X4);

	//レジ　５個
	CCubeX::Create( D3DXVECTOR3( 1950.0f, 50.0f, 300.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 100.0f), CCubeX::TYPE_1X1);
	CCubeX::Create( D3DXVECTOR3( 1750.0f, 50.0f, 300.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 100.0f), CCubeX::TYPE_1X1);
	


	//プレイヤー
	m_pPlayer = CPlayerX::Create( D3DXVECTOR3( 50.0f, 60.0f, 50.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 2.0f, 2.0f, 2.0f), 0.03f, CPlayerX::TYPE_HUMAN);


	//スコア
	m_pScore = CScore::Create( D3DXVECTOR3(150, 100.0f, 0.0f), D3DXVECTOR3( 300, 50.0f, 0.0f), 6, RED(1.0f)); 

	//タイム
	m_pTime = CTime::Create( D3DXVECTOR3(SCREEN_WIDTH/2, 100.0f, 0.0f), D3DXVECTOR3(150, 100.0f, 0.0f), 2, 99, true, BLUE(1.0f));

	//敵
	CEnemyX::Create( D3DXVECTOR3( 50, 60.0f, 600.0f), D3DXVECTOR3( 0.0f, D3DX_PI/2, 0.0f), D3DXVECTOR3( 2.0f, 2.0f, 2.0f), CEnemyX::TYPE_000);
	CEnemyX::Create( D3DXVECTOR3(350, 60.0f, 600.0f), D3DXVECTOR3( 0.0f, D3DX_PI/2, 0.0f), D3DXVECTOR3( 2.0f, 2.0f, 2.0f), CEnemyX::TYPE_000);
	CEnemyX::Create( D3DXVECTOR3(650, 60.0f, 600.0f), D3DXVECTOR3( 0.0f, D3DX_PI/2, 0.0f), D3DXVECTOR3( 2.0f, 2.0f, 2.0f), CEnemyX::TYPE_000);
	CEnemyX::Create( D3DXVECTOR3(950, 60.0f, 600.0f), D3DXVECTOR3( 0.0f, D3DX_PI/2, 0.0f), D3DXVECTOR3( 2.0f, 2.0f, 2.0f), CEnemyX::TYPE_000);

	//スーパーの食材
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
}