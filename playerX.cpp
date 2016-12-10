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
#include "manager.h"
#include "input.h"
#include "camera.h"
#include "debugproc.h"

//============================================
// マクロ定義
//============================================
#define MODEL_FILENAME "data/MODEL/plain.x"
#define VALUE_ROTATE	(D3DX_PI * 0.1f) 	// 回転量

//=============================================================================
// 構造体定義
//=============================================================================


//=============================================================================
//コンストラクタ
//=============================================================================
CPlayerX::CPlayerX()
{

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
	CSceneX::Init( pos, rot, scl, MODEL_FILENAME);

	m_isGoAhead = false;
	m_isGoBack = false;
	m_speed = speed;
	m_move = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
	m_front = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
	m_rotTarget = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
	m_rotAngle = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);	
	
	return S_OK;
}

//=============================================================================
//
//=============================================================================
void CPlayerX::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
//
//=============================================================================
void CPlayerX::Update(void)
{
	bool isMoved;
	isMoved = isKeyUse(DIK_W, DIK_S, DIK_A, DIK_D);
	//isMoved = isMouseUse();
	if( isMoved == true)
	{
		UpdateRot();
	}
	CalcNextPos();

	D3DXVECTOR3 pos = GetPosition();
	CDebugProc::Print("\nplayer x:%f, y:%f, z%f",pos.x, pos.y, pos.z);
}

//=============================================================================
//
//=============================================================================
void CPlayerX::Draw(void)
{
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

	return pPlayerX;
}


void CPlayerX::UpdateRot(void)
{
	D3DXVECTOR3 rotPlayer = GetRot();

	//回転慣性
	m_rotAngle.y *= 0.999f;

	//次の回転位置に到着したら
	float diff = abs(rotPlayer.y - m_rotTarget.y);
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

	const float rotSpeed = 1.0f;

	//初期化
	m_isGoAhead = false;
	m_isGoBack = false;


	//斜め移動
	if( (pInputKeyboard->GetKeyPress(nRight) && pInputKeyboard->GetKeyPress(nUp)) ) //右上
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(rotSpeed);
		if( m_rotTarget.y > D3DX_PI)
		{
			m_rotTarget.y -= D3DX_PI * 2.0f;
		}
		m_isGoAhead = true;
	}
	else if((pInputKeyboard->GetKeyPress(nRight) && pInputKeyboard->GetKeyPress(nDown)) ) //右下
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(rotSpeed);
		if( m_rotTarget.y > D3DX_PI)
		{
			m_rotTarget.y -= D3DX_PI * 2.0f;
		}
		m_isGoBack = true;
	}
	else if((pInputKeyboard->GetKeyPress(nLeft)  && pInputKeyboard->GetKeyPress(nUp))  ) //左上
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(-rotSpeed);
		if( m_rotTarget.y < -D3DX_PI)
		{
			m_rotTarget.y += D3DX_PI * 2.0f;
		}
		m_isGoAhead = true;
	}
	else if((pInputKeyboard->GetKeyPress(nLeft) && pInputKeyboard->GetKeyPress(nDown)) ) //左下
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(-rotSpeed);
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
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(-1.0f);
		if( m_rotTarget.y < -D3DX_PI)
		{
			m_rotTarget.y += D3DX_PI * 2.0f;
		}
		return true;
	}
	else if(pInputKeyboard->GetKeyPress(nRight) )
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(1.0f);
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

	const float rotSpeed = 1.0f;
	const int nDeadZone = 0;

	//初期化
	m_isGoAhead = false;
	m_isGoBack = false;


	//斜め移動
	if( (pInputMouse->GetMouseAxisX() > nDeadZone && pInputMouse->GetMouseLeftPress()) ) //右上
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(rotSpeed);
		if( m_rotTarget.y > D3DX_PI)
		{
			m_rotTarget.y -= D3DX_PI * 2.0f;
		}
		m_isGoAhead = true;
	}
	else if((pInputMouse->GetMouseAxisX() > nDeadZone && pInputMouse->GetMouseRightPress()) ) //右下
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(rotSpeed);
		if( m_rotTarget.y > D3DX_PI)
		{
			m_rotTarget.y -= D3DX_PI * 2.0f;
		}
		m_isGoBack = true;
	}
	else if((pInputMouse->GetMouseAxisX() < -nDeadZone  && pInputMouse->GetMouseLeftPress())  ) //左上
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(-rotSpeed);
		if( m_rotTarget.y < -D3DX_PI)
		{
			m_rotTarget.y += D3DX_PI * 2.0f;
		}
		m_isGoAhead = true;
	}
	else if((pInputMouse->GetMouseAxisX() < -nDeadZone && pInputMouse->GetMouseRightPress()) ) //左下
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(-rotSpeed);
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
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(-1.0f);
		if( m_rotTarget.y < -D3DX_PI)
		{
			m_rotTarget.y += D3DX_PI * 2.0f;
		}
		return true;
	}
	else if(pInputMouse->GetMouseAxisX() > nDeadZone )
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(1.0f);
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
		//移動慣性の初期化
		m_move = D3DXVECTOR3( m_speed, 0.0f, m_speed);

		////時計回り、または逆時計回りを決める
		//m_rotAngle =  Get2RotDiffAngle( m_rot, m_rotTarget);
	}

	if(m_isGoBack == true)
	{
		//移動慣性の初期化
		m_move = -D3DXVECTOR3( m_speed, 0.0f, m_speed);

		////時計回り、または逆時計回りを決める
		//m_rotAngle =  Get2RotDiffAngle( m_rot, m_rotTarget);		
	}

	//回転していない時
	if( m_rotAngle.y == 0)
	{
		//移動
		m_front = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
		m_front.x = m_move.x * sinf( rotPlayer.y);
		m_front.z = m_move.z * cosf( rotPlayer.y);

		//慣性処理
		m_move -= m_move * 0.25f;	
	}
}

D3DXVECTOR3 CPlayerX::GetFront(void)
{
	return m_front;
}

//=============================================================================
// 回転角度を取得
//=============================================================================
D3DXVECTOR3 CPlayerX::Get2RotDiffAngle( D3DXVECTOR3 rot, D3DXVECTOR3 rotTarget)
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