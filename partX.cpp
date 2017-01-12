//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: partX.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2017/01/04
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "partX.h"
#include "renderer.h"
#include "manager.h"
#include "playerX.h"

//============================================
// マクロ定義
//============================================
#define MODEL_FILENAME_L_HAND	"data/MODEL/mom_L_hand.x"
#define MODEL_FILENAME_R_HAND	"data/MODEL/mom_R_hand.x"
#define MODEL_FILENAME_L_FOOT	"data/MODEL/mom_L_foot.x"
#define MODEL_FILENAME_R_FOOT	"data/MODEL/mom_R_foot.x"
#define MAX_MOTION (2)

//=============================================================================
// 構造体定義
//=============================================================================

//============================================
// 静的メンバー変数の初期化
//============================================
CPartX::MOTION *CPartX::m_pMotionPara = NULL;

//=============================================================================
//コンストラクタ
//=============================================================================
CPartX::CPartX()
{
	m_pTexture = NULL;		// テクスチャへのポインタ
	m_pD3DXMesh = NULL;		// メッシュ情報へのポインタ
	m_pD3DXBuffMat = NULL;	// マテリアル情報へのポインタ
	m_nNumMat = 0;			// マテリアル情報の数

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// モデルの位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// モデルの向き(回転)
	m_scl = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// モデルの大きさ(スケール)

	D3DXMatrixIdentity(&m_mtxWorld);
}

//=============================================================================
//デストラクタ
//=============================================================================
CPartX::~CPartX()
{

}


//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CPartX::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, TYPE type)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// モデルに関する変数の初期化							
	m_pTexture = NULL;		// テクスチャへのポインタ
	m_pD3DXMesh = NULL;		// メッシュ情報へのポインタ
	m_pD3DXBuffMat = NULL;	// マテリアル情報へのポインタ
	m_nNumMat = 0;			// マテリアル情報の数

	//モーション
	m_pMotionPara = new MOTION[MAX_MOTION];
	
	m_pMotionPara[0].nFrame = 30;
	m_pMotionPara[0].rotX = D3DXToRadian(-60.0f);

	m_pMotionPara[1].nFrame = 30;
	m_pMotionPara[1].rotX = D3DXToRadian(60.0f);

	//TYPEことの初期化
	LPCSTR strFileName;
	switch(type)
	{
	case TYPE_L_HAND:
		strFileName = MODEL_FILENAME_L_HAND;
		m_rotLocal = D3DXVECTOR3( D3DXToRadian(30.0f), 0.0f, 0.0f);
		m_posLocal = D3DXVECTOR3( 8, -15, 0);
		m_nMotionNow = 0;
		break;
	case TYPE_R_HAND:
		strFileName = MODEL_FILENAME_R_HAND;
		m_rotLocal = D3DXVECTOR3( D3DXToRadian(-30.0f), 0.0f, 0.0f);
		m_posLocal = D3DXVECTOR3( -8, -15, 0);
		m_nMotionNow = 1;
		break;
	case TYPE_L_FOOT:
		strFileName = MODEL_FILENAME_L_FOOT;
		m_rotLocal = D3DXVECTOR3( D3DXToRadian(-30.0f), 0.0f, 0.0f);
		m_posLocal = D3DXVECTOR3( 4, -35, 0);
		m_nMotionNow = 1;
		break;
	case TYPE_R_FOOT:
		strFileName = MODEL_FILENAME_R_FOOT;
		m_rotLocal = D3DXVECTOR3( D3DXToRadian(30.0f), 0.0f, 0.0f);
		m_posLocal = D3DXVECTOR3( -4, -35, 0);
		m_nMotionNow = 0;
		break;
	}

	//初期設定
	m_pos = pos + m_posLocal;
	m_rot = rot + m_rotLocal;
	m_scl = scl;
	m_type = type;
	m_nCntFrame = 0;
	m_rotXTurn = m_pMotionPara[m_nMotionNow].rotX / m_pMotionPara[m_nMotionNow].nFrame;
	
	// Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(
		strFileName,			// 読み込むモデルファイル名(Xファイル)
		D3DXMESH_SYSTEMMEM,		// メッシュの作成オプションを指定
		pDevice,				// IDirect3DDevice9インターフェイスへのポインタ
		NULL,					// 隣接性データを含むバッファへのポインタ
		&m_pD3DXBuffMat,		// マテリアルデータを含むバッファへのポインタ
		NULL,					// エフェクトインスタンスの配列を含むバッファへのポインタ
		&m_nNumMat,				// D3DXMATERIAL構造体の数
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
HRESULT CPartX::LoadXfile(LPCSTR strFileName)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();


	// モデルに関する変数の初期化							
	m_pTexture = NULL;		// テクスチャへのポインタ
	m_pD3DXMesh = NULL;		// メッシュ情報へのポインタ
	m_pD3DXBuffMat = NULL;		// マテリアル情報へのポインタ
	m_nNumMat = 0;			// マテリアル情報の数
							// Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(
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


	return S_OK;
}


