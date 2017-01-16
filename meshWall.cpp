//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: scene3D.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/10
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "meshWall.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"

//============================================
// �}�N����`
//============================================

#define TEXTURENAME "data/TEXTURE/wall001.jpg"

//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================
LPDIRECT3DTEXTURE9 CMeshWall::m_pTexture = NULL;


//=============================================================================
//�R���X�g���N�^
//=============================================================================
CMeshWall::CMeshWall()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CMeshWall::~CMeshWall()
{
	
}


//=============================================================================
// �|���S���̏���������
//=============================================================================

HRESULT CMeshWall::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockY, float fSizeBlockX, float fSizeBlockY)
{
	CScene3D::Init( pos, rot, nNumBlockX, nNumBlockY, fSizeBlockX, fSizeBlockY, true);

	//scene�ɓo�^
	SetObjType(OBJTYPE_WALL);

	return S_OK;
}
//=============================================================================
//
//=============================================================================
void CMeshWall::Uninit(void)
{
	CScene3D::Uninit();
}
//=============================================================================
//
//=============================================================================
void CMeshWall::Update(void)
{
	
}
//=============================================================================
//
//=============================================================================
void CMeshWall::Draw(void)
{
	CScene3D::Draw();
}
//=============================================================================
//
//=============================================================================
CMeshWall *CMeshWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockY, float fSizeBlockX, float fSizeBlockY)
{
	CMeshWall *pMeshWall;
	pMeshWall = new CMeshWall;

	pMeshWall->Init(pos, rot, nNumBlockX, nNumBlockY, fSizeBlockX, fSizeBlockY);

	//�e�N�X�`���̊��蓖��
	pMeshWall->BindTexture( m_pTexture);

	return pMeshWall;
}

bool CMeshWall::HitCheck( D3DXVECTOR3 tNowPos, D3DXVECTOR3 tNextPos, D3DXVECTOR3 *wall_nor, D3DXVECTOR3 *HitPoint)
{
	return CScene3D::HitCheck( tNowPos, tNextPos, wall_nor, HitPoint);
}

//=============================================================================
//
//=============================================================================
HRESULT CMeshWall::Load(void)
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
//
//=============================================================================
void CMeshWall::Unload(void)
{
	//�e�N�X�`���̔j��
	if( m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}


