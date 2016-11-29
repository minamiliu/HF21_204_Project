//=============================================================================
//
// ���C������ [main.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// �w�b�_�t�@�C��
//*****************************************************************************
#include "windows.h"
#include "d3dx9.h"
#include "dinput.h"
#include "xaudio2.h"		// XAudio2�֘A�̃w�b�_�[

//*****************************************************************************
// ���C�u�����t�@�C��
// [�\���v���p�e�B]->[�����J�[]->[����]->[�ǉ��̈ˑ��t�@�C��]�ɋL�q���Ă��\
//*****************************************************************************
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dinput8.lib")

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(1280)		// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)		// �E�C���h�E�̍���

//�ėp
#define SAFE_RELEASE(ptr)		{ if(ptr) { (ptr)->Release(); (ptr) = NULL; } }

//�J���[���
#define WHITE(alpha)							D3DCOLOR_COLORVALUE(1.0f,1.0f,1.0f,(alpha))
#define RED(alpha)								D3DCOLOR_COLORVALUE(1.0f,0.0f,0.0f,(alpha))
#define GREEN(alpha)							D3DCOLOR_COLORVALUE(0.0f,1.0f,0.0f,(alpha))
#define BLUE(alpha)							D3DCOLOR_COLORVALUE(0.0f,0.0f,1.0f,(alpha))
#define SYAN(alpha)							D3DCOLOR_COLORVALUE(0.0f,1.0f,1.0f,(alpha))
#define MASENTA(alpha)							D3DCOLOR_COLORVALUE(1.0f,0.0f,1.0f,(alpha))
#define YELLOW(alpha)							D3DCOLOR_COLORVALUE(1.0f,1.0f,0.0f,(alpha))
#define D3DX_PINK(alpha)						D3DCOLOR_COLORVALUE(1.0f,0.5f,0.5f,(alpha))
#define PURPLE(alpha)							D3DCOLOR_COLORVALUE(0.5f,0.5f,1.0f,(alpha))
#define LIME(alpha)							D3DCOLOR_COLORVALUE(0.5f,1.0f,0.5f,(alpha))
#define ORANGE(alpha)							D3DCOLOR_COLORVALUE(1.0f,0.5f,0.0f,(alpha))
#define SUN(alpha)								D3DCOLOR_COLORVALUE(0.0f,1.0f,0.5f,(alpha))
#define SKY(alpha)								D3DCOLOR_COLORVALUE(0.0f,0.5f,1.0f,(alpha))
#define BIAGE(alpha)							D3DCOLOR_COLORVALUE(1.0f,0.75f,0.5f,(alpha))
#define BLACK(alpha)							D3DCOLOR_COLORVALUE(0.0f,0.0f,0.0f,(alpha))


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
#ifdef _DEBUG
int GetFPS(void);
#endif


#endif