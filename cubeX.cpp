//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: playerX.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/15
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "cubeX.h"
#include "manager.h"
#include "renderer.h"

//============================================
// マクロ定義
//============================================
#define MODEL_FILENAME_1X1 "data/MODEL/cashier.x"
#define MODEL_FILENAME_1X2 "data/MODEL/shelf200.x"
#define MODEL_FILENAME_1X4 "data/MODEL/shelf400.x"

//=============================================================================
// 構造体定義
//=============================================================================


//============================================
// 静的メンバー変数の初期化
//============================================
LPDIRECT3DTEXTURE9	CCubeX::m_pTexture		[TYPE_MAX] = {};		// テクスチャへのポインタ
LPD3DXMESH			CCubeX::m_pD3DXMesh		[TYPE_MAX] = {};		// メッシュ情報へのポインタ
LPD3DXBUFFER		CCubeX::m_pD3DXBuffMat	[TYPE_MAX] = {};		// マテリアル情報へのポインタ
DWORD				CCubeX::m_nNumMat		[TYPE_MAX] = {};		// マテリアル情報の数

//=============================================================================
//コンストラクタ
//=============================================================================
CCubeX::CCubeX()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CCubeX::~CCubeX()
{
	
}


//=============================================================================
//
//=============================================================================
HRESULT CCubeX::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 sideLen, TYPE type)
{
	m_sideLen = sideLen;
	m_type = type;
	
	switch( type)
	{
	case TYPE_1X1:
		CSceneX::Init( pos, rot, scl);
		break;

	case TYPE_1X2:
		CSceneX::Init( pos, rot, scl);
		break;

	case TYPE_1X4:
		CSceneX::Init( pos, rot, scl);
		break;
	}
	
	return S_OK;
}

//=============================================================================
//
//=============================================================================
void CCubeX::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
//
//=============================================================================
void CCubeX::Update(void)
{
	
}

//=============================================================================
//
//=============================================================================
void CCubeX::Draw(void)
{
	CSceneX::Draw();
}

//=============================================================================
//
//=============================================================================
CCubeX *CCubeX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 sideLen, TYPE type)
{
	CCubeX *pCube;
	pCube = new CCubeX;
	pCube->Init(pos, rot, D3DXVECTOR3( 1.0f, 1.0f, 1.0f), sideLen, type);

	//Xfileの割り当て
	pCube->BindXfile( m_pTexture[type], m_pD3DXMesh[type], m_pD3DXBuffMat[type], m_nNumMat[type]);

	return pCube;
}

//=============================================================================
//
//=============================================================================
D3DXVECTOR3 CCubeX::GetSideMin(void)
{
	D3DXVECTOR3 sideMin = this->GetPosition();
	sideMin.x -= m_sideLen.x / 2;
	sideMin.y -= m_sideLen.y / 2;
	sideMin.z -= m_sideLen.z / 2;

	return sideMin;
}

//=============================================================================
//
//=============================================================================
D3DXVECTOR3 CCubeX::GetSideMax(void)
{
	D3DXVECTOR3 sideMax = this->GetPosition();
	sideMax.x += m_sideLen.x / 2;
	sideMax.y += m_sideLen.y / 2;
	sideMax.z += m_sideLen.z / 2;

	return sideMax;
}

//=============================================================================
//
//=============================================================================
float CCubeX::GetDistanceBoxPoint(D3DXVECTOR3 point)
{
	float distance = 0.0f;   // 長さのべき乗の値を格納

	D3DXVECTOR3 sideMin = GetSideMin();
	D3DXVECTOR3 sideMax = GetSideMax();
	
	for(int xyz = 0; xyz < 3; xyz++)
	{
		float tpoint;
		float min, max; 

		switch( xyz)
		{
		case 0:
			tpoint = point.x;
			min = sideMin.x;
			max = sideMax.x;
			break;

		case 1:
			tpoint = point.y;
			min = sideMin.y;
			max = sideMax.y;
			break;

		case 2:
			tpoint = point.z;
			min = sideMin.z;
			max = sideMax.z;
			break;
		}

		//距離を計算
		if( tpoint < min)
		{
			distance += (tpoint - min) * (tpoint - min);
		}
		if( tpoint > max)
		{
			distance += (tpoint - max) * (tpoint - max);
		}
	}

	distance = sqrtf(distance);

	return distance;
}

//=============================================================================
//
//=============================================================================
CCubeX::TYPE CCubeX::GetType(void)
{
	return m_type;
}

//=============================================================================
//
//=============================================================================
HRESULT CCubeX::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	for(int cntType = 0; cntType < TYPE_MAX; cntType++)
	{
		LPCSTR strFileName;
		switch( cntType)
		{
		case TYPE_1X1:
			strFileName = MODEL_FILENAME_1X1;
			break;

		case TYPE_1X2:
			strFileName = MODEL_FILENAME_1X2;
			break;

		case TYPE_1X4:
			strFileName = MODEL_FILENAME_1X4;
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
//
//=============================================================================
void CCubeX::Unload(void)
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