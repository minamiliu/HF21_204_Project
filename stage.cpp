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
#include "timeBg.h"
#include "sun.h"
#include "score.h"
#include "text.h"
#include "sound.h"
//============================================
// マクロ定義
//============================================
#define TEXTURE_BG "data/TEXTURE/Stage/bg.jpg"
#define TEXTURE_START "data/TEXTURE/Stage/start.png"
#define TEXTURE_GOAL "data/TEXTURE/Stage/goal.png"
#define TEXTURE_MASU "data/TEXTURE/Stage/masu.png"

#define TEXTURE_GORIRA_MASU "data/TEXTURE/Stage/gorilla.png"
#define TEXTURE_ZEBRA_MASU "data/TEXTURE/Stage/zebra.png"
#define TEXTURE_LION_MASU "data/TEXTURE/Stage/lion.png"

#define TEXTURE_GOMIBOX "data/TEXTURE/TrashBoxGray.png"
#define TEXTURE_GOMI "data/TEXTURE/Trash.png"
#define TEXTURE_ROAD1 "data/TEXTURE/Stage/Road1.png"
#define TEXTURE_ROAD2 "data/TEXTURE/Stage/Road2.png"
#define MASU_ROTATE	(0.8)
#define ROAD_ROTATE1	(55)
#define ROAD_ROTATE2	(55)
#define ROAD2_TYOUSEI	(-5)
#define PLAYER_POS_TYOUSEI (40)

#define TEXT_SIZE_X_GORIRA	(50)
#define TEXT_SIZE_X_ZEBRA	(50)
#define TEXT_SIZE_X_LION	(50)
#define TEXT_SIZE_Y			(2.82)
#define TEXT_ROTATE			(50)
//============================================
// 静的メンバー変数の初期化
//============================================

