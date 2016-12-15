//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: food.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/12/15
//
//============================================

#ifndef _FOOD_H_
#define _FOOD_H_

//============================================
//インクルードファイル
//============================================
#include "billboard.h"

//============================================
//マクロ定義
//============================================

//============================================
//構造体定義
//============================================

class CFood : public CBillBoard
{
public:

	CFood();
	virtual ~CFood();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CFood *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif
