//============================================
//
// タイトル:	 CL25課題
// プログラム名: food2D.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2017/01/11
//
//============================================

#ifndef _FOODICON_H_
#define _FOODICON_H_

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

class CFoodIcon : public CScene2D
{
public:
	CFoodIcon();
	virtual ~CFoodIcon();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//静的関数
	static CFoodIcon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9);
	//static void CreateAllFoodIcon(void);
	//static HRESULT Load(void);
	//static void Unload(void);

private:

	//static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX];
};

#endif
