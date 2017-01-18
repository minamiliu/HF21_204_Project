//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: player2D.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/10/21
//
//============================================

#ifndef _MESSAGE_H_
#define _MESSAGE_H_

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

class CMessage : public CScene2D
{
public:
	CMessage();
	virtual ~CMessage();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool GetGorillaMode(void);
	void SetGorillaMode(void);
	static void Load(void);
	static CMessage *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,LPCSTR strFileName);
	
	
private:
	
	int m_nAnimCnt;
	int m_nPatternAnim;
	bool m_bGorillaMode;
	static LPDIRECT3DTEXTURE9 m_pTexture[2];
};

#endif
