/*******************************************************************************
//
// タイトル:	 未来創造展チーム204
// プログラム名: effectBG.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2017/01/15
//
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#ifndef _EFFECTBG_H_
#define _EFFECTBG_H_
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "main.h"
#include "scene2D.h"
/*******************************************************************************
* マクロ定義
*******************************************************************************/
/*******************************************************************************
* クラス定義
*******************************************************************************/
//クラス宣言
class CEffectBG : public CScene2D
{
public:
	CEffectBG();
	~CEffectBG();
	static CEffectBG* Create(D3DXVECTOR3 pos,D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos,D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static HRESULT Load(void);
	static void Unload(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	int m_nCntFrame;
	int m_animPat;
};
#endif