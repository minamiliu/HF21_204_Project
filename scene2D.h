//============================================
//
// タイトル:	 CL25課題
// プログラム名: scene2D.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/10/21
//
//============================================

#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//============================================
//インクルードファイル
//============================================
#include "scene.h"

//============================================
//マクロ定義
//============================================

//============================================
//構造体定義
//============================================
//敵クラス
class CScene2D : public CScene
{
public:

	CScene2D();
	virtual ~CScene2D();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScene2D *Create(void);

private:

	LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ

	D3DXVECTOR3				m_pos;			// ポリゴンの位置
};

#endif