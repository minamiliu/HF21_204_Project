//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: playerX.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/15
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "book.h"
#include "debugproc.h"
#include "manager.h"
#include "renderer.h"
#include "mousePick.h"
#include "point3D.h"
#include "input.h"
#include "zebragame.h"
#include "putbook.h"
//============================================
// マクロ定義
//============================================
#define MODEL_BOOK_GREEN "data/MODEL/book_green.x"
#define MODEL_BOOK_BLUE "data/MODEL/book_blue.x"
#define MODEL_BOOK_RED "data/MODEL/book_red.x"
#define MODEL_BOOK_YELLOW "data/MODEL/book_yellow.x"
#define VALUE_ROTATE	(D3DX_PI * 0.1f) 	// 回転量

//============================================
// 静的メンバ変数の初期化
//============================================
LPDIRECT3DTEXTURE9	CBook::m_pTexture[] ={};
LPD3DXMESH			CBook::m_pD3DXMesh[]={};			// メッシュ情報へのポインタ
LPD3DXBUFFER		CBook::m_pD3DXBuffMat	[]={};		// マテリアル情報へのポインタ
DWORD				CBook::m_nNumMat		[]={};					// マテリアル情報の数
//HRESULT CBook::LoadXfile(LPCSTR strFileName, int nCnt);
int CBook::m_nNumber = 0;
//=============================================================================
// 構造体定義
//=============================================================================

//=============================================================================
// 静的メンバ変数
//============================================================================
D3DXVECTOR3 CBook::Toyboxpos = D3DXVECTOR3(0.0f,0.0f,0.0f);
D3DXVECTOR3 CBook::Bookboxpos = D3DXVECTOR3(0.0f,0.0f,0.0f);

//=============================================================================
//コンストラクタ
//=============================================================================
CBook::CBook()
{
	GetBoxpos();
}

//=============================================================================
//デストラクタ
//=============================================================================
CBook::~CBook()
{
	
}


//=============================================================================
//
//=============================================================================
HRESULT CBook::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed)
{
	
	CSceneX::Init( pos, rot, scl);
	
	BindXfile(m_nNumber%4);
	SetObjType(OBJTYPE_BOOK); ;
	m_bPicked = false;
	m_bZebra= false;
	m_Move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_gravity = 0.1f;
	m_oldpos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_bBack = false;
	m_Timecnt = 0;
	m_nID = m_nNumber;
	m_nNumber++;
	
	return S_OK;
}

//=============================================================================
//xファイルの設定
//=============================================================================
void CBook::BindXfile(int type)	
{
	CSceneX::BindXfile( m_pTexture	[type],
					 m_pD3DXMesh	[type],	
					 m_pD3DXBuffMat[type],	
					 m_nNumMat		[type]
	);
}
//=============================================================================
//XFILEのロード
//=============================================================================
HRESULT CBook::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	for(int cntType = 0; cntType < BOOKTYPE_MAX; cntType++)
	{
		LPCSTR strFileName;
		switch( cntType)
		{
			case TYPE_GREEN:
			strFileName = MODEL_BOOK_GREEN;
			break;
			case TYPE_RED:
			strFileName = MODEL_BOOK_RED;
			break;
			case TYPE_YELLOW:
			strFileName = MODEL_BOOK_YELLOW;
			break;
			case TYPE_BLUE:
			strFileName = MODEL_BOOK_BLUE;
			break;
		}

		if( m_pTexture[cntType] == NULL &&
			m_pD3DXMesh[cntType] == NULL &&
			m_pD3DXBuffMat[cntType] == NULL &&
			m_nNumMat[cntType] == 0
			)
		{
			// Xファイルの読み込み
			if(FAILED(D3DXLoadMeshFromX(
				strFileName,			// 読み込むモデルファイル名(Xファイル)
				D3DXMESH_SYSTEMMEM,		// メッシュの作成オプションを指定
				pDevice,				// IDirect3DDevice9インターフェイスへのポインタ
				NULL,					// 隣接性データを含むバッファへのポインタ
				&m_pD3DXBuffMat[cntType],	// マテリアルデータを含むバッファへのポインタ
				NULL,					// エフェクトインスタンスの配列を含むバッファへのポインタ
				&m_nNumMat[cntType],	// D3DXMATERIAL構造体の数
				&m_pD3DXMesh[cntType]	// ID3DXMeshインターフェイスへのポインタのアドレス
				)))
			{
				return E_FAIL;
			}
		
		}
	}

	return S_OK;
}

