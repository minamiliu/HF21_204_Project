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
bool CLight::abUse[MAX_LIGHT] = {false};

//=============================================================================
//コンストラクタ
//=============================================================================
CLight::CLight()
{
	m_pLight = NULL;

	for(int cntLight = 0; cntLight < MAX_LIGHT; cntLight++)
	{
		if(abUse[cntLight] == false)
		{
			abUse[cntLight] = true;
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

	m_pLight = new D3DLIGHT9;

	// D3DLIGHT9構造体を0でクリアする
	ZeroMemory( m_pLight, sizeof(D3DLIGHT9));

	// ライト0のタイプの設定
	m_pLight->Type = D3DLIGHT_DIRECTIONAL;
	
	// ライト0の拡散光の設定
	m_pLight->Diffuse = diffuse;
	m_pLight->Ambient = D3DXCOLOR( 0.2f, 0.2f, 0.2f, 0.2f);
	
	// ライト0の方向の設定
	D3DXVec3Normalize( (D3DXVECTOR3*)&m_pLight->Direction, &vecDir);

	// ライト0をレンダリングパイプラインに設定
	pDevice->SetLight( m_nID, m_pLight);

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
	if(m_pLight != NULL)
	{
		delete m_pLight;
		m_pLight = NULL;
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