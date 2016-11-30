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
//============================================
// マクロ定義
//============================================
#define TEXTURENAME "data/TEXTURE/player000.png"
//============================================
// 静的メンバー変数の初期化
//============================================
CScene2D *CTrashGame::m_pTrash = NULL;

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

	//オブジェクトの生成(3Dポリゴン)
	//CScene3D::Create( D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 10, 10, 100.0f, 100.0f);

	//オブジェクトの生成(Xfile)
	//CPlayerX::Create( D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f), 5.0f);

	//オブジェクトの生成(2Dポリゴン)
	CPlayer2D::Create( D3DXVECTOR3( 300.0f, 500.0f, 0.0f), D3DXVECTOR3( 200.0f, 200.0f, 0.0f));

	//オブジェクトの生成（2Dポリゴン）
	m_pTrash = CTrash::Create(D3DXVECTOR3(200.0f, 300.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f));
	//CTrash::Create(D3DXVECTOR3(1000.0f, 300.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f));
	CScore::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pTrashBox = CScene2D::Create(D3DXVECTOR3(1000.0f, 500.0f, 0.0f), D3DXVECTOR3(300.0f, 300.0f, 0.0f),TEXTURENAME);
	//CPoint2D::Create(D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(0.0f,0.0f,0.0f),0);
	return S_OK;
}

void CTrashGame::Uninit()
{
	CManager::Uninit();
}

void CTrashGame::Update()
{
	CManager::Update();

	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	if( pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		SetNextScene( MODE_RESULT);
	}

	D3DXVECTOR3 posTrashBox;
	D3DXVECTOR3 sizeTrashBox;
	posTrashBox = m_pTrashBox->GetPosition();
	sizeTrashBox = m_pTrashBox->GetSize();

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
				//D3DXVECTOR3 posEnemy;
				//posEnemy = pScene->GetPosition();

				D3DXVECTOR3 posTrash;
				D3DXVECTOR3 sizeTrash;
				posTrash = pScene->GetPosition();
				sizeTrash = pScene->GetSize();
				
				//当たり判定
				if( (posTrash.y + sizeTrash.y/2 > posTrashBox.y - sizeTrash.y/2) &&
					(posTrash.y - sizeTrash.y/2 < posTrashBox.y + sizeTrash.y/2) &&
					(posTrash.x + sizeTrash.x/2 > posTrashBox.x - sizeTrash.x/2) &&
					(posTrash.x - sizeTrash.x/2 < posTrashBox.x + sizeTrash.x/2))
				{
					CScore::ScoreUp(1);
					pScene->Uninit();
				}
			}
		}
	}
}
void CTrashGame::Draw()
{
	CManager::Draw();
}
void CTrashGame::SetTrashPointer(CScene2D *pTrash)
{
	m_pTrash = pTrash;
}