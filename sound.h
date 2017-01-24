//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*********************************************************
// �T�E���h�N���X
//*********************************************************
class CSound
{
public:
	CSound();
	~CSound();

	// �T�E���h�t�@�C��
	typedef enum
	{
		SOUND_LABEL_BGM_TITLE = 0,	// BGM
		SOUND_LABEL_BGM_GORILLA,	// BGM
		SOUND_LABEL_BGM_ZEBRA,		// BGM
		SOUND_LABEL_BGM_LION,		// BGM
		SOUND_LABEL_BGM_RESULT,		// BGM
		SOUND_LABEL_BGM_STAGE,		// BGM
		SOUND_LABEL_BGM_CHANGE,		// BGM
		SOUND_LABEL_SE_LIONSOUND,	// �e���ˉ�
		SOUND_LABEL_SE_CHARAMOVE,	// �L�����ړ�
		SOUND_LABEL_SE_HITBOX,		// �Փˉ�
		SOUND_LABEL_SE_HITENEMY,	// �Փˉ� 
		SOUND_LABEL_SE_WHISTLE,		// ���J
		SOUND_LABEL_SE_COIN_GET,	// �R�C���l����
		SOUND_LABEL_SE_STAMP,		// ���q������
		SOUND_LABEL_SE_KICK,		// zebra kick
		SOUND_LABEL_SE_ITEM_GET,	// item get
		SOUND_LABEL_SE_PICK,		// pick
		SOUND_LABEL_SE_PUT,			// put
		SOUND_LABEL_SE_WRONG,		// wrong
		SOUND_LABEL_MAX
	} SOUND_LABEL;

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);
	void SetVolume(SOUND_LABEL label, float fValue);

private:
	// �p�����[�^�\����
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���^
	} PARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD dwFormat, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;				// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y

	static PARAM m_aParam[SOUND_LABEL_MAX];					// �p�����[�^
};

#endif
