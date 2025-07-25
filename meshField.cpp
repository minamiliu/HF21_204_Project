//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: meshField.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/12/15
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "meshField.h"
#include "renderer.h"
#include "manager.h"

//============================================
// マクロ定義
//============================================

#define TEXTURE_GREEN "data/TEXTURE/field000.jpg"
#define TEXTURE_WHITE "data/TEXTURE/field001.jpg"
#define TEXTURE_WOOD "data/TEXTURE/field03.png"


//============================================
// 静的メンバー変数の初期化
//============================================
LPDIRECT3DTEXTURE9 CMeshField::m_pTexture[TYPE_MAX] = {};

//=============================================================================
//コンストラクタ
//=============================================================================
CMeshField::CMeshField()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CMeshField::~CMeshField()
{
	
}


//=============================================================================
// ポリゴンの初期化処理
//=============================================================================

HRESULT CMeshField::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ)
{
	CScene3D::Init( pos, rot, nNumBlockX, nNumBlockZ, fSizeBlockX, fSizeBlockZ, false);

	return S_OK;
}
//=============================================================================
//
//=============================================================================
void CMeshField::Uninit(void)
{
	CScene3D::Uninit();
}
//=============================================================================
//
//=============================================================================
void CMeshField::Update(void)
{
	
}
//=============================================================================
//
//=============================================================================
void CMeshField::Draw(void)
{
	CScene3D::Draw();
}
//=============================================================================
//
//=============================================================================
CMeshField *CMeshField::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ, TYPE type)
{
	CMeshField *pMeshField;
	pMeshField = new CMeshField;

	pMeshField->Init(pos, rot, nNumBlockX, nNumBlockZ, fSizeBlockX, fSizeBlockZ);

	//テクスチャの割り当て
	pMeshField->BindTexture( m_pTexture[type]);

	return pMeshField;
}


//=============================================================================
//
//=============================================================================
HRESULT CMeshField::Load(void)
{
	for(int cntType = 0; cntType < TYPE_MAX; cntType++)
	{
		LPCSTR strFileName;
		switch( cntType)
		{
		case TYPE_GREEN:
			strFileName = TEXTURE_GREEN;
			break;

		case TYPE_WHITE:
			strFileName = TEXTURE_WHITE;
			break;

		case TYPE_WOOD:
			strFileName = TEXTURE_WOOD;
			break;
		}

		if( m_pTexture[cntType] == NULL)
		{
			LPDIRECT3DDEVICE9 pDevice;
			pDevice = CManager::GetRenderer()->GetDevice();

			// テクスチャの読み込み
			D3DXCreateTextureFromFile( pDevice, strFileName, &m_pTexture[cntType]);
		}	
	}

	return S_OK;
}

//=============================================================================
//
//=============================================================================
void CMeshField::Unload(void)
{
	for(int cntType = 0; cntType < TYPE_MAX; cntType++)
	{
		//テクスチャの破棄
		if( m_pTexture[cntType] != NULL)
		{
			m_pTexture[cntType]->Release();
			m_pTexture[cntType] = NULL;
		}	
	}

}


