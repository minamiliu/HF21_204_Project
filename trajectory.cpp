//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: trajectory.cpp
// 作成者:		 HAL東京ゲーム学科　山家啓介
// 作成日:       2016/12/08
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "manager.h"
#include "bullet2D.h"
#include "debugproc.h"
#include "trajectory.h"
//============================================
// マクロ定義
//============================================
#define TEXTURENAME "data/TEXTURE/maru.png"

//=============================================================================
// 構造体定義
//=============================================================================

//=============================================================================
//コンストラクタ
//=============================================================================
CTrajectory::CTrajectory()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CTrajectory::~CTrajectory()
{
	
}


//=============================================================================
// ポリゴンの初期化処理
//=============================================================================

HRESULT CTrajectory::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	m_nTrajectoryCnt = 0;
	return S_OK;
}




//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CTrajectory::Uninit(void)
{
	CScene2D::Uninit();
}


//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CTrajectory::Update(void)
{
	m_nTrajectoryCnt++;
	//CScene2D::SetAlpha(255 - (float)m_nTrajectoryCnt/30);
	CScene2D::Update();
	if(m_nTrajectoryCnt > 30)
	{
		this->Uninit();
		return;
	}
	
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CTrajectory::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ポリゴンの生成処理
//=============================================================================
CTrajectory *CTrajectory::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CTrajectory *pTrajectory;
	pTrajectory = new CTrajectory;
	pTrajectory->Init(pos, size);

	//テクスチャの割り当て
	pTrajectory->Load( TEXTURENAME);
	
	return pTrajectory;
}


