//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: scene2D.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/10/21
//
//============================================

#ifndef _CHANGETEX_H_
#define _CHANGETEX_H_

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
class CChangeTex : public CScene2D
{
public:

	CChangeTex();
	virtual ~CChangeTex();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	static CChangeTex *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, LPCSTR strFileName);
private:

};

#endif
