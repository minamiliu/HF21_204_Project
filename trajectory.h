//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: trajectory.h
// 作成者:		 HAL東京ゲーム学科　山家啓介
// 作成日:       2016/10/21
//
//============================================

#ifndef _TRAJECTORY_H_
#define _TRAJECTORY_H_

//============================================
//インクルードファイル
//============================================
#include "scene2D.h"

//============================================
//マクロ定義
//============================================

//============================================
//構造体定義
//============================================

class CTrajectory : public CScene2D
{
public:

	CTrajectory();
	virtual ~CTrajectory();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTrajectory *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	

private:
	int m_nTrajectoryCnt;
};

#endif
