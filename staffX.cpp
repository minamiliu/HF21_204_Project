//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: staff.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2017/01/23
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "staffX.h"
#include "manager.h"
#include "renderer.h"
#include "shadow.h"


//============================================
// マクロ定義
//============================================
#define MODEL_STAFF	"data/MODEL/staff.x"

//=============================================================================
// 構造体定義
//=============================================================================

//============================================
// 静的メンバー変数の初期化
//============================================
LPDIRECT3DTEXTURE9	CStaffX::m_pTexture		[TYPE_MAX] = {};		// テクスチャへのポインタ
LPD3DXMESH			CStaffX::m_pD3DXMesh	[TYPE_MAX] = {};		// メッシュ情報へのポインタ
LPD3DXBUFFER		CStaffX::m_pD3DXBuffMat	[TYPE_MAX] = {};		// マテリアル情報へのポインタ
DWORD				CStaffX::m_nNumMat		[TYPE_MAX] = {};		// マテリアル情報の数

//=============================================================================
//コンストラクタ
//=============================================================================
CStaffX::CStaffX()
{
	m_pShadow = NULL;
}

//=============================================================================
//デストラクタ
//=============================================================================
CStaffX::~CStaffX()
{
	
}


//=============================================================================
//
//=============================================================================
HRESULT CStaffX::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl)
{
	CSceneX::Init( pos, rot, scl);
	SetObjType( OBJTYPE_L_ENEMY);

	//影の生成
	m_pShadow = CShadow::Create( pos, D3DXVECTOR2( 50.0f, 50.0f));

	return S_OK;
}

//=============================================================================
//
//=============================================================================
void CStaffX::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
//
//=============================================================================
void CStaffX::Update(void)
{
	//影の更新処理
	//m_pShadow->SetPosition( this->GetPosition());
}

//=============================================================================
//
//=============================================================================
void CStaffX::Draw(void)
{
	CSceneX::Draw();
}

//=============================================================================
//
//=============================================================================
CStaffX *CStaffX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, TYPE type)
{
	CStaffX *pEnemy;
	pEnemy = new CStaffX;
	pEnemy->Init(pos, rot, scl);

	//Xfileの割り当て
	pEnemy->BindXfile( m_pTexture[type], m_pD3DXMesh[type], m_pD3DXBuffMat[type], m_nNumMat[type]);

	return pEnemy;
}


//=============================================================================
//XFILEのロード
//=============================================================================
HRESULT CStaffX::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	for(int cntType = 0; cntType < TYPE_MAX; cntType++)
	{
		LPCSTR strFileName;
		switch( cntType)
		{
		case TYPE_000:
			strFileName = MODEL_STAFF;
			break;
		}

		if( m_pTexture[cntType] == NULL &&
			m_pD3DXMesh[cntType] == NULL &&
			m_pD3DXBuffMat[cntType] == NULL &&
			m_nNumMat[cntType] == 0
			)
		{
			// Xファイルの読み込み
			if(FAILED(D3DXLoadMeshFromX(
				strFileName,			// 読み込むモデルファイル名(Xファイル)
				D3DXMESH_SYSTEMMEM,		// メッシュの作成オプションを指定
				pDevice,				// IDirect3DDevice9インターフェイスへのポインタ
				NULL,					// 隣接性データを含むバッファへのポインタ
				&m_pD3DXBuffMat[cntType],	// マテリアルデータを含むバッファへのポインタ
				NULL,					// エフェクトインスタンスの配列を含むバッファへのポインタ
				&m_nNumMat[cntType],	// D3DXMATERIAL構造体の数
				&m_pD3DXMesh[cntType]	// ID3DXMeshインターフェイスへのポインタのアドレス
				)))
			{
				return E_FAIL;
			}
		
		}
	}

	return S_OK;
}

//=============================================================================
//XFILEのアンロード
//=============================================================================
void CStaffX::Unload(void)
{
	for(int cntType = 0; cntType < TYPE_MAX; cntType++)
	{
		// テクスチャの開放
		if(m_pTexture[cntType] != NULL)
		{
			m_pTexture[cntType]->Release();
			m_pTexture[cntType] = NULL;
		}
		// メッシュの開放
		if(m_pD3DXMesh[cntType] != NULL)
		{
			m_pD3DXMesh[cntType]->Release();
			m_pD3DXMesh[cntType] = NULL;
		}
		// マテリアルの開放
		if(m_pD3DXBuffMat != NULL)
		{
			m_pD3DXBuffMat[cntType]->Release();
			m_pD3DXBuffMat[cntType] = NULL;
		}	
	}

}
