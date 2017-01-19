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
#include "point3D.h"
#include "debugproc.h"
#include "mousePick.h"
#include "toy.h"
#include "book.h"
//============================================
// マクロ定義
//============================================
#define GRAVITY_POINT (0.98f)
#define TEXTURENAME "data/TEXTURE/player000.png"
#define	TEX_PATTERN_DIVIDE_X		(2)								// アニメーションパターンのテクスチャ内での分割数(Ｘ方向)
#define	TEX_PATTERN_DIVIDE_Y		(1)								// アニメーションパターンのテクスチャ内での分割数(Ｙ方向)

#define	TEX_PATTERN_SIZE_X			(1.0f/TEX_PATTERN_DIVIDE_X)								// １パターンのテクスチャサイズ(Ｘ方向)(1.0f/X方向分割数)
#define	TEX_PATTERN_SIZE_Y			(1.0f/TEX_PATTERN_DIVIDE_Y)								// １パターンのテクスチャサイズ(Ｙ方向)(1.0f/Y方向分割数)

//=============================================================================
// 構造体定義
//=============================================================================
//bool PointFlag = false;
CScene *pScenePick = NULL;

 bool CPoint3D::m_zebra = false;
//=============================================================================
//コンストラクタ
//=============================================================================
CPoint3D::CPoint3D()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CPoint3D::~CPoint3D()
{
	
}


//=============================================================================
// ポリゴンの初期化処理
//=============================================================================

HRESULT CPoint3D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size,HWND hwnd)
{
	m_hwnd=hwnd;
	CScene2D::Init(pos, size);
	CScene2D::Load(TEXTURENAME);
	CScene2D::SetObjType(OBJTYPE_POINT);
	CScene2D::ChangeTextureAnime(1,D3DXVECTOR2(TEX_PATTERN_SIZE_X,TEX_PATTERN_SIZE_Y),D3DXVECTOR2(1,1));
	m_startPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_endPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_speed = D3DXVECTOR3(0.0f,0.0f,0.0f);

	//m_zebra = false;
	return S_OK;
}




//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CPoint3D::Uninit(void)
{
	CScene2D::Uninit();
}


//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CPoint3D::Update(void)
{
	//// マウス座標の取得
	POINT po;
	GetCursorPos(&po);
	
	ScreenToClient(m_hwnd,&po);
	ShowCursor(FALSE);
	D3DXVECTOR3 pos ;
	m_3Dpos = CMousePick::GetWorldPos(po);
	CDebugProc::Print("\nカーソルの場所3D.x.y.z:%f,%f,%f",m_3Dpos.x,m_3Dpos.y,m_3Dpos.z);
	
	
	if(CManager::GetInputMouse()->GetMouseLeftTrigger())
	{
		CScene2D::ChangeTextureAnime(1,D3DXVECTOR2(TEX_PATTERN_SIZE_X,TEX_PATTERN_SIZE_Y),D3DXVECTOR2(2,1));
		//トイの場所取得
		for(int Cnt=0; Cnt<MAX_SCENE ; Cnt++)
		{
			CScene *pScene ;
			pScene = CScene::GetScene(Cnt);
			if(pScene != NULL)
			{
				CScene::OBJTYPE type;
				type = pScene -> GetObjType();
				if(type == CScene::OBJTYPE_TOY )
				{
					D3DXVECTOR3 PosToy;
					D3DXVECTOR3 SizeToy = D3DXVECTOR3(50,50,50);
					PosToy = pScene ->GetPosition();

					//当たった
					if(	   m_3Dpos.x > PosToy.x - SizeToy.x/2.0f 
						&& m_3Dpos.x < PosToy.x + SizeToy.x/2.0f 
						&& m_3Dpos.z > PosToy.z - SizeToy.z/2.0f  
						&& m_3Dpos.z < PosToy.z + SizeToy.z/2.0f 
						)
					{
						pScenePick = pScene;
						((CToy*)pScene)->ChangePicked(true,m_zebra);
						
						return;
					}
					
				}
				if(type == CScene::OBJTYPE_BOOK )
				{
					D3DXVECTOR3 PosToy;
					D3DXVECTOR3 SizeToy = D3DXVECTOR3(50,50,50);
					PosToy = pScene ->GetPosition();

					//当たった
					if(	   m_3Dpos.x > PosToy.x - SizeToy.x/2.0f 
						&& m_3Dpos.x < PosToy.x + SizeToy.x/2.0f 
						&& m_3Dpos.z > PosToy.z - SizeToy.z/2.0f  
						&& m_3Dpos.z < PosToy.z + SizeToy.z/2.0f 
						)
					{
						pScenePick = pScene;
						((CBook*)pScene)->ChangePicked(true,m_zebra);
						
						return;
					}
					
				}
			}
			
		}
		
	}
	if(CManager::GetInputMouse()->GetMouseLeftRelease())
	{
		
		CScene2D::ChangeTextureAnime(1,D3DXVECTOR2(TEX_PATTERN_SIZE_X,TEX_PATTERN_SIZE_Y),D3DXVECTOR2(1,1));
			if(pScenePick != NULL)
			{
	
				((CToy*)pScenePick)->ChangePicked(false,m_zebra);
				pScenePick = NULL;
				return;
	
			}
		
	}
	if(CManager::GetInputMouse()->GetMouseRightTrigger())
	{
		ChangeZebra();

	}
	if(m_zebra == true)
	{
		CDebugProc::Print("\nゼブラ");
	}
	pos.x = po.x;
	pos.y = po.y;
	CPoint3D::SetPosition(D3DXVECTOR3(pos.x,pos.y,0.0f));
	CScene2D::Update();
	float print = CManager::GetInputMouse()->GetMouseAxisX();
	CDebugProc::Print("\nカーソルの場所.x.y:%f,%f",pos.x,pos.y);
	
	
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CPoint3D::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ポリゴンの生成処理
//=============================================================================
CPoint3D *CPoint3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,HWND hwnd)
{
	CPoint3D *pPoint3D;
	pPoint3D = new CPoint3D;
	pPoint3D->Init(pos, size,hwnd);
	
	return pPoint3D;
}
//=============================================================================
// ポリゴンの座標取得
//=============================================================================
D3DXVECTOR3 CPoint3D::Get3DPosition(void)
{
	return m_3Dpos;
}

//=============================================================================
//ゼブラモード
//=============================================================================
void CPoint3D::ChangeZebra(void)
{
	m_zebra = !m_zebra;
}
