//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: trashGame.cpp
// 作成者:		 HAL東京ゲーム学科　山家啓介
// 作成日:       2016/11/24
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "trashGame.h"
#include "renderer.h"
#include "input.h"
#include "player2D.h"
#include "light.h"
#include "camera.h"
#include "scene3D.h"
#include "playerX.h"
#include "trash.h"
#include "score.h"
#include "trashBox.h"
#include "point2D.h"
#include "time.h"
//============================================
// マクロ定義
//============================================
#define TEXTURENAME "data/TEXTURE/Aplayer000.png"
#define TEXTURE_POINT "data/TEXTURE/redPoint.png"
//============================================
// 静的メンバー変数の初期化
//============================================
CTrash *CTrashGame::m_pTrash = NULL;
CScene2D *CTrashGame::m_pTrashBox = NULL;
CScore   *CTrashGame::m_pScore = NULL;
//CPoint2D *m_pPoint2D = NULL;
CScene2D *CTrashGame::m_pMouse = NULL;
CScene2D *CTrashGame::m_pPoint2D = NULL;
CScene2D *CTrashGame::m_pMidpoint = NULL;
CTime *pTime = NULL;
//============================================
//コンストラクタ
//============================================
CTrashGame::CTrashGame() : CManager(MODE_GAME)
{

}

CTrashGame::~CTrashGame()
{
	
}

HRESULT CTrashGame::Init(void)
{
	m_pCamera->Init();
	//ゲーム起動時のマウスを位置を取ってしまうため、強制的に画面中央へ
	SetCursorPos(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);

	//オブジェクトの生成(3Dポリゴン)
	//CScene3D::Create( D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 10, 10, 100.0f, 100.0f);

	//オブジェクトの生成(Xfile)
	//CPlayerX::Create( D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f), 5.0f);

	//オブジェクトの生成(2Dポリゴン)
	CPlayer2D::Create( D3DXVECTOR3( 150.0f, 400.0f, 0.0f), D3DXVECTOR3( 200.0f, 200.0f, 0.0f));

	//オブジェクトの生成（2Dポリゴン）
	//ゴミ
	m_pTrash = CTrash::Create(D3DXVECTOR3(200.0f, 300.0f, 0.0f), D3DXVECTOR3(200.0f, 200.0f, 0.0f));
	//スコア
	m_pScore = CScore::Create(D3DXVECTOR3(150, 50.0f, 0.0f), D3DXVECTOR3(300.0f, 50.0f, 0.0f), 6, BLUE(1.0f));
	//ゴミ箱
	m_pTrashBox = CScene2D::Create(D3DXVECTOR3(1000.0f, 500.0f, 0.0f), D3DXVECTOR3(400.0f, 400.0f, 0.0f),TEXTURENAME);
	//タイム
	pTime = CTime::Create(D3DXVECTOR3(600, 50.0f, 0.0f),D3DXVECTOR3(100, 100.0f, 0.0f),3,0,false,D3DXCOLOR(255,255,255,255));
	//マウスの位置を得る
	CPoint2D::Create(D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(0.0f,0.0f,0.0f),0);
	//つねに中央に
	CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(70.0f, 70.0f, 0.0f),TEXTURE_POINT);
	//中央と現在位置の中間にテクスチャ
	m_pMidpoint = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(40.0f, 40.0f, 0.0f),TEXTURE_POINT);
	//マウスの位置にテクスチャ
	m_pMouse = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(120.0f, 120.0f, 0.0f),TEXTURE_POINT);
	return S_OK;
}

void CTrashGame::Uninit()
{
	CManager::Uninit();
}

void CTrashGame::Update()
{
	D3DXVECTOR3 posTrashBox;
	D3DXVECTOR3 sizeTrashBox;
	posTrashBox = m_pTrashBox->GetPosition();
	sizeTrashBox = m_pTrashBox->GetSize();
	//D3DXVECTOR3 posMouse;

	//posMouse = m_pPoint2D->GetPosition();
	//pMouse->SetPosition(posMouse); 
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	
	if( pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		SetNextScene( MODE_RESULT);
	}

	//マウスを話したらカーソルを画面中央へ
	if(CManager::GetInputMouse()->GetMouseLeftRelease())
	{
		SetCursorPos(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
	}

	for(int nCntScene = 0;nCntScene < MAX_SCENE;nCntScene++)
	{
		CScene *pScene;
		pScene = CScene::GetScene(nCntScene);
		if(pScene != NULL)
		{
			CScene::OBJTYPE type;
			type = pScene->GetObjType();
			if(type == CScene::OBJTYPE_TRASH)
			{
				D3DXVECTOR3 posTrash;
				D3DXVECTOR3 sizeTrash;
				posTrash = pScene->GetPosition();
				sizeTrash = pScene->GetSize();
				//当たり判定
				if( (posTrash.y + sizeTrash.y/2 > posTrashBox.y - sizeTrashBox.y/2) &&
					(posTrash.y - sizeTrash.y/2 < posTrashBox.y + sizeTrashBox.y/2) &&
					(posTrash.x + sizeTrash.x/2 > posTrashBox.x - sizeTrashBox.x/2) &&
					(posTrash.x - sizeTrash.x/2 < posTrashBox.x + sizeTrashBox.x/2))
				{
					D3DXVECTOR3 speed;
					speed = ((CTrash*)pScene)->GetSpeed();
					if(speed.x > 0 &&
						//(posTrash.x - sizeTrash.x/2) < (posTrashBox.x - sizeTrashBox.x) //&&
						(posTrash.y - sizeTrash.y/2) > (posTrashBox.y - sizeTrashBox.y/2) )
					{//外側の右端ではじく
						((CTrash*)pScene)->ReverseMove();
					}
					else if( speed.x > 0 &&
						(posTrash.x + sizeTrash.x/2) > (posTrashBox.x + sizeTrashBox.x/2) )
					{//内側の左側ではじく
						((CTrash*)pScene)->ReverseMove();
					}
					else /*if(posTrash.y - sizeTrash.y/2 > posTrashBox.y - sizeTrashBox.y/2 &&
					//	posTrash.x - sizeTrash.x/2 > posTrashBox.y - sizeTrashBox.x/2 &&
					//	posTrash.x + sizeTrash.x/2 < posTrashBox.y + sizeTrashBox.x/2 )*/
					//	//posTrash.x - sizeTrash.x/2 < posTrashBox.x - sizeTrash.x)
					{//完全に入ってる
						//スコア追加
						m_pScore->AddScore(100);
						//オブジェクトの位置を画面外へ -> 画面外判定で消滅
						pScene->SetPosition(D3DXVECTOR3(100.0f,1000.0f,0.0f));
					}
				}
			}
			else if(type == CScene::OBJTYPE_POINT2D)
			{//マウスの位置にテクスチャ
				D3DXVECTOR3 posMouse;
				posMouse = pScene->GetPosition();
				m_pMouse->SetPosition(posMouse);
				D3DXVECTOR3 posMidpoint;
				posMidpoint= D3DXVECTOR3( (posMouse.x + SCREEN_WIDTH/2)/2,(posMouse.y + SCREEN_HEIGHT/2)/2,0.0f);
				m_pMidpoint->SetPosition(posMidpoint);
			}
		}
	}
	/*if(pTime->TimeUp() == true)
	{
		pTime->Uninit();
		SetNextScene( MODE_RESULT);
	}*/
	CManager::Update();
}
void CTrashGame::Draw()
{
	CManager::Draw();
}
void CTrashGame::SetTrashPointer(CTrash *pTrash)
{
	m_pTrash = pTrash;
}