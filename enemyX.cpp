//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: enemyX.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/12/12
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "enemyX.h"
#include "manager.h"
#include "debugproc.h"
#include "collision.h"

//============================================
// マクロ定義
//============================================
#define MODEL_FILENAME "data/MODEL/player.x"
#define VALUE_ROTATE	(D3DX_PI * 0.1f) 	// 回転量

//=============================================================================
// 構造体定義
//=============================================================================
#define MAX_MOTION (4)
//============================================
// 静的メンバー変数の初期化
//============================================
CEnemyX::MOTION *CEnemyX::m_pMotionPara = NULL;

//=============================================================================
//コンストラクタ
//=============================================================================
CEnemyX::CEnemyX()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CEnemyX::~CEnemyX()
{
	
}


//=============================================================================
//
//=============================================================================
HRESULT CEnemyX::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl)
{
	CSceneX::Init( pos, rot, scl);
	SetObjType( OBJTYPE_L_ENEMY);

	m_nCntFrame = 0;
	m_nMotionNow = 0;

	m_pMotionPara = new MOTION[MAX_MOTION];

	m_pMotionPara[0].nFrame = 60;
	m_pMotionPara[0].front = D3DXVECTOR3( 100.0f, 0.0f, 0.0f);
	m_pMotionPara[0].rotY = 0.0f;
	
	m_pMotionPara[1].nFrame = 30;
	m_pMotionPara[1].front = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
	m_pMotionPara[1].rotY = D3DX_PI;

	m_pMotionPara[2].nFrame = 60;
	m_pMotionPara[2].front = D3DXVECTOR3( -100.0f, 0.0f, 0.0f);
	m_pMotionPara[2].rotY = 0.0f;

	m_pMotionPara[3].nFrame = 30;
	m_pMotionPara[3].front = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
	m_pMotionPara[3].rotY = D3DX_PI;

	m_front = m_pMotionPara[0].front / m_pMotionPara[0].nFrame;
	m_rotTurn = m_pMotionPara[0].rotY / m_pMotionPara[0].nFrame;

	return S_OK;
}

//=============================================================================
//
//=============================================================================
void CEnemyX::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
//
//=============================================================================
void CEnemyX::Update(void)
{
	//移動処理
	D3DXVECTOR3 pos = this->GetPosition();
	pos += m_front;
	this->SetPosition( pos);

	//向き
	D3DXVECTOR3 rot = this->GetRot();
	rot.y += m_rotTurn;
	if( rot.y > D3DX_PI)
	{
		rot.y -= D3DX_PI * 2.0f;
	}
	this->SetRot( rot);

	//モーション更新処理
	m_nCntFrame++;
	if( m_nCntFrame >= m_pMotionPara[m_nMotionNow].nFrame)
	{
		m_nMotionNow = (m_nMotionNow + 1) % MAX_MOTION;
		m_front = m_pMotionPara[m_nMotionNow].front / m_pMotionPara[m_nMotionNow].nFrame;
		m_rotTurn = m_pMotionPara[m_nMotionNow].rotY / m_pMotionPara[m_nMotionNow].nFrame;
		m_nCntFrame = 0;
	}
}

//=============================================================================
//
//=============================================================================
void CEnemyX::Draw(void)
{
	CSceneX::Draw();
}

//=============================================================================
//
//=============================================================================
CEnemyX *CEnemyX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl)
{
	CEnemyX *pEnemy;
	pEnemy = new CEnemyX;
	pEnemy->Init(pos, rot, scl);

	return pEnemy;
}

//=============================================================================
// 回転角度を取得
//=============================================================================
D3DXVECTOR3 CEnemyX::Get2RotDiffAngle( D3DXVECTOR3 rot, D3DXVECTOR3 rotTarget)
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
		tAngle[cntXYZ] = tAngle[cntXYZ] / abs(tAngle[cntXYZ]);

	}

	re.x = tAngle[0];
	re.y = tAngle[1];
	re.z = tAngle[2];

	return re;
}