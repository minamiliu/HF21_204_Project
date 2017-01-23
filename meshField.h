//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: meshField.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/12/15
//
//============================================

#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//============================================
//インクルードファイル
//============================================
#include "scene3D.h"

//============================================
//マクロ定義
//============================================

//============================================
//構造体定義
//============================================

class CMeshField : public CScene3D
{
public:
	typedef enum
	{
		TYPE_GREEN = 0,
		TYPE_WHITE,
		TYPE_WOOD,
		TYPE_MAX,
	}TYPE;

	CMeshField();
	virtual ~CMeshField();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CMeshField *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ, TYPE type);

	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX];
};

#endif
