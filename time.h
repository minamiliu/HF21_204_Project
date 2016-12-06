//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: time.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/29
//
//============================================

#ifndef _TIME_H_
#define _TIME_H_

//============================================
//インクルードファイル
//============================================
#include "score.h"

//============================================
//マクロ定義
//============================================

//============================================
//構造体定義
//============================================

class CTime : public CScore
{
public:

	CTime();
	virtual ~CTime();

	HRESULT Init(D3DXVECTOR3 numberPos, D3DXVECTOR3 numberSize, int maxKeta, int startTime, bool bCountDown, const D3DXCOLOR &col);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTime *Create(D3DXVECTOR3 numberPos, D3DXVECTOR3 numberSize, int maxKeta, int startTime, bool bCountDown, const D3DXCOLOR &col);
	bool TimeUp(void);
private:
	int m_nCntFrame;
	int m_nTime;

	bool m_bCountDown;
};

#endif
