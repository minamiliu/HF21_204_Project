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
#include "toy.h"
#include "debugproc.h"
#include "manager.h"
#include "renderer.h"
#include "mousePick.h"
#include "point3D.h"
#include "score.h"
#include "zebragame.h"
//============================================
// マクロ定義
//============================================
#define MODEL_BOOK "data/MODEL/book.x"
#define MODEL_TOY_CAR "data/MODEL/toy_car.x"
#define MODEL_FILENAME "data/MODEL/player.x"
#define VALUE_ROTATE	(D3DX_PI * 0.1f) 	// 回転量

//============================================
// 静的メンバ変数の初期化
//============================================
LPDIRECT3DTEXTURE9	CToy::m_pTexture[] ={};
LPD3DXMESH			CToy::m_pD3DXMesh[]={};			// メッシュ情報へのポインタ
LPD3DXBUFFER		CToy::m_pD3DXBuffMat	[]={};		// マテリアル情報へのポインタ
DWORD				CToy::m_nNumMat		[]={};					// マテリアル情報の数
//HRESULT CToy::LoadXfile(LPCSTR strFileName, int nCnt);
int CToy::m_nNumber = 0;
//=============================================================================
// 構造体定義
//=============================================================================

//=============================================================================
// グローバル変数
//============================================================================
D3DXVECTOR3 boxpos;
//=============================================================================
//コンストラクタ
//=============================================================================
CToy::CToy()
{
	
}

//=============================================================================
//デストラクタ
//=============================================================================
CToy::~CToy()
{
	
}


//=============================================================================
//
//=============================================================================
HRESULT CToy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed)
{
	m_nNumber++;
	CSceneX::Init( pos, rot, scl, MODEL_FILENAME);

	LoadXfile(MODEL_FILENAME,TYPE_ROBOT);
	LoadXfile(MODEL_BOOK,TYPE_BLOCK);
	LoadXfile(MODEL_TOY_CAR,TYPE_CAR);
	LoadXfile(MODEL_FILENAME,TYPE_BEAR);
	// += m_nNumber%4;
	BindXfile(m_nNumber%4);
	SetObjType(OBJTYPE_TOY); ;
	m_bPicked = false;
	m_bZebra= false;
	m_Move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	return S_OK;
}

//=============================================================================
//xファイルの設定
//=============================================================================
void CToy::BindXfile(int type)	
{
	CSceneX::BindXfile( m_pTexture	[type],
					 m_pD3DXMesh	[type],	
					 m_pD3DXBuffMat[type],	
					 m_nNumMat		[type]
	);
}
//=============================================================================
//(オーバーロード
//=============================================================================
HRESULT CToy::LoadXfile(LPCSTR strFileName, int nCnt)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	
	// モデルに関する変数の初期化							
	CToy::m_pTexture[nCnt] = NULL;		// テクスチャへのポインタ
	CToy::m_pD3DXMesh[nCnt] = NULL;		// メッシュ情報へのポインタ
	CToy::m_pD3DXBuffMat[nCnt] = NULL;		// マテリアル情報へのポインタ
	CToy::m_nNumMat[nCnt] = 0;			// マテリアル情報の数
	// Xファイルの読み込み
	if(FAILED(D3DXLoadMeshFromX(
		MODEL_FILENAME,				// 読み込むモデルファイル名(Xファイル)
		D3DXMESH_SYSTEMMEM,			// メッシュの作成オプションを指定
		pDevice,					// IDirect3DDevice9インターフェイスへのポインタ
		NULL,						// 隣接性データを含むバッファへのポインタ
		&m_pD3DXBuffMat[nCnt],		// マテリアルデータを含むバッファへのポインタ
		NULL,						// エフェクトインスタンスの配列を含むバッファへのポインタ
		&m_nNumMat[nCnt],			// D3DXMATERIAL構造体の数
		&m_pD3DXMesh[nCnt]			// ID3DXMeshインターフェイスへのポインタのアドレス
		)))
	{
		return E_FAIL;
	}	


	return S_OK;
}

//=============================================================================
//クリックされたとき
//=============================================================================
void CToy::ChangePicked(bool pick, bool zebra)	
{
	D3DXVECTOR3 pos;
	pos = CSceneX::GetPosition();
	m_bPicked = pick;
	m_bZebra = zebra ;
	if(m_bPicked == true && m_bZebra == true)
	{
		
		//現在位置と箱の位置から、速度を算出

		m_Move = boxpos-pos;
	}
}
//=============================================================================
//
//=============================================================================
void CToy::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
//
//=============================================================================
void CToy::Update(void)
{
	D3DXVECTOR3 pos;
	pos = CSceneX::GetPosition();
	CScore *pScore;
	pScore = CZebraGame::GetScoreP();
	GetBoxpos();
	CDebugProc::Print("\nトイの場所.x.y.z:%f,%f,%f",pos.x,pos.y,pos.z);
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
					
					Cursorpos.y = 20.0f;
					pos = Cursorpos;
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
						pos.z = 400.0f;
					}
					CSceneX::SetPosition(pos);
					return;
				}
			}
		}	
	}
	//ゼブラモード
	if( m_bZebra == true)
	{
		m_Move.y = 30.0f;
		pos += m_Move/100.0f;
		CSceneX::SetPosition(pos);
		if(boxpos.x<pos.x)
		{
			m_bZebra = false;
		}
	}
	else if(m_bPicked == false)
	{
		if(pos.y>=0.0f)
		{
			pos.y -= 3.0f;
			CSceneX::SetPosition(pos);
		}
		if(pos.z >200.0 && pos.y <= 0.0f)
		{
			pScore -> AddScore (100);
			Uninit();
		}
	}
}

//=============================================================================
//
//=============================================================================
void CToy::Draw(void)
{
	CSceneX::Draw();
}

//=============================================================================
//
//=============================================================================
CToy *CToy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed)
{
	CToy *pToy;
	pToy = new CToy;
	pToy->Init(pos, rot, scl, speed);

	return pToy;
}

//=============================================================================
////箱の位置を取得
//=============================================================================
void CToy::GetBoxpos(void)
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
				boxpos = pScene -> GetPosition();
			}
		}
	}	
}