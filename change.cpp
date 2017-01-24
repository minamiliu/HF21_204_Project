//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: player2D.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/10/19
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "change.h"
#include "trashGameExplosion.h"
#include "effectBG.h"
#include "scene2D.h"
#include "changeTex.h"
#include "sound.h"

//============================================
// マクロ定義
//============================================
#define TEXTURE_BG "data/TEXTURE/effectBG.png"

#define	TEX_PATTERN_DIVIDE_X		(8)												// アニメーションパターンのテクスチャ内での分割数(Ｘ方向)
#define	TEX_PATTERN_DIVIDE_Y		(1)												// アニメーションパターンのテクスチャ内での分割数(Ｙ方向)
#define	TEX_PATTERN_SIZE_X			(1.0f / TEX_PATTERN_DIVIDE_X)					// １パターンのテクスチャサイズ(Ｘ方向)(1.0f/X方向分割数)
#define	TEX_PATTERN_SIZE_Y			(1.0f / TEX_PATTERN_DIVIDE_Y)					// １パターンのテクスチャサイズ(Ｙ方向)(1.0f/Y方向分割数)
#define	NUM_ANIM_PATTERN			(TEX_PATTERN_DIVIDE_X * TEX_PATTERN_DIVIDE_Y)	// アニメーションのパターン数(X方向分割数×Y方向分割数)
#define	TIME_CHANGE_PATTERN			(10)											// アニメーションの切り替わるタイミング(フレーム数)
//============================================

//=============================================================================
// 構造体定義
//=============================================================================
CScene2D *CChange::m_pChamgeBg = NULL;
CTrashGameExplosion *pExplosion = NULL;
CChangeTex *pPlayer = NULL;
CChangeTex *pAnimal = NULL;
CChangeTex *pAnimalPlayer = NULL;
bool CChange::m_bAnimalPlayerFlag = false;
bool CChange::m_bState = true;
int CChange::changeCnt = 0;
CEffectBG *pEffect = NULL;
LPCSTR CChange::m_StrAnimalPlayerFileName;
//=============================================================================
//コンストラクタ
//=============================================================================
CChange::CChange()
{
	m_pChamgeBg = NULL;
	pPlayer = NULL;
	pAnimal = NULL;
	pAnimalPlayer = NULL;
}

//=============================================================================
//デストラクタ
//=============================================================================
CChange::~CChange()
{
	
}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================

HRESULT CChange::Init( LPCSTR strPlayerFileName, LPCSTR strAnimalFileName, LPCSTR strAnimalPlayerFileName)
{
	pEffect = CEffectBG::Create( D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT/2, 0.0f));	
	//pAnimalPlayer = CChangeTex::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f),D3DXVECTOR3(300,300,0),strAnimalPlayerFileName);
	pPlayer = CChangeTex::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f),D3DXVECTOR3(300,300,0),strPlayerFileName);
	pAnimal = CChangeTex::Create(D3DXVECTOR3(SCREEN_WIDTH+100, SCREEN_HEIGHT/2, 0.0f),D3DXVECTOR3(300,300,0),strAnimalFileName);
	
	changeCnt = 0;
	m_bState = true;
	m_bAnimalPlayerFlag = false;
	pAnimalPlayer = NULL;
	m_StrAnimalPlayerFileName = strAnimalPlayerFileName;

	//SE
	CSound *pSound = CManager::GetSound();
	pSound->Play(CSound::SOUND_LABEL_SE_CHANGE);
	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CChange::Uninit(void)
{
	pExplosion = NULL;

	//pAnimalPlayer->Uninit();
	pAnimalPlayer = NULL;

	pEffect->Uninit();
	pEffect = NULL;
	//オブジェクトの破棄
	Release();
}


//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CChange::Update(void)
{
	changeCnt++;
	//動物絵の更新
	D3DXVECTOR3 pos;
	if(pAnimal != NULL)
	{
		pos = pAnimal->GetPosition();
		pos.x-=8;
		pAnimal->SetPosition(pos);
	}
	
	if(pAnimal != NULL && pPlayer != NULL)
	{
		D3DXVECTOR3 playerPos = pPlayer->GetPosition();
		if(pos.x <= playerPos.x)
		{
			pPlayer->Uninit();
			pPlayer = NULL;
			pAnimal->Uninit();
			pAnimal = NULL;
			pExplosion = CTrashGameExplosion::Create(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3( 400.0f, 400.0f, 0.0f));
			pExplosion->ChangeTextureAnime(0, D3DXVECTOR2(TEX_PATTERN_SIZE_X,TEX_PATTERN_SIZE_Y),
									D3DXVECTOR2(TEX_PATTERN_DIVIDE_X,TEX_PATTERN_DIVIDE_Y));
			changeCnt = 0;
		}
	}

	if(pExplosion != NULL)
	{
		if(changeCnt == 8 * 10)
		{
			m_bAnimalPlayerFlag = true;
			pAnimalPlayer = CChangeTex::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f),D3DXVECTOR3(160,300,0),m_StrAnimalPlayerFileName);
		}
	}

	if(m_bAnimalPlayerFlag == true)
	{
		D3DXVECTOR3 animalPlayerPos = pAnimalPlayer->GetPosition();
		animalPlayerPos.x-=8;
		pAnimalPlayer->SetPosition(animalPlayerPos);
		if(animalPlayerPos.x  <= -100)
		{
			m_bState = false;
			if(pAnimalPlayer != NULL)
			{
				pAnimalPlayer->Uninit();
			}
		}
	}
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CChange::Draw(void)
{

}

//=============================================================================
// ポリゴンの生成処理
//=============================================================================
CChange *CChange::Create(LPCSTR strPlayerFileName, LPCSTR strAnimalFileName, LPCSTR strAnimalPlayerFileName)
{
	CChange *pChange;
	pChange = new CChange;
	pChange->Init(strPlayerFileName, strAnimalFileName,strAnimalPlayerFileName);
	
	return pChange;
}
//変身演出の状態を返す
bool CChange::GetState(void)
{
	return m_bState;
}

void CChange::changeState(void)
{
	if(m_bState == true)
	{
		m_bState = false;
	}
	else if(m_bState == false)
	{
		m_bState = true;
	}
}

D3DXVECTOR3 CChange::GetPosition(void)
{
	return D3DXVECTOR3(0,0,0);
}
D3DXVECTOR3 CChange::GetSize(void)
{
	return D3DXVECTOR3(0,0,0);
}
void CChange::SetPosition(D3DXVECTOR3 pos)
{

}