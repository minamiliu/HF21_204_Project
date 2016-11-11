//============================================
//
// �^�C�g��:	 CL25�ۑ�
// �v���O������: camera.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/10
//
//============================================

#ifndef _CAMERA_H_
#define _CAMERA_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"

//============================================
//�}�N����`
//============================================

//============================================
//�\���̒�`
//============================================

class CCamera
{
public:

	CCamera();
	virtual ~CCamera();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void SetCamera(void);
	//CCamera *GetCamera(void);

private:

	D3DXVECTOR3 m_posV;			// ���_
	D3DXVECTOR3 m_posR;			// �����_
	D3DXVECTOR3 m_vecU;			// ������x�N�g��
	D3DXVECTOR3 m_rot;			// �����i��]�p�j
	float m_fDistance;			// ���_�ƒ����_�̋���
	D3DXMATRIX m_mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;		// �r���[�}�g���b�N�X
};

#endif
