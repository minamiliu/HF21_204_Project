//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: shadow.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/12/15
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "shadow.h"
#include "renderer.h"
#include "manager.h"

//============================================
// マクロ定義
//============================================
#define TEXTURENAME "data/TEXTURE/effect000.jpg"

//============================================
// 静的メンバー変数の初期化
//============================================
LPDIRECT3DTEXTURE9 CShadow::m_pTexture = NULL;

//=============================================================================
//コンストラクタ
//=============================================================================
CShadow::CShadow()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CShadow::~CShadow()
{
	
}


//=============================================================================
// ポリゴンの初期化処理
//=============================================================================

HRESULT CShadow::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	pos.y = 0.1f;
	CScene3D::Init( pos, D3DXVECTOR3(0,0,0), 1, 1, size.x, size.y, false);
	return S_OK;
}
//=============================================================================
//
//=============================================================================
void CShadow::Uninit(void)
{
	CScene3D::Uninit();
}
//=============================================================================
//
//=============================================================================
void CShadow::Update(void)
{
	
}
//=============================================================================
//
//=============================================================================
void CShadow::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 減算合成
	pDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);// 結果 = 転送先(DEST) - 転送元(SRC)
	pDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene3D::Draw();

	// 通常ブレンド 
	pDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD);		// 結果 = 転送元(SRC) + 転送先(DEST)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//=============================================================================
//
//=============================================================================
CShadow *CShadow::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	CShadow *pShadow;
	pShadow = new CShadow;

	pShadow->Init(pos, size);

	//テクスチャの割り当て
	pShadow->BindTexture( m_pTexture);

	return pShadow;
}

//=============================================================================
// 座標の設定
//=============================================================================
void CShadow::SetPosition(D3DXVECTOR3 pos)
{
	pos.y = 0.1f;
	CScene3D::SetPosition( pos);
}

//=============================================================================
//テクスチャのロード
//=============================================================================
HRESULT CShadow::Load(void)
{
	if( m_pTexture == NULL)
	{
		LPDIRECT3DDEVICE9 pDevice;
		pDevice = CManager::GetRenderer()->GetDevice();

		// テクスチャの読み込み
		D3DXCreateTextureFromFile( pDevice, TEXTURENAME, &m_pTexture);
	}

	return S_OK;
}

//=============================================================================
//テクスチャのアンロード
//=============================================================================
void CShadow::Unload(void)
{
	//テクスチャの破棄
	if( m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}


