//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: player2D.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/10/21
//
//============================================

#ifndef _PLAYER2D_H_
#define _PLAYER2D_H_

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

class CPlayer2D : public CScene2D
{
public:

	CPlayer2D();
	virtual ~CPlayer2D();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void SetGorillaMode(void);
	bool GetGorillaMode(void);
private:
	bool m_bGorillaMode;
	//int nGorillaModeCnt;
};

#endif
