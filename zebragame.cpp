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
#include "zebragame.h"
#include "renderer.h"
#include "input.h"
#include "player2D.h"
#include "light.h"
#include "camera.h"
#include "scene3D.h"
#include "playerX.h"
#include "toy.h"
#include "point3D.h"
#include "score.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "toybox.h"
//============================================
// マクロ定義
//============================================

//============================================
// 静的メンバー変数の初期化
//============================================
CScore *CZebraGame::m_score  = NULL;
//============================================
//コンストラクタ
//============================================
CZebraGame::CZebraGame() : CManager(MODE_ZEBRAGAME)
{

}

CZebraGame::~CZebraGame()
{
	
}

HRESULT CZebraGame::Init(void)
{
	m_pCamera->Init();

	//オブジェクトの生成(3Dポリゴン)
	CScene3D::Create( D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 10, 10, 100.0f, 100.0f);
	//カメラの位置
	//CCamera::SetPosV(D3DXVECTOR3(0.0f,-500.0f,200.0f));
	unsigned int now = (unsigned int)time( 0 );
	srand(now);
	int var;
	
	for(int nCnt = 0 ; nCnt < 10 ;nCnt++)
	{
		var = rand() % 100 ;
		//オブジェクトの生成(Xfile)
		CToy::Create( D3DXVECTOR3( 5.0f*var-200.0f, 0.0f, 2.0f*var-50.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f), 5.0f);
	}
	//オブジェクトの生成(3D)
	CBookBox::Create(D3DXVECTOR3(300.0f,0.0f,300.0f) , D3DXVECTOR3( 0.0f, 0.0f, 0.0f),CBookBox::TYPE_TVSET);
	//オブジェクトの生成(2Dポリゴン)
	m_score = CScore::Create( D3DXVECTOR3(150, 100.0f, 0.0f), D3DXVECTOR3( 300, 50.0f, 0.0f), 6, RED(1.0f));
	m_score->SetScore(1000);
	//オブジェクトの生成(2Dポリゴン)
	CPoint3D::Create( D3DXVECTOR3( 300.0f, 500.0f, 0.0f), D3DXVECTOR3( 20.0f, 20.0f, 0.0f),0);
	return S_OK;
}

void CZebraGame::Uninit()
{
	CManager::Uninit();
}

void CZebraGame::Update()
{
	//入力などの更新、各シーンのUpdateの最初に呼び出す
	CManager::Update();

	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	if( pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		SetNextScene( MODE_GAME);
	}

	//シーンが切り替えるところ、各シーンのUpdateの最後に置いとく
	CManager::SceneChange();
}
void CZebraGame::Draw()
{
	CManager::Draw();
}

CScore *CZebraGame::GetScoreP(void)
{
	return m_score;
}