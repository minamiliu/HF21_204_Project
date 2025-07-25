﻿//============================================
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

class CTrashGame : public CManager
{
public:
	typedef enum
	{
		STATE_CHANGE = 0,//変身中
		STATE_MAX
	}STATE;
	CTrashGame();
	virtual ~CTrashGame();
	
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetTrashPointer(CTrash *pTrash);
	static int GetTrashGameCnt(void);
	void SetState(STATE state);
	static STATE GetState(void);
	static HRESULT LoadAll(void);
private:
	static CTrash *m_pTrash;
	static CScene2D *m_pTrashBox;
	static CScore *m_pScore;
	static CScene2D *m_pPoint2D;
	static CScene2D *m_pMouse;
	static CScene2D *m_pMidpoint;
	static int m_nTrashGameCnt;
	static CScene2D *m_pCenterPoint;
	static STATE m_state;
};

#endif
