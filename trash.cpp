//============================================
//
// タイトル:	 HF
// プログラム名: trash.cpp
// 作成者:		 HAL東京ゲーム学科　yamaga keisuke
// 作成日:       2016/11/10
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "manager.h"
#include "input.h"
#include "trash.h"
#include "debugproc.h"
#include "score.h"
#include "trashBox.h"
#include "trashGame.h"
#include "player2D.h"
#include "trajectory.h"
#include "renderer.h"
//============================================
// マクロ定義
//============================================
#define TEXTURE_TRASH "data/TEXTURE/ペットボトル.png"
#define TEXTURE_BANANA "data/TEXTURE/banana.png"
#define TEXTURE_PAPER "data/TEXTURE/paper.png"

#define GRAVITY_POINT (0.98f)
#define WEIGHT_COEFFICIENT_LIGHT (0.5f)
#define WEIGHT_COEFFICIENT_HEAVY (3.0f)
//=============================================================================
// 構造体定義
//=============================================================================


//静的メンバ変数
int CTrash::m_cnt = 0;
LPDIRECT3DTEXTURE9 CTrash::m_pTexture[] = {};

//=============================================================================
//コンストラクタ
//=============================================================================
CTrash::CTrash()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CTrash::~CTrash()
{
	m_gravityCoefficient = 1.0;
}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CTrash::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(CScene::OBJTYPE_TRASH);
	m_speed = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_fallFlag = false;
	m_cnt = 0;
	m_apFlag = false;
	//m_gravityCoefficient = 1.0;//1.0+rand()%4;//1.0~4.0のランダムな値
	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CTrash::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CTrash::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	D3DXVECTOR3 posTrash = GetPosition();

	CDebugProc::Print("\n差異:%f",m_gravityCoefficient);

	
	if(CManager::GetInputMouse()->GetMouseLeftPress() && m_fallFlag == false && CTrashGame::GetState() != CTrashGame::STATE_CHANGE)
	{
		//マウスの移動量を取得
		m_speed.x -= CManager::GetInputMouse()->GetMouseAxisX()/3;
		switch(GetObjType())
		{
		case OBJTYPE_LEFTTRASH:
			m_speed.x *= 1.00;
			break;
		case OBJTYPE_TRASH:
			m_speed.x *= 1.01;
			break;
		case OBJTYPE_RIGHTTRASH:
			m_speed.x *= 1.02;
			break;
		}
		m_speed.y += CManager::GetInputMouse()->GetMouseAxisY()/3;
	}

	if(CManager::GetInputMouse()->GetMouseLeftRelease() && m_fallFlag == false && CTrashGame::GetState() != CTrashGame::STATE_CHANGE)
	{
		//マウスを話したら落下フラグをＯＮ
		m_fallFlag = true;
		//出現フラグをＯＮ
		m_apFlag = true;
		//移動量の最大（最小）範囲を設定
		if(m_speed.x > 200)
		{
			m_speed.x = 200;
		}
		else if(m_speed.y < -200)
		{
			m_speed.y = -200;
		}
	}

	if(m_fallFlag == true)
	{

		//軌跡生成
		if(CTrashGame::GetTrashGameCnt() % 5 == 0)
		{
			CTrajectory::Create(D3DXVECTOR3(posTrash.x,posTrash.y,100.0f),D3DXVECTOR3(50,50,0.0f),CTrajectory::TJRTYPE_NORMAL,0.0);
		}
		//放物線移動
		posTrash.x += m_speed.x / 10;
		m_speed.y -= GRAVITY_POINT * m_gravityCoefficient;
		posTrash.y += -m_speed.y / 10;
	}
	if(m_apFlag == true && CTrashGame::GetState())
	{
		//出現タイミングをカウントで計る
		m_cnt++;
		if(m_cnt > 20)
		{
			//新しいオブジェクトを生成
			int nNum = rand()%3;//０～２のランダムな数
			CScene2D* pTrash;
			if(nNum == 0)
			{
				if(GetObjType() == OBJTYPE_TRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(200.0f, 400.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_BANANA,OBJTYPE_TRASH);
				}
				else if(GetObjType() == OBJTYPE_LEFTTRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(100.0f, 370.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_BANANA,OBJTYPE_LEFTTRASH);
				}
				else if(GetObjType() == OBJTYPE_RIGHTTRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(300.0f, 370.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_BANANA,OBJTYPE_RIGHTTRASH);
				}
			}
			else if(nNum == 1)
			{
				if(GetObjType() == OBJTYPE_TRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(200.0f, 400.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_TRASH,OBJTYPE_TRASH);
				}
				else if(GetObjType() == OBJTYPE_LEFTTRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(100.0f, 370.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_TRASH,OBJTYPE_LEFTTRASH);
				}
				else if(GetObjType() == OBJTYPE_RIGHTTRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(300.0f, 370.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_TRASH,OBJTYPE_RIGHTTRASH);
				}
			}
			else if(nNum == 2)
			{
				if(GetObjType() == OBJTYPE_TRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(200.0f, 400.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_PAPER,OBJTYPE_TRASH);
				}
				else if(GetObjType() == OBJTYPE_LEFTTRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(100.0f, 370.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_PAPER,OBJTYPE_LEFTTRASH);
				}
				else if(GetObjType() == OBJTYPE_RIGHTTRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(300.0f, 370.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_PAPER,OBJTYPE_RIGHTTRASH);
				}
			}
			//カウントをリセット
			m_cnt = 0;
			//一度の投げで２回以上出現しないようにフラグを管理
			m_apFlag = false;
		}
	}
	this->CTrash::SetPosition(posTrash);
	
	if(posTrash.y > SCREEN_HEIGHT || posTrash.x > SCREEN_WIDTH || posTrash.x < 0)
	{//画面外判定
		if(m_apFlag == true)//その投げによって再出現していないなら
		{
			//生成
			CTrash* pTrash;
			int nNum = rand()%3;//０～２のランダムな数
			if(nNum == 0)
			{
				if(GetObjType() == OBJTYPE_TRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(200.0f, 400.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_BANANA,OBJTYPE_TRASH);
				}
				else if(GetObjType() == OBJTYPE_LEFTTRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(100.0f, 370.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_BANANA,OBJTYPE_LEFTTRASH);
				}
				else if(GetObjType() == OBJTYPE_RIGHTTRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(300.0f, 370.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_BANANA,OBJTYPE_RIGHTTRASH);
				}
			}
			else if(nNum == 1)
			{
				if(GetObjType() == OBJTYPE_TRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(200.0f, 400.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_TRASH,OBJTYPE_TRASH);
				}
				else if(GetObjType() == OBJTYPE_LEFTTRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(100.0f, 370.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_TRASH,OBJTYPE_LEFTTRASH);
				}
				else if(GetObjType() == OBJTYPE_RIGHTTRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(300.0f, 370.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_TRASH,OBJTYPE_RIGHTTRASH);
				}
			}
			else if(nNum == 2)
			{
				if(GetObjType() == OBJTYPE_TRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(200.0f, 400.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_PAPER,OBJTYPE_TRASH);
				}
				else if(GetObjType() == OBJTYPE_LEFTTRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(100.0f, 370.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_PAPER,OBJTYPE_LEFTTRASH);
				}
				else if(GetObjType() == OBJTYPE_RIGHTTRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(300.0f, 370.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_PAPER,OBJTYPE_RIGHTTRASH);
				}
			}
			CTrashGame::SetTrashPointer(pTrash);
			//再出現しないようにリセット
			m_cnt = 0;
			m_apFlag = false;
		}
		m_fallFlag = false;
		//破棄
		this->Uninit();
	}
	
	
	CScene2D::Update();
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CTrash::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ポリゴンの生成処理
//=============================================================================
CTrash *CTrash::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,LPCSTR strFileName,OBJTYPE type)
{
	CTrash *pTrash;
	pTrash = new CTrash;
	pTrash->Init(pos, size);
	pTrash->SetObjType(type);
	int num = rand()%3;
	float plus;
	switch(num)
	{
	case 0:
		plus = 0.0;
		break;
	case 1:
		plus = 0.4;
		break;
	case 2:
		plus = 0.7;
		break;
	}

	if(strFileName == TEXTURE_TRASH)
	{
		pTrash->m_gravityCoefficient = 1.8 + plus;
		pTrash->m_TrashType = TRASHTYPE_HEAVY;
	}
	else if(strFileName == TEXTURE_BANANA)
	{
		pTrash->m_gravityCoefficient = 1.5 + plus;
		pTrash->m_TrashType = TRASHTYPE_NORMAL;
	}
	else if(strFileName == TEXTURE_PAPER)
	{
		pTrash->m_gravityCoefficient = 0.5 + plus;
		pTrash->m_TrashType = TRASHTYPE_LIGHT;
	}
	
	pTrash->CScene2D::BindTexture(m_pTexture[pTrash->m_TrashType]);

	return pTrash;
}

