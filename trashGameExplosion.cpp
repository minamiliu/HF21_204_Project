//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: player2D.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/10/19
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "manager.h"
#include "trashGameExplosion.h"
#include "debugproc.h"

//============================================
// マクロ定義
//============================================

#define TEXTURE_EXPLOSION "data/TEXTURE/explosion000.png"
#define	TEX_PATTERN_DIVIDE_X		(8)												// アニメーションパターンのテクスチャ内での分割数(Ｘ方向)
#define	TEX_PATTERN_DIVIDE_Y		(1)												// アニメーションパターンのテクスチャ内での分割数(Ｙ方向)
#define	TEX_PATTERN_SIZE_X			(1.0f / TEX_PATTERN_DIVIDE_X)					// １パターンのテクスチャサイズ(Ｘ方向)(1.0f/X方向分割数)
#define	TEX_PATTERN_SIZE_Y			(1.0f / TEX_PATTERN_DIVIDE_Y)					// １パターンのテクスチャサイズ(Ｙ方向)(1.0f/Y方向分割数)
#define	NUM_ANIM_PATTERN			(TEX_PATTERN_DIVIDE_X * TEX_PATTERN_DIVIDE_Y)	// アニメーションのパターン数(X方向分割数×Y方向分割数)
#define	TIME_CHANGE_PATTERN			(10)											// アニメーションの切り替わるタイミング(フレーム数)
//============================================
//=============================================================================
// 構造体定義
//=============================================================================

//=============================================================================
//コンストラクタ
//=============================================================================
CTrashGameExplosion::CTrashGameExplosion()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CTrashGameExplosion::~CTrashGameExplosion()
{
	
}


//=============================================================================
// ポリゴンの初期化処理
//=============================================================================

HRESULT CTrashGameExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	m_nAnimCnt = 0;
	m_nPatternAnim = 0;
	ChangeTextureAnime(m_nPatternAnim, D3DXVECTOR2(TEX_PATTERN_SIZE_X,TEX_PATTERN_SIZE_Y), D3DXVECTOR2(TEX_PATTERN_DIVIDE_X,TEX_PATTERN_DIVIDE_Y));
	return S_OK;
}




//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CTrashGameExplosion::Uninit(void)
{
	CScene2D::Uninit();
}


//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CTrashGameExplosion::Update(void)
{
	CScene2D::Update();
	//爆発アニメーション
		m_nAnimCnt++;
		if((m_nAnimCnt % TIME_CHANGE_PATTERN) == 0)
		{
			if( m_nPatternAnim == ( NUM_ANIM_PATTERN -1) )
			{
				//g_explosion[nCntExplosion].bUse = false;//未使用に変更
				//CScene2D::Uninit();
				this->Uninit();
				return;
			}
			// パターンの切り替え
			m_nPatternAnim = (m_nPatternAnim + 1) % NUM_ANIM_PATTERN;
			ChangeTextureAnime(m_nPatternAnim, D3DXVECTOR2(TEX_PATTERN_SIZE_X,TEX_PATTERN_SIZE_Y),
												D3DXVECTOR2(TEX_PATTERN_DIVIDE_X,TEX_PATTERN_DIVIDE_Y));
		}
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CTrashGameExplosion::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ポリゴンの生成処理
//=============================================================================
CTrashGameExplosion *CTrashGameExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CTrashGameExplosion *pTrashBox2D;
	pTrashBox2D = new CTrashGameExplosion;
	pTrashBox2D->Init(pos, size);

	//テクスチャの割り当て
	pTrashBox2D->Load( TEXTURE_EXPLOSION);
	
	return pTrashBox2D;
}


