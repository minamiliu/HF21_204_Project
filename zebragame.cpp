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
#include "meshField.h"
#include "playerX.h"
#include "toy.h"
#include "point3D.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "time.h"
#include "toybox.h"
#include "book.h"
#include "meshWall.h"
#include "putbook.h"
//============================================
// マクロ定義
//============================================

//============================================
// 静的メンバー変数の初期化
//============================================
int CZebraGame::m_PutToy = 0;
int CZebraGame::m_PutBook = 0;
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
	//カメラの位置
	m_pCamera->Init();
	m_pCamera->SetPosV(D3DXVECTOR3(0.0f,300.0f,-500.0f));
	m_pCamera->SetPosR(D3DXVECTOR3(0.0f,0.0f,400.0f));

	//床
	CMeshField::Create( D3DXVECTOR3( 0.0f,- 10.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 10, 10, 100.0f, 100.0f, CMeshField::TYPE_GREEN);

	//ウォール
	CMeshWall::Create( D3DXVECTOR3( 0.0f, 100.0f, 450.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 10, 10, 100.0f, 100.0f);
	CMeshWall::Create( D3DXVECTOR3( -450.0f, 100.0f, 200.0f), D3DXVECTOR3( 0.0f, D3DXToRadian(270.0f), 0.0f), 10, 10, 100.0f, 100.0f);
	CMeshWall::Create( D3DXVECTOR3( 450.0f, 100.0f, 200.0f), D3DXVECTOR3( 0.0f, D3DXToRadian(90.0f), 0.0f), 10, 10, 100.0f, 100.0f);

	//乱数
	unsigned int now = (unsigned int)time( 0 );
	srand(now);
	int varX,varZ,varR;
	//オブジェクトの生成(3D)
	CBookBox::Create(D3DXVECTOR3(300.0f,0.0f,370.0f) , D3DXVECTOR3( 0.0f, 0.0f, 0.0f),CBookBox::TYPE_TOYBOX);
	CBookBox::Create(D3DXVECTOR3(-300.0f,0.0f,370.0f) , D3DXVECTOR3( 0.0f,D3DXToRadian(90.0f), 0.0f),CBookBox::TYPE_BOOKBOX);
	for(int nCnt = 0 ; nCnt < MAX_TOY ;nCnt++)
	{
		varX = rand() % 101 ;
		varZ = rand() % 101 ;
		varR = rand() % 101 ;
		//オブジェクトの生成(Xfile)
		CToy::Create( D3DXVECTOR3( 5.0f*varX-350.0f, 10.0f, 5.0f*varZ-240.0f), D3DXVECTOR3( 0.0f,D3DXToRadian(30*varR), 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f), 5.0f);
	}


	for(int nCnt = 0 ; nCnt < MAX_BOOK ;nCnt++)
	{
		varX = rand() % 101 ;
		varZ = rand() % 101 ;
		varR = rand() % 101 ;
		//オブジェクトの生成(Xfile)
		CBook::Create( D3DXVECTOR3( 5.0f*varX-350.0f, 10.0f, 5.0f*varZ-240.0f), D3DXVECTOR3( 0.0f,D3DXToRadian(30*varR), 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f), 5.0f);
	}

	
	
	//オブジェクトの生成(2Dポリゴン)
	//タイム
	CTime::Create(D3DXVECTOR3(600, 50.0f, 0.0f),D3DXVECTOR3(100, 100.0f, 0.0f),3,0,false,D3DXCOLOR(255,255,255,255));
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

#ifdef _DEBUG
	//スキップシーン
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	if( pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		SetNextScene( MODE_STAGE_ZEBRA);
	}
#endif

	//シーンが切り替えるところ、各シーンのUpdateの最後に置いとく
	CManager::SceneChange();
}
void CZebraGame::Draw()
{
	CManager::Draw();
}

void CZebraGame :: PutObj(bool toy)
{
	if(toy == true)
	{
		m_PutToy++;
	}
	if(toy == false)
	{
		m_PutBook++;
	}
	if( m_PutToy + m_PutBook == 20)
	{
		CPoint3D::ChangeZebra();
	}
	if (m_PutToy + m_PutBook == MAX_TOY + MAX_BOOK)
	{
		SetNextScene( MODE_STAGE_ZEBRA);
	}
}
//=============================================================================
//ゲームが立ち上がるとき、一回のみ全部ロードする
//=============================================================================
HRESULT CZebraGame::LoadAll(void)
{
	CMeshField::Load();
	CMeshWall::Load();
	CPutBook::Load();
	CToy::Load();
	CBook::Load();

	return S_OK;
}
