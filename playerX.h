//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: playerX.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/15
//
//============================================

#ifndef _PLAYERX_H_
#define _PLAYERX_H_

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

class CPlayerX : public CSceneX
{
public:
	typedef enum
	{
		TYPE_HUMAN = 0,
		TYPE_LION,
		TYPE_MAX,
	}TYPE;

	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_HIT,
		STATE_UPGRADE,
		STATE_LION,
		STATE_GOAL,
		STATE_FINISH,
		STATE_MAX,
	}STATE;

	CPlayerX();
	virtual ~CPlayerX();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetState(STATE state);
	STATE GetState(void);
	int GetFoodNum(void);
	void BindXfile(TYPE type);
	D3DXVECTOR3 GetFront(void);

	static CPlayerX *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed, TYPE type);
	static HRESULT Load(void);
	static void Unload(void);


protected:
	void UpdateRot(void);
	void CalcFront(void);
	bool isKeyUse(int nUp, int nDown, int nLeft, int nRight);
	bool isMouseUse(void);
	bool isCollision(void);
	D3DXVECTOR3 Get2RotDiffAngle( D3DXVECTOR3 rot, D3DXVECTOR3 rotTarget);

private:
	static LPDIRECT3DTEXTURE9	m_pTexture		[TYPE_MAX];		// テクスチャへのポインタ
	static LPD3DXMESH			m_pD3DXMesh		[TYPE_MAX];		// メッシュ情報へのポインタ
	static LPD3DXBUFFER			m_pD3DXBuffMat	[TYPE_MAX];		// マテリアル情報へのポインタ
	static DWORD				m_nNumMat		[TYPE_MAX];		// マテリアル情報の数

	float m_fSpeed;				// モデルのスピード
	float m_fAccel;				// 加速度
	D3DXVECTOR3 m_front;		// 前進ベクトル

	D3DXVECTOR3 m_rotTarget;	// モデルの向き(回転)
	D3DXVECTOR3 m_rotAngle;		// モデルの向き(回転)

	bool m_isGoAhead;			//前進フラグ
	bool m_isGoBack;			//後退フラグ

	STATE m_state;				//状態
	int m_nCntState;			//状態のカウンター
	CShadow *m_pShadow;			//影

	CLimbX *m_pLimb[MAX_LIMB];	//手足x4
	
	int m_nNumFoodGet; //集めた食材の数
};

#endif
