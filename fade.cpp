//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: fade.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/19
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "scene2D.h"
#include "fade.h"
#include "renderer.h"
#include "manager.h"

//============================================
// マクロ定義
//============================================

//============================================
// 静的メンバー変数の初期化
//============================================
LPDIRECT3DVERTEXBUFFER9 CFade::m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
int CFade::m_nAlpha = 0;
CFade::FADE CFade::m_state = CFade::FADE_NONE;


//=============================================================================
//コンストラクタ
//=============================================================================
CFade::CFade()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CFade::~CFade()
{
	
}


//=============================================================================
// ポリゴンの初期化処理
//=============================================================================

HRESULT CFade::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();


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
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f + SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f + SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f + SCREEN_WIDTH, 0.0f + SCREEN_HEIGHT, 0.0f);

	//rhw
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//color
	pVtx[0].col = D3DCOLOR_RGBA(0,0,0,0);
	pVtx[1].col = D3DCOLOR_RGBA(0,0,0,0);
	pVtx[2].col = D3DCOLOR_RGBA(0,0,0,0);
	pVtx[3].col = D3DCOLOR_RGBA(0,0,0,0);

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
void CFade::Uninit(void)
{
	// 頂点バッファの破棄
	if(m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}


//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CFade::Update(void)
{
	switch( m_state)
	{
		case FADE_OUT:
			m_nAlpha += 5;
			if(m_nAlpha >= 255)
			{
				m_nAlpha = 255;
				m_state = FADE_CHANGE;
			}
			SetAlpha(m_nAlpha);
			break;

		case FADE_CHANGE:
			CManager::NextModeChange();
			m_state = FADE_IN;
			break;

		case FADE_IN:
			m_nAlpha -= 5;
			if( m_nAlpha <= 0)
			{
				m_nAlpha = 0;
				m_state = FADE_NONE;
			}
			SetAlpha( m_nAlpha);
			break;

		case FADE_NONE:
			break;
	}
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CFade::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, NULL);

	// ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,						//ロードする最初の頂点インデックス
		NUM_POLYGON				//ポリゴンの数
	);
}

//=============================================================================
// フェードの設置
//=============================================================================
void CFade::SetFade(void)
{
	m_state = FADE_OUT;
}

//=============================================================================
// フェード中ですか
//=============================================================================
bool CFade::isFading(void)
{
	if( m_state == FADE_NONE)
	{
		return false;
	}
	return true;
}
//=============================================================================
// アルファ値を設定
//=============================================================================
void CFade::SetAlpha(int alpha)
{
	//頂点バッファの中身を埋める
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//color
	pVtx[0].col = D3DCOLOR_RGBA( 0, 0, 0, alpha);
	pVtx[1].col = D3DCOLOR_RGBA( 0, 0, 0, alpha);
	pVtx[2].col = D3DCOLOR_RGBA( 0, 0, 0, alpha);
	pVtx[3].col = D3DCOLOR_RGBA( 0, 0, 0, alpha);

	// 頂点データをアンロックする
	m_pVtxBuff->Unlock();
}
