//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: itemX.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/12/12
//
//============================================

#ifndef _ITEMX_H_
#define _ITEMX_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "sceneX.h"

//============================================
//�}�N����`
//============================================

//============================================
//�\���̒�`
//============================================

class CItemX : public CSceneX
{
public:

	CItemX();
	virtual ~CItemX();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CItemX *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl);

private:

};

#endif
