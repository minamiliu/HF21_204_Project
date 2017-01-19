//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: effect3D.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2017/01/19
//
//============================================

#ifndef _EFFECT3D_H_
#define _EFFECT3D_H_

//============================================
//インクルードファイル
//============================================
#include "billboard.h"

//============================================
//マクロ定義
//============================================

//============================================
//前方宣言
//============================================

//============================================
//構造体定義
//============================================
class CEffect3D : public CBillBoard
{
public:
	typedef enum 
	{
		TYPE_MARU = 0,
		TYPE_MAX,
	}TYPE;

	CEffect3D();
	virtual ~CEffect3D();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size, TYPE type, const D3DXCOLOR &col);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEffect3D *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, TYPE type, const D3DXCOLOR &col);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX];

	TYPE m_type;
	D3DXCOLOR m_col;
};

#endif
