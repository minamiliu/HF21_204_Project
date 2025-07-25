//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: meshRoof.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2017/01/11
//
//============================================

#ifndef _MESHROOF_H_
#define _MESHROOF_H_

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

class CMeshRoof : public CScene3D
{
public:
	typedef enum
	{
		TYPE_GREEN = 0,
		TYPE_WHITE,
		TYPE_MAX,
	}TYPE;

	CMeshRoof();
	virtual ~CMeshRoof();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CMeshRoof *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ, TYPE type);

	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX];
};

#endif
