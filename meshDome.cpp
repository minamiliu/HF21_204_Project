//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: meshDome.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2017/01/12
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "meshDome.h"
#include "scene3D.h"
#include "renderer.h"
#include "manager.h"

//============================================
// マクロ定義
//============================================
#define	TEXTURE_MESHDOME	"data/TEXTURE/pattern02.jpg"	// 読み込むテクスチャファイル名
#define	VALUE_MOVE_DOME		(4.0f)						// 移動速度
#define	VALUE_ROTATE_DOME	(D3DX_PI * 0.01f)			// 回転速度

#define	DOME_HEIGHT_RATE	(1.0f)		// 空ドームの高さ係数
#define	TEX_COUNT_LOOP		(8)			// テクスチャの繰り返し回数

//============================================
// 静的メンバー変数の初期化
//============================================
LPDIRECT3DTEXTURE9 CMeshDome::m_pTexture = NULL;	// テクスチャへのポインタ

//=============================================================================
//コンストラクタ
//=============================================================================
CMeshDome::CMeshDome()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CMeshDome::~CMeshDome()
{
	
}


//=============================================================================
// メシュポリゴンの初期化処理
//=============================================================================
HRESULT CMeshDome::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, int nNumBlockH, int nNumBlockV)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 位置・向き・半径（グローバル変数）の初期設定
	m_pos = pos;
	m_rot = rot;
	m_fRadius = fRadius;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile( pDevice, TEXTURE_MESHDOME, &m_pTexture);

	// ブロック数H/V（グローバル変数）の設定
	m_nNumBlockH = nNumBlockH;
	m_nNumBlockV = nNumBlockV;

	// 頂点数（グローバル変数）の設定
	m_nNumVertex = (m_nNumBlockH + 1) * (m_nNumBlockV + 1);

	// ポリゴン数（グローバル変数）の設定
	m_nNumPolygon = ( m_nNumBlockH * (m_nNumBlockV * 2) + (m_nNumBlockV - 1) * 4);

	// インデックス数（グローバル変数）の設定
	m_nNumVertexIndex = (m_nNumBlockH * (m_nNumBlockV * 2) + m_nNumBlockV * 2 + (m_nNumBlockV - 1) * 2);

	// オブジェクトの頂点バッファを生成
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumVertex,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,							// 頂点バッファの使用法　
												FVF_VERTEX_3D,								// 使用する頂点フォーマット
												D3DPOOL_MANAGED,							// リソースのバッファを保持するメモリクラスを指定
												&m_pVtxBuff,					// 頂点バッファインターフェースへのポインタ
												NULL)))										// NULLに設定
	{
        return E_FAIL;
	}

	// オブジェクトの頂点バッファを生成
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (m_nNumBlockH + 1),		// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,						// 頂点バッファの使用法　
												FVF_VERTEX_3D,							// 使用する頂点フォーマット
												D3DPOOL_MANAGED,						// リソースのバッファを保持するメモリクラスを指定
												&m_pVtxBuffTop,						// 頂点バッファインターフェースへのポインタ
												NULL)))									// NULLに設定
	{
        return E_FAIL;
	}

	// オブジェクトのインデックスバッファを生成
	if(FAILED(pDevice->CreateIndexBuffer(sizeof(WORD) * m_nNumVertexIndex,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,					// 頂点バッファの使用法　
												D3DFMT_INDEX16,						// 使用するインデックスフォーマット
												D3DPOOL_MANAGED,					// リソースのバッファを保持するメモリクラスを指定
												&m_pIdxBuff,					// インデックスバッファインターフェースへのポインタ
												NULL)))								// NULLに設定
	{
        return E_FAIL;
	}

	// オブジェクトのインデックスバッファを生成
	if(FAILED(pDevice->CreateIndexBuffer(sizeof(WORD) * (m_nNumBlockH + 2),			// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,					// 頂点バッファの使用法　
												D3DFMT_INDEX16,						// 使用するインデックスフォーマット
												D3DPOOL_MANAGED,					// リソースのバッファを保持するメモリクラスを指定
												&m_pIdxBuffTop,					// インデックスバッファインターフェースへのポインタ
												NULL)))								// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;
		const float angleH = (D3DX_PI * 2.0f) / m_nNumBlockH;
		const float angleV = (D3DX_PI / 2.0f) / (m_nNumBlockV + 1);
		const float width = 1.0f / m_nNumBlockH;
		const float height = 1.0f / m_nNumBlockV;
		float lengthXZ;
		D3DXVECTOR3 nor;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_pVtxBuff->Lock( 0, 0, (void**)&pVtx, 0);
		for(int nCntV = 0; nCntV < (m_nNumBlockV + 1); nCntV++)
		{
			lengthXZ = cosf(angleV * nCntV) * m_fRadius;

			for(int nCntH = 0; nCntH < (m_nNumBlockH + 1); nCntH++, pVtx++)
			{
				// 頂点座標の設定
				pVtx->vtx.x = sinf(angleH * nCntH) * lengthXZ;
				pVtx->vtx.y = sinf(angleV * nCntV) * m_fRadius * DOME_HEIGHT_RATE;
				pVtx->vtx.z = -cosf(angleH * nCntH) * lengthXZ;

				// 法線の設定
				nor = pVtx->vtx;
				D3DXVec3Normalize(&nor, &nor);
				pVtx->nor = nor;

				// 頂点カラーの設定
				pVtx->col = D3DCOLOR_RGBA(255,255,255,255);

				// テクスチャ座標の設定
				pVtx->tex.x = nCntH * width * TEX_COUNT_LOOP;

				if(nCntV == m_nNumBlockV)
				{
					pVtx->tex.y = 0.01f;
				}
				else
				{
					pVtx->tex.y = 1.0f - nCntV * height;
				}
			}
		}
		// 頂点データをアンロックする
		m_pVtxBuff->Unlock();

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_pVtxBuffTop->Lock( 0, 0, (void**)&pVtx, 0);
		// 頂点座標の設定
		pVtx->vtx.x = 0.0f;
		pVtx->vtx.y = sinf(angleV * (m_nNumBlockV + 1)) * m_fRadius * DOME_HEIGHT_RATE;
		pVtx->vtx.z = 0.0f;

		// 法線の設定
		nor = pVtx->vtx;
		D3DXVec3Normalize(&nor, &nor);
		pVtx->nor = nor;

		// 頂点カラーの設定
		pVtx->col = D3DCOLOR_RGBA(255,255,255,255);

		// テクスチャ座標の設定
		pVtx->tex.x = 0.5f;
		pVtx->tex.y = 0.0f;

		// 頂点バッファのポインタをインクリメント
		pVtx++;

		lengthXZ = cosf(angleV * m_nNumBlockV) * m_fRadius;
		for(int nCntH = 0; nCntH < m_nNumBlockH; nCntH++, pVtx++)
		{
			// 頂点座標の設定
			pVtx->vtx.x = -sinf(angleH * nCntH) * lengthXZ;
			pVtx->vtx.y = sinf(angleV * m_nNumBlockV) * m_fRadius * DOME_HEIGHT_RATE;
			pVtx->vtx.z = -cosf(angleH * nCntH) * lengthXZ;

			// 法線の設定
			nor = pVtx->vtx;
			D3DXVec3Normalize(&nor, &nor);
			pVtx->nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 頂点カラーの設定
			pVtx->col = D3DCOLOR_RGBA(255,255,255,255);

			// テクスチャ座標の設定
			pVtx->tex.x = 0.5f;
			pVtx->tex.y = 1.0f;
		}

		// 頂点データをアンロックする
		m_pVtxBuffTop->Unlock();
	}

	{//インデックスバッファの中身を埋める
		WORD *pIdx;

		// インデックスデータの範囲をロックし、頂点バッファへのポインタを取得
		m_pIdxBuff->Lock( 0, 0, (void**)&pIdx, 0);
		for(int nCntV = 0; nCntV < m_nNumBlockV; nCntV++)
		{
			if(nCntV != 0)
			{
				*pIdx = nCntV * (m_nNumBlockH + 1);
				pIdx++;
			}

			for(int nCntH = 0; nCntH < m_nNumBlockH + 1; nCntH++)
			{
				*pIdx = nCntV * (m_nNumBlockH + 1) + nCntH;
				pIdx++;

				*pIdx = (nCntV + 1) * (m_nNumBlockH + 1) + nCntH;
				pIdx++;
			}

			if(nCntV != (m_nNumBlockV - 1))
			{
				*pIdx = (nCntV + 1) * (m_nNumBlockH + 1);
				pIdx++;
			}
		}

		// インデックスデータをアンロックする
		m_pIdxBuff->Unlock();

		// インデックスデータの範囲をロックし、頂点バッファへのポインタを取得
		m_pIdxBuffTop->Lock( 0, 0, (void**)&pIdx, 0);
		for(int nCntH = 0; nCntH < m_nNumBlockH + 1; nCntH++, pIdx++)
		{
			*pIdx = nCntH;
		}
		*pIdx = 1;

		// インデックスデータをアンロックする
		m_pIdxBuffTop->Unlock();
	}

	return S_OK;
}
//=============================================================================
// メシュポリゴンの終了処理
//=============================================================================
void CMeshDome::Uninit(void)
{
	if(m_pVtxBuff != NULL)
	{// 頂点バッファの開放
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	if(m_pIdxBuff != NULL)
	{// インデックスバッファの開放
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	if(m_pVtxBuffTop != NULL)
	{// 頂点バッファの開放
		m_pVtxBuffTop->Release();
		m_pVtxBuffTop = NULL;
	}

	if(m_pIdxBuffTop != NULL)
	{// インデックスバッファの開放
		m_pIdxBuffTop->Release();
		m_pIdxBuffTop = NULL;
	}

	if(m_pTexture != NULL && m_bLoadTexture == true)
	{// テクスチャの開放
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	//オブジェクトの破棄
	Release();
}
//=============================================================================
// メシュポリゴンの更新処理
//=============================================================================
void CMeshDome::Update(void)
{

}
//=============================================================================
// メシュポリゴンの描画処理
//=============================================================================
void CMeshDome::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTranslate;

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);	// 裏面をカリング

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity( &m_mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll( &mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation( &mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform( D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをレンダリングパイプラインに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// インデックスバッファをレンダリングパイプラインに設定
	pDevice->SetIndices(m_pIdxBuff);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,			//プリミティブの種類
		0,								//最初の頂点インデックスまでのオフセット
		0,								//最小の頂点インデックス
		m_nNumVertex,		//頂点の数
		0,								//読み取りを開始する位置
		m_nNumPolygon		//ポリゴンの数
	);

	// 頂点バッファをレンダリングパイプラインに設定
	pDevice->SetStreamSource(0, m_pVtxBuffTop, 0, sizeof(VERTEX_3D));

	// インデックスバッファをレンダリングパイプラインに設定
	pDevice->SetIndices(m_pIdxBuffTop);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLEFAN,				//プリミティブの種類
		0,								//最初の頂点インデックスまでのオフセット
		0,								//最小の頂点インデックス
		(m_nNumBlockH + 1),		//頂点の数
		0,								//読み取りを開始する位置
		m_nNumBlockH		//ポリゴンの数
	);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	// 裏面をカリング
}

//=============================================================================
// メシュポリゴンの生成
//=============================================================================
CMeshDome *CMeshDome::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, int nNumBlockH, int nNumBlockV)
{
	CMeshDome *pDome;
	pDome = new CMeshDome;
	pDome->Init(pos, rot, fRadius, nNumBlockH, nNumBlockV);

	//テクスチャの読み込み
	pDome->Load();

	return pDome;
}

//=============================================================================
// 座標の取得
//=============================================================================
D3DXVECTOR3 CMeshDome::GetPosition(void)
{
	return m_pos;
}
//=============================================================================
// サイズの取得
//=============================================================================
D3DXVECTOR3 CMeshDome::GetSize(void)
{
	return D3DXVECTOR3( m_fRadius, m_fRadius, m_fRadius);
}


//=============================================================================
// メシュポリゴンのテクスチャを読み込む
//=============================================================================
HRESULT CMeshDome::Load(void)
{
	if( m_pTexture == NULL)
	{
		LPDIRECT3DDEVICE9 pDevice;
		pDevice = CManager::GetRenderer()->GetDevice();

		// テクスチャの読み込み
		D3DXCreateTextureFromFile( pDevice, TEXTURE_MESHDOME, &m_pTexture);

		// テクスチャの読み込みフラグ
		m_bLoadTexture = true;
	}

	return S_OK;
}

//=============================================================================
// メシュポリゴンのテクスチャを割り当てる
//=============================================================================
void CMeshDome::BindTexture( LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
//=============================================================================
// 座標の設定
//=============================================================================
void CMeshDome::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}