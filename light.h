//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: light.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/10
//
//============================================

#ifndef _LIGHT_H_
#define _LIGHT_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"

//============================================
//�}�N����`
//============================================
#define MAX_LIGHT		(8)		// ���C�g�̐�

//============================================
//�\���̒�`
//============================================

class CLight
{
public:

	CLight();
	virtual ~CLight();

	HRESULT Init(D3DXVECTOR3 vecDir, D3DXCOLOR diffuse);
	void Uninit(void);

	static void SetAllLightOn(void);
	static CLight *Create(D3DXVECTOR3 vecDir, D3DXCOLOR diffuse);
	static void ReleaseAll(void);

private:
	static CLight *m_apLight[MAX_LIGHT]; //�����������C�g���̂��Ǘ�����
	D3DLIGHT9 *m_pD3DLight;		//���C�g���
	int m_nID;					//���C�g�ԍ�
};

#endif

