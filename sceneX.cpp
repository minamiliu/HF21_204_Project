//============================================
//
// �^�C�g��:	 CL25�ۑ�
// �v���O������: sceneX.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/15
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "sceneX.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"

//============================================
// �}�N����`
//============================================
#define MODEL_FILENAME "data/MODEL/player.x"


//=============================================================================
// �\���̒�`
//=============================================================================


//=============================================================================
//�R���X�g���N�^
//=============================================================================
CSceneX::CSceneX()
{
	m_pTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
	m_pD3DXMesh = NULL;		// ���b�V�����ւ̃|�C���^
	m_pD3DXBuffMat = NULL;	// �}�e���A�����ւ̃|�C���^
	m_nNumMat = 0;			// �}�e���A�����̐�

	m_pos = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);		// ���f���̈ʒu
	m_rot = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);		// ���f���̌���(��])
	m_scl = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);		// ���f���̑傫��(�X�P�[��)
	m_move = 0.0f;								// ���f���̈ړ���

	D3DXMatrixIdentity( &m_mtxWorld);
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CSceneX::~CSceneX()
{
	
}


//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CSceneX::Init(void)
{
	return S_OK;
}

//=============================================================================
//
//=============================================================================
HRESULT CSceneX::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float move)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	m_pos = pos;
	m_rot = rot;
	m_scl = scl;
	m_move = move;

	// ���f���Ɋւ���ϐ��̏�����							
	m_pTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
	m_pD3DXMesh = NULL;		// ���b�V�����ւ̃|�C���^
	m_pD3DXBuffMat = NULL;		// �}�e���A�����ւ̃|�C���^
	m_nNumMat = 0;			// �}�e���A�����̐�

	// X�t�@�C���̓ǂݍ���
	if(FAILED(D3DXLoadMeshFromX(
		MODEL_FILENAME,				// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
		D3DXMESH_SYSTEMMEM,			// ���b�V���̍쐬�I�v�V�������w��
		pDevice,					// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
		NULL,						// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
		&m_pD3DXBuffMat,		// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^
		NULL,						// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
		&m_nNumMat,			// D3DXMATERIAL�\���̂̐�
		&m_pD3DXMesh			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
		)))
	{
		return E_FAIL;
	}	


	return S_OK;
}

//=============================================================================
//
//=============================================================================
void CSceneX::Uninit(void)
{
	// �e�N�X�`���̊J��
	if(m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// ���b�V���̊J��
	if(m_pD3DXMesh != NULL)
	{
		m_pD3DXMesh->Release();
		m_pD3DXMesh = NULL;
	}
	// �}�e���A���̊J��
	if(m_pD3DXBuffMat != NULL)
	{
		m_pD3DXBuffMat->Release();
		m_pD3DXBuffMat = NULL;
	}
}

//=============================================================================
//
//=============================================================================
void CSceneX::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

		//�ړ�
	if(pInputKeyboard->GetKeyPress(DIK_W))
	{
		m_pos.z -= m_move;
	}
	if(pInputKeyboard->GetKeyPress(DIK_S))
	{
		m_pos.z += m_move;
	}
	if(pInputKeyboard->GetKeyPress(DIK_A))
	{
		m_pos.x += m_move;
	}
	if(pInputKeyboard->GetKeyPress(DIK_D))
	{
		m_pos.x -= m_move;
	}
}

//=============================================================================
//
//=============================================================================
void CSceneX::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity( &m_mtxWorld);
	
	// �X�P�[���𔽉f
	D3DXMatrixScaling( &mtxScl, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxScl);
	
	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll( &mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxRot);
	
	// �ړ��𔽉f
	D3DXMatrixTranslation( &mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxTranslate);
	
	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform( D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);
	
	// �}�e���A�����ɑ΂���|�C���^���擾
	pD3DXMat = (D3DXMATERIAL *)m_pD3DXBuffMat->GetBufferPointer();
	for(int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial( &pD3DXMat[nCntMat].MatD3D);
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture( 0, m_pTexture);
		// �`��
		m_pD3DXMesh->DrawSubset( nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial( &matDef);
}

//=============================================================================
//
//=============================================================================
CSceneX *CSceneX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float move)
{
	CSceneX *pSceneX;
	pSceneX = new CSceneX;
	pSceneX->Init(pos, rot, scl, move);

	return pSceneX;
}
