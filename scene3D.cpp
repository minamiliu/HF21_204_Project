//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: scene3D.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/10
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "scene3D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"

//============================================
// マクロ定義
//============================================

#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#define TEXTURENAME "data/TEXTURE/field000.jpg"


//=============================================================================
// 構造体定義
//=============================================================================
//３Ｄポリゴン
typedef struct
{
	D3DXVECTOR3 vtx; //頂点座標
	D3DXVECTOR3 nor; //法線ベクトル
	D3DCOLOR	col; //頂点カラー
	D3DXVECTOR2	tex; //テクスチャ座標
}VERTEX_3D;

//=============================================================================
//コンストラクタ
//=============================================================================
CScene3D::CScene3D()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CScene3D::~CScene3D()
{
	
}


//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CScene3D::Init(void)
{
	return S_OK;
}

HRESULT CScene3D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 位置・回転・スケールの初期設定
	m_pos = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);

	m_nNumBlockX = nNumBlockX;
	m_nNumBlockZ = nNumBlockZ;
	m_fSizeBlockX = fSizeBlockX;
	m_fSizeBlockZ = fSizeBlockZ;

	m_nNumVertex = (nNumBlockX+1) * (nNumBlockZ+1);
	m_nNumVertexIndex = (nNumBlockX + 1)*2*nNumBlockZ + (nNumBlockZ - 1)*2;
	m_nNumPolygon = nNumBlockX*nNumBlockZ*2 + (nNumBlockZ - 1)*4;

	m_pTexture = NULL;	
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	
	// 頂点情報の作成
	MakeVertex(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile( pDevice, TEXTURENAME, &m_pTexture);


	return S_OK;
}
void CScene3D::Uninit(void)
{
	if(m_pTexture != NULL)
	{// テクスチャの開放
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	if(m_pVtxBuff != NULL) 
	{// 頂点バッファの開放
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//オブジェクトの破棄
	Release();
}

void CScene3D::Update(void)
{

}

void CScene3D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
		
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

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// インデックスバッファをレンダリングパイプラインに設定
	pDevice->SetIndices(m_pIdxBuff);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);
	
	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,						//最初の頂点インデックスまでのオフセット
		0,						//最小の頂点インデックス
		m_nNumVertex,			//頂点の数
		0,						//読み取りを開始する位置
		m_nNumPolygon			//ポリゴンの数
	);
}

CScene3D *CScene3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ)
{
	CScene3D *pScene3D;
	pScene3D = new CScene3D;
	pScene3D->Init(pos, rot, nNumBlockX, nNumBlockZ, fSizeBlockX, fSizeBlockZ);
	
	return pScene3D;
}

HRESULT CScene3D::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if(FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * m_nNumVertex,	//頂点データのバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,					//頂点フォーマット
		D3DPOOL_MANAGED,
		&m_pVtxBuff,			//頂点バッファインターフェースのポインタ
		NULL)))
	{
		return E_FAIL;
	}

	// オブジェクトのインデックスバッファを生成
	if(FAILED(pDevice->CreateIndexBuffer(
		sizeof(WORD) * m_nNumVertexIndex,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL)))
	{
		return E_FAIL;
	}

	
	{//頂点バッファの中身を埋める

		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_pVtxBuff->Lock( 0, 0, (void**)&pVtx, 0);

		for(int nCntZ = 0; nCntZ < m_nNumBlockZ+1; nCntZ++)
		{
			for(int nCntX = 0; nCntX < m_nNumBlockX+1; nCntX++)
			{
				pVtx[0].vtx = D3DXVECTOR3( -m_fSizeBlockX*m_nNumBlockX/2 + nCntX*m_fSizeBlockX, 0.0f, m_fSizeBlockZ*m_nNumBlockZ/2 - nCntZ*m_fSizeBlockZ);
				pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
				pVtx[0].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f);
				pVtx[0].tex = D3DXVECTOR2( 1.0f * nCntX, 1.0f * nCntZ );
				pVtx++;
			}
		}


		// 頂点データをアンロックする
		m_pVtxBuff->Unlock();	
	}


	{//インデックスバッファの中身を埋める

		WORD *pIdx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_pIdxBuff->Lock( 0, 0, (void**)&pIdx, 0);

		for(int nCntZ = 0; nCntZ < m_nNumBlockZ; nCntZ++)
		{
			if(nCntZ > 0)
			{
				pIdx[0] = (m_nNumBlockX + 1) * (nCntZ + 1);
				pIdx++;
			}
			for(int nCntX = 0; nCntX < m_nNumBlockX+1; nCntX++, pIdx+=2)
			{
				//頂点座標の設定
				pIdx[0] = (m_nNumBlockX + 1) * (nCntZ + 1) + nCntX; 
				pIdx[1] = (m_nNumBlockX + 1) * (nCntZ) + nCntX;
			}
			if(nCntZ < m_nNumBlockZ - 1)
			{
				*pIdx = *(pIdx-1);
				pIdx++;
			}
		}

		// 頂点データをアンロックする
		m_pIdxBuff->Unlock();	
	}

	return S_OK;
}

D3DXVECTOR3 CScene3D::GetPosition(void)
{
	return m_pos;
}
D3DXVECTOR3 CScene3D::GetSize(void)
{
	return m_size;
}
void CScene3D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}