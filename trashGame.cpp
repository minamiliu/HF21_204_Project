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
#include "debugproc.h"
#include "trajectory.h"
#include "getScore.h"
#include "trashPlayer.h"
#include "trashGameExplosion.h"
#include "message.h"
#include "change.h"
//============================================
// マクロ定義
//============================================
#define TEXTURENAME "data/TEXTURE/player000.png"
#define TEXTURE_POINT "data/TEXTURE/redPoint.png"
#define TEXTURE_TRASH "data/TEXTURE/ペットボトル.png"
#define TEXTURE_TRASHBOX "data/TEXTURE/ゴミ箱(灰色).png"
#define TEXTURE_GORILLA "data/TEXTURE/throwingGorilla.png"
#define TEXTURE_BGPOLYGON "data/TEXTURE/rendering003-16.png"
#define TEXTURE_PLAYER "data/TEXTURE/throwingMother.png"
#define TEXTURE_START "data/TEXTURE/start.png"
#define TEXTURE_FINISH "data/TEXTURE/finish.png"
#define GORILLA_GORILLA "data/TEXTURE/ゴリラ.png"
#define STAND_GORILLA "data/TEXTURE/ゴリラ(立ち絵).png"

#define TEXTURE_EXPLOSION "data/TEXTURE/explosion000.png"
#define	TEX_PATTERN_DIVIDE_X		(8)												// アニメーションパターンのテクスチャ内での分割数(Ｘ方向)
#define	TEX_PATTERN_DIVIDE_Y		(1)												// アニメーションパターンのテクスチャ内での分割数(Ｙ方向)
#define	TEX_PATTERN_SIZE_X			(1.0f / TEX_PATTERN_DIVIDE_X)					// １パターンのテクスチャサイズ(Ｘ方向)(1.0f/X方向分割数)
#define	TEX_PATTERN_SIZE_Y			(1.0f / TEX_PATTERN_DIVIDE_Y)					// １パターンのテクスチャサイズ(Ｙ方向)(1.0f/Y方向分割数)
#define	NUM_ANIM_PATTERN			(TEX_PATTERN_DIVIDE_X * TEX_PATTERN_DIVIDE_Y)	// アニメーションのパターン数(X方向分割数×Y方向分割数)
#define	TIME_CHANGE_PATTERN			(10)											// アニメーションの切り替わるタイミング(フレーム数)
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
CScene2D *CTrashGame::m_pCenterPoint = NULL;
CTime *pTime = NULL;
CPlayer2D *pPlayer2D = NULL;
int CTrashGame::m_nTrashGameCnt = 0;
CTrashPlayer *pAnimPlayer = NULL;
CScene2D *pExplosion = NULL;

bool bMessageFlag = false;
//============================================
//コンストラクタ
//============================================
CTrashGame::CTrashGame() : CManager(MODE_TRASHGAME)
{
	m_nTrashGameCnt = 0;
}

CTrashGame::~CTrashGame()
{
	
}

HRESULT CTrashGame::Init(void)
{ 
	m_pCamera->Init();
	//ゲーム起動時のマウスを位置を取ってしまうため、強制的に画面中央へ
	SetCursorPos(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
	//スコア初期化
	SaveScore(MODE_TRASHGAME,0);
	//テクスチャの割り当て
	CTrash::Load();
	CTrajectory::Load();
	CTrashPlayer::Load();
	//背景
	CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f),D3DXVECTOR3(SCREEN_WIDTH*1.2,SCREEN_HEIGHT*1.4,0.0f),TEXTURE_BGPOLYGON);
	//オブジェクトの生成
	//プレイヤー
	pAnimPlayer = CTrashPlayer::Create( D3DXVECTOR3( 150.0f, 580.0f, 0.0f), D3DXVECTOR3( 300.0f, 300.0f, 0.0f),TEXTURE_PLAYER);
	//ゴミ
	m_pTrash = CTrash::Create(D3DXVECTOR3(200.0f, 400.0f, 0.0f), D3DXVECTOR3(200.0f, 200.0f, 0.0f),TEXTURE_TRASH,CScene::OBJTYPE_TRASH);
	//スコア
	m_pScore = CScore::Create(D3DXVECTOR3(150, 50.0f, 0.0f), D3DXVECTOR3(300.0f, 50.0f, 0.0f), 6, BLUE(1.0f));
	//ゴミ箱
	//m_pTrashBox = CScene2D::Create(D3DXVECTOR3(1000.0f, 500.0f, 0.0f), D3DXVECTOR3(800.0f, 600.0f, 0.0f),TEXTURE_TRASHBOX);
	m_pTrashBox = CScene2D::Create(D3DXVECTOR3(1100.0f, 350.0f, 0.0f), D3DXVECTOR3(650.0f, 300.0f, 0.0f),TEXTURE_TRASHBOX);
	//タイム
	pTime = CTime::Create(D3DXVECTOR3(600, 50.0f, 0.0f),D3DXVECTOR3(100, 100.0f, 0.0f),3,12,true,D3DXCOLOR(255,255,255,255));
	pTime->StopTime();
	//マウスの位置を得る
	CPoint2D::Create(D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(0.0f,0.0f,0.0f),0);
	//つねに中央に
	m_pCenterPoint = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(70.0f, 70.0f, 0.0f),TEXTURE_POINT);
	//中央と現在位置の中間にテクスチャ
	m_pMidpoint = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(40.0f, 40.0f, 0.0f),TEXTURE_POINT);
	//マウスの位置にテクスチャ
	m_pMouse = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(120.0f, 120.0f, 0.0f),TEXTURE_POINT);

	pExplosion = NULL;
	bMessageFlag = false;
	return S_OK;
}

