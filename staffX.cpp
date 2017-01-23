//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: staff.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2017/01/23
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "staffX.h"
#include "manager.h"
#include "renderer.h"
#include "shadow.h"


//============================================
// �}�N����`
//============================================
#define MODEL_STAFF	"data/MODEL/staff.x"

//=============================================================================
// �\���̒�`
//=============================================================================

//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================
LPDIRECT3DTEXTURE9	CStaffX::m_pTexture		[TYPE_MAX] = {};		// �e�N�X�`���ւ̃|�C���^
LPD3DXMESH			CStaffX::m_pD3DXMesh	[TYPE_MAX] = {};		// ���b�V�����ւ̃|�C���^
LPD3DXBUFFER		CStaffX::m_pD3DXBuffMat	[TYPE_MAX] = {};		// �}�e���A�����ւ̃|�C���^
DWORD				CStaffX::m_nNumMat		[TYPE_MAX] = {};		// �}�e���A�����̐�

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CStaffX::CStaffX()
{
	m_pShadow = NULL;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CStaffX::~CStaffX()
{
	
}


//=============================================================================
//
//=============================================================================
HRESULT CStaffX::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl)
{
	CSceneX::Init( pos, rot, scl);
	SetObjType( OBJTYPE_L_ENEMY);

	//�e�̐���
	m_pShadow = CShadow::Create( pos, D3DXVECTOR2( 50.0f, 50.0f));

	return S_OK;
}

//=============================================================================
//
//=============================================================================
void CStaffX::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
//
//=============================================================================
void CStaffX::Update(void)
{
	//�e�̍X�V����
	//m_pShadow->SetPosition( this->GetPosition());
}

//=============================================================================
//
//=============================================================================
void CStaffX::Draw(void)
{
	CSceneX::Draw();
}

//=============================================================================
//
//=============================================================================
CStaffX *CStaffX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, TYPE type)
{
	CStaffX *pEnemy;
	pEnemy = new CStaffX;
	pEnemy->Init(pos, rot, scl);

	//Xfile�̊��蓖��
	pEnemy->BindXfile( m_pTexture[type], m_pD3DXMesh[type], m_pD3DXBuffMat[type], m_nNumMat[type]);

	return pEnemy;
}


//=============================================================================
//XFILE�̃��[�h
//=============================================================================
HRESULT CStaffX::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	for(int cntType = 0; cntType < TYPE_MAX; cntType++)
	{
		LPCSTR strFileName;
		switch( cntType)
		{
		case TYPE_000:
			strFileName = MODEL_STAFF;
			break;
		}

		if( m_pTexture[cntType] == NULL &&
			m_pD3DXMesh[cntType] == NULL &&
			m_pD3DXBuffMat[cntType] == NULL &&
			m_nNumMat[cntType] == 0
			)
		{
			// X�t�@�C���̓ǂݍ���
			if(FAILED(D3DXLoadMeshFromX(
				strFileName,			// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
				D3DXMESH_SYSTEMMEM,		// ���b�V���̍쐬�I�v�V�������w��
				pDevice,				// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
				NULL,					// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
				&m_pD3DXBuffMat[cntType],	// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^
				NULL,					// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
				&m_nNumMat[cntType],	// D3DXMATERIAL�\���̂̐�
				&m_pD3DXMesh[cntType]	// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
				)))
			{
				return E_FAIL;
			}
		
		}
	}

	return S_OK;
}

//=============================================================================
//XFILE�̃A�����[�h
//=============================================================================
void CStaffX::Unload(void)
{
	for(int cntType = 0; cntType < TYPE_MAX; cntType++)
	{
		// �e�N�X�`���̊J��
		if(m_pTexture[cntType] != NULL)
		{
			m_pTexture[cntType]->Release();
			m_pTexture[cntType] = NULL;
		}
		// ���b�V���̊J��
		if(m_pD3DXMesh[cntType] != NULL)
		{
			m_pD3DXMesh[cntType]->Release();
			m_pD3DXMesh[cntType] = NULL;
		}
		// �}�e���A���̊J��
		if(m_pD3DXBuffMat != NULL)
		{
			m_pD3DXBuffMat[cntType]->Release();
			m_pD3DXBuffMat[cntType] = NULL;
		}	
	}

}
