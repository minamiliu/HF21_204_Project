/*******************************************************************************
//
// タイトル:	 未来創造展チーム204
// プログラム名: effectBG.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2017/01/15
//
********************************************************************************
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "effectBG.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"

/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define BG_TEX_NAME	"data/TEXTURE/effectBG.jpg"
#define ANIM_PAT_X (4)
#define ANIM_PAT_Y (1)
#define ANIM_CANGE_FRAME (5)
/*******************************************************************************
* クラス定義
*******************************************************************************/
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// 静的
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEffectBG::m_pTexture = NULL;
//=============================================================================
// コンストラクタ
//=============================================================================
CEffectBG :: CEffectBG() : CScene2D(LAYER_CHANGE)
{
	m_nCntFrame = 0;
	m_animPat = 0;
	
}
//=============================================================================
// デストラクタ
//=============================================================================
CEffectBG :: ~CEffectBG()
{
}
CEffectBG* CEffectBG::Create(D3DXVECTOR3 pos,D3DXVECTOR3 size)
{
	CEffectBG *pEffect;
	pEffect = new CEffectBG;
	pEffect->Init(pos,size);
	
	//テクスチャの割り当て
	pEffect->BindTexture(m_pTexture);

	return pEffect;
}
//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CEffectBG :: Init(void)
{
	CScene2D::Init();


	return S_OK;
}
//=============================================================================
// ポリゴンの初期化処理(オーバーロード)
//=============================================================================
HRESULT CEffectBG :: Init(D3DXVECTOR3 pos,D3DXVECTOR3 size)
{
	CScene2D::Init(pos,size);

	CScene2D::SetTexture(ANIM_PAT_X,ANIM_PAT_Y,m_animPat);

	return S_OK;
}
//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CEffectBG :: Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CEffectBG :: Update(void)
{
	m_nCntFrame++;
	if(m_nCntFrame >= ANIM_CANGE_FRAME)
	{
		m_animPat = (m_animPat + 1) % ANIM_PAT_X;
		CScene2D::SetTexture(ANIM_PAT_X,ANIM_PAT_Y,m_animPat);
		m_nCntFrame = 0;
	}

}
//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CEffectBG :: Draw(void)
{
	CScene2D::Draw();
}
//=============================================================================
//テクスチャのロード
//=============================================================================
HRESULT CEffectBG::Load(void)
{
	if (m_pTexture == NULL)
	{
		LPDIRECT3DDEVICE9 pDevice;
		pDevice = CManager::GetRenderer()->GetDevice();

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, BG_TEX_NAME, &m_pTexture);
	}

	return S_OK;
}

//=============================================================================
//テクスチャのアンロード
//=============================================================================
void CEffectBG::Unload(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
