//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: game.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/17
//
//============================================

#ifndef _TRASHGAME_H_
#define _TRASHGAME_H_

//============================================
//インクルードファイル
//============================================
#include "manager.h"
#include "scene2D.h"
//============================================
//マクロ定義
//============================================

//============================================
//前方宣言
//============================================
class CTrash;
class CTrashBox;
//============================================
//構造体定義
//============================================

class CTrashGame : public CManager
{
public:

	CTrashGame();
	virtual ~CTrashGame();
	
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetTrashPointer(CScene2D *pTrash);
private:
	static CScene2D *m_pTrash;
	CScene2D *m_pTrashBox;
};

#endif
