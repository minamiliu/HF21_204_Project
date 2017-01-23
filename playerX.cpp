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
#include "manager.h"
#include "renderer.h"
#include "playerX.h"
#include "input.h"
#include "camera.h"
#include "debugproc.h"
#include "collision.h"
#include "score.h"
#include "lionGame.h"
#include "shadow.h"
#include "food.h"
#include "foodIcon.h"
#include "limbX.h"
#include "meshWall.h"
#include "cubeX.h"
#include "enemyX.h"

//============================================
// マクロ定義
//============================================
#define MODEL_FILENAME_BODY			"data/MODEL/mom_body.x"
#define MODEL_FILENAME_LION_BODY	"data/MODEL/lionMom_body.x"

#define VALUE_ROTATE	(1.0f) 	// 回転量

#define PLAYER_RADIUS	(15.0f)
#define CAMERA_DISTANCE	(200.0f)
//=============================================================================
// 構造体定義
//=============================================================================

//============================================
// 静的メンバー変数の初期化
//============================================
LPDIRECT3DTEXTURE9	CPlayerX::m_pTexture		[TYPE_MAX] = {};		// テクスチャへのポインタ
LPD3DXMESH			CPlayerX::m_pD3DXMesh		[TYPE_MAX] = {};		// メッシュ情報へのポインタ
LPD3DXBUFFER		CPlayerX::m_pD3DXBuffMat	[TYPE_MAX] = {};		// マテリアル情報へのポインタ
DWORD				CPlayerX::m_nNumMat			[TYPE_MAX] = {};		// マテリアル情報の数


//=============================================================================
//コンストラクタ
//=============================================================================
CPlayerX::CPlayerX()
{
	m_pShadow = NULL;

	//手足
	for(int cntLimb = 0; cntLimb < MAX_LIMB; cntLimb++)
	{
		m_pLimb[cntLimb] = NULL;
	}
}

//=============================================================================
//デストラクタ
//=============================================================================
CPlayerX::~CPlayerX()
{
	
}


//=============================================================================
//
//=============================================================================
HRESULT CPlayerX::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed)
{
	CSceneX::Init( pos, rot, scl);

	m_isGoAhead = false;
	m_isGoBack = false;
	
	m_fSpeed = 0.0f;
	m_fAccel = speed;

	m_front = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
	m_rotTarget = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
	m_rotAngle = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);

	m_state = STATE_NORMAL;
	m_nCntState = 0;
	m_nNumFoodGet = 0; //集めた食材の数

	//手足
	m_pLimb[0] = CLimbX::Create( pos, rot, scl, CLimbX::TYPE_L_HAND);
	m_pLimb[1] = CLimbX::Create( pos, rot, scl, CLimbX::TYPE_R_HAND);
	m_pLimb[2] = CLimbX::Create( pos, rot, scl, CLimbX::TYPE_L_FOOT);
	m_pLimb[3] = CLimbX::Create( pos, rot, scl, CLimbX::TYPE_R_FOOT);

	//影の生成
	m_pShadow = CShadow::Create( pos, D3DXVECTOR2( 50.0f, 50.0f));

	return S_OK;
}

//=============================================================================
//
//=============================================================================
void CPlayerX::Uninit(void)
{
	//手足
	for(int cntLimb = 0; cntLimb < MAX_LIMB; cntLimb++)
	{
		m_pLimb[cntLimb]->Uninit();
	}

	//本体
	CSceneX::Uninit();
}

//=============================================================================
//
//=============================================================================
void CPlayerX::Update(void)
{
	{//カメラ追従
		CCamera *pCamera = CManager::GetCamera();

		//注視点
		pCamera->SetPosR( this->GetPosition());

		//視点
		D3DXVECTOR3 posV = pCamera->GetPosV();
		posV.x = pCamera->GetPosR().x - CAMERA_DISTANCE * sinf(pCamera->GetRot().y);
		posV.z = pCamera->GetPosR().z - CAMERA_DISTANCE * cosf(pCamera->GetRot().y);
		pCamera->SetPosV( posV);

		//向き
		pCamera->SetRot( this->GetRot());
	}

	//移動処理
	if( isMouseUse())
	{
		UpdateRot();
	}

#ifdef _DEBUG
	if( isKeyUse(DIK_W, DIK_S, DIK_A, DIK_D) || isMouseUse())
	{
		UpdateRot();
	}
#endif

	//状態更新
	switch( m_state)
	{
	case STATE_HIT:
		m_nCntState--;
		if( m_nCntState <= 0)
		{
			m_state = STATE_NORMAL;
			m_front = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 tPos = this->GetPosition();
			tPos.y = 60.0f;
			this->SetPosition( tPos);
		}
		else
		{
			//跳ね返る処理
			m_front.y = (m_nCntState - 15) * 0.2f;
			//移動慣性
			m_fSpeed -= m_fSpeed * 0.05f;
		}
		break;

	case STATE_UPGRADE:
	case STATE_GOAL:
		
		m_front = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
		break;

	case STATE_NORMAL:
	case STATE_LION:
		//前進ベクトルの更新
		CalcFront();
		break;
	}

	//座標更新処理
	if( isCollision() == false)
	{
		SetPosition( this->GetPosition() + m_front);
	}
	//手足
	for(int cntLimb = 0; cntLimb < MAX_LIMB; cntLimb++)
	{
		m_pLimb[cntLimb]->SetPosition(this->GetPosition());
		m_pLimb[cntLimb]->SetRot(this->GetRot());
		m_pLimb[cntLimb]->Update();
	}

	//影の更新処理
	m_pShadow->SetPosition( this->GetPosition());

}

