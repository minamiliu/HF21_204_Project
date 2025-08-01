//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: player2D.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/10/19
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "manager.h"
#include "input.h"
#include "player2D.h"
#include "bullet2D.h"
#include "debugproc.h"

//============================================
// マクロ定義
//============================================
#define TEXTURENAME "data/TEXTURE/player000.png"
#define TEXTURE_GORILLA "data/TEXTURE/gorilla.png"
//=============================================================================
// 構造体定義
//=============================================================================

//=============================================================================
//コンストラクタ
//=============================================================================
CPlayer2D::CPlayer2D()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CPlayer2D::~CPlayer2D()
{
	
}


//=============================================================================
// ポリゴンの初期化処理
//=============================================================================

HRESULT CPlayer2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	m_bGorillaMode = false;
	CScene2D::SetObjType(CScene::OBJTYPE_PLAYER);

	return S_OK;
}




//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CPlayer2D::Uninit(void)
{
	CScene2D::Uninit();

	CBullet2D::Unload();
}


//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CPlayer2D::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputMouse *pInputMouse = CManager::GetInputMouse();
	D3DXVECTOR3 pos = CPlayer2D::GetPosition();
	
	CScene2D::Update();
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CPlayer2D::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ポリゴンの生成処理
//=============================================================================
CPlayer2D *CPlayer2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CPlayer2D *pPlayer2D;
	pPlayer2D = new CPlayer2D;
	pPlayer2D->Init(pos, size);

	//テクスチャの割り当て
	pPlayer2D->Load( TEXTURENAME);
	
	return pPlayer2D;
}

void CPlayer2D::SetGorillaMode(void)
{
	m_bGorillaMode = true;
	SetTexture(TEXTURE_GORILLA);
}


bool CPlayer2D::GetGorillaMode(void)
{
	return m_bGorillaMode;
}

