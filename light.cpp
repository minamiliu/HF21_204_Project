//============================================
//
// タイトル:	 未来創造展チーム204
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
CLight *CLight::m_apLight[MAX_LIGHT] = {};

//=============================================================================
//コンストラクタ
//=============================================================================
CLight::CLight()
{
	m_pD3DLight = NULL;

	for(int cntLight = 0; cntLight < MAX_LIGHT; cntLight++)
	{
		if(m_apLight[cntLight] == NULL)
		{
			m_apLight[cntLight] = this;
			m_nID = cntLight;
			break;
		}
	}
}

//=============================================================================
//デストラクタ
//=============================================================================
CLight::~CLight()
{
	
}

//=============================================================================
//ライト初期化
//=============================================================================
HRESULT CLight::Init(D3DXVECTOR3 vecDir, D3DXCOLOR diffuse)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	m_pD3DLight = new D3DLIGHT9;

	// D3DLIGHT9構造体を0でクリアする
	ZeroMemory( m_pD3DLight, sizeof(D3DLIGHT9));

	// ライト0のタイプの設定
	m_pD3DLight->Type = D3DLIGHT_DIRECTIONAL;
	
	// ライト0の拡散光の設定
	m_pD3DLight->Diffuse = diffuse;
	m_pD3DLight->Ambient = D3DXCOLOR( 0.2f, 0.2f, 0.2f, 0.2f);
	
	// ライト0の方向の設定
	D3DXVec3Normalize( (D3DXVECTOR3*)&m_pD3DLight->Direction, &vecDir);

	// ライト0をレンダリングパイプラインに設定
	pDevice->SetLight( m_nID, m_pD3DLight);

	// ライト0を使用使用状態に
	pDevice->LightEnable( m_nID, TRUE);

	return S_OK;
}

//=============================================================================
//ライト解放
//=============================================================================
void CLight::Uninit(void)
{
	// テクスチャの破棄
	if(m_pD3DLight != NULL)
	{
		delete m_pD3DLight;
		m_pD3DLight = NULL;
	}
}
//=============================================================================
//ライトの生成
//=============================================================================
CLight *CLight::Create(D3DXVECTOR3 vecDir, D3DXCOLOR diffuse)
{
	CLight *pLight = new CLight;
	pLight->Init( vecDir, diffuse);

	return pLight;
}
//=============================================================================
//総ライトを有効にする
//=============================================================================
void CLight::SetAllLightOn(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ライティングモードをON
	pDevice->SetRenderState( D3DRS_LIGHTING, TRUE);
}

//=============================================================================
//総ライトを破棄する
//=============================================================================
void CLight::ReleaseAll(void)
{
	for(int cntLight = 0; cntLight < MAX_LIGHT; cntLight++)
	{
		if(m_apLight[cntLight] != NULL)
		{
			m_apLight[cntLight]->Uninit();
			m_apLight[cntLight] = NULL;
		}
	}
}