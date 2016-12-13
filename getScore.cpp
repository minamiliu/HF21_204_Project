//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: getScore.cpp
// 作成者:		 HAL東京ゲーム学科　山家啓介
// 作成日:       2016/12/13
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "score.h"
#include "number.h"
#include "getScore.h"
#include "scene.h"
//============================================
// マクロ定義
//============================================
#define TEXTURENAME "data/TEXTURE/number001.png"

#define	TEX_PATTERN_DIVIDE_X		(10)								// アニメーションパターンのテクスチャ内での分割数(Ｘ方向)
#define	TEX_PATTERN_DIVIDE_Y		(1)								// アニメーションパターンのテクスチャ内での分割数(Ｙ方向)
#define	TEX_PATTERN_SIZE_X			(1.0f/TEX_PATTERN_DIVIDE_X)		// １パターンのテクスチャサイズ(Ｘ方向)(1.0f/X方向分割数)
#define	TEX_PATTERN_SIZE_Y			(1.0f/TEX_PATTERN_DIVIDE_Y)		// １パターンのテクスチャサイズ(Ｙ方向)(1.0f/Y方向分割数)

#define	NUM_ANIM_PATTERN			(TEX_PATTERN_DIVIDE_X*TEX_PATTERN_DIVIDE_Y)	// アニメーションのパターン数(X方向分割数×Y方向分割数)
//#define	TIME_CHANGE_PATTERN			(5)								// アニメーションの切り替わるタイミング(フレーム数)

//============================================
// 静的メンバー変数の初期化
//============================================

//=============================================================================
// 構造体定義
//=============================================================================

//=============================================================================
//コンストラクタ
//=============================================================================
CGetScore::CGetScore()
{
	m_ppPolygon = NULL;
	m_pTexture = NULL;
}

//=============================================================================
//デストラクタ
//=============================================================================
CGetScore::~CGetScore()
{
	
}


//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CGetScore::Init(void)
{
	return S_OK;
}
HRESULT CGetScore::Init(D3DXVECTOR3 numberPos, D3DXVECTOR3 numberSize, int maxKeta, const D3DXCOLOR &col)
{
	//初期値を設定
	m_nMaxKeta = maxKeta;
	m_nValue = 0;
	m_pos = numberPos;
	m_size = numberSize;
	m_nApCnt = 0;
	//Numberポインター配列の生成
	m_ppPolygon = new CNumber*[maxKeta];

	//スタート位置(右)と桁サイズの計算
	D3DXVECTOR3 rightPos = numberPos;
	D3DXVECTOR3 ketaSize = numberSize;
	ketaSize.x /= maxKeta;
	rightPos.x = numberPos.x + ketaSize.x * (maxKeta - 1) / 2.0f;
	
	//桁分のNumberの生成
	D3DXVECTOR3 tmpPos = rightPos;
	for(int cntKeta = 0; cntKeta < m_nMaxKeta; cntKeta++)
	{
		m_ppPolygon[cntKeta] = CNumber::Create( tmpPos , ketaSize, D3DXVECTOR2( TEX_PATTERN_SIZE_X, TEX_PATTERN_SIZE_Y));
		tmpPos.x -= ketaSize.x;
	}

	//色を設定
	SetColor( col);

	return S_OK;
}




//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CGetScore::Uninit(void)
{
	for(int cntKeta = 0; cntKeta < m_nMaxKeta; cntKeta++)
	{
		//数字桁の破棄
		m_ppPolygon[cntKeta]->Uninit();
	}

	delete[] m_ppPolygon;
	m_ppPolygon = NULL;

	//テクスチャの破棄
	this->Unload();
	
	//オブジェクトの破棄
	Release();
}


//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CGetScore::Update(void)
{
	D3DXVECTOR3 posGetScore = GetPosition();
	
	m_nApCnt++;
	posGetScore.y-=1;

	SetPosition(posGetScore);
	
	if(m_nApCnt >60)
	{
		this->Uninit();
	}

}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CGetScore::Draw(void)
{
	for(int nKeta = 0; nKeta < m_nMaxKeta; nKeta++)
	{
		m_ppPolygon[nKeta]->Draw();
	}
}

//=============================================================================
// ポリゴンの生成処理
//=============================================================================
CGetScore *CGetScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int maxKeta, const D3DXCOLOR &col)
{
	CGetScore *pGetScore;
	pGetScore = new CGetScore;
	pGetScore->Init(pos, size, maxKeta, col);

	//テクスチャの読み込み
	pGetScore->Load();

	//桁分のテクスチャの割り当て
	pGetScore->BindAllTexture();
	
	return pGetScore;
}

//=============================================================================
//
//=============================================================================
HRESULT CGetScore::Load(void)
{
	if( m_pTexture == NULL)
	{
		LPDIRECT3DDEVICE9 pDevice;
		pDevice = CManager::GetRenderer()->GetDevice();

		// テクスチャの読み込み
		D3DXCreateTextureFromFile( pDevice, TEXTURENAME, &m_pTexture);
	}

	return S_OK;
}

//=============================================================================
//
//=============================================================================
void CGetScore::Unload(void)
{
	//テクスチャの破棄
	if( m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
//数字をそのまま表示する
//=============================================================================
void CGetScore::SetScore(int score)
{
	int number;

	//範囲チェック
	int maxGetScore = powf( 10.0f, m_nMaxKeta) -1;
	if(score >  maxGetScore) score = maxGetScore;
	else if(score < 0) score = 0;

	//値を更新
	m_nValue = score;

	for(int nKeta = 0; nKeta < m_nMaxKeta; nKeta++)
	{
		//一番右の数字を取る
		number = int(score % (int)powf( 10.0f, float(nKeta+1)) / powf( 10.0f, float(nKeta)));

		//テクスチャをずらす
		m_ppPolygon[nKeta]->ChangeTextureAnime( number, D3DXVECTOR2( TEX_PATTERN_SIZE_X, TEX_PATTERN_SIZE_Y), D3DXVECTOR2( TEX_PATTERN_DIVIDE_X, TEX_PATTERN_DIVIDE_Y));
	}
}

//=============================================================================
//桁分のテクスチャの割り当て
//=============================================================================
void CGetScore::BindAllTexture(void)
{
	for(int cntKeta = 0; cntKeta < m_nMaxKeta; cntKeta++)
	{
		//テクスチャの割り当て
		m_ppPolygon[cntKeta]->BindTexture( m_pTexture);
	}
}

//=============================================================================
//全桁の色を一気に変更
//=============================================================================
void CGetScore::SetColor(const D3DXCOLOR &col)
{
	for(int cntKeta = 0; cntKeta < m_nMaxKeta; cntKeta++)
	{
		m_ppPolygon[cntKeta]->SetColor( col);
	}
}

//=============================================================================
//得点を上げる
//=============================================================================
void CGetScore::AddScore(int score)
{
	m_nValue += score;
	SetScore( m_nValue);
}
//=============================================================================
//座標を取得
//=============================================================================
D3DXVECTOR3 CGetScore::GetPosition(void)
{
	return m_pos;
}
//=============================================================================
//サイズを取得
//=============================================================================
D3DXVECTOR3 CGetScore::GetSize(void)
{
	return m_size;
}

void CGetScore::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
	for(int cntKeta = 0; cntKeta < m_nMaxKeta; cntKeta++)
	{
		D3DXVECTOR3 posGetScore;
		posGetScore = m_ppPolygon[cntKeta]->GetPosition();
		posGetScore.y = pos.y;
		//数字桁の破棄
		m_ppPolygon[cntKeta]->SetPosition(posGetScore);
	}
}