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
#include "player2D.h"
#include "light.h"
#include "camera.h"
#include "scene3D.h"
#include "playerX.h"

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
	CScene3D::Create( D3DXVECTOR3( 0.0f, 0.0f, 500.0f), D3DXVECTOR3( D3DXToRadian(90.0f), 0.0f, 0.0f), 10, 1, 100.0f, 100.0f);
	CScene3D::Create( D3DXVECTOR3( 500.0f, 0.0f, 0.0f), D3DXVECTOR3( D3DXToRadian(90.0f), D3DXToRadian(90.0f), 0.0f), 10, 1, 100.0f, 100.0f);
	CScene3D::Create( D3DXVECTOR3( -500.0f, 0.0f, 0.0f), D3DXVECTOR3( D3DXToRadian(90.0f), D3DXToRadian(-90.0f), 0.0f), 10, 1, 100.0f, 100.0f);
	CScene3D::Create( D3DXVECTOR3( 0.0f, 0.0f, -500.0f), D3DXVECTOR3( D3DXToRadian(90.0f), D3DXToRadian(180.0f), 0.0f), 10, 1, 100.0f, 100.0f);

	//オブジェクトの生成(Xfile)
	m_player = CPlayerX::Create( D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f), 2.0f);

	//オブジェクトの生成(2Dポリゴン)

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
