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
#include "scene3D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"

//============================================
// �}�N����`
//============================================

#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#define TEXTURENAME "data/TEXTURE/field000.jpg"


//=============================================================================
// �\���̒�`
//=============================================================================
//�R�c�|���S��
typedef struct
{
	D3DXVECTOR3 vtx; //���_���W
	D3DXVECTOR3 nor; //�@���x�N�g��
	D3DCOLOR	col; //���_�J���[
	D3DXVECTOR2	tex; //�e�N�X�`�����W
}VERTEX_3D;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CScene3D::CScene3D()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CScene3D::~CScene3D()
{
	
}


//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CScene3D::Init(void)
{
	return S_OK;
}

HRESULT CScene3D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	m_pos = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);

	m_nNumBlockX = nNumBlockX;
	m_nNumBlockZ = nNumBlockZ;
	m_fSizeBlockX = fSizeBlockX;
	m_fSizeBlockZ = fSizeBlockZ;

	m_nNumVertex = (nNumBlockX+1) * (nNumBlockZ+1);
	m_nNumVertexIndex = (nNumBlockX + 1)*2*nNumBlockZ + (nNumBlockZ - 1)*2;
	m_nNumPolygon = nNumBlockX*nNumBlockZ*2 + (nNumBlockZ - 1)*4;

	m_pTexture = NULL;	
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	
	// ���_���̍쐬
	MakeVertex(pDevice);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile( pDevice, TEXTURENAME, &m_pTexture);


	return S_OK;
}
void CScene3D::Uninit(void)
{
	if(m_pTexture != NULL)
	{// �e�N�X�`���̊J��
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	if(m_pVtxBuff != NULL) 
	{// ���_�o�b�t�@�̊J��
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

void CScene3D::Update(void)
{

}

void CScene3D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
		
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity( &m_mtxWorld);
	
	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll( &mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxRot);
	
	// �ړ��𔽉f
	D3DXMatrixTranslation( &mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxTranslate);
	
	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform( D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);
	
	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,						//�ŏ��̒��_�C���f�b�N�X�܂ł̃I�t�Z�b�g
		0,						//�ŏ��̒��_�C���f�b�N�X
		m_nNumVertex,			//���_�̐�
		0,						//�ǂݎ����J�n����ʒu
		m_nNumPolygon			//�|���S���̐�
	);
}

CScene3D *CScene3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ)
{
	CScene3D *pScene3D;
	pScene3D = new CScene3D;
	pScene3D->Init(pos, rot, nNumBlockX, nNumBlockZ, fSizeBlockX, fSizeBlockZ);
	
	return pScene3D;
}

HRESULT CScene3D::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if(FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * m_nNumVertex,	//���_�f�[�^�̃o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,					//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,			//���_�o�b�t�@�C���^�[�t�F�[�X�̃|�C���^
		NULL)))
	{
		return E_FAIL;
	}

	// �I�u�W�F�N�g�̃C���f�b�N�X�o�b�t�@�𐶐�
	if(FAILED(pDevice->CreateIndexBuffer(
		sizeof(WORD) * m_nNumVertexIndex,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL)))
	{
		return E_FAIL;
	}

	
	{//���_�o�b�t�@�̒��g�𖄂߂�

		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock( 0, 0, (void**)&pVtx, 0);

		for(int nCntZ = 0; nCntZ < m_nNumBlockZ+1; nCntZ++)
		{
			for(int nCntX = 0; nCntX < m_nNumBlockX+1; nCntX++)
			{
				pVtx[0].vtx = D3DXVECTOR3( -m_fSizeBlockX*m_nNumBlockX/2 + nCntX*m_fSizeBlockX, 0.0f, m_fSizeBlockZ*m_nNumBlockZ/2 - nCntZ*m_fSizeBlockZ);
				pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
				pVtx[0].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f);
				pVtx[0].tex = D3DXVECTOR2( 1.0f * nCntX, 1.0f * nCntZ );
				pVtx++;
			}
		}


		// ���_�f�[�^���A�����b�N����
		m_pVtxBuff->Unlock();	
	}


	{//�C���f�b�N�X�o�b�t�@�̒��g�𖄂߂�

		WORD *pIdx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pIdxBuff->Lock( 0, 0, (void**)&pIdx, 0);

		for(int nCntZ = 0; nCntZ < m_nNumBlockZ; nCntZ++)
		{
			if(nCntZ > 0)
			{
				pIdx[0] = (m_nNumBlockX + 1) * (nCntZ + 1);
				pIdx++;
			}
			for(int nCntX = 0; nCntX < m_nNumBlockX+1; nCntX++, pIdx+=2)
			{
				//���_���W�̐ݒ�
				pIdx[0] = (m_nNumBlockX + 1) * (nCntZ + 1) + nCntX; 
				pIdx[1] = (m_nNumBlockX + 1) * (nCntZ) + nCntX;
			}
			if(nCntZ < m_nNumBlockZ - 1)
			{
				*pIdx = *(pIdx-1);
				pIdx++;
			}
		}

		// ���_�f�[�^���A�����b�N����
		m_pIdxBuff->Unlock();	
	}

	return S_OK;
}

D3DXVECTOR3 CScene3D::GetPosition(void)
{
	return m_pos;
}
D3DXVECTOR3 CScene3D::GetSize(void)
{
	return m_size;
}
void CScene3D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}