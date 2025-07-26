/*******************************************************************************
* タイトル:		タイトルオブジェクト
* プログラム名:	titleObj.cpp
* 作成者:		小林玲雄
* 作成日:		2017/01/09
********************************************************************************
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "titleObj.h"
#include "manager.h"
#include "scene2D.h"

/*******************************************************************************
* マクロ定義
*******************************************************************************/

/*******************************************************************************
* クラス定義
*******************************************************************************/
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// 静的
//*****************************************************************************
LPDIRECT3DTEXTURE9 CTitleObj::m_pTexture[MAX_TITLE_OBJ] = {};

char *CTitleObj::g_TitleObjTex[MAX_TITLE_OBJ] = 
{
	{"data/TEXTURE/Savannah/bg/titleBg.png"},
	{"data/TEXTURE/Savannah/logo/logo.png"},
	{"data/TEXTURE/Savannah/gorilla/gori.png"},
	{"data/TEXTURE/Savannah/zebra/zebra.png"},
	{"data/TEXTURE/Savannah/lion/lion.png"},
	{"data/TEXTURE/Savannah/start/start.png"}
};

bool CTitleObj::bScl = false;
int CTitleObj::alpha = 0;
//=============================================================================
// コンストラクタ
//=============================================================================
CTitleObj :: CTitleObj()
{
	m_time = 0;
	m_animPat = 0;
}
//=============================================================================
// デストラクタ
//=============================================================================
CTitleObj :: ~CTitleObj()
{
}
CTitleObj* CTitleObj::Create(TITLE_OBJ_TYPE nType,D3DXVECTOR3 pos,D3DXVECTOR3 rot,D3DXVECTOR3 size)
{
	CTitleObj *pTitleObj;
	pTitleObj = new CTitleObj;
	pTitleObj->Init(nType,pos,rot,size);

	//テクスチャの割り当て
	pTitleObj->Load(g_TitleObjTex[nType]);
	return pTitleObj;
}
//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CTitleObj :: Init(void)
{
	CScene2D::Init();

	return S_OK;
}
//=============================================================================
// ポリゴンの初期化処理(オーバーロード)
//=============================================================================
HRESULT CTitleObj :: Init(TITLE_OBJ_TYPE nType,D3DXVECTOR3 pos,D3DXVECTOR3 rot,D3DXVECTOR3 size)
{
	CScene2D::Init(pos,size,D3DXVECTOR2(1,1));
	m_type = nType;

	return S_OK;
}
//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CTitleObj :: Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CTitleObj :: Update(void)
{
	D3DXVECTOR3 pos = GetPosition();//ポジション受け取る
	D3DXVECTOR3 size = GetSize();

	m_time ++;

	switch(m_type)
	{
	case TITLE_BG:
		if(bScl == true)
		{
			CScene2D::Scl(0.001,CScene2D::SCL_LEFT);
		}
		break;
	case TITLE_LOGO:
		if(bScl == false)
		{
			alpha = 0;
		}
		else
		{
			if(alpha < 255)
			{
				alpha += 5;
			}
			if(alpha > 255)
			{
				alpha = 255;
			}
		}
		CScene2D::SetAlpha(alpha);
		break;
	case TITLE_GORIRA:
		if(m_time%20 == 0)
		{
			m_animPat++;
		}
		if(pos.x > 340)
		{
			pos.x-=2;
		}
		CScene2D::SetTexture(4,1,m_animPat);
		break;
	case TITLE_ZEBRA:
		if(m_time%8 == 0)
		{
			m_animPat++;
		}
		if(pos.x > 640)
		{
			pos.x-=2;
		}
		CScene2D::SetTexture(7,1,m_animPat);
		break;
	case TITLE_LION:
		if(m_time%15 == 0)
		{
			m_animPat++;
		}
		if(pos.x > 940)
		{
			pos.x-=2;
		}
		else
		{
			bScl = true;
		}
		CScene2D::SetTexture(4,1,m_animPat);
		break;
	case TITLE_START:
		if(bScl == false)
		{
			alpha = 0;
		}
		else
		{
			if(alpha < 255)
			{
				alpha += 5;
			}
			if(alpha > 255)
			{
				alpha = 255;
			}
		}
		if(alpha == 255)
		{
			if(m_time%15 == 0)
			{
				m_animPat++;
			}
		}
		CScene2D::SetTexture(1,4,m_animPat);
		break;
	}

	this->CTitleObj::SetPosition(pos);//ポジション返す
}
//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CTitleObj :: Draw(void)
{
	CScene2D::Draw();
}
