//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
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
bool CLight::abUse[MAX_LIGHT] = {false};

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CLight::CLight()
{
	m_pLight = NULL;

	for(int cntLight = 0; cntLight < MAX_LIGHT; cntLight++)
	{
		if(abUse[cntLight] == false)
		{
			abUse[cntLight] = true;
			m_nID = cntLight;
			break;
		}
	}
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CLight::~CLight()
{
	
}

//=============================================================================
//���C�g������
//=============================================================================
HRESULT CLight::Init(D3DXVECTOR3 vecDir, D3DXCOLOR diffuse)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	m_pLight = new D3DLIGHT9;

	// D3DLIGHT9�\���̂�0�ŃN���A����
	ZeroMemory( m_pLight, sizeof(D3DLIGHT9));

	// ���C�g0�̃^�C�v�̐ݒ�
	m_pLight->Type = D3DLIGHT_DIRECTIONAL;
	
	// ���C�g0�̊g�U���̐ݒ�
	m_pLight->Diffuse = diffuse;
	m_pLight->Ambient = D3DXCOLOR( 0.2f, 0.2f, 0.2f, 0.2f);
	
	// ���C�g0�̕����̐ݒ�
	D3DXVec3Normalize( (D3DXVECTOR3*)&m_pLight->Direction, &vecDir);

	// ���C�g0�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetLight( m_nID, m_pLight);

	// ���C�g0���g�p�g�p��Ԃ�
	pDevice->LightEnable( m_nID, TRUE);

	return S_OK;
}

//=============================================================================
//���C�g���
//=============================================================================
void CLight::Uninit(void)
{
	// �e�N�X�`���̔j��
	if(m_pLight != NULL)
	{
		delete m_pLight;
		m_pLight = NULL;
	}
}
//=============================================================================
//���C�g�̐���
//=============================================================================
CLight *CLight::Create(D3DXVECTOR3 vecDir, D3DXCOLOR diffuse)
{
	CLight *pLight = new CLight;
	pLight->Init( vecDir, diffuse);

	return pLight;
}
//=============================================================================
//�����C�g��L���ɂ���
//=============================================================================
void CLight::SetAllLightOn(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���C�e�B���O���[�h��ON
	pDevice->SetRenderState( D3DRS_LIGHTING, TRUE);
}