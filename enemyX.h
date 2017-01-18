//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: enemyX.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/12/12
//
//============================================

#ifndef _ENEMYX_H_
#define _ENEMYX_H_

//============================================
//インクルードファイル
//============================================
#include "sceneX.h"

//============================================
//マクロ定義
//============================================
#define MAX_LIMB (4)
//============================================
//前方宣言
//============================================
class CShadow;
class CLimbX;

//============================================
//構造体定義
//============================================
class CEnemyX : public CSceneX
{
public:
	typedef struct
	{
		int nFrame;
		D3DXVECTOR3 front;
		float rotY;
	}MOTION;

	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_000,
		TYPE_MAX,
	}TYPE;

	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_STUN,
		STATE_MAX,
	}STATE;

	CEnemyX();
	virtual ~CEnemyX();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetState(STATE state, int nCntState);
	STATE GetState(void);

	static CEnemyX *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, TYPE type);
	static HRESULT Load(void);
	static void Unload(void);
	static HRESULT LoadMotion(void);

protected:
	D3DXVECTOR3 Get2RotDiffAngle( D3DXVECTOR3 rot, D3DXVECTOR3 rotTarget);
	void UpdateMotion(void);

private:
	//モデル関係
	static LPDIRECT3DTEXTURE9	m_pTexture		[TYPE_MAX];		// テクスチャへのポインタ
	static LPD3DXMESH			m_pD3DXMesh		[TYPE_MAX];		// メッシュ情報へのポインタ
	static LPD3DXBUFFER			m_pD3DXBuffMat	[TYPE_MAX];		// マテリアル情報へのポインタ
	static DWORD				m_nNumMat		[TYPE_MAX];		// マテリアル情報の数	

	//モーション関係
	static MOTION *m_pMotionPara;
	int m_nCntMotion;
	int m_nMotionNow;

	//基本情報
	D3DXVECTOR3 m_front;
	float m_rotTurn;
	STATE m_state;
	int m_nCntState;
	D3DXVECTOR3 m_posInit;
	D3DXVECTOR3 m_rotInit;
	D3DXVECTOR3 m_sclInit;
	D3DXVECTOR3 m_rotSave;

	CShadow *m_pShadow;			//影
	CLimbX *m_pLimb[MAX_LIMB];	//手足x4
};

#endif
