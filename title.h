//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: title.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/17
//
//============================================

#ifndef _TITLE_H_
#define _TITLE_H_

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

//============================================
//構造体定義
//============================================

class CTitle : public CManager
{
public:

	CTitle();
	virtual ~CTitle();
	
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

};

#endif
