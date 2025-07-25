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
#include "effect3D.h"
#include "score.h"
#include "zebragame.h"
#include "effectBoom.h"
#include "sound.h"
//============================================
// マクロ定義
//============================================
#define MODEL_TOY_BEAR    "data/MODEL/kuma.x"
#define MODEL_TOY_CAR "data/MODEL/toy_car.x"
#define MODEL_TOY_ROBOT "data/MODEL/robot.x"
#define MODEL_TOY_BLOCK "data/MODEL/block.x"
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
// 静的メンバ変数
//============================================================================
D3DXVECTOR3 CToy::Toyboxpos = D3DXVECTOR3(0.0f,0.0f,0.0f);
D3DXVECTOR3 CToy::Bookboxpos = D3DXVECTOR3(0.0f,0.0f,0.0f);

//=============================================================================
//コンストラクタ
//=============================================================================
CToy::CToy()
{
	GetBoxpos();
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
	CSceneX::Init( pos, rot, scl);
	
	BindXfile(m_nNumber%4);
	SetObjType(OBJTYPE_TOY); ;
	m_bPicked = false;
	m_bZebra= false;
	m_Move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_gravity = 0.1f;
	m_oldpos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_bBack = false;
	m_Timecnt = 0;
	m_nNumber ++;
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
//XFILEのロード
//=============================================================================
HRESULT CToy::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	for(int cntType = 0; cntType < TOYTYPE_MAX; cntType++)
	{
		LPCSTR strFileName;
		switch( cntType)
		{
			case TYPE_ROBOT:
			strFileName = MODEL_TOY_ROBOT;
			break;
			case TYPE_BLOCK:
			strFileName = MODEL_TOY_BLOCK;
			break;
			case TYPE_CAR:
			strFileName = MODEL_TOY_CAR;
			break;
			case TYPE_BEAR:
			strFileName = MODEL_TOY_BEAR;
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
void CToy::ChangePicked(bool pick, bool zebra)	
{
	D3DXVECTOR3 pos;
	pos = CSceneX::GetPosition();
	if(pick == true)
	{
		m_oldpos = pos;

		//SE
		CSound *pSound = CManager::GetSound();
		pSound->Play(CSound::SOUND_LABEL_SE_PICK);
	}
	m_bPicked = pick;
	m_bZebra = zebra ;
	if(m_bPicked == true && m_bZebra == true)
	{
		//現在位置と箱の位置から、速度を算出
		m_Move = Toyboxpos-pos;
		m_Move.y = 500.0f;
		m_Move = m_Move/100.0f;

		//SE
		CSound *pSound = CManager::GetSound();
		pSound->Play(CSound::SOUND_LABEL_SE_KICK);
	}

	//エフェクト
	CEffectBoom::Create( pos, D3DXVECTOR3(100, 20, 100), 5);
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
					
					Cursorpos.y = 30.0f;
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

		//エフェクト
		CEffect3D::Create( pos, D3DXVECTOR2( 20.0f, 20.0f), CEffect3D::TYPE_MARU, GREEN(1.0f), 0.02f);

		if(m_Timecnt == 99)
		{
			m_bZebra = false;
			m_bPicked = false;
			m_Timecnt = 0;
			CZebraGame::PutObj(true);

			//エフェクト
			CEffectBoom::Create( pos, D3DXVECTOR3( 200, 200, 200), 5);

			CZebraGame::GetScore()->AddScore(100);

			//SE
			CSound *pSound = CManager::GetSound();
			pSound->Play(CSound::SOUND_LABEL_SE_ITEM_GET);

			Uninit();
			return;
		}
	}
	else if(m_bPicked == false && m_bPicked == false)
	{
		//適当な場所
		if(pos.y>=0.0f)
		{
			pos.y -= 3.0f;
			CSceneX::SetPosition(pos);

			//SE
			CSound *pSound = CManager::GetSound();
			pSound->Play(CSound::SOUND_LABEL_SE_PUT);
		}
		//間違い
		if( pos.y <= 0.0f&&
			     pos.x > Bookboxpos.x - 120.0f
			  && pos.x < Bookboxpos.x + 120.0f
			  && pos.z > Bookboxpos.z - 70.0f  
			  && pos.z < Bookboxpos.z + 70.0f 
			)
		{
			//現在位置と箱の位置から、速度を算出
			m_Move = m_oldpos-pos;
			m_Move.y = 250.0f;
			m_Move = m_Move/50.0f;
			m_bBack = true;

			//SE
			CSound *pSound = CManager::GetSound();
			pSound->Play(CSound::SOUND_LABEL_SE_WRONG);
		}
		//正解
		if( pos.y <= 0.0f&&
			     pos.x > Toyboxpos.x - 150.0f 
			  && pos.x < Toyboxpos.x + 150.0f 
			  && pos.z > Toyboxpos.z - 150.0f  
			  && pos.z < Toyboxpos.z + 150.0f 
			)
		{
			CZebraGame::GetScore()->AddScore(100);
			CZebraGame::PutObj(true);

			//エフェクト
			CEffectBoom::Create( pos, D3DXVECTOR3( 200, 200, 200), 5);

			//SE
			CSound *pSound = CManager::GetSound();
			pSound->Play(CSound::SOUND_LABEL_SE_ITEM_GET);

			Uninit();
			return;
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
	if(Bookboxpos == D3DXVECTOR3(0,0,0) || Bookboxpos == D3DXVECTOR3(0,0,0))
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
}