//=============================================================================
//
//=============================================================================
void CPartX::Uninit(void)
{
	// テクスチャの開放
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// メッシュの開放
	if (m_pD3DXMesh != NULL)
	{
		m_pD3DXMesh->Release();
		m_pD3DXMesh = NULL;
	}
	// マテリアルの開放
	if (m_pD3DXBuffMat != NULL)
	{
		m_pD3DXBuffMat->Release();
		m_pD3DXBuffMat = NULL;
	}

	//オブジェクトの破棄
	//Release();
}
//=============================================================================
// Xファイルを割り当てる
//=============================================================================
void CPartX::BindXfile(LPDIRECT3DTEXTURE9	pTexture,		// テクスチャへのポインタ
	LPD3DXMESH			pD3DXMesh,			// メッシュ情報へのポインタ
	LPD3DXBUFFER		pD3DXBuffMat,		// マテリアル情報へのポインタ
	DWORD				nNumMat
)					// マテリアル情報の数
{
	m_pTexture = pTexture;
	m_pD3DXMesh = pD3DXMesh;
	m_pD3DXBuffMat = pD3DXBuffMat;
	m_nNumMat = nNumMat;
}
//=============================================================================
//
//=============================================================================
void CPartX::Update(void)
{
	//CDebugProc::Print("\nposX = %f\n", m_pos.x);
	//CDebugProc::Print("posZ = %f\n", m_pos.z);
	//CDebugProc::Print("rotY = %f\n", m_rot.y);

	//ローカル座標の更新
	m_pos.x +=  m_posLocal.x * sinf(this->GetRot().y + D3DX_PI / 2.0f);
	m_pos.z +=  m_posLocal.x * cosf(this->GetRot().y + D3DX_PI / 2.0f);
	m_pos.y += m_posLocal.y;

	//向き
	m_rotLocal.x += m_rotXTurn;
	m_rot += m_rotLocal;

	//モーション更新処理
	m_nCntFrame++;
	if( m_nCntFrame >= m_pMotionPara[m_nMotionNow].nFrame)
	{
		m_nMotionNow = (m_nMotionNow + 1) % MAX_MOTION;
		m_rotXTurn = m_pMotionPara[m_nMotionNow].rotX / m_pMotionPara[m_nMotionNow].nFrame;
		m_nCntFrame = 0;
	}
}

//=============================================================================
//
//=============================================================================
void CPartX::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアル情報に対するポインタを取得
	pD3DXMat = (D3DXMATERIAL *)m_pD3DXBuffMat->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
		// テクスチャの設定
		pDevice->SetTexture(0, m_pTexture);
		// 描画
		m_pD3DXMesh->DrawSubset(nCntMat);
	}

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
//
//=============================================================================
CPartX *CPartX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, TYPE type)
{
	CPartX *pSceneX;
	pSceneX = new CPartX;
	pSceneX->Init(pos, rot, scl, type);

	return pSceneX;
}

D3DXVECTOR3 CPartX::GetPosition(void)
{
	return m_pos;
}

D3DXVECTOR3 CPartX::GetSize(void)
{
	return m_size;
}
D3DXVECTOR3 CPartX::GetRot(void)
{
	return m_rot;
}

void CPartX::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

void CPartX::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

void CPartX::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
