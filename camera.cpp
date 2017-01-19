//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: camera.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/10
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "camera.h"
#include "renderer.h"
#include "manager.h"
#include "playerX.h"

//============================================
// �}�N����`
//============================================
#define	CAM_POS_V_X				(0.0f)					// �J�����̎��_�����ʒu(X���W)
#define	CAM_POS_V_Y				(100.0f)				// �J�����̎��_�����ʒu(Y���W)
#define	CAM_POS_V_Z				(-300.0f)				// �J�����̎��_�����ʒu(Z���W)
#define	CAM_POS_R_X				(0.0f)					// �J�����̒����_�����ʒu(X���W)
#define	CAM_POS_R_Y				(0.0f)					// �J�����̒����_�����ʒu(Y���W)
#define	CAM_POS_R_Z				(0.0f)					// �J�����̒����_�����ʒu(Z���W)
#define	VIEW_ANGLE				(D3DXToRadian(60.0f))							// �r���[���ʂ̎���p
#define	VIEW_ASPECT				((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��
#define	VIEW_NEAR_Z				(100.f)											// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z				(4000.0f)										// �r���[���ʂ�FarZ�l
#define	VALUE_MOVE_CAMERA		(2.0f)											// �J�����̈ړ���
#define	VALUE_ROTATE_CAMERA		(D3DX_PI * 0.01f)								// �J�����̉�]��
#define	VALUE_ADJUST_DISTANCE	(2.0f)											// ���_�ƒ����_�̋���������

#define CAM_ROT_X				(D3DXToRadian(22.0f))

//=============================================================================
// �\���̒�`
//=============================================================================

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{
	
}

HRESULT CCamera::Init(void)
{
	float fVecX,fVecZ;

	// ���_������
	m_posV = D3DXVECTOR3( CAM_POS_V_X, CAM_POS_V_Y, CAM_POS_V_Z);
	// �����_������
	m_posR = D3DXVECTOR3( CAM_POS_R_X, CAM_POS_R_Y, CAM_POS_R_Z);
	// ������x�N�g��������
	m_vecU = D3DXVECTOR3( 0.0f, 1.0f, 0.0f);
	// �J���������i��]�p�j�̏�����
	m_rot = D3DXVECTOR3( CAM_ROT_X, 0.0f, 0.0f);
	// ���_�ƒ����_�̋��������߂�
	fVecX = m_posV.x - m_posR.x;						// X�����i���_�[�����_�j
	fVecZ = m_posV.z - m_posR.z;						// Z�����i���_�[�����_�j
	// ���_�ƒ����_�̋���
	m_fDistance = sqrtf(fVecX * fVecX + fVecZ * fVecZ);

	return S_OK;
}

void CCamera::Uninit(void)
{

}

void CCamera::Update(void)
{

}

void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);
	
	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH( &m_mtxView, &m_posV, &m_posR, &m_vecU);
	
	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform( D3DTS_VIEW, &m_mtxView);
	
	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity( &m_mtxProjection);
	
	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH( &m_mtxProjection, VIEW_ANGLE, VIEW_ASPECT, VIEW_NEAR_Z, VIEW_FAR_Z);
	
	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�(�����ϊ��̐ݒ�)
	pDevice->SetTransform( D3DTS_PROJECTION, &m_mtxProjection);
}

D3DXVECTOR3 CCamera::GetRot(void)
{
	return m_rot;
}
void CCamera::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

D3DXVECTOR3 CCamera::GetPosR(void)
{
	return m_posR;
}
void CCamera::SetPosR(D3DXVECTOR3 posR)
{
	m_posR = posR;
}

D3DXVECTOR3 CCamera::GetPosV(void)
{
	return m_posV;
}
void CCamera::SetPosV(D3DXVECTOR3 posV)
{
	m_posV = posV;
}

D3DXMATRIX *CCamera::GetMtxView(void)
{
	return &m_mtxView;
}
D3DXMATRIX *CCamera::GetMtxProjection(void)
{
	return &m_mtxProjection;
}