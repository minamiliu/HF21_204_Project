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
#include "collision.h"

//============================================
// マクロ定義
//============================================
#define TEXTURENAME "data/TEXTURE/field000.jpg"


//=============================================================================
// 構造体定義
//=============================================================================

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
HRESULT CScene3D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 位置・回転・スケールの初期設定
	m_pos = pos;
	m_rot = rot;

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
	m_bLoadTexture = false;
	
	// 頂点情報の作成
	MakeVertex(pDevice);

	return S_OK;
}
void CScene3D::Uninit(void)
{
	if(m_pTexture != NULL && m_bLoadTexture == true)
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

	//テクスチャの読み込み
	pScene3D->Load(TEXTURENAME);

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

bool CScene3D::HitCheck( D3DXVECTOR3 tNowPos, D3DXVECTOR3 tNextPos, D3DXVECTOR3 *wall_nor, D3DXVECTOR3 *HitPoint)
{
	bool bHit = false;
	D3DXVECTOR3 tHitPosNear = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
	D3DXMATRIX mtxRot, mtxTranslate;
	D3DXVECTOR3 tPos[4];


	// メッシュ壁構造体のポインタにメッシュ壁ワークの先頭アドレスを代入
	CScene3D *pMesh = this;


	// ワールドマトリックスの初期化
	D3DXMatrixIdentity( &pMesh->m_mtxWorld);
	
	// 回転を反映
	D3DXMatrixRotationYawPitchRoll( &mtxRot, pMesh->m_rot.y, pMesh->m_rot.x, pMesh->m_rot.z);
	D3DXMatrixMultiply( &pMesh->m_mtxWorld, &pMesh->m_mtxWorld, &mtxRot);
	
	// 移動を反映
	D3DXMatrixTranslation( &mtxTranslate, pMesh->m_pos.x, pMesh->m_pos.y, pMesh->m_pos.z);
	D3DXMatrixMultiply( &pMesh->m_mtxWorld, &pMesh->m_mtxWorld, &mtxTranslate);

	{//頂点バッファの取得

		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		pMesh->m_pVtxBuff->Lock( 0, 0, (void**)&pVtx, 0);

		tPos[0] = pVtx[0].vtx;
		tPos[1] = pVtx[pMesh->m_nNumBlockX].vtx;
		tPos[2] = pVtx[(pMesh->m_nNumBlockX+1) * pMesh->m_nNumBlockZ].vtx;
		tPos[3] = pVtx[(pMesh->m_nNumBlockX+1) * (pMesh->m_nNumBlockZ+1) - 1 ].vtx;


		// 頂点データをアンロックする
		pMesh->m_pVtxBuff->Unlock();	
	}

	//頂点バッファにワールドマトリックスを掛ける、頂点バッファが更新される
	D3DXVec3TransformCoord( &tPos[0], &tPos[0], &pMesh->m_mtxWorld);
	D3DXVec3TransformCoord( &tPos[1], &tPos[1], &pMesh->m_mtxWorld);
	D3DXVec3TransformCoord( &tPos[2], &tPos[2], &pMesh->m_mtxWorld);
	D3DXVec3TransformCoord( &tPos[3], &tPos[3], &pMesh->m_mtxWorld);


	D3DXVECTOR3 tHitPos;
	if( CCollision::HitCheck( tPos[0], tPos[1], tPos[2], tNowPos, tNextPos, &tHitPos) )
	{
		bHit = true;

		//一番近い交点を求める
		D3DXVECTOR3 v1 = tHitPosNear - tNowPos;
		D3DXVECTOR3 v2 = tHitPos - tNowPos;
		if( D3DXVec3Length(&v1) > D3DXVec3Length(&v2))
		{
			tHitPosNear = tHitPos;

			//壁の法線を取得
			if(wall_nor != NULL) *wall_nor = CCollision::CrossProduct( tPos[0] - tPos[1], tPos[2] - tPos[1]);
		}
			
	}
	else if( CCollision::HitCheck( tPos[1], tPos[2], tPos[3], tNowPos, tNextPos, &tHitPos) )
	{
		bHit = true;

		//一番近い交点を求める
		D3DXVECTOR3 v1 = tHitPosNear - tNowPos;
		D3DXVECTOR3 v2 = tHitPos - tNowPos;
		if( D3DXVec3Length(&v1) > D3DXVec3Length(&v2))
		{
			tHitPosNear = tHitPos;

			//壁の法線を取得
			if(wall_nor != NULL) *wall_nor = CCollision::CrossProduct( tPos[1] - tPos[2], tPos[3] - tPos[2]);
		}
	}

	//一番近い交点を渡す
	if(HitPoint != NULL) *HitPoint = tHitPosNear;

	return bHit;
}

//=============================================================================
// ポリゴンのテクスチャを読み込む
//=============================================================================
HRESULT CScene3D::Load(LPCSTR strFileName)
{
	if( m_pTexture == NULL)
	{
		LPDIRECT3DDEVICE9 pDevice;
		pDevice = CManager::GetRenderer()->GetDevice();

		// テクスチャの読み込み
		D3DXCreateTextureFromFile( pDevice, strFileName, &m_pTexture);

		// テクスチャの読み込みフラグ
		m_bLoadTexture = true;
	}

	return S_OK;
}

//=============================================================================
// ポリゴンのテクスチャを割り当てる
//=============================================================================
void CScene3D::BindTexture( LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
