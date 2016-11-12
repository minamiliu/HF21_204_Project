/*******************************************************************************
* �^�C�g��:		�f�o�b�O�\������
* �v���O������:	debugproc.cpp
* �쐬��:		HAL�����Q�[���w�ȁ@����G
* �쐬��:		2016/11/12
*******************************************************************************/
#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_

#include "Main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//============================================
//�\���̒�`
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

	static LPD3DXFONT	m_pD3DXFontDebug;	// �t�H���g�ւ̃|�C���^
	static char		m_aStrDebug[1024];		// �f�o�b�O���
};

#endif