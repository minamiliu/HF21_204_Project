//============================================
//
// タイトル:	 CL25課題
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
#include "input.h"

//============================================
// マクロ定義
//============================================
#define MODEL_FILENAME "data/MODEL/player.x"


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
	m_move = 0.0f;								// モデルの移動量

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
HRESULT CSceneX::Init(void)
{
	return S_OK;
}

//=============================================================================
//
//=============================================================================
HRESULT CSceneX::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float move)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 位置・回転・スケールの初期設定
	m_pos = pos;
	m_rot = rot;
	m_scl = scl;
	m_move = move;

	// モデルに関する変数の初期化							
	m_pTexture = NULL;		// テクスチャへのポインタ
	m_pD3DXMesh = NULL;		// メッシュ情報へのポインタ
	m_pD3DXBuffMat = NULL;		// マテリアル情報へのポインタ
	m_nNumMat = 0;			// マテリアル情報の数

	// Xファイルの読み込み
	if(FAILED(D3DXLoadMeshFromX(
		MODEL_FILENAME,				// 読み込むモデルファイル名(Xファイル)
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


	return S_OK;
}

//=============================================================================
//
//=============================================================================
void CSceneX::Uninit(void)
{
	// テクスチャの開放
	if(m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// メッシュの開放
	if(m_pD3DXMesh != NULL)
	{
		m_pD3DXMesh->Release();
		m_pD3DXMesh = NULL;
	}
	// マテリアルの開放
	if(m_pD3DXBuffMat != NULL)
	{
		m_pD3DXBuffMat->Release();
		m_pD3DXBuffMat = NULL;
	}
}

//=============================================================================
//
//=============================================================================
void CSceneX::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

		//移動
	if(pInputKeyboard->GetKeyPress(DIK_W))
	{
		m_pos.z -= m_move;
	}
	if(pInputKeyboard->GetKeyPress(DIK_S))
	{
		m_pos.z += m_move;
	}
	if(pInputKeyboard->GetKeyPress(DIK_A))
	{
		m_pos.x += m_move;
	}
	if(pInputKeyboard->GetKeyPress(DIK_D))
	{
		m_pos.x -= m_move;
	}
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
CSceneX *CSceneX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float move)
{
	CSceneX *pSceneX;
	pSceneX = new CSceneX;
	pSceneX->Init(pos, rot, scl, move);

	return pSceneX;
}