//各マスの位置
D3DXVECTOR3 CStage::pos[MASU_MAX] = 
{
	//Wの形ver
	//D3DXVECTOR3( SCREEN_WIDTH*1/6, SCREEN_HEIGHT*3/4, 0.0f),//スタート位置
	//D3DXVECTOR3( SCREEN_WIDTH*2/6, SCREEN_HEIGHT*2/4, 0.0f),//ゴミ捨て
	//D3DXVECTOR3( SCREEN_WIDTH*3/6, SCREEN_HEIGHT*3/4, 0.0f),//片付け
	//D3DXVECTOR3( SCREEN_WIDTH*4/6, SCREEN_HEIGHT*2/4, 0.0f),//買い物
	//D3DXVECTOR3( SCREEN_WIDTH*5/6, SCREEN_HEIGHT*3/4, 0.0f)	//ゴール位置

	//倒したZの形ver
	D3DXVECTOR3( SCREEN_WIDTH*1/6, SCREEN_HEIGHT-200, 0.0f),//スタート位置
	D3DXVECTOR3( SCREEN_WIDTH*1/6+100, SCREEN_HEIGHT-350, 0.0f),//ゴミ捨て
	D3DXVECTOR3( SCREEN_WIDTH*3/6, SCREEN_HEIGHT-350, 0.0f),//片付け
	D3DXVECTOR3( SCREEN_WIDTH*5/6-100, SCREEN_HEIGHT-350, 0.0f),//買い物
	D3DXVECTOR3( SCREEN_WIDTH*5/6, SCREEN_HEIGHT-500, 0.0f)	//ゴール位置

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

	//BGM	
	CSound *pSound = CManager::GetSound();
	pSound->Play(CSound::SOUND_LABEL_BGM_STAGE);

	switch(m_stageNow)
	{
	case MASU_START:
		CTimeBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_WIDTH/16, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH/8, 0.0f),3,0);
		//CTimeBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_WIDTH*6/16, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH*4/8, 0.0f),3,1);

		CSun::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/6,0),//スタート位置
					D3DXVECTOR3(90, 90, 0.0f),
					4.0);


		break;
	case MASU_GORIRA:
		CTimeBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_WIDTH/16, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH/8, 0.0f),0,0);
		//CTimeBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_WIDTH*6/16, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH*4/8, 0.0f),0,1);

		CSun::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/6,0),//スタート位置
					D3DXVECTOR3(90, 90, 0.0f),
					4.4);


		break;
	case MASU_ZEBRA:
		CTimeBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_WIDTH/16, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH/8, 0.0f),1,0);
		//CTimeBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_WIDTH*6/16, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH*4/8, 0.0f),1,1);

		CSun::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/6,0),//スタート位置
					D3DXVECTOR3(90, 90, 0.0f),
					4.8);

		break;
	case MASU_LION:
		CTimeBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_WIDTH/16, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH/8, 0.0f),2,0);
		//CTimeBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_WIDTH*6/16, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH*4/8, 0.0f),2,1);

		CSun::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/6,0),//スタート位置
					D3DXVECTOR3(90, 90, 0.0f),
					5.2);

		break;
	}

	CStageBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	switch(m_stageNow)
	{
	case MASU_START:
		//CTimeBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_WIDTH/16, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH/8, 0.0f),3,0);
		CTimeBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_WIDTH*6/16, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH*4/8, 0.0f),3,1);
		break;
	case MASU_GORIRA:
		//CTimeBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_WIDTH/16, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH/8, 0.0f),0,0);
		CTimeBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_WIDTH*6/16, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH*4/8, 0.0f),0,1);
		break;
	case MASU_ZEBRA:
		//CTimeBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_WIDTH/16, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH/8, 0.0f),1,0);
		CTimeBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_WIDTH*6/16, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH*4/8, 0.0f),1,1);
		break;
	case MASU_LION:
		//CTimeBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_WIDTH/16, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH/8, 0.0f),2,0);
		CTimeBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_WIDTH*6/16, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH*4/8, 0.0f),2,1);
		break;
	}


	//道
	CScene2D::Create(	D3DXVECTOR3(pos[MASU_START].x-(pos[MASU_START].x-pos[MASU_GORIRA].x)/2,pos[MASU_START].y-(pos[MASU_START].y-pos[MASU_GORIRA].y)/2,pos[MASU_START].z),
						D3DXVECTOR3(5*ROAD_ROTATE1, 5*ROAD_ROTATE1, 0.0f),
						TEXTURE_ROAD1);

	CScene2D::Create(	D3DXVECTOR3(pos[MASU_GORIRA].x-(pos[MASU_GORIRA].x-pos[MASU_ZEBRA].x)/2,pos[MASU_GORIRA].y-(pos[MASU_GORIRA].y-pos[MASU_ZEBRA].y)/2 - ROAD2_TYOUSEI,pos[MASU_GORIRA].z),
						D3DXVECTOR3(5*ROAD_ROTATE2, 5*ROAD_ROTATE2, 0.0f),
						TEXTURE_ROAD2);

	CScene2D::Create(	D3DXVECTOR3(pos[MASU_ZEBRA].x-(pos[MASU_ZEBRA].x-pos[MASU_LION].x)/2,pos[MASU_ZEBRA].y-(pos[MASU_ZEBRA].y-pos[MASU_LION].y)/2 - ROAD2_TYOUSEI,pos[MASU_ZEBRA].z),
						D3DXVECTOR3(5*ROAD_ROTATE2, 5*ROAD_ROTATE2, 0.0f),
						TEXTURE_ROAD2);

	CScene2D::Create(	D3DXVECTOR3(pos[MASU_LION].x-(pos[MASU_START].x-pos[MASU_GORIRA].x)/2,pos[MASU_LION].y-(pos[MASU_START].y-pos[MASU_GORIRA].y)/2 - ROAD2_TYOUSEI,pos[MASU_LION].z),
						D3DXVECTOR3(5*ROAD_ROTATE1, 5*ROAD_ROTATE1, 0.0f),
						TEXTURE_ROAD1);

	//スタート
	CScene2D::Create( pos[MASU_START], D3DXVECTOR3(300, 120, 0.0f), TEXTURE_START);

	//ゴミ捨てゲーム
	CScene2D::Create( pos[MASU_GORIRA], D3DXVECTOR3(300, 300, 0.0f) * MASU_ROTATE, TEXTURE_GORIRA_MASU);
	//CScene2D::Create( D3DXVECTOR3( SCREEN_WIDTH*2/5, SCREEN_HEIGHT*2/4-120, 0.0f), D3DXVECTOR3(200, 120, 0.0f), TEXTURE_GOMIBOX);
	//CScene2D::Create( D3DXVECTOR3( SCREEN_WIDTH*2/5-50, SCREEN_HEIGHT*2/4-170, 0.0f), D3DXVECTOR3(70, 50, 0.0f), TEXTURE_GOMI);

	//片付けゲーム
	CScene2D::Create( pos[MASU_ZEBRA], D3DXVECTOR3(300, 300, 0.0f) * MASU_ROTATE, TEXTURE_ZEBRA_MASU);

	//買い物ゲーム
	CScene2D::Create( pos[MASU_LION], D3DXVECTOR3(300, 300, 0.0f) * MASU_ROTATE, TEXTURE_LION_MASU);

	//ゴール
	CScene2D::Create( pos[MASU_GOAL], D3DXVECTOR3(300, 120, 0.0f), TEXTURE_GOAL);
	switch(m_stageNow)
	{
	case MASU_START:
		CStagePlayer::Create(	D3DXVECTOR3(pos[MASU_START].x,pos[MASU_START].y-PLAYER_POS_TYOUSEI,0),//スタート位置
							D3DXVECTOR3(pos[MASU_GORIRA].x,pos[MASU_GORIRA].y-PLAYER_POS_TYOUSEI,0),//ゴール位置
							D3DXVECTOR3(100, 100, 0.0f)
						);
		CText::Create(	D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT-(TEXT_SIZE_Y*TEXT_ROTATE/2),0),
						D3DXVECTOR3(TEXT_SIZE_X_GORIRA*TEXT_ROTATE,TEXT_SIZE_Y*TEXT_ROTATE,0),
						1,
						0);

		break;
	case MASU_GORIRA:
		CStagePlayer::Create(	D3DXVECTOR3(pos[MASU_GORIRA].x,pos[MASU_GORIRA].y-PLAYER_POS_TYOUSEI,0),//スタート位置
							D3DXVECTOR3(pos[MASU_ZEBRA].x,pos[MASU_ZEBRA].y-PLAYER_POS_TYOUSEI,0),//ゴール位置
							D3DXVECTOR3(100, 100, 0.0f)
						);
		CText::Create(	D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT-(TEXT_SIZE_Y*TEXT_ROTATE/2),0),
						D3DXVECTOR3(TEXT_SIZE_X_ZEBRA*TEXT_ROTATE,TEXT_SIZE_Y*TEXT_ROTATE,0),
						1,
						1);
		//スコア
		m_pScore = CScore::Create( pos[MASU_GORIRA] + D3DXVECTOR3( 0.0f, 50.0f, 0.0f), D3DXVECTOR3( 240, 40.0f, 0.0f), 6, BLUE(1.0f));
		m_pScore->SetScore(CManager::LoadScore(MODE_TRASHGAME));
		break;
	case MASU_ZEBRA:
		CStagePlayer::Create(	D3DXVECTOR3(pos[MASU_ZEBRA].x,pos[MASU_ZEBRA].y-PLAYER_POS_TYOUSEI,0),//スタート位置
							D3DXVECTOR3(pos[MASU_LION].x,pos[MASU_LION].y-PLAYER_POS_TYOUSEI,0),//ゴール位置
							D3DXVECTOR3(100, 100, 0.0f)
						);
		CText::Create(	D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT-(TEXT_SIZE_Y*TEXT_ROTATE/2),0),
						D3DXVECTOR3(TEXT_SIZE_X_LION*TEXT_ROTATE,TEXT_SIZE_Y*TEXT_ROTATE,0),
						1,
						2);

		//スコア
		m_pScore = CScore::Create( pos[MASU_GORIRA] + D3DXVECTOR3( 0.0f, 50.0f, 0.0f), D3DXVECTOR3( 240, 40.0f, 0.0f), 6, BLUE(1.0f));
		m_pScore->SetScore(CManager::LoadScore(MODE_TRASHGAME));
		//スコア
		m_pScore = CScore::Create( pos[MASU_ZEBRA] + D3DXVECTOR3( 0.0f, 50.0f, 0.0f), D3DXVECTOR3( 240, 40.0f, 0.0f), 6, BLUE(1.0f));
		m_pScore->SetScore(CManager::LoadScore(MODE_ZEBRAGAME));

		break;
	case MASU_LION:
		CStagePlayer::Create(	D3DXVECTOR3(pos[MASU_LION].x,pos[MASU_LION].y-PLAYER_POS_TYOUSEI,0),//スタート位置
							D3DXVECTOR3(pos[MASU_GOAL].x,pos[MASU_GOAL].y-PLAYER_POS_TYOUSEI,0),//ゴール位置
							D3DXVECTOR3(100, 100, 0.0f)
						);
		//スコア
		m_pScore = CScore::Create( pos[MASU_GORIRA] + D3DXVECTOR3( 0.0f, 50.0f, 0.0f), D3DXVECTOR3( 240, 40.0f, 0.0f), 6, BLUE(1.0f));
		m_pScore->SetScore(CManager::LoadScore(MODE_TRASHGAME));
		//スコア
		m_pScore = CScore::Create( pos[MASU_ZEBRA] + D3DXVECTOR3( 0.0f, 50.0f, 0.0f), D3DXVECTOR3( 240, 40.0f, 0.0f), 6, BLUE(1.0f));
		m_pScore->SetScore(CManager::LoadScore(MODE_ZEBRAGAME));
		//スコア
		m_pScore = CScore::Create( pos[MASU_LION] + D3DXVECTOR3( 0.0f, 50.0f, 0.0f), D3DXVECTOR3( 240, 40.0f, 0.0f), 6, BLUE(1.0f));
		m_pScore->SetScore(CManager::LoadScore(MODE_LIONGAME));
		break;
	}

	return S_OK;
}

void CStage::Uninit()
{
	CSound *pSound = CManager::GetSound();
	pSound->Stop(CSound::SOUND_LABEL_BGM_STAGE);

	CManager::Uninit();
}

void CStage::Update()
{
	//入力などの更新、各シーンのUpdateの最初に呼び出す
	CManager::Update();


	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputMouse *pInputMouse = CManager::GetInputMouse();
	if( pInputKeyboard->GetKeyTrigger(DIK_RETURN) || pInputMouse->GetMouseLeftTrigger())
	{

		//SE
		CSound *pSound = CManager::GetSound();
		pSound->Play(CSound::SOUND_LABEL_SE_CHARAMOVE);
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
		case MASU_LION:
			SetNextScene( MODE_RESULT);
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