D3DXVECTOR3 CTrash::GetSpeed(void)
{
	return m_speed;
}

void CTrash::SetSpeed(D3DXVECTOR3 speed)
{
	m_speed = speed;
}
	
void CTrash::ReverseMove(void)
{
	m_speed.x *= -1;
}

CTrash::TRASHTYPE CTrash::GetTrashType(void)
{
	return m_TrashType;
}
//タイムアップ時に呼ぶ
void CTrash::TrashEnd(void)
{
	//落下フラグをＯＮ
	m_fallFlag = true;
	//出現フラグをOFF
	m_apFlag = false;
}

void CTrash::Load(void)
{
	for(int cnt=0 ;cnt<TRASHTYPE_MAX;cnt++)
	{
		LPCSTR strFileName;
		switch( cnt)
		{
		case TRASHTYPE_NORMAL:
			strFileName = TEXTURE_BANANA;
			break;
		case TRASHTYPE_LIGHT:
			strFileName = TEXTURE_PAPER;
			break;
		case TRASHTYPE_HEAVY:
			strFileName = TEXTURE_TRASH;
			break;
		}

		if( m_pTexture[cnt] == NULL)
		{
			LPDIRECT3DDEVICE9 pDevice;
			pDevice = CManager::GetRenderer()->GetDevice();
			// テクスチャの読み込み
			D3DXCreateTextureFromFile( pDevice, strFileName, &m_pTexture[cnt]);
		}
	}
}