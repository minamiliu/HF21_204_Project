//============================================
//
// �^�C�g��:	 CL25�ۑ�
// �v���O������: light.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/10
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "light.h"
#include "renderer.h"
#include "manager.h"

//============================================
// �}�N����`
//============================================

//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================
D3DLIGHT9 CLight::m_aLight[NUM_LIGHT] = {};	

//=============================================================================
// �\���̒�`
//=============================================================================

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CLight::CLight()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CLight::~CLight()
{
	
}

HRESULT CLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXVECTOR3 vecDir;

	// D3DLIGHT9�\���̂�0�ŃN���A����
	ZeroMemory( &m_aLight[0], sizeof(D3DLIGHT9));
	
	// ���C�g0�̃^�C�v�̐ݒ�
	m_aLight[0].Type = D3DLIGHT_DIRECTIONAL;
	
	// ���C�g0�̊g�U���̐ݒ�
	m_aLight[0].Diffuse = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f);
	m_aLight[0].Ambient = D3DXCOLOR( 0.2f, 0.2f, 0.2f, 0.2f);
	
	// ���C�g0�̕����̐ݒ�
	vecDir = D3DXVECTOR3( 0.2f, -0.6f, 0.8f);
	D3DXVec3Normalize( (D3DXVECTOR3*)&m_aLight[0].Direction, &vecDir);
	
	// ���C�g0�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetLight( 0, &m_aLight[0]);

	// ���C�g0���g�p�g�p��Ԃ�
	pDevice->LightEnable( 0, TRUE);

	// D3DLIGHT9�\���̂�0�ŃN���A����
	ZeroMemory( &m_aLight[1], sizeof(D3DLIGHT9));

	// ���C�g1�̃^�C�v�̐ݒ�
	m_aLight[1].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g1�̊g�U���̐ݒ�
	m_aLight[1].Diffuse = D3DXCOLOR( 0.75f, 0.75f, 0.75f, 1.0f);
	m_aLight[1].Ambient = D3DXCOLOR( 0.2f, 0.2f, 0.2f, 1.0f);

    // ���C�g1�̕����̐ݒ�
	vecDir = D3DXVECTOR3( -0.2f, -0.3f, -0.5f);
	D3DXVec3Normalize( (D3DXVECTOR3*)&m_aLight[1].Direction, &vecDir);

	// ���C�g1�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetLight( 1, &m_aLight[1]);

	// ���C�g1�̂��g�p�g�p��Ԃ�
	pDevice->LightEnable( 1, TRUE);

	// D3DLIGHT9�\���̂�0�ŃN���A����
	ZeroMemory( &m_aLight[2], sizeof(D3DLIGHT9));
	
	// ���C�g2�̃^�C�v�̐ݒ�
	m_aLight[2].Type = D3DLIGHT_DIRECTIONAL;
	
	// ���C�g2�̊g�U���̐ݒ�
	m_aLight[2].Diffuse = D3DXCOLOR( 0.15f, 0.15f, 0.15f, 1.0f);
	m_aLight[2].Ambient = D3DXCOLOR( 0.2f, 0.2f, 0.2f, 1.0f);
	
	// ���C�g2�̕����̐ݒ�
	vecDir = D3DXVECTOR3( 0.8f, 0.1f, 0.5f);
	D3DXVec3Normalize( (D3DXVECTOR3*)&m_aLight[2].Direction, &vecDir);
	
	// ���C�g2�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetLight( 2, &m_aLight[2]);

	// ���C�g2���g�p�g�p��Ԃ�
	pDevice->LightEnable( 2, TRUE);

	// ���C�e�B���O���[�h��ON
	pDevice->SetRenderState( D3DRS_LIGHTING, TRUE);

	return S_OK;
}

void CLight::Uninit(void)
{

}