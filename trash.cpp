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
//============================================
// マクロ定義
//============================================
#define TEXTURENAME "data/TEXTURE/player000.png"
#define GRAVITY_POINT (0.98f)
#define WEIGHT_COEFFICIENT_LIGHT (0.5f)
#define WEIGHT_COEFFICIENT_HEAVY (3.0f)
//=============================================================================
// 構造体定義
//=============================================================================


//静的メンバ変数
int CTrash::m_cnt = 0;


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
	//CTrash* pTrash;
	//CTrashBox2D* pTrashBox;
	D3DXVECTOR3 posTrash = GetPosition();
		//pTrash->GetPosition();
	//D3DXVECTOR3 sizeTrash = pTrash->GetSize();
	//D3DXVECTOR3 posTrashBox = GetPosition();
	//D3DXVECTOR3 sizeTrashBox = pTrashBox->GetSize();

	if(CManager::GetInputMouse()->GetMouseLeftPress() && m_fallFlag == false)
	{
		//マウスの移動量を取得
		m_speed.x -= CManager::GetInputMouse()->GetMouseAxisX()/3;
		m_speed.y += CManager::GetInputMouse()->GetMouseAxisY()/3;
	}

	if(CManager::GetInputMouse()->GetMouseLeftRelease() && m_fallFlag == false)
	{
		//マウスを話したら落下フラグをＯＮ
		m_fallFlag = true;
		//出現フラグをＯＮ
		m_apFlag = true;
	}
	if(m_fallFlag == true)
	{
		//放物線移動
		posTrash.x += m_speed.x / 10;
		m_speed.y -= GRAVITY_POINT * WEIGHT_COEFFICIENT_HEAVY;
		posTrash.y += -m_speed.y / 10;
	}
	if(m_apFlag == true)
	{
		//出現タイミングをカウントで計る
		m_cnt++;
		if(m_cnt > 40)
		{
			//新しいオブジェクトを生成
			CScene2D* pTrash;
			pTrash = CTrash::Create(D3DXVECTOR3(200.0f, 300.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f));
			//カウントをリセット
			m_cnt = 0;
			//一度の投げで２回以上出現しないようにフラグを管理
			m_apFlag = false;
		}
	}
	this->CTrash::SetPosition(posTrash);
	//デバッグ用print
	/*PrintDebugProc("\nm_speed.x:%f",m_speed.x);
	PrintDebugProc("\nm_speed.y:%f",m_speed.y);
	PrintDebugProc("\nflag:%d",m_fallFlag);
	PrintDebugProc("\ncnt:%d",m_cnt);*/
	
	if(posTrash.y > SCREEN_HEIGHT)
	{//画面外判定
		if(m_apFlag == true)//その投げによって再出現していないなら
		{
			CScene2D* pTrash;
			//生成
			pTrash = CTrash::Create(D3DXVECTOR3(200.0f, 300.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f));
			CTrashGame::SetTrashPointer(pTrash);
			//再出現しないようにリセット
			m_cnt = 0;
			m_apFlag = false;
		}
		m_fallFlag = false;
		//CScore::ScoreUp(1);
		//破棄
		this->Uninit();
	}
	

	//当たり判定
	/*if( (posTrash.y + sizeTrash.y/2 > posTrashBox.y - sizeTrash.y/2) &&
		(posTrash.y - sizeTrash.y/2 < posTrashBox.y + sizeTrash.y/2) &&
		(posTrash.x + sizeTrash.x/2 > posTrashBox.x - sizeTrash.x/2) &&
		(posTrash.x - sizeTrash.x/2 < posTrashBox.x + sizeTrash.x/2))
	{
		CScore::ScoreUp(1);
	}*/


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
CTrash *CTrash::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CTrash *pTrash;
	pTrash = new CTrash;
	pTrash->Init(pos, size);

	//テクスチャの割り当て
	pTrash->Load( TEXTURENAME);
	return pTrash;
}

