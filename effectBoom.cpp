//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: bg.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/12/07
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "effectBoom.h"
#include "effect3D.h"
//============================================
// マクロ定義
//============================================

//=============================================================================
// 構造体定義
//=============================================================================
D3DXCOLOR CEffectBoom::m_paraColor[] =
{
	WHITE(1.0f),
	RED(1.0f),
	ORANGE(1.0f),
	YELLOW(1.0f),
	GREEN(1.0f),
	SYAN(1.0f),	
	BLUE(1.0f),	
	MASENTA(1.0f),	
	PINK(1.0f),
	PURPLE(1.0f),
	LIME(1.0f),
	SUN(1.0f),	
	SKY(1.0f),
	BIAGE(1.0f),
};

//=============================================================================
//コンストラクタ
//=============================================================================
CEffectBoom::CEffectBoom() : CScene(LAYER_EFFECT)
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CEffectBoom::~CEffectBoom()
{
	
}


//=============================================================================
// 背景の初期化処理
//=============================================================================
HRESULT CEffectBoom::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, float speed)
{	
	m_pos = pos;
	m_size = size;
	m_fSpeed = speed;

	float fAngle = D3DX_PI*2 / MAX_EFFECT;
	for(int cntEffect = 0; cntEffect < MAX_EFFECT; cntEffect++)
	{	
		//start
		m_posNow[cntEffect] = pos;

		//Goal
		m_posGoal[cntEffect].x = pos.x + m_size.x * cosf(fAngle * cntEffect);
		m_posGoal[cntEffect].z = pos.z + m_size.z * sinf(fAngle * cntEffect);
		m_posGoal[cntEffect].y = size.y;

		//front vector
		D3DXVECTOR3 vec = m_posGoal[cntEffect] - pos;
		D3DXVec3Normalize(&vec, &vec);
		m_front[cntEffect] = vec * speed;
	}

	return S_OK;
}

//=============================================================================
// 背景の終了処理
//=============================================================================
void CEffectBoom::Uninit(void)
{
	//２重管理のないように注意

	//オブジェクトの破棄
	Release();
}


//=============================================================================
// 背景の更新処理
//=============================================================================
void CEffectBoom::Update(void)
{
	bool bGoal = false;

	//２重管理のないように注意
	for(int cntEffect = 0; cntEffect < MAX_EFFECT; cntEffect++)
	{
		//エフェクト
		CEffect3D::Create( m_posNow[cntEffect], D3DXVECTOR2( 15.0f, 15.0f), CEffect3D::TYPE_MARU, m_paraColor[cntEffect], 0.125f);

		m_posNow[cntEffect] += m_front[cntEffect];

		if( m_posNow[cntEffect] == m_posGoal[cntEffect] || m_posNow[cntEffect].y >= m_posGoal[cntEffect].y)
		{
			bGoal = true;
		}
	}

	if(bGoal == true) this->Uninit();
}

//=============================================================================
// 背景の描画処理
//=============================================================================
void CEffectBoom::Draw(void)
{
	//２重管理のないように注意
}

//=============================================================================
// 背景の生成処理
//=============================================================================
CEffectBoom *CEffectBoom::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float speed)
{
	CEffectBoom *pEffect;
	pEffect = new CEffectBoom;
	pEffect->Init(pos, size, speed);

	return pEffect;
}
//=============================================================================
//座標を取得
//=============================================================================
D3DXVECTOR3 CEffectBoom::GetPosition(void)
{
	return m_pos;
}
//=============================================================================
//サイズを取得
//=============================================================================
D3DXVECTOR3 CEffectBoom::GetSize(void)
{
	return m_size;
}
//=============================================================================
//座標を設定
//=============================================================================
void CEffectBoom::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}