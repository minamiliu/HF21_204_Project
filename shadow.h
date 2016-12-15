//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: shadow.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/12/15
//
//============================================

#ifndef _SHADOW_H_
#define _SHADOW_H_

//============================================
//インクルードファイル
//============================================
#include "scene3D.h"

//============================================
//マクロ定義
//============================================
class CShadow : public CScene3D
{
public:

	CShadow();
	virtual ~CShadow();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);

	static CShadow *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif
