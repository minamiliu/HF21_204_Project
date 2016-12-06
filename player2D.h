//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: player2D.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/10/21
//
//============================================

#ifndef _PLAYER2D_H_
#define _PLAYER2D_H_

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

class CPlayer2D : public CScene2D
{
public:

	CPlayer2D();
	virtual ~CPlayer2D();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void SetGorillaMode(void);
	bool GetGorillaMode(void);
private:
	bool m_bGorillaMode;
	//int nGorillaModeCnt;
};

#endif
