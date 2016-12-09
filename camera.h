//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
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

	D3DXVECTOR3 GetRot(void);		//����
	void SetRot(D3DXVECTOR3 rot);	//����
	
	D3DXVECTOR3 GetPosR(void);		//�����_
	void SetPosR(D3DXVECTOR3 posR);	//�����_
	
	D3DXVECTOR3 GetPosV(void);		//���_
	void SetPosV(D3DXVECTOR3 posV);	//���_
	
	D3DXMATRIX *GetMtxView(void);
	D3DXMATRIX *GetMtxProjection(void);


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
