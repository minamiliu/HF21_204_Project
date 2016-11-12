/*******************************************************************************
* �^�C�g��:		�f�o�b�O�\������
* �v���O������:	debugproc.cpp
* �쐬��:		TH�������@���
* �쐬��:		2015/10/20
********************************************************************************
* �X�V����:		- 2015/10/20	 ���
*					- V1.00		Initial Version
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include <stdio.h>
#include "debugproc.h"

#include "renderer.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�[�ϐ��̏�����
//*****************************************************************************
LPD3DXFONT	CDebugProc::m_pD3DXFontDebug = NULL;	// �t�H���g�ւ̃|�C���^
char		CDebugProc::m_aStrDebug[1024] = {"\0"};		// �f�o�b�O���


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CDebugProc::CDebugProc()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CDebugProc::~CDebugProc()
{

}

//=============================================================================
// �f�o�b�O�\�������̏�����
//=============================================================================
HRESULT CDebugProc::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager :: GetRenderer()->GetDevice();
	HRESULT hr;

	// ���\���p�t�H���g��ݒ�
	hr = D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
					OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pD3DXFontDebug);

	// ���N���A
	memset(m_aStrDebug, 0, sizeof m_aStrDebug);

	return hr;
}

//=============================================================================
// �f�o�b�O�\�������̏I������
//=============================================================================
void CDebugProc::Uninit(void)
{
	if(m_pD3DXFontDebug != NULL)
	{// ���\���p�t�H���g�̊J��
		m_pD3DXFontDebug->Release();
		m_pD3DXFontDebug = NULL;
	}
}

//=============================================================================
// �f�o�b�O�\�������̍X�V����
//=============================================================================
void CDebugProc::Update(void)
{
}

//=============================================================================
// �f�o�b�O�\�������̕`�揈��
//=============================================================================
void CDebugProc::Draw(void)
{
	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

	// ���\��
	m_pD3DXFontDebug->DrawText(NULL, m_aStrDebug, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	// ���N���A
	memset(m_aStrDebug, 0, sizeof m_aStrDebug);
}

//=============================================================================
// �f�o�b�O�\���̓o�^
//=============================================================================
void CDebugProc::Print(char *fmt,...)
{
#if 0
	long *pParam;
	static char aBuf[256];

	pParam = (long*)&fmt;
	sprintf(aBuf, fmt, pParam[1], pParam[2], pParam[3], pParam[4],
									pParam[5], pParam[6], pParam[7], pParam[8],
									pParam[9], pParam[10], pParam[11], pParam[12]);
#else
	va_list list;			// �ψ�������������ׂɎg�p����ϐ�
	char *pCur;
	char aBuf[256]={"\0"};
	char aWk[32];

	// �ψ����ɃA�N�Z�X����O�̏�������
	va_start(list, fmt);

	pCur = fmt;
	for( ; *pCur; ++pCur)
	{
		if(*pCur != '%')
		{
			sprintf(aWk, "%c", *pCur);
		}
		else
		{
			pCur++;

			switch(*pCur)
			{
			case 'd':
				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
				sprintf(aWk, "%d", va_arg(list, int));
				break;

			case 'f':
				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
				sprintf(aWk, "%.2f", va_arg(list, double));		// double�^�Ŏw��
				break;

			case 's':
				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
				sprintf(aWk, "%s", va_arg(list, char*));
				break;

			case 'c':
				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
				sprintf(aWk, "%c", va_arg(list, char));
				break;

			default:
				sprintf(aWk, "%c", *pCur);
				break;
			}
		}
		strcat(aBuf, aWk);
	}

	// �ψ����ɃA�N�Z�X������̏I������
	va_end(list);

	// �A��
	if((strlen(m_aStrDebug) + strlen(aBuf)) < ((sizeof m_aStrDebug) - 1))
	{
		strcat(m_aStrDebug, aBuf);
	}
#endif
}