//=============================================================================
//
//=============================================================================
void CPlayerX::Draw(void)
{
	//手足
	for(int cntLimb = 0; cntLimb < MAX_LIMB; cntLimb++)
	{
		m_pLimb[cntLimb]->Draw();
	}

	//本体
	CSceneX::Draw();
}

//=============================================================================
//
//=============================================================================
CPlayerX *CPlayerX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed, TYPE type)
{
	CPlayerX *pPlayerX;
	pPlayerX = new CPlayerX;
	pPlayerX->Init(pos, rot, scl, speed);

	//Xファイルの割り当て
	((CSceneX*)pPlayerX)->BindXfile( m_pTexture[type], m_pD3DXMesh[type], m_pD3DXBuffMat[type], m_nNumMat[type]);

	return pPlayerX;
}


void CPlayerX::UpdateRot(void)
{
	D3DXVECTOR3 rotPlayer = GetRot();

	//回転慣性
	m_rotAngle.y *= 0.999f;

	//次の回転位置に到着したら
	float diff = fabsf(rotPlayer.y - m_rotTarget.y);
	if( diff > D3DX_PI)
	{
		diff -= D3DX_PI*2;
	}

	if(diff < VALUE_ROTATE)
	{
		rotPlayer.y = m_rotTarget.y;
		m_rotAngle.y = 0;
	}
	else //次の回転位置にまだ到着してない
	{
		rotPlayer.y += m_rotAngle.y;

		//モデル角度修正
		if( rotPlayer.y > D3DX_PI)
		{
			rotPlayer.y -= D3DX_PI*2;
		}
		else if(rotPlayer.y <= -D3DX_PI)
		{
			rotPlayer.y += D3DX_PI*2;
		}
	}	

	//データの更新
	SetRot(rotPlayer);
}

