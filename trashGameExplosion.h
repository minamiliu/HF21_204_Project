//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: player2D.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/10/21
//
//============================================

#ifndef _TRASHGAMEEXPLOSION_H_
#define _TRASHGAMEEXPLOSION_H_

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

class CTrashGameExplosion : public CScene2D
{
public:
	CTrashGameExplosion();
	virtual ~CTrashGameExplosion();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTrashGameExplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	
	
private:
	
	int m_nAnimCnt;
	int m_nPatternAnim;

};

#endif
