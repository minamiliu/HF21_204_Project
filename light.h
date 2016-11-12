//============================================
//
// タイトル:	 CL25課題
// プログラム名: light.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/10
//
//============================================

#ifndef _LIGHT_H_
#define _LIGHT_H_

//============================================
//インクルードファイル
//============================================
#include "main.h"

//============================================
//マクロ定義
//============================================
#define MAX_LIGHT		(8)		// ライトの数

//============================================
//構造体定義
//============================================

class CLight
{
public:

	CLight();
	virtual ~CLight();

	HRESULT Init(D3DXVECTOR3 vecDir, D3DXCOLOR diffuse);
	void Uninit(void);

	static void SetAllLightOn(void);
	static CLight *Create(D3DXVECTOR3 vecDir, D3DXCOLOR diffuse);

private:
	static bool abUse[MAX_LIGHT];
	D3DLIGHT9 *m_pLight;		// ライト情報
	int m_nID;
};

#endif