bool CPlayerX::isKeyUse(int nUp, int nDown, int nLeft, int nRight)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	D3DXVECTOR3 rotCamera = CManager::GetCamera()->GetRot();
	D3DXVECTOR3 rotPlayer = GetRot();

	//初期化
	m_isGoAhead = false;
	m_isGoBack = false;


	//斜め移動
	if( (pInputKeyboard->GetKeyPress(nRight) && pInputKeyboard->GetKeyPress(nUp)) ) //右上
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(VALUE_ROTATE);
		if( m_rotTarget.y > D3DX_PI)
		{
			m_rotTarget.y -= D3DX_PI * 2.0f;
		}
		m_isGoAhead = true;
	}
	else if((pInputKeyboard->GetKeyPress(nRight) && pInputKeyboard->GetKeyPress(nDown)) ) //右下
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(VALUE_ROTATE);
		if( m_rotTarget.y > D3DX_PI)
		{
			m_rotTarget.y -= D3DX_PI * 2.0f;
		}
		m_isGoBack = true;
	}
	else if((pInputKeyboard->GetKeyPress(nLeft)  && pInputKeyboard->GetKeyPress(nUp))  ) //左上
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(-VALUE_ROTATE);
		if( m_rotTarget.y < -D3DX_PI)
		{
			m_rotTarget.y += D3DX_PI * 2.0f;
		}
		m_isGoAhead = true;
	}
	else if((pInputKeyboard->GetKeyPress(nLeft) && pInputKeyboard->GetKeyPress(nDown)) ) //左下
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(-VALUE_ROTATE);
		if( m_rotTarget.y < -D3DX_PI)
		{
			m_rotTarget.y += D3DX_PI * 2.0f;
		}
		m_isGoBack = true;
	}
	else if(pInputKeyboard->GetKeyPress(nUp) )
	{
		m_isGoAhead = true;
	}
	else if(pInputKeyboard->GetKeyPress(nDown) )
	{
		m_isGoBack = true;
	}
	else if(pInputKeyboard->GetKeyPress(nLeft) )
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(-VALUE_ROTATE);
		if( m_rotTarget.y < -D3DX_PI)
		{
			m_rotTarget.y += D3DX_PI * 2.0f;
		}
		return true;
	}
	else if(pInputKeyboard->GetKeyPress(nRight) )
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(VALUE_ROTATE);
		if( m_rotTarget.y > D3DX_PI)
		{
			m_rotTarget.y -= D3DX_PI * 2.0f;
		}
		return true;
	}

	//操作したか
	return (m_isGoAhead || m_isGoBack);
}
bool CPlayerX::isMouseUse(void)
{
	CInputMouse *pInputMouse = CManager::GetInputMouse();
	D3DXVECTOR3 rotCamera = CManager::GetCamera()->GetRot();
	D3DXVECTOR3 rotPlayer = GetRot();

	const int nDeadZone = 0;

	//初期化
	m_isGoAhead = false;
	m_isGoBack = false;


	//斜め移動
	if( (pInputMouse->GetMouseAxisX() > nDeadZone && pInputMouse->GetMouseLeftPress()) ) //右上
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(VALUE_ROTATE);
		if( m_rotTarget.y > D3DX_PI)
		{
			m_rotTarget.y -= D3DX_PI * 2.0f;
		}
		m_isGoAhead = true;
	}
	else if((pInputMouse->GetMouseAxisX() > nDeadZone && pInputMouse->GetMouseRightPress()) ) //右下
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(VALUE_ROTATE);
		if( m_rotTarget.y > D3DX_PI)
		{
			m_rotTarget.y -= D3DX_PI * 2.0f;
		}
		m_isGoBack = true;
	}
	else if((pInputMouse->GetMouseAxisX() < -nDeadZone  && pInputMouse->GetMouseLeftPress())  ) //左上
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(-VALUE_ROTATE);
		if( m_rotTarget.y < -D3DX_PI)
		{
			m_rotTarget.y += D3DX_PI * 2.0f;
		}
		m_isGoAhead = true;
	}
	else if((pInputMouse->GetMouseAxisX() < -nDeadZone && pInputMouse->GetMouseRightPress()) ) //左下
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(-VALUE_ROTATE);
		if( m_rotTarget.y < -D3DX_PI)
		{
			m_rotTarget.y += D3DX_PI * 2.0f;
		}
		m_isGoBack = true;
	}
	else if(pInputMouse->GetMouseLeftPress() )
	{
		m_isGoAhead = true;
	}
	else if(pInputMouse->GetMouseRightPress() )
	{
		m_isGoBack = true;
	}
	else if(pInputMouse->GetMouseAxisX() < -nDeadZone )
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(-VALUE_ROTATE);
		if( m_rotTarget.y < -D3DX_PI)
		{
			m_rotTarget.y += D3DX_PI * 2.0f;
		}
		return true;
	}
	else if(pInputMouse->GetMouseAxisX() > nDeadZone )
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(VALUE_ROTATE);
		if( m_rotTarget.y > D3DX_PI)
		{
			m_rotTarget.y -= D3DX_PI * 2.0f;
		}
		return true;
	}

	//操作したか
	return (m_isGoAhead || m_isGoBack);
}

void CPlayerX::CalcFront(void)
{
	D3DXVECTOR3 posPlayer = GetPosition();
	D3DXVECTOR3 rotPlayer = GetRot();

	if(m_isGoAhead == true)
	{
		m_fSpeed += m_fAccel;
		if( m_fSpeed > 10.0f)
		{
			m_fSpeed = 10.0f;
		}
	}
	else if(m_isGoBack == true)
	{
		m_fSpeed -= m_fAccel;

		if( m_fSpeed < -10.0f)
		{
			m_fSpeed = -10.0f;
		}
	}
	else
	{
		//移動慣性
		m_fSpeed -= m_fSpeed * 0.05f;	
	}


	//回転していない時
	if( m_rotAngle.y == 0)
	{
		//移動
		m_front.x = m_fSpeed * sinf( rotPlayer.y);
		m_front.z = m_fSpeed * cosf( rotPlayer.y);
	}
}

D3DXVECTOR3 CPlayerX::GetFront(void)
{
	return m_front;
}

