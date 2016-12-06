//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: sceneX.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/15
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "sceneX.h"
#include "renderer.h"
#include "manager.h"
#include "camera.h"
#include "input.h"
#include "debugproc.h"

//============================================
// マクロ定義
//============================================
#define MODEL_FILENAME "data/MODEL/player.x"
#define VALUE_ROTATE	(D3DX_PI * 0.1f) 	// 回転量

//=============================================================================
// 構造体定義
//=============================================================================


//=============================================================================
//コンストラクタ
//=============================================================================
CSceneX::CSceneX()
{
	m_pTexture = NULL;		// テクスチャへのポインタ
	m_pD3DXMesh = NULL;		// メッシュ情報へのポインタ
	m_pD3DXBuffMat = NULL;	// マテリアル情報へのポインタ
	m_nNumMat = 0;			// マテリアル情報の数

	m_pos = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);		// モデルの位置
	m_rot = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);		// モデルの向き(回転)
	m_scl = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);		// モデルの大きさ(スケール)
	m_move = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);	// モデルの移動量

	m_rotTarget = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
	m_rotAngle = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);

	D3DXMatrixIdentity( &m_mtxWorld);
}

//=============================================================================
//デストラクタ
//=============================================================================
CSceneX::~CSceneX()
{
	
}


//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CSceneX::Init(void)
{
	return S_OK;
}

//=============================================================================
//
//=============================================================================
HRESULT CSceneX::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 位置・回転・スケールの初期設定
	m_pos = pos;
	m_rot = rot;
	m_scl = scl;
	m_speed = speed;

	// モデルに関する変数の初期化							
	m_pTexture = NULL;		// テクスチャへのポインタ
	m_pD3DXMesh = NULL;		// メッシュ情報へのポインタ
	m_pD3DXBuffMat = NULL;		// マテリアル情報へのポインタ
	m_nNumMat = 0;			// マテリアル情報の数

	// Xファイルの読み込み
	if(FAILED(D3DXLoadMeshFromX(
		MODEL_FILENAME,				// 読み込むモデルファイル名(Xファイル)
		D3DXMESH_SYSTEMMEM,			// メッシュの作成オプションを指定
		pDevice,					// IDirect3DDevice9インターフェイスへのポインタ
		NULL,						// 隣接性データを含むバッファへのポインタ
		&m_pD3DXBuffMat,		// マテリアルデータを含むバッファへのポインタ
		NULL,						// エフェクトインスタンスの配列を含むバッファへのポインタ
		&m_nNumMat,			// D3DXMATERIAL構造体の数
		&m_pD3DXMesh			// ID3DXMeshインターフェイスへのポインタのアドレス
		)))
	{
		return E_FAIL;
	}	


	return S_OK;
}

//=============================================================================
//
//=============================================================================
void CSceneX::Uninit(void)
{
	// テクスチャの開放
	if(m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// メッシュの開放
	if(m_pD3DXMesh != NULL)
	{
		m_pD3DXMesh->Release();
		m_pD3DXMesh = NULL;
	}
	// マテリアルの開放
	if(m_pD3DXBuffMat != NULL)
	{
		m_pD3DXBuffMat->Release();
		m_pD3DXBuffMat = NULL;
	}

	//オブジェクトの破棄
	Release();
}

//=============================================================================
//
//=============================================================================
void CSceneX::Update(void)
{
	CDebugProc::Print("\nposX = %f\n", m_pos.x);
	CDebugProc::Print("posZ = %f\n", m_pos.z);
	CDebugProc::Print("rotY = %f\n", m_rot.y);
}

//=============================================================================
//
//=============================================================================
void CSceneX::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity( &m_mtxWorld);
	
	// スケールを反映
	D3DXMatrixScaling( &mtxScl, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxScl);
	
	// 回転を反映
	D3DXMatrixRotationYawPitchRoll( &mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxRot);
	
	// 移動を反映
	D3DXMatrixTranslation( &mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxTranslate);
	
	// ワールドマトリックスの設定
	pDevice->SetTransform( D3DTS_WORLD, &m_mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);
	
	// マテリアル情報に対するポインタを取得
	pD3DXMat = (D3DXMATERIAL *)m_pD3DXBuffMat->GetBufferPointer();
	for(int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial( &pD3DXMat[nCntMat].MatD3D);
		// テクスチャの設定
		pDevice->SetTexture( 0, m_pTexture);
		// 描画
		m_pD3DXMesh->DrawSubset( nCntMat);
	}

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial( &matDef);
}

//=============================================================================
//
//=============================================================================
CSceneX *CSceneX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed)
{
	CSceneX *pSceneX;
	pSceneX = new CSceneX;
	pSceneX->Init(pos, rot, scl, speed);

	return pSceneX;
}