//=============================================================================
//クリックされたとき
//=============================================================================
void CBook::ChangePicked(bool pick, bool zebra)	
{
	D3DXVECTOR3 pos;
	pos = CSceneX::GetPosition();
	if(pick == true)
	{
		m_oldpos = pos;
	}
	m_bPicked = pick;
	m_bZebra = zebra ;
	if(m_bPicked == true && m_bZebra == true)
	{
		//現在位置と箱の位置から、速度を算出
		m_Move = Bookboxpos-pos;
		m_Move.y = 500.0f;
		m_Move = m_Move/100.0f;
	}
}
//=============================================================================
//
//=============================================================================
void CBook::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
//
//=============================================================================
void CBook::Update(void)
{
	D3DXVECTOR3 pos;
	pos = CSceneX::GetPosition();
	
	
	CDebugProc::Print("\n本の場所.x.y.z:%f,%f,%f",pos.x,pos.y,pos.z);
	if(m_bPicked == true && m_bZebra == false)
	{
		//カーソルの位置を取得
		for(int Cnt=0; Cnt<MAX_SCENE ; Cnt++)
		{
			CScene *pScene;
			pScene = CScene::GetScene(Cnt);
			if(pScene != NULL)
			{
				CScene::OBJTYPE type;
				type = pScene -> GetObjType();
				if(type == CScene::OBJTYPE_POINT)
				{
					D3DXVECTOR3 Cursorpos;
					Cursorpos = ((CPoint3D*)pScene)->Get3DPosition();
					
					
					pos.x = Cursorpos.x;
					pos.z = Cursorpos.z;

					if(pos.x <= -400.0f)
					{
						pos.x = -400.0f;
					}
					if(pos.x >= 400.0f)
					{
						pos.x = 400.0f;
					}
					if(pos.z >= 400.0f)
					{
						D3DXVECTOR3 move ;
						CInputMouse *pInputMouse;
						pInputMouse = CManager::GetInputMouse();
						move.x = pInputMouse ->GetMouseAxisX();
						move.y = pInputMouse ->GetMouseAxisY();
						
						/*POINT po;
						GetCursorPos(&po);
						pos.y = -po.y+300.0f;*/
						//Cursorpos = ((CPoint3D*)pScene)->Get3DPosition();
						pos.x += move.x;
						pos.y -= move.y;

						pos.z = 400.0f;
						
					}
					else 
					{
						pos.y = 20.0f;
					}
					CSceneX::SetPosition(pos);
					return;
				}
			}
		}	
	}
	//バックモード
	if( m_bZebra == false && m_bBack == true)
	{
		m_Move.y -= m_gravity;
		m_Timecnt++;
		pos += m_Move;
		CSceneX::SetPosition(pos);
		if(m_Timecnt == 50)
		{
			m_Timecnt = 0;
			m_bBack = false;
		}
	}
	//ゼブラモード
	if( m_bZebra == true)
	{
		m_Move.y -= m_gravity;
		pos += m_Move;
		m_Timecnt ++;
		CSceneX::SetPosition(pos);
		if(m_Timecnt == 99)
		{
			m_bZebra = false;
			m_bPicked = false;
			m_Timecnt = 0;
			CZebraGame::PutObj(false);
			CPutBook::Create( D3DXVECTOR3(0.0f, 10.0f, 0.0f), D3DXVECTOR3( 0.0f,0.0f, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f), m_nID%4);

			Uninit();
		}
	}
	else if(m_bPicked == false && m_bPicked == false)
	{
		//適当な場所
		if(pos.y>=0.0f)
		{
			pos.y -= 3.0f;
			CSceneX::SetPosition(pos);
		}
		//間違い
		if( pos.y <= 0.0f&&
			     pos.x > Toyboxpos.x - 150.0f 
			  && pos.x < Toyboxpos.x + 150.0f 
			  && pos.z > Toyboxpos.z - 150.0f  
			  && pos.z < Toyboxpos.z + 150.0f 
			)
		{
			//現在位置と箱の位置から、速度を算出
			m_Move = m_oldpos-pos;
			m_Move.y = 250.0f;
			m_Move = m_Move/50.0f;
			m_bBack = true;
		}
		//正解
		
		if(      pos.x > Bookboxpos.x - 120.0f 
			  && pos.x < Bookboxpos.x + 120.0f 
			  && pos.z > Bookboxpos.z - 70.0f  
			  && pos.z < Bookboxpos.z + 70.0f 
			)
		{
			CZebraGame::PutObj(false);
			CPutBook::Create( D3DXVECTOR3(0.0f, 10.0f, 0.0f), D3DXVECTOR3( 0.0f,0.0f, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f), m_nID%4);

			Uninit();
		}
	}
	
}

//=============================================================================
//
//=============================================================================
void CBook::Draw(void)
{
	CSceneX::Draw();
}

//=============================================================================
//
//=============================================================================
CBook *CBook::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed)
{
	CBook *pToy;
	pToy = new CBook;
	pToy->Init(pos, rot, scl, speed);

	return pToy;
}

//=============================================================================
////箱の位置を取得
//=============================================================================
void CBook::GetBoxpos(void)
{
	for(int Cnt=0; Cnt<MAX_SCENE ; Cnt++)
	{
		CScene *pScene;
		pScene = CScene::GetScene(Cnt);
		if(pScene != NULL)
		{
			CScene::OBJTYPE type;
			type = pScene -> GetObjType();
			if(type == CScene::OBJTYPE_TOYBOX)
			{
				Toyboxpos = pScene -> GetPosition();
			}
			type = pScene -> GetObjType();
			if(type == CScene::OBJTYPE_BOOKBOX)
			{
				Bookboxpos = pScene -> GetPosition();
			}
		}
	}	
}