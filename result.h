//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: result.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/17
//
//============================================

#ifndef _RESULT_H_
#define _RESULT_H_

//============================================
//インクルードファイル
//============================================
#include "manager.h"

//============================================
//マクロ定義
//============================================

//============================================
//前方宣言
//============================================
class CSound;
//============================================
//構造体定義
//============================================
class CScore;
class CScene2D;
class CResult : public CManager
{
public:

	CResult();
	virtual ~CResult();
	
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	int m_resultCnt;
	int m_nCntCoin;
	static CScore *m_pTrashGameScore;
	static CScore *m_pZebraGameScore;
	static CScore *m_pLionGameScore;
	static CScene2D *m_pRank[3];
	int m_nTrashGameScore;
	int m_nZebraGameScore;
	int m_nLionGameScore;
	int m_nTargetScore[3];

	CSound *m_pSound;
};

#endif
