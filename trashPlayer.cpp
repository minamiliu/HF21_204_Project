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
#include "renderer.h"
#include "input.h"
#include "trashplayer.h"
#include "debugproc.h"

//============================================
// マクロ定義
//============================================

#define TEXTURE_PLAYER "data/TEXTURE/throwingMother.png"
#define	TEX_PATTERN_DIVIDE_X		(5)												// アニメーションパターンのテクスチャ内での分割数(Ｘ方向)
#define	TEX_PATTERN_DIVIDE_Y		(1)												// アニメーションパターンのテクスチャ内での分割数(Ｙ方向)
#define	TEX_PATTERN_SIZE_X			(1.0f / TEX_PATTERN_DIVIDE_X)					// １パターンのテクスチャサイズ(Ｘ方向)(1.0f/X方向分割数)
#define	TEX_PATTERN_SIZE_Y			(1.0f / TEX_PATTERN_DIVIDE_Y)					// １パターンのテクスチャサイズ(Ｙ方向)(1.0f/Y方向分割数)
#define	NUM_ANIM_PATTERN			(TEX_PATTERN_DIVIDE_X * TEX_PATTERN_DIVIDE_Y)	// アニメーションのパターン数(X方向分割数×Y方向分割数)
#define	TIME_CHANGE_PATTERN			(5)											// アニメーションの切り替わるタイミング(フレーム数)

#define TEXTURE_GORILLA "data/TEXTURE/throwingGorilla.png"
//============================================

LPDIRECT3DTEXTURE9 CTrashPlayer::m_pTexture[2] = {NULL,NULL};

//=============================================================================
// 構造体定義
//=============================================================================

//=============================================================================
//コンストラクタ
//=============================================================================
CTrashPlayer::CTrashPlayer()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CTrashPlayer::~CTrashPlayer()
{
	
}


//=============================================================================
// ポリゴンの初期化処理
//=============================================================================

HRESULT CTrashPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	m_nAnimCnt = 0;
	m_nPatternAnim = 0;
	m_bGorillaMode = false;;
	ChangeTextureAnime(m_nPatternAnim, D3DXVECTOR2(TEX_PATTERN_SIZE_X,TEX_PATTERN_SIZE_Y), D3DXVECTOR2(TEX_PATTERN_DIVIDE_X,TEX_PATTERN_DIVIDE_Y));
	return S_OK;
}




//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CTrashPlayer::Uninit(void)
{
	CScene2D::Uninit();
}


//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CTrashPlayer::Update(void)
{
	CScene2D::Update();
	if(CManager::GetInputMouse()->GetMouseLeftPress() || m_nPatternAnim >= 3)
	{
		//アニメーション
		m_nAnimCnt++;
		if((m_nAnimCnt % TIME_CHANGE_PATTERN) == 0)
		{
			//アニメーションを途中で止める
			if( m_nPatternAnim == (3 -1) )
			{
				return;
			}
			// パターンの切り替え
			m_nPatternAnim = (m_nPatternAnim + 1) % NUM_ANIM_PATTERN;
			ChangeTextureAnime(m_nPatternAnim, D3DXVECTOR2(TEX_PATTERN_SIZE_X,TEX_PATTERN_SIZE_Y), D3DXVECTOR2(TEX_PATTERN_DIVIDE_X,TEX_PATTERN_DIVIDE_Y));
		}
	}

	//マウスを話したらアニメーションを更新
	if(CManager::GetInputMouse()->GetMouseLeftRelease())
	{
		m_nPatternAnim = 3;
	}
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CTrashPlayer::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ポリゴンの生成処理
//=============================================================================
CTrashPlayer *CTrashPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,LPCSTR strFileName)
{
	CTrashPlayer *pTrashBox2D;
	pTrashBox2D = new CTrashPlayer;
	pTrashBox2D->Init(pos, size);

	//テクスチャの割り当て
	//pTrashBox2D->Load( TEXTURE_PLAYER);
	if(strFileName == TEXTURE_PLAYER)
	{
		pTrashBox2D->BindTexture(m_pTexture[0]);
	}
	else if(strFileName == TEXTURE_GORILLA)
	{
		pTrashBox2D->BindTexture(m_pTexture[1]);
	}

	return pTrashBox2D;
}

bool CTrashPlayer::GetGorillaMode(void)
{
	return m_bGorillaMode;
}

void CTrashPlayer::SetGorillaMode(void)
{
	m_bGorillaMode = true;
}

void CTrashPlayer::Load(void)
{
	if(m_pTexture[0] == NULL)
	{
		LPDIRECT3DDEVICE9 pDevice;
		pDevice = CManager::GetRenderer()->GetDevice();

		// テクスチャの読み込み
		D3DXCreateTextureFromFile( pDevice,TEXTURE_PLAYER, &m_pTexture[0]);
	}

	if(m_pTexture[1] == NULL)
	{
		LPDIRECT3DDEVICE9 pDevice;
		pDevice = CManager::GetRenderer()->GetDevice();

		// テクスチャの読み込み
		D3DXCreateTextureFromFile( pDevice,TEXTURE_GORILLA, &m_pTexture[1]);
	}
}