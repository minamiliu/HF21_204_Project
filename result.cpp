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
#include "score.h"

//============================================
// マクロ定義
//============================================
#define TEXTURE_BG "data/TEXTURE/resultBG.jpg"
#define TEXTURE_RANK_C "data/TEXTURE/rankC.png"
#define TEXTURE_RANK_A "data/TEXTURE/rankA.png"
#define TEXTURE_RANK_B "data/TEXTURE/rankB.png"
#define TEXTURE_RANK_S "data/TEXTURE/rankSサイズ調整.png"
#define TRASHGAME_SCORE_RANK_S (1500)
#define TRASHGAME_SCORE_RANK_A (1000)
#define TRASHGAME_SCORE_RANK_B (500)
#define TRASHGAME_SCORE_RANK_C (0)
#define ZEBRAGAME_SCORE_RANK_S (1500)
#define ZEBRAGAME_SCORE_RANK_A (1000)
#define ZEBRAGAME_SCORE_RANK_B (500)
#define ZEBRAGAME_SCORE_RANK_C (0)
#define LIONGAME_SCORE_RANK_S (1500)
#define LIONGAME_SCORE_RANK_A (1000)
#define LIONGAME_SCORE_RANK_B (500)
#define LIONGAME_SCORE_RANK_C (0)

//============================================
// 静的メンバー変数の初期化
//============================================
CScore *CResult::m_pTrashGameScore = NULL;
CScore *CResult::m_pZebraGameScore = NULL;
CScore *CResult::m_pLionGameScore = NULL;
//ランクのテクスチャのポインタを入れる変数
CScene2D *CResult::m_pRank[3];
//============================================
//コンストラクタ
//============================================
CResult::CResult() : CManager(MODE_RESULT)
{
	m_resultCnt = 0;
	m_pTrashGameScore = NULL;
	m_pZebraGameScore = NULL;
	m_pLionGameScore = NULL;
	m_pRank[0] = NULL;
	m_pRank[1] = NULL;
	m_pRank[2] = NULL;
	m_nTrashGameScore = 300;
	m_nZebraGameScore = 500;
	m_nLionGameScore = 100;
}

CResult::~CResult()
{
	
}

HRESULT CResult::Init(void)
{


	//オブジェクトの生成(2Dポリゴン)
	CScene2D::Create( D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), TEXTURE_BG);

	
	m_pTrashGameScore = NULL;
	m_pZebraGameScore = NULL;
	m_pLionGameScore = NULL;
	m_pRank[0] = NULL;
	m_pRank[1] = NULL;
	m_pRank[2] = NULL;
	m_resultCnt = 0;
	//スコア取得
	m_nTrashGameScore = CManager::LoadScore(MODE_TRASHGAME);
	m_nZebraGameScore = 2000;
	m_nLionGameScore = 2000;
	//目標値
	m_nTargetScore[0] = m_nTrashGameScore;
	m_nTargetScore[1] = m_nZebraGameScore;
	m_nTargetScore[2] = m_nLionGameScore;

	return S_OK;
}

void CResult::Uninit()
{
	CManager::Uninit();
}

