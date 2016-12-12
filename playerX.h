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

//============================================
//構造体定義
//============================================

class CPlayerX : public CSceneX
{
public:
	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_DOWN,
		STATE_MAX,
	}STATE;

	CPlayerX();
	virtual ~CPlayerX();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayerX *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed);
	D3DXVECTOR3 GetFront(void);

	void SetState(STATE state);
	STATE GetState(void);

protected:
	D3DXVECTOR3 Get2RotDiffAngle( D3DXVECTOR3 rot, D3DXVECTOR3 rotTarget);
	void UpdateRot(void);
	void CalcNextPos(void);
	bool isKeyUse(int nUp, int nDown, int nLeft, int nRight);
	bool isMouseUse(void);

private:
	D3DXVECTOR3 m_move;			// モデルの移動量
	float m_speed;				// モデルのスピード
	float m_Accel;				// 加速度
	D3DXVECTOR3 m_front;		// 前進ベクトル


	D3DXVECTOR3 m_rotTarget;	// モデルの向き(回転)
	D3DXVECTOR3 m_rotAngle;		// モデルの向き(回転)

	bool m_isGoAhead;			//前進フラグ
	bool m_isGoBack;			//後退フラグ

	STATE m_state;
	int m_nCntState;
};

#endif
