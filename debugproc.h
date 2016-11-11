/*******************************************************************************
* タイトル:		デバッグ表示処理
* プログラム名:	debugproc.cpp
* 作成者:		小室直也
* 作成日:		2016/05/19
*******************************************************************************/
#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_

#include "Main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitDebugProc(void);
void UninitDebugProc(void);
void UpdateDebugProc(void);
void DrawDebugProc(void);

void PrintDebugProc(char *fmt,...);

#endif