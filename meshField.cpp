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
#include "meshField.h"
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
LPDIRECT3DTEXTURE9 CMeshField::m_pTexture[TYPE_MAX] = {};

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CMeshField::CMeshField()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CMeshField::~CMeshField()
{
	
}


//=============================================================================
// �|���S���̏���������
//=============================================================================

HRESULT CMeshField::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ)
{
	CScene3D::Init( pos, rot, nNumBlockX, nNumBlockZ, fSizeBlockX, fSizeBlockZ, false);

	return S_OK;
}
//=============================================================================
//
//=============================================================================
void CMeshField::Uninit(void)
{
	CScene3D::Uninit();
}
//=============================================================================
//
//=============================================================================
void CMeshField::Update(void)
{
	
}
//=============================================================================
//
//=============================================================================
void CMeshField::Draw(void)
{
	CScene3D::Draw();
}
//=============================================================================
//
//=============================================================================
CMeshField *CMeshField::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ, TYPE type)
{
	CMeshField *pMeshField;
	pMeshField = new CMeshField;

	pMeshField->Init(pos, rot, nNumBlockX, nNumBlockZ, fSizeBlockX, fSizeBlockZ);

	//�e�N�X�`���̊��蓖��
	pMeshField->BindTexture( m_pTexture[type]);

	return pMeshField;
}


//=============================================================================
//
//=============================================================================
HRESULT CMeshField::Load(void)
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
void CMeshField::Unload(void)
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


