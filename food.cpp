//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: food.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/10
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "food.h"
#include "foodIcon.h"

//============================================
// マクロ定義
//============================================
#define TEXTURE_TOMATO	"data/TEXTURE/LionGame/tomato.png"
#define TEXTURE_CARROT  "data/TEXTURE/LionGame/carrot.png"
#define TEXTURE_BANANA	"data/TEXTURE/LionGame/banana.png"
#define TEXTURE_MILK	"data/TEXTURE/LionGame/milk.png"
#define TEXTURE_CABBAGE	"data/TEXTURE/LionGame/cabbage.png"
#define TEXTURE_CURRY	"data/TEXTURE/LionGame/curry.png"
#define TEXTURE_EGG		"data/TEXTURE/LionGame/egg.png"
#define TEXTURE_ONION	"data/TEXTURE/LionGame/onion.png"
#define TEXTURE_POTATO	"data/TEXTURE/LionGame/potato.png"
#define TEXTURE_MEAT	"data/TEXTURE/LionGame/meat.png"


//============================================
// 静的メンバー変数の初期化
//============================================
LPDIRECT3DTEXTURE9 CFood::m_pTexture[TYPE_MAX] = {};
bool CFood::bClear[TYPE_MAX] = {false};
//=============================================================================
//コンストラクタ
//=============================================================================
CFood::CFood()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CFood::~CFood()
{
	
}


//=============================================================================
// ポリゴンの初期化処理
//=============================================================================

HRESULT CFood::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size, TYPE type)
{
	CBillBoard::Init( pos, size);
	SetObjType(OBJTYPE_L_FOOD);

	//初期状態
	m_type = type;
	bClear[type] = false;
	m_state = STATE_NORMAL;
	m_nCntState = 0;
	m_posInit = pos;
	m_fAngle = 0.0f;
	m_fTurn = 0.0f;
	m_fMoveY = 0.0f;

	//アイコン
	m_pIcon = CFoodIcon::Create(D3DXVECTOR3(100.0f, 100.0f, 0.0f), m_pTexture[type], (int)type);

	return S_OK;
}
//=============================================================================
//
//=============================================================================
void CFood::Uninit(void)
{
	CBillBoard::Uninit();
}
//=============================================================================
//
//=============================================================================
void CFood::Update(void)
{
	//状態更新
	switch( m_state)
	{
	case STATE_NORMAL:

		break;
	case STATE_FLYING:
		m_nCntState--;
		if( m_nCntState <= 0)
		{			
			//食材の破棄
			this->Uninit();
			return;
		}
		else
		{
			//座標
			D3DXVECTOR3 pos = this->GetPosition();
			m_fMoveY += 0.1f;
			pos.y += m_fMoveY;
			
			//回転
			m_fAngle += 0.01f;
			m_fTurn += m_fAngle; 
			pos.x = m_posInit.x + 30.0f * sinf( m_fTurn); 
			pos.z = m_posInit.z + 30.0f * cosf( m_fTurn);

			this->SetPosition(pos);
		}
		break;
	}	
}
//=============================================================================
//
//=============================================================================
void CFood::Draw(void)
{
	CBillBoard::Draw();
}
//=============================================================================
//
//=============================================================================
CFood *CFood::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, TYPE type)
{
	CFood *pFood;
	pFood = new CFood;

	pFood->Init(pos, size, type);

	//テクスチャの割り当て
	pFood->BindTexture( m_pTexture[type]);

	return pFood;
}
//=============================================================================
//テクスチャのロード
//=============================================================================
HRESULT CFood::Load(void)
{
	for (int cntType = 0; cntType < TYPE_MAX; cntType++)
	{
		LPCSTR strFileName;
		switch (cntType)
		{
		case TYPE_TOMATO:
			strFileName = TEXTURE_TOMATO;
			break;

		case TYPE_CARROT:
			strFileName = TEXTURE_CARROT;
			break;

		case TYPE_BANANA:
			strFileName = TEXTURE_BANANA;
			break;

		case TYPE_MILK:
			strFileName = TEXTURE_MILK;
			break;

		case TYPE_CABBAGE:
			strFileName = TEXTURE_CABBAGE;
			break;

		case TYPE_CURRY:
			strFileName = TEXTURE_CURRY;
			break;

		case TYPE_EGG:
			strFileName = TEXTURE_EGG;
			break;

		case TYPE_ONION:
			strFileName = TEXTURE_ONION;
			break;

		case TYPE_POTATO:
			strFileName = TEXTURE_POTATO;
			break;

		case TYPE_MEAT:
			strFileName = TEXTURE_MEAT;
			break;
		}

		if (m_pTexture[cntType] == NULL)
		{
			LPDIRECT3DDEVICE9 pDevice;
			pDevice = CManager::GetRenderer()->GetDevice();

			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice, strFileName, &m_pTexture[cntType]);
		}
	}

	return S_OK;
}

//=============================================================================
//テクスチャのアンロード
//=============================================================================
void CFood::Unload(void)
{
	//テクスチャの破棄
	for (int cntType = 0; cntType < TYPE_MAX; cntType++)
	{
		if (m_pTexture[cntType] != NULL)
		{
			m_pTexture[cntType]->Release();
			m_pTexture[cntType] = NULL;
		}
	}
}

//=============================================================================
//アイコンの取得
//=============================================================================
CFoodIcon* CFood::GetIcon(void)
{
	return m_pIcon;
}

//=============================================================================
//食材をゲット
//=============================================================================
void CFood::SetClear(void)
{
	bClear[m_type] = true;
}

//=============================================================================
//食材を全部ゲットしたか
//=============================================================================
bool CFood::isAllClear(void)
{
	//check
	for(int cntType = 0; cntType < TYPE_MAX; cntType++)
	{
		if( bClear[cntType] == false)
		{
			return false;
		}
	}
	return true;
}
//=============================================================================
// ステートを設定
//=============================================================================
void CFood::SetState(STATE state, int nCntState)
{
	m_state = state;
	m_nCntState = nCntState;
}
//=============================================================================
// ステートを取得
//=============================================================================
CFood::STATE CFood::GetState(void)
{
	return m_state;
}