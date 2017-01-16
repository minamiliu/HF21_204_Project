//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: limbX.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2017/01/16
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "limbX.h"
#include "renderer.h"
#include "manager.h"

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
CLimbX::MOTION *CLimbX::m_pMotionPara = NULL;
LPDIRECT3DTEXTURE9	CLimbX::m_pTexture		[TYPE_MAX] = {};		// テクスチャへのポインタ
LPD3DXMESH			CLimbX::m_pD3DXMesh		[TYPE_MAX] = {};		// メッシュ情報へのポインタ
LPD3DXBUFFER		CLimbX::m_pD3DXBuffMat	[TYPE_MAX] = {};		// マテリアル情報へのポインタ
DWORD				CLimbX::m_nNumMat		[TYPE_MAX] = {};		// マテリアル情報の数

//=============================================================================
//コンストラクタ
//=============================================================================
CLimbX::CLimbX()
{
}

//=============================================================================
//デストラクタ
//=============================================================================
CLimbX::~CLimbX()
{

}


//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CLimbX::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, TYPE type)
{
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
	D3DXVECTOR3 tPos = pos + m_posLocal;
	D3DXVECTOR3 tRot = rot + m_rotLocal;
	D3DXVECTOR3 tScl = scl;
	CPartX::Init( tPos, tRot, tScl);

	m_type = type;
	m_nCntFrame = 0;
	m_rotXTurn = m_pMotionPara[m_nMotionNow].rotX / m_pMotionPara[m_nMotionNow].nFrame;
	

	return S_OK;
}

//=============================================================================
//
//=============================================================================
void CLimbX::Uninit(void)
{
	CPartX::Uninit();
}

//=============================================================================
//
//=============================================================================
void CLimbX::Update(void)
{
	//CDebugProc::Print("\nposX = %f\n", m_pos.x);
	//CDebugProc::Print("posZ = %f\n", m_pos.z);
	//CDebugProc::Print("rotY = %f\n", m_rot.y);

	//ローカル座標の更新
	D3DXVECTOR3 tPos = this->GetPosition();
	tPos.x +=  m_posLocal.x * sinf(this->GetRot().y + D3DX_PI / 2.0f);
	tPos.z +=  m_posLocal.x * cosf(this->GetRot().y + D3DX_PI / 2.0f);
	tPos.y += m_posLocal.y;
	this->SetPosition( tPos);

	//向き
	D3DXVECTOR3 tRot = this->GetRot();
	m_rotLocal.x += m_rotXTurn;
	tRot += m_rotLocal;
	this->SetRot( tRot);

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
void CLimbX::Draw(void)
{
	CPartX::Draw();
}

//=============================================================================
//
//=============================================================================
CLimbX *CLimbX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, TYPE type)
{
	CLimbX *pSceneX;
	pSceneX = new CLimbX;
	pSceneX->Init(pos, rot, scl, type);
	
	//Xファイルの割り当て
	pSceneX->BindXfile( m_pTexture[type], m_pD3DXMesh[type], m_pD3DXBuffMat[type], m_nNumMat[type]);

	return pSceneX;
}

//=============================================================================
//XFILEのロード
//=============================================================================
HRESULT CLimbX::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	for(int cntType = 0; cntType < TYPE_MAX; cntType++)
	{
		LPCSTR strFileName;
		switch( cntType)
		{
		case TYPE_L_HAND:
			strFileName = MODEL_FILENAME_L_HAND;
			break;
		case TYPE_R_HAND:
			strFileName = MODEL_FILENAME_R_HAND;
			break;
		case TYPE_L_FOOT:
			strFileName = MODEL_FILENAME_L_FOOT;
			break;
		case TYPE_R_FOOT:
			strFileName = MODEL_FILENAME_R_FOOT;
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
void CLimbX::Unload(void)
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
