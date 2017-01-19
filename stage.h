//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: title.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/17
//
//============================================

#ifndef _STAGE_H_
#define _STAGE_H_

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

class CStage : public CManager
{
public:
	typedef enum
	{
		MASU_START = 0,
		MASU_GORIRA,
		MASU_ZEBRA,
		MASU_LION,
		MASU_GOAL,
		MASU_MAX
	}MASU_TYPE;
	CStage();
	CStage::CStage(MASU_TYPE type);
	virtual ~CStage();
	
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static D3DXVECTOR3 pos[MASU_MAX];
	static MASU_TYPE m_stageNow;
};

#endif
