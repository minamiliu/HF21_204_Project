//============================================
//
// タイトル:	 CL25課題
// プログラム名: texture.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/10/19
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "texture.h"
#include "renderer.h"


//============================================
// マクロ定義
//============================================

// 頂点フォーマット( 頂点座標[2D] / 頂点カラー / テクスチャ座標 )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#define NUM_VERTEX (4)
#define NUM_POLYGON (2)
#define POLYGON_POS_X	(SCREEN_WIDTH/2)//ポリゴンの左上X
#define POLYGON_POS_Y	(SCREEN_HEIGHT/2)//ポリゴンの左上Y
#define POLYGON_SIZE_X	(300)//ポリゴンのSIZE X
#define POLYGON_SIZE_Y	(300)//ポリゴンのSIZE Y
#define POLYGON_TEXTURENAME "data/TEXTURE/player000.png"

//============================================
// 構造体定義
//============================================
// 上記頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	float rhw;			// 座標変換用係数(1.0fで固定)
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
} VERTEX_2D;

//============================================
//コンストラクタ
//============================================
CTexture::CTexture()
{
	m_pTexture = NULL;		// テクスチャへのポインタ
	m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	m_pos = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);			// ポリゴンの位置
}

CTexture::~CTexture()
{
	
}


//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CTexture::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;	
	pDevice = GetRenderer()->GetDevice();

	// ポリゴンの位置を設定
	m_pos = D3DXVECTOR3( POLYGON_POS_X, POLYGON_POS_Y, 0.0f);

	// テクスチャの生成
	D3DXCreateTextureFromFile( pDevice, POLYGON_TEXTURENAME, &m_pTexture);

	// 頂点バッファの生成
	if(FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX,	//頂点データのバッファサイズ 
		D3DUSAGE_WRITEONLY, 
		FVF_VERTEX_2D,			//頂点フォーマット
		D3DPOOL_MANAGED, 
		&m_pVtxBuff,		//頂点バッファインターフェースのポインタ
		NULL)))
	{
		return E_FAIL;
	}

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock( 0, 0, (void**)&pVtx, 0);

	// ポリゴンの位置を設定
	pVtx[0].pos = D3DXVECTOR3(POLYGON_POS_X - (POLYGON_SIZE_X/2), POLYGON_POS_Y - (POLYGON_SIZE_Y/2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(POLYGON_POS_X + (POLYGON_SIZE_X/2), POLYGON_POS_Y - (POLYGON_SIZE_Y/2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(POLYGON_POS_X - (POLYGON_SIZE_X/2), POLYGON_POS_Y + (POLYGON_SIZE_Y/2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(POLYGON_POS_X + (POLYGON_SIZE_X/2), POLYGON_POS_Y + (POLYGON_SIZE_Y/2), 0.0f);

	//rhw
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//color
	pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);

	//テクスチャ座標指定
	pVtx[0].tex = D3DXVECTOR2(0.0F, 0.0F);
	pVtx[1].tex = D3DXVECTOR2(1.0F, 0.0F);
	pVtx[2].tex = D3DXVECTOR2(0.0F, 1.0F);
	pVtx[3].tex = D3DXVECTOR2(1.0F, 1.0F);

	m_pVtxBuff->Unlock();

	return S_OK;
}



//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CTexture::Uninit(void)
{
	// 頂点バッファの破棄
	if(m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// テクスチャの破棄
	if(m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}


//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CTexture::Update(void)
{
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CTexture::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,						//ロードする最初の頂点インデックス
		NUM_POLYGON				//ポリゴンの数
	);
}