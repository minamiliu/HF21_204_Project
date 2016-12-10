//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: game.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/17
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "game.h"
#include "renderer.h"
#include "input.h"
#include "light.h"
#include "camera.h"
#include "scene3D.h"
#include "meshWall.h"
#include "playerX.h"
#include "collision.h"
#include "cubeX.h"
#include "debugproc.h"

//============================================
// マクロ定義
//============================================
#define CAMERA_DISTANCE	(200.0f)
//============================================
// 静的メンバー変数の初期化
//============================================


//============================================
//コンストラクタ
//============================================
CGame::CGame() : CManager(MODE_GAME)
{

}

CGame::~CGame()
{
	
}

HRESULT CGame::Init(void)
{
	m_pCamera->Init();

	//オブジェクトの生成(3Dポリゴン)
	CScene3D::Create( D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 10, 10, 100.0f, 100.0f);

	//ウォール
	CMeshWall::Load();
	m_nNumWall = 0;
	m_pMeshWall[m_nNumWall++] = CMeshWall::Create( D3DXVECTOR3( 0.0f, 100.0f, 500.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 11, 4, 100.0f, 100.0f);
	m_pMeshWall[m_nNumWall++] = CMeshWall::Create( D3DXVECTOR3( 500.0f, 100.0f, 0.0f), D3DXVECTOR3( 0.0f, D3DXToRadian(90.0f), 0.0f), 11, 4, 100.0f, 100.0f);
	m_pMeshWall[m_nNumWall++] = CMeshWall::Create( D3DXVECTOR3( -500.0f, 100.0f, 0.0f), D3DXVECTOR3( 0.0f, D3DXToRadian(-90.0f), 0.0f), 11, 4, 100.0f, 100.0f);
	m_pMeshWall[m_nNumWall++] = CMeshWall::Create( D3DXVECTOR3( 0.0f, 100.0f, -500.0f), D3DXVECTOR3( 0.0f, D3DXToRadian(180.0f), 0.0f), 11, 4, 100.0f, 100.0f);


	//オブジェクトの生成(Xfile)
	m_player = CPlayerX::Create( D3DXVECTOR3( -100.0f, 0.0f, -100.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f), 5.0f);
	
	m_nNumCube = 0;
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3( 0.0f, 50.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f), D3DXVECTOR3( 100.0f, 100.0f, 300.0f));
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3( 300.0f, 50.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f), D3DXVECTOR3( 100.0f, 100.0f, 300.0f));
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3( -300.0f, 50.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f), D3DXVECTOR3( 100.0f, 100.0f, 300.0f));
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3( 0.0f, 50.0f, 300.0f), D3DXVECTOR3( 0.0f, D3DXToRadian(90.0f), 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f), D3DXVECTOR3( 300.0f, 100.0f, 100.0f));
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3( 0.0f, 50.0f, -300.0f), D3DXVECTOR3( 0.0f, D3DXToRadian(90.0f), 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f), D3DXVECTOR3( 300.0f, 100.0f, 100.0f));

	return S_OK;
}

void CGame::Uninit()
{
	CManager::Uninit();
}

void CGame::Update()
{
	//入力などの更新、各シーンのUpdateの最初に呼び出す
	CManager::Update();

	{//カメラ追従
		CCamera *pCamera = GetCamera();

		//注視点
		pCamera->SetPosR( m_player->GetPosition());

		//視点
		D3DXVECTOR3 posV = pCamera->GetPosV();
		posV.x = pCamera->GetPosR().x - CAMERA_DISTANCE * sinf(pCamera->GetRot().y);
		posV.z = pCamera->GetPosR().z - CAMERA_DISTANCE * cosf(pCamera->GetRot().y);
		pCamera->SetPosV( posV);

		//向き
		pCamera->SetRot( m_player->GetRot());
	}

	//壁との当たり判定
	bool bHit = false;
	D3DXVECTOR3 front = m_player->GetFront();
	D3DXVECTOR3 posP = m_player->GetPosition();
	D3DXVECTOR3 wall_nor;
	for(int cntWall = 0; cntWall < m_nNumWall; cntWall++)
	{
		if( m_pMeshWall[cntWall]->HitCheck( posP,  posP + front, &wall_nor, NULL))
		{
			bHit = true;
			break;
		}
	}

	//キューブとの当たり判定
	bool bHitCube = false;
	int nIDCube = 0;
	for(int cntCube = 0; cntCube < m_nNumCube; cntCube++)
	{
		float len = m_cube[cntCube]->GetDistanceBoxPoint( m_player->GetPosition() + front);
		if( len < 15.0f)
		{
			bHitCube = true;
			bHit = true;
			nIDCube = cntCube;
			break;
		}	
	}



	//移動
	if( bHit == false)
	{
		m_player->SetPosition( posP + front);
	}
	else
	{
		if( bHitCube == true)
		{
			D3DXVECTOR3 vecX = D3DXVECTOR3( 1.0f, 0.0f, 0.0f);
			D3DXVECTOR3 vecZ = D3DXVECTOR3( 0.0f, 0.0f, 1.0f);
			CCollision::GetWallScratchVector( &vecX, front, vecX);
			CCollision::GetWallScratchVector( &vecZ, front, vecZ);
			

			if( m_cube[nIDCube]->GetDistanceBoxPoint( m_player->GetPosition() + vecX) >= 15.0f)
			{
				m_player->SetPosition( posP + vecX);
			}
			if( m_cube[nIDCube]->GetDistanceBoxPoint( m_player->GetPosition() + vecZ) >= 15.0f)
			{
				m_player->SetPosition( posP + vecZ);
			}			


		}
		else
		{
			bHit = false;

			//前進方向の修正
			CCollision::GetWallScratchVector( &front, front, wall_nor);

			//壁との当たり判定(2回目)
			for(int cntWall = 0; cntWall < m_nNumWall; cntWall++)
			{
				if( m_pMeshWall[cntWall]->HitCheck( posP,  posP + front, &wall_nor, NULL))
				{
					bHit = true;
					break;
				}
			}
			//移動
			if( bHit == false)
			{
				m_player->SetPosition( posP + front);
			}		
		}


	}



	//スキップシーン
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	if( pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		SetNextScene( MODE_TRASHGAME);
	}

	//シーンが切り替えるところ、各シーンのUpdateの最後に置いとく
	CManager::SceneChange();
}
void CGame::Draw()
{
	CManager::Draw();
}
