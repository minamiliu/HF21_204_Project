//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: player2D.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/10/21
//
//============================================

#ifndef _TRASHBOX_H_
#define _TRASHBOX_H_

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

class CTrashBox2D : public CScene2D
{
public:

	CTrashBox2D();
	virtual ~CTrashBox2D();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTrashBox2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	

private:

};

#endif
