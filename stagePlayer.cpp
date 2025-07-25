/*******************************************************************************
* タイトル:		ゴリラ
* プログラム名:	stagePlayer.cpp
* 作成者:		小林玲雄
* 作成日:		2016/12/03
********************************************************************************
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "stagePlayer.h"
#include "manager.h"
#include "scene2D.h"
#include "stageBg.h"
#include "timeBg.h"
/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define STAGEPLAYER_TEX_NAME	"data/TEXTURE/ステージ用/母（歩き）.png"
#define ANIM_PAT_X (4)
#define ANIM_PAT_Y (1)
#define ANIM_CANGE_FRAME (20)
/*******************************************************************************
* クラス定義
*******************************************************************************/
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_VERTEX		(4)			// 頂点数
#define NUM_POLYGON		(2)			// ポリゴン数
// 頂点フォーマット( 頂点座標[2D] / 頂点カラー / テクスチャ座標 )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)


#define MOVE_TIME (60)
//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// 静的
//*****************************************************************************
D3DXVECTOR3 CStagePlayer::m_startPos = D3DXVECTOR3(0,0,0);
D3DXVECTOR3 CStagePlayer::m_nextPos = D3DXVECTOR3(0,0,0);
CStagePlayer::STAGE_PLAYER_STATE CStagePlayer::m_state = STATE_NORMAL;
CStagePlayer::STAGE_PLAYER_STATE CStagePlayer::m_oldState = STATE_NORMAL;
//=============================================================================
// コンストラクタ
//=============================================================================
CStagePlayer :: CStagePlayer()
{
	m_time = 0;
	m_animPat = 0;
	m_work = 0;
	m_animCnt = 0;
}
//=============================================================================
// デストラクタ
//=============================================================================
CStagePlayer :: ~CStagePlayer()
{
}
CStagePlayer* CStagePlayer::Create(D3DXVECTOR3 pos,D3DXVECTOR3 nextPos,D3DXVECTOR3 size)
{
	CStagePlayer *pStagePlayer;
	pStagePlayer = new CStagePlayer;
	pStagePlayer->Init(pos,size);
	
	pStagePlayer->Load(STAGEPLAYER_TEX_NAME);

	m_startPos = pos;
	m_nextPos = nextPos;
	return pStagePlayer;
}
//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CStagePlayer :: Init(void)
{
	CScene2D::Init();


	return S_OK;
}
//=============================================================================
// ポリゴンの初期化処理(オーバーロード)
//=============================================================================
HRESULT CStagePlayer :: Init(D3DXVECTOR3 pos,D3DXVECTOR3 size)
{
	CScene2D::Init(pos,size);

	CScene2D::SetTexture(ANIM_PAT_X,ANIM_PAT_Y,m_animPat);

	return S_OK;
}
//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CStagePlayer :: Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CStagePlayer :: Update(void)
{
	D3DXVECTOR3 posStagePlayer = GetPosition();
	D3DXVECTOR3 sizeStagePlayer = GetSize();
	m_time++;
	m_animCnt++;
	if((posStagePlayer == m_startPos)||(m_time > MOVE_TIME))//スタート位置にいるか、ムーブタイムがオーバーしたら
	{
		m_state = STATE_NORMAL;
	}
	if((posStagePlayer == m_startPos)&&(m_time >60))
	{
		m_state = STATE_MOVE;
	}

	if(m_state != m_oldState)//前フレームと状態が違ったら
	{
		m_time = 0;//リセット
	}

	switch(m_state)
	{
	case STATE_NORMAL:
		if(m_animCnt%ANIM_CANGE_FRAME == 0)
		{
			m_work++;
		}
		//m_animPat = m_work%3;//静止時の横のアニメーション数
		CStageBg::SetScl(false);
		CTimeBg::SetScl(false);
		break;
	case STATE_MOVE:
		if(m_time < MOVE_TIME)
		{
			posStagePlayer += ((m_nextPos - m_startPos)/MOVE_TIME);
		}
		if(m_animCnt%ANIM_CANGE_FRAME == 0)
		{
			m_work++;
		}
		//m_animPat = 9+m_work%3;//静止時の横のアニメーション数 + 移動時のアニメーション数
		CStageBg::SetScl(true);
		CTimeBg::SetScl(true);
		break;
	}
	m_animPat = m_work%4;

	CScene2D::SetTexture(ANIM_PAT_X,ANIM_PAT_Y,m_animPat);

	m_oldState = m_state;
	this->CStagePlayer::SetPosition(posStagePlayer);
}
//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CStagePlayer :: Draw(void)
{
	CScene2D::Draw();
}