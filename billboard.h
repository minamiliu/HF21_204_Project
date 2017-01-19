//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: billboard.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/12/15
//
//============================================

#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//============================================
//インクルードファイル
//============================================
#include "scene3D.h"

//============================================
//マクロ定義
//============================================
class CBillBoard : public CScene3D
{
public:

	CBillBoard();
	CBillBoard(LAYER layer);
	virtual ~CBillBoard();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBillBoard *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);

private:

};

#endif
