//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: itemX.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/12/12
//
//============================================

#ifndef _ITEMX_H_
#define _ITEMX_H_

//============================================
//インクルードファイル
//============================================
#include "sceneX.h"

//============================================
//マクロ定義
//============================================

//============================================
//構造体定義
//============================================

class CItemX : public CSceneX
{
public:

	CItemX();
	virtual ~CItemX();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CItemX *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl);

private:

};

#endif
