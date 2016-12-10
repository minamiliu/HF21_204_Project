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
#include "collision.h"

//============================================
// �}�N����`
//============================================
#define TEXTURENAME "data/TEXTURE/field000.jpg"


//=============================================================================
// �\���̒�`
//=============================================================================

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
HRESULT CScene3D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	m_pos = pos;
	m_rot = rot;

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
	m_bLoadTexture = false;
	
	// ���_���̍쐬
	MakeVertex(pDevice);

	return S_OK;
}
void CScene3D::Uninit(void)
{
	if(m_pTexture != NULL && m_bLoadTexture == true)
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

	//�e�N�X�`���̓ǂݍ���
	pScene3D->Load(TEXTURENAME);

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

bool CScene3D::HitCheck( D3DXVECTOR3 tNowPos, D3DXVECTOR3 tNextPos, D3DXVECTOR3 *wall_nor, D3DXVECTOR3 *HitPoint)
{
	bool bHit = false;
	D3DXVECTOR3 tHitPosNear = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
	D3DXMATRIX mtxRot, mtxTranslate;
	D3DXVECTOR3 tPos[4];


	// ���b�V���Ǎ\���̂̃|�C���^�Ƀ��b�V���ǃ��[�N�̐擪�A�h���X����
	CScene3D *pMesh = this;


	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity( &pMesh->m_mtxWorld);
	
	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll( &mtxRot, pMesh->m_rot.y, pMesh->m_rot.x, pMesh->m_rot.z);
	D3DXMatrixMultiply( &pMesh->m_mtxWorld, &pMesh->m_mtxWorld, &mtxRot);
	
	// �ړ��𔽉f
	D3DXMatrixTranslation( &mtxTranslate, pMesh->m_pos.x, pMesh->m_pos.y, pMesh->m_pos.z);
	D3DXMatrixMultiply( &pMesh->m_mtxWorld, &pMesh->m_mtxWorld, &mtxTranslate);

	{//���_�o�b�t�@�̎擾

		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		pMesh->m_pVtxBuff->Lock( 0, 0, (void**)&pVtx, 0);

		tPos[0] = pVtx[0].vtx;
		tPos[1] = pVtx[pMesh->m_nNumBlockX].vtx;
		tPos[2] = pVtx[(pMesh->m_nNumBlockX+1) * pMesh->m_nNumBlockZ].vtx;
		tPos[3] = pVtx[(pMesh->m_nNumBlockX+1) * (pMesh->m_nNumBlockZ+1) - 1 ].vtx;


		// ���_�f�[�^���A�����b�N����
		pMesh->m_pVtxBuff->Unlock();	
	}

	//���_�o�b�t�@�Ƀ��[���h�}�g���b�N�X���|����A���_�o�b�t�@���X�V�����
	D3DXVec3TransformCoord( &tPos[0], &tPos[0], &pMesh->m_mtxWorld);
	D3DXVec3TransformCoord( &tPos[1], &tPos[1], &pMesh->m_mtxWorld);
	D3DXVec3TransformCoord( &tPos[2], &tPos[2], &pMesh->m_mtxWorld);
	D3DXVec3TransformCoord( &tPos[3], &tPos[3], &pMesh->m_mtxWorld);


	D3DXVECTOR3 tHitPos;
	if( CCollision::HitCheck( tPos[0], tPos[1], tPos[2], tNowPos, tNextPos, &tHitPos) )
	{
		bHit = true;

		//��ԋ߂���_�����߂�
		D3DXVECTOR3 v1 = tHitPosNear - tNowPos;
		D3DXVECTOR3 v2 = tHitPos - tNowPos;
		if( D3DXVec3Length(&v1) > D3DXVec3Length(&v2))
		{
			tHitPosNear = tHitPos;

			//�ǂ̖@�����擾
			if(wall_nor != NULL) *wall_nor = CCollision::CrossProduct( tPos[0] - tPos[1], tPos[2] - tPos[1]);
		}
			
	}
	else if( CCollision::HitCheck( tPos[1], tPos[2], tPos[3], tNowPos, tNextPos, &tHitPos) )
	{
		bHit = true;

		//��ԋ߂���_�����߂�
		D3DXVECTOR3 v1 = tHitPosNear - tNowPos;
		D3DXVECTOR3 v2 = tHitPos - tNowPos;
		if( D3DXVec3Length(&v1) > D3DXVec3Length(&v2))
		{
			tHitPosNear = tHitPos;

			//�ǂ̖@�����擾
			if(wall_nor != NULL) *wall_nor = CCollision::CrossProduct( tPos[1] - tPos[2], tPos[3] - tPos[2]);
		}
	}

	//��ԋ߂���_��n��
	if(HitPoint != NULL) *HitPoint = tHitPosNear;

	return bHit;
}

//=============================================================================
// �|���S���̃e�N�X�`����ǂݍ���
//=============================================================================
HRESULT CScene3D::Load(LPCSTR strFileName)
{
	if( m_pTexture == NULL)
	{
		LPDIRECT3DDEVICE9 pDevice;
		pDevice = CManager::GetRenderer()->GetDevice();

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile( pDevice, strFileName, &m_pTexture);

		// �e�N�X�`���̓ǂݍ��݃t���O
		m_bLoadTexture = true;
	}

	return S_OK;
}

//=============================================================================
// �|���S���̃e�N�X�`�������蓖�Ă�
//=============================================================================
void CScene3D::BindTexture( LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
