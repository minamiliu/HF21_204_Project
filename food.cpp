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
#define TEXTURE_TOMATO	"data/TEXTURE/tomato.png"
#define TEXTURE_CABBAGE "data/TEXTURE/cabbage.png"
#define TEXTURE_MEAT	"data/TEXTURE/meat.png"

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

	m_type = type;
	bClear[type] = false;

	//アイコン
	m_pIcon = CFoodIcon::Create(D3DXVECTOR3( 50.0f + type * 100.0f, 50.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), m_pTexture[type]);

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

		case TYPE_CABBAGE:
			strFileName = TEXTURE_CABBAGE;
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
