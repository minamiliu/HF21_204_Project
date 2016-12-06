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
#define TEXTURE_TRASH "data/TEXTURE/ペットボトル.png"
#define GRAVITY_POINT (0.98f)
#define WEIGHT_COEFFICIENT_LIGHT (0.5f)
#define WEIGHT_COEFFICIENT_HEAVY (3.0f)
//=============================================================================
// 構造体定義
//=============================================================================


//静的メンバ変数
int CTrash::m_cnt = 0;
LPDIRECT3DTEXTURE9 CTrash::m_pTexture = NULL;

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
	m_gravityCoefficient = 1.0;//1.0+rand()%4;//1.0~4.0のランダムな値
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
		m_speed.y -= GRAVITY_POINT * m_gravityCoefficient;
		posTrash.y += -m_speed.y / 10;
	}
	if(m_apFlag == true)
	{
		//出現タイミングをカウントで計る
		m_cnt++;
		if(m_cnt > 20)
		{
			//新しいオブジェクトを生成
			CScene2D* pTrash;
			pTrash = CTrash::Create(D3DXVECTOR3(200.0f, 300.0f, 0.0f), D3DXVECTOR3(200.0f, 200.0f, 0.0f));
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
			CTrash* pTrash;
			//生成
			pTrash = CTrash::Create(D3DXVECTOR3(200.0f, 300.0f, 0.0f), D3DXVECTOR3(200.0f, 200.0f, 0.0f));
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
CTrash *CTrash::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CTrash *pTrash;
	pTrash = new CTrash;
	pTrash->Init(pos, size);

	//テクスチャの割り当て
	pTrash->Load(TEXTURE_TRASH);
	
	//pTrash->CScene2D::BindTexture(m_pTexture);

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