void CResult::Update()
{
	//入力などの更新、各シーンのUpdateの最初に呼び出す
	CManager::Update();
	//時間経過を表すためのカウント
	m_resultCnt++;
	//スコア加算に６０F、ランク表示に４０F使う
	if(m_resultCnt == 30)
	{
		//スコア生成
		m_pTrashGameScore = CScore::Create(D3DXVECTOR3(640, 160.0f, 0.0f), D3DXVECTOR3(600.0f, 100.0f, 0.0f), 6, YELLOW(1.0f));
	}
	else if(m_resultCnt == 30 + 60 + 1 + 40)
	{
		m_pZebraGameScore = CScore::Create(D3DXVECTOR3(640, 360.0f, 0.0f), D3DXVECTOR3(600.0f, 100.0f, 0.0f), 6, RED(1.0f));
	}
	else if(m_resultCnt == 150 + 40 + 1 + 40)
	{
		m_pLionGameScore = CScore::Create(D3DXVECTOR3(640, 560.0f, 0.0f), D3DXVECTOR3(600.0f, 100.0f, 0.0f), 6, BLUE(1.0f));
	}

	//数値加算(一番上)
	if(m_pTrashGameScore != NULL && m_nTrashGameScore != 0)
	{
		if( m_nTrashGameScore > 0 )
		{
			//60Fで目標値に到達するようにスコア加算
			m_pTrashGameScore->AddScore(m_nTargetScore[0]/60);
			m_nTrashGameScore-=m_nTargetScore[0]/60;
		}
		else if(m_nTrashGameScore < 0 && m_nTrashGameScore > -10000)
		{
			//スコア調整
			m_pTrashGameScore->SetScore(m_nTargetScore[0]);
			m_nTrashGameScore = 0;
		}
	}
	else if(m_pTrashGameScore != NULL && m_nTrashGameScore == 0)
	{
		//ランク表示
		if(m_nTargetScore[0] >= TRASHGAME_SCORE_RANK_S)
		{//ランクS
			m_pRank[0] = CScene2D::Create(D3DXVECTOR3(1100, 160.0f, 0.0f),D3DXVECTOR3(270.0f, 270.0f, 0.0f),TEXTURE_RANK_S);
			m_pRank[0]->SetColor(YELLOW(1.0f));
		}
		else if(m_nTargetScore[0] >= TRASHGAME_SCORE_RANK_A && m_nTargetScore[0] < TRASHGAME_SCORE_RANK_S)
		{//ランクA
			m_pRank[0] = CScene2D::Create(D3DXVECTOR3(1100, 160.0f, 0.0f),D3DXVECTOR3(380.0f, 380.0f, 0.0f),TEXTURE_RANK_A);
		}
		else if(m_nTargetScore[0] >= TRASHGAME_SCORE_RANK_B && m_nTargetScore[0] < TRASHGAME_SCORE_RANK_A)
		{//ランクB
			m_pRank[0] = CScene2D::Create(D3DXVECTOR3(1100, 160.0f, 0.0f),D3DXVECTOR3(380.0f, 380.0f, 0.0f),TEXTURE_RANK_B);
		}
		else if(m_nTargetScore[0] >= TRASHGAME_SCORE_RANK_C && m_nTargetScore[0] < TRASHGAME_SCORE_RANK_B)
		{//ランクC
			m_pRank[0] = CScene2D::Create(D3DXVECTOR3(1100, 180.0f, 0.0f),D3DXVECTOR3(380.0f, 380.0f, 0.0f),TEXTURE_RANK_C);
		}
		

		m_nTrashGameScore -= 100000;
	}
	//スコア加算（2つ目）
	if(m_pZebraGameScore != NULL && m_nZebraGameScore != 0)
	{
		if( m_nZebraGameScore > 0 )
		{
			//60Fで目標値に到達するようにスコア加算
			m_pZebraGameScore->AddScore(m_nTargetScore[1]/60);
			m_nZebraGameScore-=m_nTargetScore[1]/60;
		}
		else if(m_nZebraGameScore < 0 && m_nZebraGameScore > -10000)
		{//スコア調整
			m_pZebraGameScore->SetScore(m_nTargetScore[1]);
			m_nZebraGameScore = 0;
		}
	}
	else if(m_pZebraGameScore != NULL && m_nZebraGameScore == 0)
	{
		//ランク表示
		if(m_nTargetScore[1] >= ZEBRAGAME_SCORE_RANK_S)
		{//ランクS
			m_pRank[1] = CScene2D::Create(D3DXVECTOR3(1100, 360.0f, 0.0f),D3DXVECTOR3(270.0f, 270.0f, 0.0f),TEXTURE_RANK_S);
			m_pRank[1]->SetColor(YELLOW(1.0f));
		}
		else if(m_nTargetScore[1] >= ZEBRAGAME_SCORE_RANK_A && m_nTargetScore[1] < ZEBRAGAME_SCORE_RANK_S)
		{//ランクA
			m_pRank[1] = CScene2D::Create(D3DXVECTOR3(1100, 380.0f, 0.0f),D3DXVECTOR3(380.0f, 380.0f, 0.0f),TEXTURE_RANK_A);
		}
		else if(m_nTargetScore[1] >= ZEBRAGAME_SCORE_RANK_B && m_nTargetScore[1] < ZEBRAGAME_SCORE_RANK_A)
		{//ランクB
			m_pRank[1] = CScene2D::Create(D3DXVECTOR3(1100, 380.0f, 0.0f),D3DXVECTOR3(380.0f, 380.0f, 0.0f),TEXTURE_RANK_B);
		}
		else if(m_nTargetScore[1] >= ZEBRAGAME_SCORE_RANK_C && m_nTargetScore[1] < ZEBRAGAME_SCORE_RANK_B)
		{//ランクC
			m_pRank[1] = CScene2D::Create(D3DXVECTOR3(1100, 380.0f, 0.0f),D3DXVECTOR3(380.0f, 380.0f, 0.0f),TEXTURE_RANK_C);
		}
		m_nZebraGameScore -= 100000;
	}
	//スコア加算（3つ目）
	if(m_pLionGameScore != NULL && m_nLionGameScore != 0)
	{
		if( m_nLionGameScore > 0 )
		{
			m_pLionGameScore->AddScore(m_nTargetScore[2]/60);
			m_nLionGameScore-=m_nTargetScore[2]/60;
		}
		else if(m_nLionGameScore < 0 && m_nLionGameScore > -10000)
		{//スコア調整
			m_pLionGameScore->SetScore(m_nTargetScore[2]);
			m_nLionGameScore = 0;
		}
	}
	else if(m_pLionGameScore != NULL && m_nLionGameScore == 0)
	{
		//ランク表示
		if(m_nTargetScore[2] >= LIONGAME_SCORE_RANK_S)
		{//ランクS
			m_pRank[2] = CScene2D::Create(D3DXVECTOR3(1100, 560.0f, 0.0f),D3DXVECTOR3(270.0f, 270.0f, 0.0f),TEXTURE_RANK_S);
			m_pRank[2]->SetColor(YELLOW(1.0f));
		}
		else if(m_nTargetScore[2] >= ZEBRAGAME_SCORE_RANK_A && m_nTargetScore[2] < LIONGAME_SCORE_RANK_S)
		{//ランクA
			m_pRank[2] = CScene2D::Create(D3DXVECTOR3(1100, 580.0f, 0.0f),D3DXVECTOR3(380.0f, 380.0f, 0.0f),TEXTURE_RANK_A);
		}
		else if(m_nTargetScore[2] >= ZEBRAGAME_SCORE_RANK_B && m_nTargetScore[2] < LIONGAME_SCORE_RANK_A)
		{//ランクB
			m_pRank[2] = CScene2D::Create(D3DXVECTOR3(1100, 580.0f, 0.0f),D3DXVECTOR3(380.0f, 380.0f, 0.0f),TEXTURE_RANK_B);
		}
		else if(m_nTargetScore[2] >= ZEBRAGAME_SCORE_RANK_C && m_nTargetScore[2] < LIONGAME_SCORE_RANK_B)
		{//ランクC
			m_pRank[2] = CScene2D::Create(D3DXVECTOR3(1100, 580.0f, 0.0f),D3DXVECTOR3(380.0f, 380.0f, 0.0f),TEXTURE_RANK_C);
		}
		m_nLionGameScore -= 100000;
	}
	//ランク表示（サイズ変更）
	if(m_pRank[0] != NULL )
	{
		if(m_nTargetScore[0] >= TRASHGAME_SCORE_RANK_S && m_pRank[0]->GetSize().x > 150)
		{
			m_pRank[0]->SetSize(D3DXVECTOR3(m_pRank[0]->GetSize().x-3,m_pRank[0]->GetSize().y-3,0.0));
		}
		else if (m_pRank[0]->GetSize().x > 300)
		{
			m_pRank[0]->SetSize(D3DXVECTOR3(m_pRank[0]->GetSize().x-2,m_pRank[0]->GetSize().y-2,0.0));
		}
	}
	
	if(m_pRank[1] != NULL)
	{
		if(m_nTargetScore[1] >= ZEBRAGAME_SCORE_RANK_S && m_pRank[1]->GetSize().x > 150)
		{
			m_pRank[1]->SetSize(D3DXVECTOR3(m_pRank[1]->GetSize().x-3,m_pRank[1]->GetSize().y-3,0.0));
		}
		else if(m_pRank[1]->GetSize().x > 300)
		{
			m_pRank[1]->SetSize(D3DXVECTOR3(m_pRank[1]->GetSize().x-2,m_pRank[1]->GetSize().y-2,0.0));
		}
	}
	
	if(m_pRank[2] != NULL )
	{
		if(m_nTargetScore[2] >= ZEBRAGAME_SCORE_RANK_S && m_pRank[2]->GetSize().x > 150)
		{
			m_pRank[2]->SetSize(D3DXVECTOR3(m_pRank[2]->GetSize().x-3,m_pRank[2]->GetSize().y-3,0.0));
		}
		else if(m_pRank[2]->GetSize().x > 300)
		{
			m_pRank[2]->SetSize(D3DXVECTOR3(m_pRank[2]->GetSize().x-2,m_pRank[2]->GetSize().y-2,0.0));
		}
	}
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

#ifdef _DEBUG
	if( pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		SetNextScene( MODE_TITLE);
	}
#endif

	//シーンが切り替えるところ、各シーンのUpdateの最後に置いとく
	CManager::SceneChange();
}
void CResult::Draw()
{
	CManager::Draw();
}