//=============================================================================
// 回転角度を取得
//=============================================================================
D3DXVECTOR3 CSceneX::Get2VecRotAngle( D3DXVECTOR3 rot, D3DXVECTOR3 rotTarget)
{
	float tAngle[3];
	D3DXVECTOR3 re;

	tAngle[0] = rotTarget.x - rot.x;
	tAngle[1] = rotTarget.y - rot.y;
	tAngle[2] = rotTarget.z - rot.z;

	for(int cntXYZ = 0; cntXYZ < 3; cntXYZ++)
	{
		if(tAngle[cntXYZ] > D3DX_PI)
		{
			tAngle[cntXYZ] -= 2 * D3DX_PI;
		}
		if(tAngle[cntXYZ] < -D3DX_PI)
		{
			tAngle[cntXYZ] += 2 * D3DX_PI;
		}		

//		tAngle[cntXYZ] = tAngle[cntXYZ] / DIVIDE_ROTATE;
		tAngle[cntXYZ] = tAngle[cntXYZ] / abs(tAngle[cntXYZ]) * VALUE_ROTATE;

	}

	re.x = tAngle[0];
	re.y = tAngle[1];
	re.z = tAngle[2];

	return re;
}

void CSceneX::UpdateModelMove(int nUp, int nDown, int nLeft, int nRight)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	D3DXVECTOR3 rotCamera = CManager::GetCamera()->GetCameraRot();


	//移動処理
	bool isKeyPressed = false;
	//斜め移動
	if( (pInputKeyboard->GetKeyPress(nRight) && pInputKeyboard->GetKeyPress(nUp)) ) //右上
	{
		m_rotTarget.y = rotCamera.y + D3DXToRadian(45.0f);
		if( m_rotTarget.y > D3DX_PI)
		{
			m_rotTarget.y -= D3DX_PI * 2.0f;
		}
		isKeyPressed = true;
	}
	else if((pInputKeyboard->GetKeyPress(nRight) && pInputKeyboard->GetKeyPress(nDown)) ) //右下
	{
		m_rotTarget.y = rotCamera.y + D3DXToRadian(135.0f);
		if( m_rotTarget.y > D3DX_PI)
		{
			m_rotTarget.y -= D3DX_PI * 2.0f;
		}
		isKeyPressed = true;
	}
	else if((pInputKeyboard->GetKeyPress(nLeft)  && pInputKeyboard->GetKeyPress(nUp))  ) //左上
	{
		m_rotTarget.y = rotCamera.y + D3DXToRadian(-45.0f);
		if( m_rotTarget.y < -D3DX_PI)
		{
			m_rotTarget.y += D3DX_PI * 2.0f;
		}
		isKeyPressed = true;
	}
	else if((pInputKeyboard->GetKeyPress(nLeft) && pInputKeyboard->GetKeyPress(nDown)) ) //左下
	{
		m_rotTarget.y = rotCamera.y + D3DXToRadian(-135.0f);
		if( m_rotTarget.y < -D3DX_PI)
		{
			m_rotTarget.y += D3DX_PI * 2.0f;
		}
		isKeyPressed = true;
	}
	else if(pInputKeyboard->GetKeyPress(nUp) )
	{
		m_rotTarget.y = rotCamera.y;
		isKeyPressed = true;
	}
	else if(pInputKeyboard->GetKeyPress(nDown) )
	{
		m_rotTarget.y = rotCamera.y + D3DXToRadian(180.0f);
		if( m_rotTarget.y > D3DX_PI)
		{
			m_rotTarget.y -= D3DX_PI * 2.0f;
		}
		isKeyPressed = true;
	}
	else if(pInputKeyboard->GetKeyPress(nLeft) )
	{
		m_rotTarget.y = rotCamera.y + D3DXToRadian(-90.0f);
		if( m_rotTarget.y < -D3DX_PI)
		{
			m_rotTarget.y += D3DX_PI * 2.0f;
		}
		isKeyPressed = true;
	}
	else if(pInputKeyboard->GetKeyPress(nRight) )
	{
		m_rotTarget.y = rotCamera.y + D3DXToRadian(90.0f);
		if( m_rotTarget.y > D3DX_PI)
		{
			m_rotTarget.y -= D3DX_PI * 2.0f;
		}
		isKeyPressed = true;
	}

	if(isKeyPressed == true)
	{
		//移動慣性の初期化
		m_move = D3DXVECTOR3( m_speed, 0.0f, m_speed);

		//時計回り、または逆時計回りを決める
		m_rotAngle =  Get2VecRotAngle( m_rot, m_rotTarget);
	}

	//回転慣性
	m_rotAngle.y *= 0.999f;

	//次の回転位置に到着したら
	float diff = abs(m_rot.y - m_rotTarget.y);
	if( diff > D3DX_PI)
	{
		diff -= D3DX_PI*2;
	}

	if(diff < VALUE_ROTATE)
	{
		m_rot.y = m_rotTarget.y;
		m_rotAngle.y = 0;
	}
	else //次の回転位置にまだ到着してない
	{
		m_rot.y += m_rotAngle.y;

		//モデル角度修正
		if( m_rot.y > D3DX_PI)
		{
			m_rot.y -= D3DX_PI*2;
		}
		else if(m_rot.y <= -D3DX_PI)
		{
			m_rot.y += D3DX_PI*2;
		}
	}	


	//回転していない時
	if( m_rotAngle.y == 0)
	{
		//移動
		m_pos.x += m_move.x * sinf( m_rot.y);
		m_pos.z += m_move.z * cosf( m_rot.y);

		//慣性処理
		m_move -= m_move * 0.25f;	
	}
}


D3DXVECTOR3 CSceneX::GetPosition(void)
{
	return m_pos;
}

D3DXVECTOR3 CSceneX::GetSize(void)
{
	return m_size;
}
void CSceneX::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}