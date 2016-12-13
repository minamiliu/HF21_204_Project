//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: trashGameResult.h
// 作成者:		 HAL東京ゲーム学科　山家啓介
// 作成日:       2016/12/13
//
//============================================

#ifndef _TRASHGAMERESULT_H_
#define _TRASHGAMERESULT_H_

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
class CTrash;
class CTrashBox;
class CScene2D;
class CScore;
//============================================
//構造体定義
//============================================

class CTrashGameResult : public CManager
{
public:

	CTrashGameResult();
	virtual ~CTrashGameResult();
	
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static int GetTrashGameResultCnt(void);
private:
	static CScore *m_pScore;
	static int m_nTrashGameResultCnt;
};

#endif