void CTrashGame::Uninit()
{
	CManager::Uninit();
}

void CTrashGame::Update()
{
	//入力などの更新、各シーンのUpdateの最初に呼び出す
	CManager::Update();

	m_nTrashGameCnt++;

	D3DXVECTOR3 posTrashBox;
	D3DXVECTOR3 sizeTrashBox;
	posTrashBox = m_pTrashBox->GetPosition();
	sizeTrashBox = m_pTrashBox->GetSize();
	
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	//時止め
	if( pInputKeyboard->GetKeyTrigger(DIK_T))
	{
		pTime->StopTime();
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
			if(type == CScene::OBJTYPE_TRASH || type == CScene::OBJTYPE_LEFTTRASH || type == CScene::OBJTYPE_RIGHTTRASH)
			{
				D3DXVECTOR3 posTrash;
				D3DXVECTOR3 sizeTrash;
				posTrash = pScene->GetPosition();
				sizeTrash = pScene->GetSize();
				//当たり判定
				if( (posTrash.y + sizeTrash.y/2 > posTrashBox.y - sizeTrashBox.y*0.8/2) &&
					(posTrash.y - sizeTrash.y/2 < posTrashBox.y + sizeTrashBox.y*0.8/2) &&
					(posTrash.x + sizeTrash.x/2 > posTrashBox.x - sizeTrashBox.x*0.4/2) &&
					(posTrash.x - sizeTrash.x/2 < posTrashBox.x + sizeTrashBox.x*0.4/2))
				{
					D3DXVECTOR3 speed;
					speed = ((CTrash*)pScene)->GetSpeed();
					if(speed.x > 0 &&
						//(posTrash.x - sizeTrash.x/2) < (posTrashBox.x - sizeTrashBox.x) //&&
						(posTrash.y - sizeTrash.y/2) > (posTrashBox.y - sizeTrashBox.y/2) )//||
						//(posTrash.x < (posTrashBox.x - sizeTrashBox.x/2)))
					{//外側の右端ではじく
						((CTrash*)pScene)->ReverseMove();
						CTrajectory::Create(D3DXVECTOR3(posTrash.x,posTrash.y,100.0f),D3DXVECTOR3(100,100,0.0f),CTrajectory::TJRTYPE_NORMAL,0.0);
					}
					else
					{//完全に入ってる
						//最初に入ったときに時間を動かす
						if(LoadScore(MODE_TRASHGAME) == 0)
						{
							pTime->StopTime();
							CMessage::Create(D3DXVECTOR3(SCREEN_WIDTH + 100,100,0),D3DXVECTOR3(250,250,0),TEXTURE_START);
						}
						//スコア追加
						if(((CTrash*)pScene)->GetTrashType() == CTrash::TRASHTYPE_NORMAL)
						{
							m_pScore->AddScore(100);
							CGetScore *pGetScore = CGetScore::Create(posTrash,D3DXVECTOR3(100,100,0.0f),3,BLUE(1.0));
							pGetScore->AddScore(100);
							CManager::AddScore(CManager::MODE_TRASHGAME,100);
						}
						else if(((CTrash*)pScene)->GetTrashType() == CTrash::TRASHTYPE_LIGHT)
						{
							m_pScore->AddScore(180);
							CGetScore *pGetScore = CGetScore::Create(posTrash,D3DXVECTOR3(140,140,0.0f),3,RED(1.0));
							pGetScore->AddScore(180);
							CManager::AddScore(CManager::MODE_TRASHGAME,180);
							for(int cnt=0;cnt<8;cnt++)
							{
								CTrajectory::Create(D3DXVECTOR3(posTrash.x,posTrash.y,100.0f),D3DXVECTOR3(100,100,0.0f),CTrajectory::TJRTYPE_ALLDIRECTION,2*3.14/8*cnt);
							}
						}
						else if(((CTrash*)pScene)->GetTrashType() == CTrash::TRASHTYPE_HEAVY)
						{
							m_pScore->AddScore(150);
							CGetScore *pGetScore = CGetScore::Create(posTrash,D3DXVECTOR3(120,120,0.0f),3,YELLOW(1.0));
							pGetScore->AddScore(150);
							CManager::AddScore(CManager::MODE_TRASHGAME,150);
						}
						//オブジェクトの位置を画面外へ -> 画面外判定で消滅
						pScene->SetPosition(D3DXVECTOR3(100.0f,1000.0f,0.0f));
						
					}
				}
			}
			else if(type == CScene::OBJTYPE_POINT2D)
			{//マウスの位置にテクスチャ
				
				//調整中
				/*if( CManager::GetInputMouse()->GetMouseLeftTrigger() )
				{
					m_pMouse->SetPosition(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f));
				}*/

				D3DXVECTOR3 posMouse;
				posMouse = pScene->GetPosition();
				m_pMouse->SetPosition(posMouse);


				//画面中心にテクスチャ
				m_pCenterPoint->SetPosition(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f));
				//マウスの位置と画面中央の間にテクスチャ
				D3DXVECTOR3 posMidpoint;
				posMidpoint= D3DXVECTOR3( (posMouse.x + SCREEN_WIDTH/2)/2,(posMouse.y + SCREEN_HEIGHT/2)/2,0.0f);
				m_pMidpoint->SetPosition(posMidpoint);
				//クリックしてないときは画面外へ
				if(!CManager::GetInputMouse()->GetMouseLeftPress())
				{
					m_pCenterPoint->SetPosition(D3DXVECTOR3(-100,-100,0.0f));
					m_pMidpoint->SetPosition(D3DXVECTOR3(-100,-100,0.0f));
					m_pMouse->SetPosition(D3DXVECTOR3(-100,-100,0.0f));
				}
			}
		}
	}
	//変身直前
	if(pTime->GetTime() == 11)
	{
		pAnimPlayer->SetColor(RED(1.0));
		if(pExplosion == NULL)
		{
			//煙
			//pExplosion = CTrashGameExplosion::Create(D3DXVECTOR3( 150.0f, 580.0f, 0.0f), D3DXVECTOR3( 400.0f, 400.0f, 0.0f));
			//pExplosion->ChangeTextureAnime(0, D3DXVECTOR2(TEX_PATTERN_SIZE_X,TEX_PATTERN_SIZE_Y),
											//D3DXVECTOR2(TEX_PATTERN_DIVIDE_X,TEX_PATTERN_DIVIDE_Y));

		}
	}
	
	if(pTime->GetTime() <= 11 && pTime->GetTime() >= 10)
	{
		
	}
	//残り時間が１０になったら
	if(pTime->GetTime() == 10)
	{
		pAnimPlayer->SetColor(WHITE(1.0));
		//playerのポインタを取る
		//CPlayer2D* pPlayer;
		//for(int nCntScene = 0;nCntScene < MAX_SCENE;nCntScene++)
		//{
		//	CScene *pScene;
		//	pScene = CScene::GetScene(nCntScene);
		//	if(pScene != NULL)
		//	{
		//		CScene::OBJTYPE type;
		//		type = pScene->GetObjType();
		//		if(type == CScene::OBJTYPE_PLAYER)
		//		{
		//			if( ((CPlayer2D*)pScene)->GetGorillaMode() == false )
		//			{
		//				//ゴリラモードへ
		//				((CPlayer2D*)pScene)->SetGorillaMode();
		
		//ゴリラモードにする
		if( pAnimPlayer->GetGorillaMode() == false )
		{
			pTime->StopTime();
			CChange::Create(TEXTURENAME,GORILLA_GORILLA,STAND_GORILLA);

			//pAnimPlayer->Uninit();
			//pAnimPlayer = NULL;
			//pAnimPlayer = CTrashPlayer::Create(D3DXVECTOR3( 150.0f, 580.0f, 0.0f), D3DXVECTOR3( 200.0f, 200.0f, 0.0f),TEXTURE_GORILLA);
			pAnimPlayer->SetGorillaMode();

			//ゴミを複数生成
			//CTrash::Create(D3DXVECTOR3(100.0f, 370.0f, 0.0f), D3DXVECTOR3(200.0f, 200.0f, 0.0f),TEXTURE_TRASH,CTrash::OBJTYPE_LEFTTRASH);
			//CTrash::Create(D3DXVECTOR3(300.0f, 370.0f, 0.0f), D3DXVECTOR3(200.0f, 200.0f, 0.0f),TEXTURE_TRASH,CTrash::OBJTYPE_RIGHTTRASH);
		}
						/*			}
				}
			}
			break;
		}*/
	}

	if(pAnimPlayer->GetGorillaMode() == true && CChange::GetState() == false)
	{
		pAnimPlayer->Uninit();
		pAnimPlayer = NULL;
		pAnimPlayer = CTrashPlayer::Create(D3DXVECTOR3( 150.0f, 580.0f, 0.0f), D3DXVECTOR3( 200.0f, 200.0f, 0.0f),TEXTURE_GORILLA);
		pAnimPlayer->SetGorillaMode();
		//ゴミを複数生成
		//CTrash::Create(D3DXVECTOR3(100.0f, 370.0f, 0.0f), D3DXVECTOR3(200.0f, 200.0f, 0.0f),TEXTURE_TRASH,CTrash::OBJTYPE_LEFTTRASH);
		//CTrash::Create(D3DXVECTOR3(300.0f, 370.0f, 0.0f), D3DXVECTOR3(200.0f, 200.0f, 0.0f),TEXTURE_TRASH,CTrash::OBJTYPE_RIGHTTRASH);
	
		CChange::changeState();
		pTime->StopTime();
	}

	if(pTime != NULL && pTime->GetTime() == 1)
	{
		if(bMessageFlag == false)
		{
			CMessage::Create(D3DXVECTOR3(SCREEN_WIDTH + 100,100,0),D3DXVECTOR3(200,200,0),TEXTURE_FINISH);
			bMessageFlag = true;
		}
	}
	//時間が０になったら
	if(pTime != NULL && pTime->GetTime() == 0)
	{
		if(bMessageFlag == false)
		{
			CMessage::Create(D3DXVECTOR3(SCREEN_WIDTH + 100,100,0),D3DXVECTOR3(200,200,0),TEXTURE_FINISH);
			bMessageFlag = true;
		}
		for(int nCntScene = 0;nCntScene < MAX_SCENE;nCntScene++)
		{
			CScene *pScene;
			pScene = CScene::GetScene(nCntScene);
			if(pScene != NULL)
			{
				CScene::OBJTYPE type;
				type = pScene->GetObjType();
				if(type == CScene::OBJTYPE_TRASH || type == CScene::OBJTYPE_LEFTTRASH || type == CScene::OBJTYPE_RIGHTTRASH)
				{
					((CTrash*)pScene)->TrashEnd();
				}
			}
		}

		//pTime->Uninit();
		//SaveScore(GAME_TRASH,);
		SetNextScene( MODE_TRASHGAMERESULT);
		//pTime->Uninit();
		//return;
		//pTime->StopTime();
		//pTime->Uninit();
		//pTime = NULL;

	}
#ifdef _DEBUG
	//シーンの切り替え
	if( pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		SetNextScene( MODE_ZEBRAGAME);
	}

	//シーンの切り替え
	if( pInputKeyboard->GetKeyTrigger(DIK_E))
	{
		SetNextScene( MODE_RESULT);
	}
#endif

	//シーンが切り替えるところ、各シーンのUpdateの最後に置いとく
	CManager::SceneChange();
}
void CTrashGame::Draw()
{
	CManager::Draw();
}
//次に投げるゴミのポインタをセット
void CTrashGame::SetTrashPointer(CTrash *pTrash)
{
	m_pTrash = pTrash;
}

int CTrashGame::GetTrashGameCnt(void)
{
	return m_nTrashGameCnt;
}