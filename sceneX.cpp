//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: sceneX.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/15
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "sceneX.h"
#include "renderer.h"
#include "manager.h"
#include "camera.h"
#include "input.h"
#include "debugproc.h"

//============================================
// マクロ定義
//============================================

//=============================================================================
// 構造体定義
//=============================================================================


//=============================================================================
//コンストラクタ
//=============================================================================
CSceneX::CSceneX()
{
	m_pTexture = NULL;		// テクスチャへのポインタ
	m_pD3DXMesh = NULL;		// メッシュ情報へのポインタ
	m_pD3DXBuffMat = NULL;	// マテリアル情報へのポインタ
	m_nNumMat = 0;			// マテリアル情報の数

	m_pos = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);		// モデルの位置
	m_rot = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);		// モデルの向き(回転)
	m_scl = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);		// モデルの大きさ(スケール)

	D3DXMatrixIdentity( &m_mtxWorld);
}

//=============================================================================
//デストラクタ
//=============================================================================
CSceneX::~CSceneX()
{
	
}


//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CSceneX::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 位置・回転・スケールの初期設定
	m_pos = pos;
	m_rot = rot;
	m_scl = scl;

	//Xファイルの読み込みフラグ
	m_bLoadXfile = false;
	
	return S_OK;
}

//=============================================================================
//
//=============================================================================
HRESULT CSceneX::LoadXfile(LPCSTR strFileName)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	
	// モデルに関する変数の初期化							
	m_pTexture = NULL;		// テクスチャへのポインタ
	m_pD3DXMesh = NULL;		// メッシュ情報へのポインタ
	m_pD3DXBuffMat = NULL;		// マテリアル情報へのポインタ
	m_nNumMat = 0;			// マテリアル情報の数
	// Xファイルの読み込み
	if(FAILED(D3DXLoadMeshFromX(
		strFileName,				// 読み込むモデルファイル名(Xファイル)
		D3DXMESH_SYSTEMMEM,			// メッシュの作成オプションを指定
		pDevice,					// IDirect3DDevice9インターフェイスへのポインタ
		NULL,						// 隣接性データを含むバッファへのポインタ
		&m_pD3DXBuffMat,		// マテリアルデータを含むバッファへのポインタ
		NULL,						// エフェクトインスタンスの配列を含むバッファへのポインタ
		&m_nNumMat,			// D3DXMATERIAL構造体の数
		&m_pD3DXMesh			// ID3DXMeshインターフェイスへのポインタのアドレス
		)))
	{
		return E_FAIL;
	}	

	//Xファイルの読み込みフラグ
	m_bLoadXfile = true;
	
	return S_OK;
}


//=============================================================================
//
//=============================================================================
void CSceneX::Uninit(void)
{
	// テクスチャの開放
	if(m_pTexture != NULL && m_bLoadXfile == true)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// メッシュの開放
	if(m_pD3DXMesh != NULL && m_bLoadXfile == true)
	{
		m_pD3DXMesh->Release();
		m_pD3DXMesh = NULL;
	}
	// マテリアルの開放
	if(m_pD3DXBuffMat != NULL && m_bLoadXfile == true)
	{
		m_pD3DXBuffMat->Release();
		m_pD3DXBuffMat = NULL;
	}

	//オブジェクトの破棄
	Release();
}
//=============================================================================
// Xファイルを割り当てる
//=============================================================================
void CSceneX::BindXfile(LPDIRECT3DTEXTURE9	pTexture,	// テクスチャへのポインタ
						LPD3DXMESH  pD3DXMesh,			// メッシュ情報へのポインタ
						LPD3DXBUFFER  pD3DXBuffMat,		// マテリアル情報へのポインタ
						DWORD	nNumMat)				// マテリアル情報の数
{
	m_pTexture		= pTexture;
	m_pD3DXMesh		= pD3DXMesh;
	m_pD3DXBuffMat	= pD3DXBuffMat;
	m_nNumMat		= nNumMat;
}
//=============================================================================
//
//=============================================================================
void CSceneX::Update(void)
{
	//CDebugProc::Print("\nposX = %f\n", m_pos.x);
	//CDebugProc::Print("posZ = %f\n", m_pos.z);
	//CDebugProc::Print("rotY = %f\n", m_rot.y);
}

//=============================================================================
//
//=============================================================================
void CSceneX::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity( &m_mtxWorld);
	
	// スケールを反映
	D3DXMatrixScaling( &mtxScl, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxScl);
	
	// 回転を反映
	D3DXMatrixRotationYawPitchRoll( &mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxRot);
	
	// 移動を反映
	D3DXMatrixTranslation( &mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxTranslate);
	
	// ワールドマトリックスの設定
	pDevice->SetTransform( D3DTS_WORLD, &m_mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);
	
	// マテリアル情報に対するポインタを取得
	pD3DXMat = (D3DXMATERIAL *)m_pD3DXBuffMat->GetBufferPointer();
	for(int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial( &pD3DXMat[nCntMat].MatD3D);
		// テクスチャの設定
		pDevice->SetTexture( 0, m_pTexture);
		// 描画
		m_pD3DXMesh->DrawSubset( nCntMat);
	}

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial( &matDef);
}

//=============================================================================
//
//=============================================================================
CSceneX *CSceneX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, LPCSTR strFileName)
{
	CSceneX *pSceneX;
	pSceneX = new CSceneX;
	pSceneX->Init(pos, rot, scl);

	//Xファイルの読み込み
	pSceneX->LoadXfile(strFileName);

	return pSceneX;
}

D3DXVECTOR3 CSceneX::GetPosition(void)
{
	return m_pos;
}

D3DXVECTOR3 CSceneX::GetSize(void)
{
	return m_scl;
}
D3DXVECTOR3 CSceneX::GetRot(void)
{
	return m_rot;
}

void CSceneX::SetPosition( D3DXVECTOR3 pos)
{
	m_pos = pos;
}

void CSceneX::SetSize( D3DXVECTOR3 scl)
{
	m_scl = scl;
}

void CSceneX::SetRot( D3DXVECTOR3 rot)
{
	m_rot = rot;
}
