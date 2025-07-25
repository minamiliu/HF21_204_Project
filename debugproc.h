/*******************************************************************************
* タイトル:		デバッグ表示処理
* プログラム名:	debugproc.cpp
* 作成者:		HAL東京ゲーム学科　劉南宏
* 作成日:		2016/11/12
*******************************************************************************/
#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_

#include "Main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//============================================
//構造体定義
//============================================

class CDebugProc
{
public:

	CDebugProc();
	virtual ~CDebugProc();

	static HRESULT Init(void);
	static void Uninit(void);
	static void Update(void);
	static void Draw(void);

	static void Print(char *fmt,...);

private:

	static LPD3DXFONT	m_pD3DXFontDebug;	// フォントへのポインタ
	static char		m_aStrDebug[1024];		// デバッグ情報
};

#endif