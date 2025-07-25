﻿//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: bullet2D.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/11
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "time.h"


//============================================
// マクロ定義
//============================================

//============================================
// 静的メンバー変数の初期化
//============================================

//=============================================================================
// 構造体定義
//=============================================================================

//=============================================================================
//コンストラクタ
//=============================================================================
CTime::CTime()
{
}

//=============================================================================
//デストラクタ
//=============================================================================
CTime::~CTime()
{
	
}


//=============================================================================
// ポリゴンの初期化処理
//=============================================================================

HRESULT CTime::Init(D3DXVECTOR3 numberPos, D3DXVECTOR3 numberSize, int maxKeta, int startTime, bool bCountDown, const D3DXCOLOR &col)
{
	CScore::Init( numberPos, numberSize, maxKeta, col);
	CScore::SetScore(startTime);

	m_nCntFrame = 0;
	m_nTime = 0;
	m_nTime = startTime;
	m_bCountDown = bCountDown;
	m_useFlag = true;
	return S_OK;
}




//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CTime::Uninit(void)
{
	CScore::Uninit();
}


//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CTime::Update(void)
{
	if(m_useFlag == true)
	{
		m_nCntFrame++;

		if( m_nCntFrame >= 60)
		{
			if( m_bCountDown == true)
			{
				if( m_nTime > 0) m_nTime--;
			}
			else
			{
				m_nTime++;
			}

			m_nCntFrame = 0;
			this->SetScore(m_nTime);
		}
	}
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CTime::Draw(void)
{
	CScore::Draw();
}

CTime *CTime::Create(D3DXVECTOR3 pos, D3DXVECTOR3 numberSize, int maxKeta, int startTime, bool bCountDown, const D3DXCOLOR &col)
{
	CTime *pTime;
	pTime = new CTime;
	pTime->Init(pos, numberSize, maxKeta, startTime, bCountDown, col);

	//テクスチャの読み込み
	pTime->Load();

	//桁分のテクスチャの割り当て
	pTime->BindAllTexture();
	
	return pTime;
}



bool CTime::TimeUp(void)
{
	if(m_bCountDown == true && m_nTime == 0)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

int CTime::GetTime(void)
{
	return m_nTime;
}

void CTime::StopTime(void)
{
	if(m_useFlag == true)
		m_useFlag = false;
	else if(m_useFlag == false)
		m_useFlag = true;
}

bool CTime::GetTimeFlag(void)
{
	return m_useFlag;
}