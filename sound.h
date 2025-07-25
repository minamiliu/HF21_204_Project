//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*********************************************************
// サウンドクラス
//*********************************************************
class CSound
{
public:
	CSound();
	~CSound();

	// サウンドファイル
	typedef enum
	{
		SOUND_LABEL_BGM_TITLE = 0,	// BGM
		SOUND_LABEL_BGM_GORILLA,	// BGM
		SOUND_LABEL_BGM_ZEBRA,		// BGM
		SOUND_LABEL_BGM_LION,		// BGM
		SOUND_LABEL_BGM_RESULT,		// BGM
		SOUND_LABEL_BGM_STAGE,		// BGM
		SOUND_LABEL_BGM_CHANGE,		// BGM
		SOUND_LABEL_SE_LIONSOUND,	// 弾発射音
		SOUND_LABEL_SE_CHARAMOVE,	// キャラ移動
		SOUND_LABEL_SE_HITBOX,		// 衝突音
		SOUND_LABEL_SE_HITENEMY,	// 衝突音 
		SOUND_LABEL_SE_WHISTLE,		// 口笛
		SOUND_LABEL_SE_COIN_GET,	// コイン獲得音
		SOUND_LABEL_SE_STAMP,		// 判子を押す
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
	// パラメータ構造体
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウンタ
	} PARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD dwFormat, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2;									// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;				// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ

	static PARAM m_aParam[SOUND_LABEL_MAX];					// パラメータ
};

#endif
