//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: player2D.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/10/21
//
//============================================

#ifndef _MESSAGE_H_
#define _MESSAGE_H_

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

class CMessage : public CScene2D
{
public:
	CMessage();
	virtual ~CMessage();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool GetGorillaMode(void);
	void SetGorillaMode(void);
	static void Load(void);
	static CMessage *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,LPCSTR strFileName);
	
	
private:
	
	int m_nAnimCnt;
	int m_nPatternAnim;
	bool m_bGorillaMode;
	static LPDIRECT3DTEXTURE9 m_pTexture[2];
};

#endif
