﻿//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: billboard.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/12/15
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "billboard.h"
#include "renderer.h"
#include "manager.h"
#include "camera.h"

//============================================
// マクロ定義
//============================================
#define TEXTURENAME "data/TEXTURE/tomato.png"

//============================================
// 静的メンバー変数の初期化
//============================================

//=============================================================================
//コンストラクタ
//=============================================================================
CBillBoard::CBillBoard()
{

}

CBillBoard::CBillBoard(LAYER layer) : CScene3D( layer)
{

}
//=============================================================================
//デストラクタ
//=============================================================================
CBillBoard::~CBillBoard()
{
	
}


//=============================================================================
// ポリゴンの初期化処理
//=============================================================================

HRESULT CBillBoard::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	CScene3D::Init( pos, D3DXVECTOR3(0,0,0), 1, 1, size.x, size.y, true);
	return S_OK;
}
//=============================================================================
//
//=============================================================================
void CBillBoard::Uninit(void)
{
	CScene3D::Uninit();
}
//=============================================================================
//
//=============================================================================
void CBillBoard::Update(void)
{
	
}
//=============================================================================
//
//=============================================================================
void CBillBoard::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX *mtxView = CManager::GetCamera()->GetMtxView();

	//αテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	
	CScene3D::Draw(mtxView);

	// αテストを無効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
//=============================================================================
//
//=============================================================================
CBillBoard *CBillBoard::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	CBillBoard *pBoard;
	pBoard = new CBillBoard;

	pBoard->Init(pos, size);

	return pBoard;
}


