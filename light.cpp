//============================================
//
// タイトル:	 CL25課題
// プログラム名: light.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/10
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "light.h"
#include "renderer.h"
#include "manager.h"

//============================================
// マクロ定義
//============================================

//============================================
// 静的メンバー変数の初期化
//============================================
D3DLIGHT9 CLight::m_aLight[NUM_LIGHT] = {};	

//=============================================================================
// 構造体定義
//=============================================================================

//=============================================================================
//コンストラクタ
//=============================================================================
CLight::CLight()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CLight::~CLight()
{
	
}

HRESULT CLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXVECTOR3 vecDir;

	// D3DLIGHT9構造体を0でクリアする
	ZeroMemory( &m_aLight[0], sizeof(D3DLIGHT9));
	
	// ライト0のタイプの設定
	m_aLight[0].Type = D3DLIGHT_DIRECTIONAL;
	
	// ライト0の拡散光の設定
	m_aLight[0].Diffuse = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f);
	m_aLight[0].Ambient = D3DXCOLOR( 0.2f, 0.2f, 0.2f, 0.2f);
	
	// ライト0の方向の設定
	vecDir = D3DXVECTOR3( 0.2f, -0.6f, 0.8f);
	D3DXVec3Normalize( (D3DXVECTOR3*)&m_aLight[0].Direction, &vecDir);
	
	// ライト0をレンダリングパイプラインに設定
	pDevice->SetLight( 0, &m_aLight[0]);

	// ライト0を使用使用状態に
	pDevice->LightEnable( 0, TRUE);

	// D3DLIGHT9構造体を0でクリアする
	ZeroMemory( &m_aLight[1], sizeof(D3DLIGHT9));

	// ライト1のタイプの設定
	m_aLight[1].Type = D3DLIGHT_DIRECTIONAL;

	// ライト1の拡散光の設定
	m_aLight[1].Diffuse = D3DXCOLOR( 0.75f, 0.75f, 0.75f, 1.0f);
	m_aLight[1].Ambient = D3DXCOLOR( 0.2f, 0.2f, 0.2f, 1.0f);

    // ライト1の方向の設定
	vecDir = D3DXVECTOR3( -0.2f, -0.3f, -0.5f);
	D3DXVec3Normalize( (D3DXVECTOR3*)&m_aLight[1].Direction, &vecDir);

	// ライト1をレンダリングパイプラインに設定
	pDevice->SetLight( 1, &m_aLight[1]);

	// ライト1のを使用使用状態に
	pDevice->LightEnable( 1, TRUE);

	// D3DLIGHT9構造体を0でクリアする
	ZeroMemory( &m_aLight[2], sizeof(D3DLIGHT9));
	
	// ライト2のタイプの設定
	m_aLight[2].Type = D3DLIGHT_DIRECTIONAL;
	
	// ライト2の拡散光の設定
	m_aLight[2].Diffuse = D3DXCOLOR( 0.15f, 0.15f, 0.15f, 1.0f);
	m_aLight[2].Ambient = D3DXCOLOR( 0.2f, 0.2f, 0.2f, 1.0f);
	
	// ライト2の方向の設定
	vecDir = D3DXVECTOR3( 0.8f, 0.1f, 0.5f);
	D3DXVec3Normalize( (D3DXVECTOR3*)&m_aLight[2].Direction, &vecDir);
	
	// ライト2をレンダリングパイプラインに設定
	pDevice->SetLight( 2, &m_aLight[2]);

	// ライト2を使用使用状態に
	pDevice->LightEnable( 2, TRUE);

	// ライティングモードをON
	pDevice->SetRenderState( D3DRS_LIGHTING, TRUE);

	return S_OK;
}

void CLight::Uninit(void)
{

}