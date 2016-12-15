//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: shadow.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/12/15
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "shadow.h"
#include "renderer.h"
#include "manager.h"

//============================================
// �}�N����`
//============================================
#define TEXTURENAME "data/TEXTURE/effect000.jpg"

//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================
LPDIRECT3DTEXTURE9 CShadow::m_pTexture = NULL;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CShadow::CShadow()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CShadow::~CShadow()
{
	
}


//=============================================================================
// �|���S���̏���������
//=============================================================================

HRESULT CShadow::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	pos.y = 0.1f;
	CScene3D::Init( pos, D3DXVECTOR3(0,0,0), 1, 1, size.x, size.y, false);
	return S_OK;
}
//=============================================================================
//
//=============================================================================
void CShadow::Uninit(void)
{
	CScene3D::Uninit();
}
//=============================================================================
//
//=============================================================================
void CShadow::Update(void)
{
	
}
//=============================================================================
//
//=============================================================================
void CShadow::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���Z����
	pDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);// ���� = �]����(DEST) - �]����(SRC)
	pDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene3D::Draw();

	// �ʏ�u�����h 
	pDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD);		// ���� = �]����(SRC) + �]����(DEST)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//=============================================================================
//
//=============================================================================
CShadow *CShadow::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	CShadow *pShadow;
	pShadow = new CShadow;

	pShadow->Init(pos, size);

	//�e�N�X�`���̊��蓖��
	pShadow->BindTexture( m_pTexture);

	return pShadow;
}

//=============================================================================
// ���W�̐ݒ�
//=============================================================================
void CShadow::SetPosition(D3DXVECTOR3 pos)
{
	pos.y = 0.1f;
	CScene3D::SetPosition( pos);
}

//=============================================================================
//�e�N�X�`���̃��[�h
//=============================================================================
HRESULT CShadow::Load(void)
{
	if( m_pTexture == NULL)
	{
		LPDIRECT3DDEVICE9 pDevice;
		pDevice = CManager::GetRenderer()->GetDevice();

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile( pDevice, TEXTURENAME, &m_pTexture);
	}

	return S_OK;
}

//=============================================================================
//�e�N�X�`���̃A�����[�h
//=============================================================================
void CShadow::Unload(void)
{
	//�e�N�X�`���̔j��
	if( m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}


