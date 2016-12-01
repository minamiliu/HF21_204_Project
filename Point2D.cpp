//============================================
//
// タイトル:	 HF
// プログラム名: trash.cpp
// 作成者:		 HAL東京ゲーム学科　yamaga keisuke
// 作成日:       2016/11/10
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "manager.h"
#include "input.h"
#include "point2D.h"
#include "debugproc.h"
//============================================
// マクロ定義
//============================================
#define GRAVITY_POINT (0.98f)

//=============================================================================
// 構造体定義
//=============================================================================
bool PointFlag = false;

//=============================================================================
//コンストラクタ
//=============================================================================
CPoint2D::CPoint2D()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CPoint2D::~CPoint2D()
{
	
}


//=============================================================================
// ポリゴンの初期化処理
//=============================================================================

HRESULT CPoint2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size,HWND hwnd)
{
	m_hwnd=hwnd;
	CScene2D::Init(pos, size);
	m_startPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_endPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_speed = D3DXVECTOR3(0.0f,0.0f,0.0f);
	return S_OK;
}




//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CPoint2D::Uninit(void)
{
	CScene2D::Uninit();
}


//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CPoint2D::Update(void)
{
	//// マウス座標の取得
	POINT po;
	GetCursorPos(&po);
	ScreenToClient(m_hwnd,&po);
	ShowCursor(FALSE);
	D3DXVECTOR3 pos ;
	if(CManager::GetInputMouse()->GetMouseLeftPress())
	{
	}

	if(CManager::GetInputMouse()->GetMouseLeftRelease())
	{
	}
	pos.x = po.x;
	pos.y = po.y;
	CPoint2D::SetPosition(D3DXVECTOR3(pos.x,pos.y,0.0f));
	CScene2D::Update();
	float print = CManager::GetInputMouse()->GetMouseAxisX();
	CDebugProc::Print("\nカーソルの場所.x.y:%f,%f",pos.x,pos.y);
	//PrintDebugProc("\nm_startPos.y:%f",m_startPos.y);
	//PrintDebugProc("\nm_speed.x:%f",m_speed.x);
	//PrintDebugProc("\nm_speed.y:%f",m_speed.y);
	//PrintDebugProc("\nprint:%f",print);
	
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CPoint2D::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ポリゴンの生成処理
//=============================================================================
CPoint2D *CPoint2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,HWND hwnd)
{
	CPoint2D *pPoint2D;
	pPoint2D = new CPoint2D;
	pPoint2D->Init(pos, size,hwnd);
	
	return pPoint2D;
}

