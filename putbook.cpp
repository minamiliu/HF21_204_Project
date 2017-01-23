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
#include "putbook.h"
#include "debugproc.h"
#include "manager.h"
#include "renderer.h"
#include "mousePick.h"
#include "point3D.h"
#include "input.h"
#include "zebragame.h"
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
LPDIRECT3DTEXTURE9	CPutBook::m_pTexture[] ={};
LPD3DXMESH			CPutBook::m_pD3DXMesh[]={};			// メッシュ情報へのポインタ
LPD3DXBUFFER		CPutBook::m_pD3DXBuffMat	[]={};		// マテリアル情報へのポインタ
DWORD				CPutBook::m_nNumMat		[]={};					// マテリアル情報の数

int CPutBook::m_nNumber = 0;
D3DXVECTOR3 CPutBook::m_PutBookPos[MAX_BOOK] = {};

//=============================================================================
// 構造体定義
//=============================================================================

//=============================================================================
// 静的メンバ変数
//============================================================================

//=============================================================================
//コンストラクタ
//=============================================================================
CPutBook::CPutBook()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CPutBook::~CPutBook()
{
	
}


//=============================================================================
//
//=============================================================================
HRESULT CPutBook::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, int type)
{
	
	CSceneX::Init( m_PutBookPos[m_nNumber],  D3DXVECTOR3( D3DXToRadian(90),0.0f,D3DXToRadian(-90)), scl);

	BindXfile(type);
	SetObjType(OBJTYPE_BOOK); ;
	
	m_Timecnt = 0;
	m_nNumber++;
	return S_OK;
}

//=============================================================================
//xファイルの設定
//=============================================================================
void CPutBook::BindXfile(int type)	
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
HRESULT CPutBook::Load(void)
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
//
//=============================================================================
void CPutBook::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
//
//=============================================================================
void CPutBook::Update(void)
{
	D3DXVECTOR3 pos;

	pos = CSceneX::GetPosition();
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard	= CManager::GetInputKeyboard();
	if( pInputKeyboard ->GetKeyPress(DIK_W))
	{
		pos.z+=1.0f;
	}
	if( pInputKeyboard ->GetKeyPress(DIK_A))
	{
		pos.x-=1.0f;
	}
	if( pInputKeyboard ->GetKeyPress(DIK_S))
	{
		pos.z-=1.0f;
	}
	if( pInputKeyboard ->GetKeyPress(DIK_D))
	{
		pos.x+=1.0f;
	}
	if( pInputKeyboard ->GetKeyPress(DIK_Q))
	{
		pos.y+=1.0f;
	}
	if( pInputKeyboard ->GetKeyPress(DIK_E))
	{
		pos.y-=1.0f;
	}
	CSceneX::SetPosition(pos);
	CDebugProc::Print("\n本の場所.x.y.z:%f,%f,%f",pos.x,pos.y,pos.z);
	

}

//=============================================================================
//
//=============================================================================
void CPutBook::Draw(void)
{
	CSceneX::Draw();
}

//=============================================================================
//
//=============================================================================
CPutBook *CPutBook::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl,int type)
{
	CPutBook *pToy;
	pToy = new CPutBook;
	pToy->Init(pos, rot, scl, type);

	return pToy;
}

void CPutBook::InitPubBookPos(void)
{
	for (int yoko = 0 ;yoko < 5 ; yoko++)
	{
		m_PutBookPos[yoko]		= D3DXVECTOR3(-380.0f+ (yoko*25.0f),235.0f,375);
		m_PutBookPos[yoko + 5]  = D3DXVECTOR3(-380.0f+ (yoko*25.0f),150.0f,375);
		m_PutBookPos[yoko + 10] = D3DXVECTOR3(-380.0f+ (yoko*25.0f), 50.0f,375);
	}
}