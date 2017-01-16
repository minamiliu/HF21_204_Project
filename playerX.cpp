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
#include "partX.h"
#include "meshWall.h"
#include "cubeX.h"

//============================================
// マクロ定義
//============================================
#define MODEL_FILENAME_BODY		"data/MODEL/mom_body.x"
#define VALUE_ROTATE	(1.0f) 	// 回転量

#define PLAYER_RADIUS	(20.0f)
#define CAMERA_DISTANCE	(200.0f)
//=============================================================================
// 構造体定義
//=============================================================================


//=============================================================================
//コンストラクタ
//=============================================================================
CPlayerX::CPlayerX()
{
	m_shadow = NULL;
	m_pRHand = NULL;
	m_pLHand = NULL;
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

	m_move = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
	m_front = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
	m_rotTarget = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
	m_rotAngle = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);

	m_state = STATE_NORMAL;
	m_nCntState = 0;

	//手足
	m_pLHand = CPartX::Create( pos, rot, scl, CPartX::TYPE_L_HAND);
	m_pRHand = CPartX::Create( pos, rot, scl, CPartX::TYPE_R_HAND);
	m_pLFoot = CPartX::Create( pos, rot, scl, CPartX::TYPE_L_FOOT);
	m_pRFoot = CPartX::Create( pos, rot, scl, CPartX::TYPE_R_FOOT);

	//影の生成
	m_shadow = CShadow::Create( pos, D3DXVECTOR2( 50.0f, 50.0f));

	return S_OK;
}

//=============================================================================
//
//=============================================================================
void CPlayerX::Uninit(void)
{
	//手足
	m_pLHand->Uninit();
	m_pRHand->Uninit();
	m_pLFoot->Uninit();
	m_pRFoot->Uninit();

	//本体
	CSceneX::Uninit();
}

//=============================================================================
//
//=============================================================================
void CPlayerX::Update(void)
{
	//移動処理
	bool isMoved;
	bool bHitWall = false;
	bool bHitCube = false;
	int nHitCubeID = 0;
	D3DXVECTOR3 wall_nor;
	D3DXVECTOR3 posPlayer = GetPosition();


	isMoved = isKeyUse(DIK_W, DIK_S, DIK_A, DIK_D);
	//isMoved = isMouseUse();
	if( isMoved == true)
	{
		UpdateRot();
	}
	CalcNextPos();

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
				D3DXVECTOR3 posFood;
				posFood = pScene->GetPosition();

				if (CCollision::HitCheckCircleXZ(posPlayer, PLAYER_RADIUS, posFood, 10.f))
				{
					CFood *pFood = ((CFood*)pScene);

					//アイコンの色を変える
					CFoodIcon *pFoodIcon = pFood->GetIcon();
					pFoodIcon->SetColor(WHITE(1.0f));

					//食材ゲット
					pFood->SetClear();

					//食材の破棄
					pScene->Uninit();

					//スコア
					//CLionGame::GetScore()->AddScore(100);

					//return;
				}
			}

			//敵との当たり判定
			else if( type == CScene::OBJTYPE_L_ENEMY && m_state != STATE_CRASH)
			{
				D3DXVECTOR3 posEnemy;
				posEnemy = pScene->GetPosition();

				if( CCollision::HitCheckBall( posPlayer, PLAYER_RADIUS, posEnemy, PLAYER_RADIUS))
				{
					//スコア
					//CLionGame::GetScore()->AddScore( -100);
					
					m_state = STATE_CRASH;
					m_nCntState = 60;
					m_fSpeed = -2.0f;
					
					//return;
				}
			}

			//壁とのあたり判定
			else if( type == CScene::OBJTYPE_WALL)
			{
				CMeshWall *pWall = (CMeshWall*)pScene;
				
				if( pWall->HitCheck( posPlayer, posPlayer + m_front, &wall_nor, NULL))
				{
					bHitWall = true;
				}
				
			}

			//棚とのあたり判定
			else if( type == CScene::OBJTYPE_CUBE)
			{
				CCubeX *pCube = (CCubeX*)pScene;
				
				float len = pCube->GetDistanceBoxPoint( posPlayer + m_front);
				if( len < 15.0f)
				{
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
				
					if( pWall->HitCheck( posPlayer, posPlayer + m_front, &wall_nor, NULL))
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

				if( pCube->GetDistanceBoxPoint( posPlayer + vecX) >= 15.0f)
				{
					bHitCube = false;
					m_front = vecX;
				}
				if( pCube->GetDistanceBoxPoint( posPlayer + vecZ) >= 15.0f)
				{
					bHitCube = false;
					m_front = vecZ;
				}
			}	
		}		
	}
	
	//座標更新処理
	if( bHitWall != true && bHitCube != true)
	{
		SetPosition( posPlayer + m_front);
	}


	//状態更新
	switch( m_state)
	{
	case STATE_CRASH:
		m_nCntState--;
		if( m_nCntState <= 0)
		{
			m_state = STATE_NORMAL;
		}
		break;
	}

	//手足
	m_pLHand->SetPosition(this->GetPosition());
	m_pLHand->SetRot(this->GetRot());
	m_pLHand->Update();

	m_pRHand->SetPosition(this->GetPosition());
	m_pRHand->SetRot(this->GetRot());
	m_pRHand->Update();
	
	m_pLFoot->SetPosition(this->GetPosition());
	m_pLFoot->SetRot(this->GetRot());
	m_pLFoot->Update();

	m_pRFoot->SetPosition(this->GetPosition());
	m_pRFoot->SetRot(this->GetRot());
	m_pRFoot->Update();

	//影の更新処理
	m_shadow->SetPosition( this->GetPosition());

}

//=============================================================================
//
//=============================================================================
void CPlayerX::Draw(void)
{
	//手足
	m_pLHand->Draw();
	m_pRHand->Draw();
	m_pLFoot->Draw();
	m_pRFoot->Draw();

	//本体
	CSceneX::Draw();
}

//=============================================================================
//
//=============================================================================
CPlayerX *CPlayerX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed)
{
	CPlayerX *pPlayerX;
	pPlayerX = new CPlayerX;
	pPlayerX->Init(pos, rot, scl, speed);

	//Xファイルの読み込み
	pPlayerX->LoadXfile(MODEL_FILENAME_BODY);

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
	if( m_isGoAhead || m_isGoBack)
	{
		return true;
	}
	else
	{
		return false;
	}
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
	if( m_isGoAhead || m_isGoBack)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CPlayerX::CalcNextPos(void)
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

		//移動慣性の初期化
		m_move = D3DXVECTOR3( m_fSpeed, 0.0f, m_fSpeed);

	}
	else if(m_isGoBack == true)
	{
		m_fSpeed -= m_fAccel;

		if( m_fSpeed < -10.0f)
		{
			m_fSpeed = -10.0f;
		}

		//移動慣性の初期化
		m_move = D3DXVECTOR3( m_fSpeed, 0.0f, m_fSpeed);	
	}
	else
	{
		m_fSpeed -= m_fSpeed * 0.25f;
	}


	//回転していない時
	if( m_rotAngle.y == 0)
	{
		//移動
		m_front = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
		m_front.x = m_move.x * sinf( rotPlayer.y);
		m_front.z = m_move.z * cosf( rotPlayer.y);

		//慣性処理
		m_move -= m_move * 0.05f;	
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
}
//=============================================================================
// ステートを取得
//=============================================================================
CPlayerX::STATE CPlayerX::GetState(void)
{
	return m_state;
}