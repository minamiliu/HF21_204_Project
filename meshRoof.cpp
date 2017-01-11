//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: meshField.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/12/15
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "meshRoof.h"
#include "renderer.h"
#include "manager.h"

//============================================
// �}�N����`
//============================================

#define TEXTURE_GREEN "data/TEXTURE/field000.jpg"
#define TEXTURE_WHITE "data/TEXTURE/field001.jpg"


//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================
LPDIRECT3DTEXTURE9 CMeshRoof::m_pTexture[TYPE_MAX] = {};

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CMeshRoof::CMeshRoof()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CMeshRoof::~CMeshRoof()
{
	
}


//=============================================================================
// �|���S���̏���������
//=============================================================================

HRESULT CMeshRoof::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ)
{
	CScene3D::Init( pos, rot, nNumBlockX, nNumBlockZ, fSizeBlockX, fSizeBlockZ, false);

	return S_OK;
}
//=============================================================================
//
//=============================================================================
void CMeshRoof::Uninit(void)
{
	CScene3D::Uninit();
}
//=============================================================================
//
//=============================================================================
void CMeshRoof::Update(void)
{
	
}
//=============================================================================
//
//=============================================================================
void CMeshRoof::Draw(void)
{	
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//���_�̕`�揇�Ԃ�ς���
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	CScene3D::Draw();

	//���_�̕`�揇�Ԃ�߂�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
//=============================================================================
//
//=============================================================================
CMeshRoof *CMeshRoof::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ, TYPE type)
{
	CMeshRoof *pMeshField;
	pMeshField = new CMeshRoof;

	pMeshField->Init(pos, rot, nNumBlockX, nNumBlockZ, fSizeBlockX, fSizeBlockZ);

	//�e�N�X�`���̊��蓖��
	pMeshField->BindTexture( m_pTexture[type]);

	return pMeshField;
}


//=============================================================================
//
//=============================================================================
HRESULT CMeshRoof::Load(void)
{
	for(int cntType = 0; cntType < TYPE_MAX; cntType++)
	{
		LPCSTR strFileName;
		switch( cntType)
		{
		case TYPE_GREEN:
			strFileName = TEXTURE_GREEN;
			break;

		case TYPE_WHITE:
			strFileName = TEXTURE_WHITE;
			break;
		}

		if( m_pTexture[cntType] == NULL)
		{
			LPDIRECT3DDEVICE9 pDevice;
			pDevice = CManager::GetRenderer()->GetDevice();

			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile( pDevice, strFileName, &m_pTexture[cntType]);
		}	
	}

	return S_OK;
}

//=============================================================================
//
//=============================================================================
void CMeshRoof::Unload(void)
{
	for(int cntType = 0; cntType < TYPE_MAX; cntType++)
	{
		//�e�N�X�`���̔j��
		if( m_pTexture[cntType] != NULL)
		{
			m_pTexture[cntType]->Release();
			m_pTexture[cntType] = NULL;
		}	
	}

}


