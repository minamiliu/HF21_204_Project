//============================================
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
#include "number.h"


//============================================
// マクロ定義
//============================================
#define TEXTURENAME "data/TEXTURE/number000.png"

#define	TEX_PATTERN_DIVIDE_X		(10)								// アニメーションパターンのテクスチャ内での分割数(Ｘ方向)
#define	TEX_PATTERN_DIVIDE_Y		(1)								// アニメーションパターンのテクスチャ内での分割数(Ｙ方向)
#define	TEX_PATTERN_SIZE_X			(1.0f/TEX_PATTERN_DIVIDE_X)		// １パターンのテクスチャサイズ(Ｘ方向)(1.0f/X方向分割数)
#define	TEX_PATTERN_SIZE_Y			(1.0f/TEX_PATTERN_DIVIDE_Y)		// １パターンのテクスチャサイズ(Ｙ方向)(1.0f/Y方向分割数)

#define	NUM_ANIM_PATTERN			(TEX_PATTERN_DIVIDE_X*TEX_PATTERN_DIVIDE_Y)	// アニメーションのパターン数(X方向分割数×Y方向分割数)
//#define	TIME_CHANGE_PATTERN			(5)								// アニメーションの切り替わるタイミング(フレーム数)

//============================================
// 静的メンバー変数の初期化
//============================================
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;

//=============================================================================
// 構造体定義
//=============================================================================

//=============================================================================
//コンストラクタ
//=============================================================================
CNumber::CNumber()
{
}

//=============================================================================
//デストラクタ
//=============================================================================
CNumber::~CNumber()
{
	
}


//=============================================================================
// ポリゴンの初期化処理
//=============================================================================

HRESULT CNumber::Init(D3DXVECTOR3 numberPos, D3DXVECTOR3 numberSize, int maxKeta)
{
	m_nMaxKeta = maxKeta;
	D3DXVECTOR3 rightPos = numberPos;
	D3DXVECTOR3 ketaSize = numberSize;

	m_ppPolygon = new CScene2D*[maxKeta];

	//初期化
	ketaSize.x /= maxKeta;
	rightPos.x = numberPos.x + ketaSize.x * (maxKeta - 1) / 2.0f;
	
	D3DXVECTOR3 tmpPos = rightPos;
	for(int cntKeta = 0; cntKeta < m_nMaxKeta; cntKeta++)
	{
		m_ppPolygon[cntKeta] = new CScene2D;
		m_ppPolygon[cntKeta]->Init( tmpPos , ketaSize, D3DXVECTOR2( TEX_PATTERN_SIZE_X, TEX_PATTERN_SIZE_Y));
		tmpPos.x -= ketaSize.x;
	}

	//タイマーを初期化
	m_nCntFrame = 0;
	m_nCntTime = 0;
	return S_OK;
}




//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CNumber::Uninit(void)
{
	for(int cntKeta = 0; cntKeta < m_nMaxKeta; cntKeta++)
	{
		//数字桁の破棄
		m_ppPolygon[cntKeta]->Uninit();
	}

	delete[] m_ppPolygon;
	m_ppPolygon = NULL;
	
	//number本体の破棄
	CScene2D::Uninit();
}


//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CNumber::Update(void)
{
	m_nCntFrame++;

	if( m_nCntFrame >= 60)
	{
		m_nCntFrame = 0;
		m_nCntTime++;
		this->SetNumber(m_nCntTime);
	}

	
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CNumber::Draw(void)
{
	for(int nKeta = 0; nKeta < m_nMaxKeta; nKeta++)
	{
		m_ppPolygon[nKeta]->Draw();
	}
}

//=============================================================================
// ポリゴンの生成処理
//=============================================================================
CNumber *CNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CNumber *pNumber;
	pNumber = new CNumber;
	pNumber->Init(pos, size, 6);

	//テクスチャの読み込み
	pNumber->Load();

	for(int cntKeta = 0; cntKeta < pNumber->m_nMaxKeta; cntKeta++)
	{
		//テクスチャの割り当て
		pNumber->m_ppPolygon[cntKeta]->BindTexture( m_pTexture);
	}
	
	return pNumber;
}

//=============================================================================
//
//=============================================================================
HRESULT CNumber::Load(void)
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
void CNumber::Unload(void)
{
	//テクスチャの破棄
	if( m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
//
//=============================================================================
void CNumber::SetNumber(const int score)
{
	int number;

	for(int nKeta = 0; nKeta < m_nMaxKeta; nKeta++)
	{
		//一番右の数字を取る
		number = int(score % (int)powf( 10.0f, float(nKeta+1)) / powf( 10.0f, float(nKeta)));

		//テクスチャをずらす
		m_ppPolygon[nKeta]->ChangeTextureAnime( number, D3DXVECTOR2( TEX_PATTERN_SIZE_X, TEX_PATTERN_SIZE_Y), D3DXVECTOR2( TEX_PATTERN_DIVIDE_X, TEX_PATTERN_DIVIDE_Y));
	}
}

