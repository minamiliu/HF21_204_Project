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
#include "meshWall.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"

//============================================
// マクロ定義
//============================================

#define TEXTURENAME "data/TEXTURE/wall000.jpg"

//============================================
// 静的メンバー変数の初期化
//============================================
LPDIRECT3DTEXTURE9 CMeshWall::m_pTexture = NULL;


//=============================================================================
//コンストラクタ
//=============================================================================
CMeshWall::CMeshWall()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CMeshWall::~CMeshWall()
{
	
}


//=============================================================================
// ポリゴンの初期化処理
//=============================================================================

HRESULT CMeshWall::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ)
{
	CScene3D::Init( pos, rot, nNumBlockX, nNumBlockZ, fSizeBlockX, fSizeBlockZ);
	return S_OK;
}
//=============================================================================
//
//=============================================================================
void CMeshWall::Uninit(void)
{
	CScene3D::Uninit();
}
//=============================================================================
//
//=============================================================================
void CMeshWall::Update(void)
{
	
}
//=============================================================================
//
//=============================================================================
void CMeshWall::Draw(void)
{
	CScene3D::Draw();
}
//=============================================================================
//
//=============================================================================
CMeshWall *CMeshWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ)
{
	CMeshWall *pMeshWall;
	pMeshWall = new CMeshWall;

	rot.x = D3DXToRadian(-90.0f); //壁を立てる

	pMeshWall->Init(pos, rot, nNumBlockX, nNumBlockZ, fSizeBlockX, fSizeBlockZ);

	//テクスチャの割り当て
	pMeshWall->BindTexture( m_pTexture);

	return pMeshWall;
}

bool CMeshWall::HitCheck( D3DXVECTOR3 tNowPos, D3DXVECTOR3 tNextPos, D3DXVECTOR3 *wall_nor, D3DXVECTOR3 *HitPoint)
{
	return CScene3D::HitCheck( tNowPos, tNextPos, wall_nor, HitPoint);
}

//=============================================================================
//
//=============================================================================
HRESULT CMeshWall::Load(void)
{
	if( m_pTexture == NULL)
	{
		LPDIRECT3DDEVICE9 pDevice;
		pDevice = CManager::GetRenderer()->GetDevice();

		// テクスチャの読み込み
		D3DXCreateTextureFromFile( pDevice, TEXTURENAME, &m_pTexture);
	}

	return S_OK;
}

//=============================================================================
//
//=============================================================================
void CMeshWall::Unload(void)
{
	//テクスチャの破棄
	if( m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}


