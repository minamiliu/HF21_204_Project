//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: player2D.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/10/21
//
//============================================

#ifndef _TRASHPLAYER_H_
#define _TRASHPLAYER_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "scene2D.h"

//============================================
//�}�N����`
//============================================

//============================================
//�\���̒�`
//============================================

class CTrashPlayer : public CScene2D
{
public:
	CTrashPlayer();
	virtual ~CTrashPlayer();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool GetGorillaMode(void);
	void SetGorillaMode(void);
	static void Load(void);
	static CTrashPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,LPCSTR strFileName);
	
	
private:
	
	int m_nAnimCnt;
	int m_nPatternAnim;
	bool m_bGorillaMode;
	static LPDIRECT3DTEXTURE9 m_pTexture[2];
};

#endif
