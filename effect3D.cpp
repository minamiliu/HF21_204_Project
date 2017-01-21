//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: effect3D.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2017/01/19
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "effect3D.h"
#include "scene.h"

//============================================
// マクロ定義
//============================================
#define TEXTURE_TOMATO	"data/TEXTURE/effect000.jpg"

//============================================
// 静的メンバー変数の初期化
//============================================
LPDIRECT3DTEXTURE9 CEffect3D::m_pTexture[TYPE_MAX] = {};
//int CEffect3D::m_nColorID = 0;
//D3DXCOLOR CEffect3D::m_paraColor[] =
//{
//	RED(1.0f),
//	ORANGE(1.0f),
//	YELLOW(1.0f),
//	GREEN(1.0f),
//	SYAN(1.0f),	
//	BLUE(1.0f),	
//	MASENTA(1.0f),
//};

//=============================================================================
//コンストラクタ
//=============================================================================
CEffect3D::CEffect3D() : CBillBoard( LAYER_EFFECT)
{
}

//=============================================================================
//デストラクタ
//=============================================================================
CEffect3D::~CEffect3D()
{
	
}


//=============================================================================
// ポリゴンの初期化処理
//=============================================================================

HRESULT CEffect3D::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size, TYPE type, const D3DXCOLOR &col, float fPercent)
{
	CBillBoard::Init( pos, size);

	//初期状態
	m_type = type;
	m_fPercent = fPercent;
	m_col = col;

	//m_col = m_paraColor[m_nColorID];
	//this->SetColor(m_col);
	//m_nColorID = (m_nColorID + 1) % 7;

	return S_OK;
}
//=============================================================================
//
//=============================================================================
void CEffect3D::Uninit(void)
{
	CBillBoard::Uninit();
}
//=============================================================================
//
//=============================================================================
void CEffect3D::Update(void)
{
	m_col.a -= m_fPercent;
	this->SetColor(m_col);
	if( m_col.a <= 0)
	{
		this->Uninit();
		return;
	}
}
//=============================================================================
//
//=============================================================================
void CEffect3D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 加算合成
	pDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD);	// 結果 = 転送元(SRC) + 転送先(DEST)
	pDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE);

	// Z比較なし
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	// ライティングモードをOFF
	pDevice->SetRenderState( D3DRS_LIGHTING, FALSE);

	//αテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//描画
	CBillBoard::Draw();

	// ライティングモードをON
	pDevice->SetRenderState( D3DRS_LIGHTING, TRUE);

	// αテストを無効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// 通常ブレンド 
	pDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD);	// 結果 = 転送元(SRC) + 転送先(DEST)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// Z比較あり
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
}
//=============================================================================
//
//=============================================================================
CEffect3D *CEffect3D::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, TYPE type, const D3DXCOLOR &col, float fPercent)
{
	CEffect3D *pEffect;
	pEffect = new CEffect3D;

	pEffect->Init(pos, size, type, col, fPercent);

	//テクスチャの割り当て
	pEffect->BindTexture( m_pTexture[type]);

	return pEffect;
}
//=============================================================================
//テクスチャのロード
//=============================================================================
HRESULT CEffect3D::Load(void)
{
	for (int cntType = 0; cntType < TYPE_MAX; cntType++)
	{
		LPCSTR strFileName;
		switch (cntType)
		{
		case TYPE_MARU:
			strFileName = TEXTURE_TOMATO;
			break;
		}

		if (m_pTexture[cntType] == NULL)
		{
			LPDIRECT3DDEVICE9 pDevice;
			pDevice = CManager::GetRenderer()->GetDevice();

			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice, strFileName, &m_pTexture[cntType]);
		}
	}

	return S_OK;
}

//=============================================================================
//テクスチャのアンロード
//=============================================================================
void CEffect3D::Unload(void)
{
	//テクスチャの破棄
	for (int cntType = 0; cntType < TYPE_MAX; cntType++)
	{
		if (m_pTexture[cntType] != NULL)
		{
			m_pTexture[cntType]->Release();
			m_pTexture[cntType] = NULL;
		}
	}
}
