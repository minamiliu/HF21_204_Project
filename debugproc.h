/*******************************************************************************
* �^�C�g��:		�f�o�b�O�\������
* �v���O������:	debugproc.cpp
* �쐬��:		��������
* �쐬��:		2016/05/19
*******************************************************************************/
#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_

#include "Main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitDebugProc(void);
void UninitDebugProc(void);
void UpdateDebugProc(void);
void DrawDebugProc(void);

void PrintDebugProc(char *fmt,...);

#endif