//=============================================================================
// ステートを設定
//=============================================================================
void CPlayerX::SetState(STATE state)
{
	m_state = state;
	
	switch(m_state)
	{
	case STATE_LION:
		//BODY
		this->BindXfile( TYPE_LION);

		//手足
		m_pLimb[0]->BindXfile(CLimbX::TYPE_LION_L_HAND);
		m_pLimb[1]->BindXfile(CLimbX::TYPE_LION_R_HAND);
		m_pLimb[2]->BindXfile(CLimbX::TYPE_LION_L_FOOT);
		m_pLimb[3]->BindXfile(CLimbX::TYPE_LION_R_FOOT);
		
		break;
	}
}
//=============================================================================
// ステートを取得
//=============================================================================
CPlayerX::STATE CPlayerX::GetState(void)
{
	return m_state;
}
//=============================================================================
// プレイヤーのあたり判定を計算する
//=============================================================================
bool CPlayerX::isCollision(void)
{
	D3DXVECTOR3 posPlayer = this->GetPosition();
	D3DXVECTOR3 rotPlayer = this->GetRot();
	D3DXVECTOR3 wall_nor = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
	bool bHitWall = false;
	bool bHitCube = false;
	int nHitCubeID = 0;

	//当たり判定の前準備
	D3DXVECTOR3 posLside = posPlayer;
	posLside.x = posPlayer.x +  PLAYER_RADIUS * sinf(rotPlayer.y + D3DXToRadian(-90.0f));
	posLside.z = posPlayer.z +  PLAYER_RADIUS * cosf(rotPlayer.y + D3DXToRadian(-90.0f));

	D3DXVECTOR3 posRside = posPlayer;
	posRside.x = posPlayer.x +  PLAYER_RADIUS * sinf(rotPlayer.y + D3DXToRadian(90.0f));
	posRside.z = posPlayer.z +  PLAYER_RADIUS * cosf(rotPlayer.y + D3DXToRadian(90.0f));

	//当たり判定
	for( int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		CScene *pScene;
		pScene = CScene::GetScene( nCntScene);
		
		if( pScene != NULL)
		{
			CScene::OBJTYPE type;
			type = pScene->GetObjType();

			//食材とのあたり判定
			if (type == CScene::OBJTYPE_L_FOOD)
			{
				CFood *pFood = (CFood*)pScene;

				D3DXVECTOR3 posFood;
				posFood = pFood->GetPosition();

				if (pFood->GetState() == CFood::STATE_NORMAL && CCollision::HitCheckCircleXZ(posPlayer, PLAYER_RADIUS, posFood, 15.0f))
				{
					//アイコンの色を変える
					CFoodIcon *pFoodIcon = pFood->GetIcon();
					pFoodIcon->SetColor(WHITE(1.0f));

					//食材ゲット
					pFood->SetClear();
					pFood->SetState( CFood::STATE_FLYING, 120);
					m_nNumFoodGet++;

					//スコア
					CLionGame::GetScore()->AddScore(100);
				}
			}

			//敵との当たり判定
			else if( type == CScene::OBJTYPE_L_ENEMY && m_state != STATE_HIT)
			{
				D3DXVECTOR3 posEnemy;
				posEnemy = pScene->GetPosition();

				if( CCollision::HitCheckBall( posPlayer, PLAYER_RADIUS, posEnemy, PLAYER_RADIUS))
				{
					switch(m_state)
					{
					case STATE_NORMAL:
						m_state = STATE_HIT;
						m_nCntState = 30;
						m_front = posPlayer - posEnemy;
						D3DXVec3Normalize( &m_front, &m_front);
						m_front *= 2.0f;
						break;
					case STATE_LION:
						CEnemyX *pEnemy = (CEnemyX*)pScene;
						pEnemy->SetState(CEnemyX::STATE_STUN, 60);
						break;
					}
			
				}
			}

			//壁とのあたり判定
			else if( type == CScene::OBJTYPE_WALL)
			{
				CMeshWall *pWall = (CMeshWall*)pScene;

				D3DXVECTOR3 tSphere;
				D3DXVec3Normalize( &tSphere, &m_front);
				tSphere *= PLAYER_RADIUS;

				if( pWall->HitCheck( posPlayer, posPlayer + tSphere, &wall_nor, NULL) ||
					pWall->HitCheck( posLside, posLside + tSphere, &wall_nor, NULL) ||
					pWall->HitCheck( posRside, posRside + tSphere, &wall_nor, NULL))
				{
					bHitWall = true;
				}
			}

			//棚とのあたり判定
			else if( type == CScene::OBJTYPE_CUBE)
			{
				CCubeX *pCube = (CCubeX*)pScene;

				//あたり判定
				float len = pCube->GetDistanceBoxPoint( posPlayer + m_front);
				if( len < PLAYER_RADIUS)
				{
					//レジ
					if(pCube->GetType() == CCubeX::TYPE_1X1)
					{
						if(CFood::isAllClear() == true)
						{
							//goal
							this->SetState(STATE_GOAL);
						}
					}

					nHitCubeID = nCntScene;
					bHitCube = true;
				}	
				
			}
		}
	}

	//修正した前進ベクトルをもう一度あたり判定をとる
	if( bHitWall == true)
	{
		bHitWall = false;

		//前進方向の修正
		CCollision::GetWallScratchVector( &m_front, m_front, wall_nor);

		//当たり判定(二回目)
		for( int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			CScene *pScene;
			pScene = CScene::GetScene( nCntScene);
		
			if( pScene != NULL)
			{
				CScene::OBJTYPE type;
				type = pScene->GetObjType();

				//壁とのあたり判定(二回目)
				if( type == CScene::OBJTYPE_WALL)
				{
					CMeshWall *pWall = (CMeshWall*)pScene;

					D3DXVECTOR3 tSphere;
					D3DXVec3Normalize( &tSphere, &m_front);
					tSphere *= PLAYER_RADIUS;
				
					if( pWall->HitCheck( posPlayer, posPlayer + tSphere, &wall_nor, NULL) ||
						pWall->HitCheck( posLside, posLside + tSphere, &wall_nor, NULL) ||
						pWall->HitCheck( posRside, posRside + tSphere, &wall_nor, NULL))
					{
						bHitWall = true;
					}
				
				}	
			}		
		}
	}
	else if( bHitCube == true)
	{
		//前進方向の修正
		D3DXVECTOR3 vecX = D3DXVECTOR3( 1.0f, 0.0f, 0.0f);
		D3DXVECTOR3 vecZ = D3DXVECTOR3( 0.0f, 0.0f, 1.0f);
		CCollision::GetWallScratchVector( &vecX, m_front, vecX);
		CCollision::GetWallScratchVector( &vecZ, m_front, vecZ);

		//当たり判定(二回目)
		CScene *pScene;
		pScene = CScene::GetScene( nHitCubeID);
		
		if( pScene != NULL)
		{
			CScene::OBJTYPE type;
			type = pScene->GetObjType();

			//棚とのあたり判定(二回目)
			if( type == CScene::OBJTYPE_CUBE)
			{
				CCubeX *pCube = (CCubeX*)pScene;

				if( pCube->GetDistanceBoxPoint( posPlayer + vecX) >= PLAYER_RADIUS)
				{
					bHitCube = false;
					m_front = vecX;
				}
				if( pCube->GetDistanceBoxPoint( posPlayer + vecZ) >= PLAYER_RADIUS)
				{
					bHitCube = false;
					m_front = vecZ;
				}
			}	
		}		
	}

	return (bHitCube || bHitWall);
}
//=============================================================================
//XFILEのロード
//=============================================================================
HRESULT CPlayerX::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	for(int cntType = 0; cntType < TYPE_MAX; cntType++)
	{
		LPCSTR strFileName;
		switch( cntType)
		{
		//HUMAN
		case TYPE_HUMAN:
			strFileName = MODEL_FILENAME_BODY;
			break;
		case TYPE_LION:
			strFileName = MODEL_FILENAME_LION_BODY;
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
//XFILEのアンロード
//=============================================================================
void CPlayerX::Unload(void)
{
	for(int cntType = 0; cntType < TYPE_MAX; cntType++)
	{
		// テクスチャの開放
		if(m_pTexture[cntType] != NULL)
		{
			m_pTexture[cntType]->Release();
			m_pTexture[cntType] = NULL;
		}
		// メッシュの開放
		if(m_pD3DXMesh[cntType] != NULL)
		{
			m_pD3DXMesh[cntType]->Release();
			m_pD3DXMesh[cntType] = NULL;
		}
		// マテリアルの開放
		if(m_pD3DXBuffMat != NULL)
		{
			m_pD3DXBuffMat[cntType]->Release();
			m_pD3DXBuffMat[cntType] = NULL;
		}	
	}

}
//=============================================================================
//XFILEの割り当て
//=============================================================================
void CPlayerX::BindXfile(TYPE type)
{
	((CSceneX*)this)->BindXfile( m_pTexture[type], m_pD3DXMesh[type], m_pD3DXBuffMat[type], m_nNumMat[type]);
}
//=============================================================================
//プレイヤーがゲットした食材の数を取得
//=============================================================================
int CPlayerX::GetFoodNum(void)
{
	return m_nNumFoodGet;
}