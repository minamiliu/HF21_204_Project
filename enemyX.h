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

	CEnemyX();
	virtual ~CEnemyX();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEnemyX *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl);
protected:
	D3DXVECTOR3 Get2RotDiffAngle( D3DXVECTOR3 rot, D3DXVECTOR3 rotTarget);

private:
	static MOTION *m_pMotionPara;
	int m_nCntFrame;
	int m_nMotionNow;

	D3DXVECTOR3 m_front;
	float m_rotTurn;
};

#endif
