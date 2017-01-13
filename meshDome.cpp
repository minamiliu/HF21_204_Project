//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: meshDome.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2017/01/12
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "meshDome.h"
#include "scene3D.h"
#include "renderer.h"
#include "manager.h"

//============================================
// �}�N����`
//============================================
#define	TEXTURE_MESHDOME	"data/TEXTURE/pattern01.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	VALUE_MOVE_DOME		(4.0f)						// �ړ����x
#define	VALUE_ROTATE_DOME	(D3DX_PI * 0.01f)			// ��]���x

#define	DOME_HEIGHT_RATE	(1.0f)		// ��h�[���̍����W��
#define	TEX_COUNT_LOOP		(8)			// �e�N�X�`���̌J��Ԃ���

//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================
LPDIRECT3DTEXTURE9 CMeshDome::m_pTexture = NULL;	// �e�N�X�`���ւ̃|�C���^

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CMeshDome::CMeshDome()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CMeshDome::~CMeshDome()
{
	
}


//=============================================================================
// ���V���|���S���̏���������
//=============================================================================
HRESULT CMeshDome::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, int nNumBlockH, int nNumBlockV)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �ʒu�E�����E���a�i�O���[�o���ϐ��j�̏����ݒ�
	m_pos = pos;
	m_rot = rot;
	m_fRadius = fRadius;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile( pDevice, TEXTURE_MESHDOME, &m_pTexture);

	// �u���b�N��H/V�i�O���[�o���ϐ��j�̐ݒ�
	m_nNumBlockH = nNumBlockH;
	m_nNumBlockV = nNumBlockV;

	// ���_���i�O���[�o���ϐ��j�̐ݒ�
	m_nNumVertex = (m_nNumBlockH + 1) * (m_nNumBlockV + 1);

	// �|���S�����i�O���[�o���ϐ��j�̐ݒ�
	m_nNumPolygon = ( m_nNumBlockH * (m_nNumBlockV * 2) + (m_nNumBlockV - 1) * 4);

	// �C���f�b�N�X���i�O���[�o���ϐ��j�̐ݒ�
	m_nNumVertexIndex = (m_nNumBlockH * (m_nNumBlockV * 2) + m_nNumBlockV * 2 + (m_nNumBlockV - 1) * 2);

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumVertex,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,							// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,								// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,							// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&m_pVtxBuff,					// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))										// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (m_nNumBlockH + 1),		// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,						// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,							// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,						// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&m_pVtxBuffTop,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))									// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	// �I�u�W�F�N�g�̃C���f�b�N�X�o�b�t�@�𐶐�
	if(FAILED(pDevice->CreateIndexBuffer(sizeof(WORD) * m_nNumVertexIndex,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,					// ���_�o�b�t�@�̎g�p�@�@
												D3DFMT_INDEX16,						// �g�p����C���f�b�N�X�t�H�[�}�b�g
												D3DPOOL_MANAGED,					// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&m_pIdxBuff,					// �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))								// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	// �I�u�W�F�N�g�̃C���f�b�N�X�o�b�t�@�𐶐�
	if(FAILED(pDevice->CreateIndexBuffer(sizeof(WORD) * (m_nNumBlockH + 2),			// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,					// ���_�o�b�t�@�̎g�p�@�@
												D3DFMT_INDEX16,						// �g�p����C���f�b�N�X�t�H�[�}�b�g
												D3DPOOL_MANAGED,					// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&m_pIdxBuffTop,					// �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))								// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;
		const float angleH = (D3DX_PI * 2.0f) / m_nNumBlockH;
		const float angleV = (D3DX_PI / 2.0f) / (m_nNumBlockV + 1);
		const float width = 1.0f / m_nNumBlockH;
		const float height = 1.0f / m_nNumBlockV;
		float lengthXZ;
		D3DXVECTOR3 nor;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock( 0, 0, (void**)&pVtx, 0);
		for(int nCntV = 0; nCntV < (m_nNumBlockV + 1); nCntV++)
		{
			lengthXZ = cosf(angleV * nCntV) * m_fRadius;

			for(int nCntH = 0; nCntH < (m_nNumBlockH + 1); nCntH++, pVtx++)
			{
				// ���_���W�̐ݒ�
				pVtx->vtx.x = sinf(angleH * nCntH) * lengthXZ;
				pVtx->vtx.y = sinf(angleV * nCntV) * m_fRadius * DOME_HEIGHT_RATE;
				pVtx->vtx.z = -cosf(angleH * nCntH) * lengthXZ;

				// �@���̐ݒ�
				nor = pVtx->vtx;
				D3DXVec3Normalize(&nor, &nor);
				pVtx->nor = nor;

				// ���_�J���[�̐ݒ�
				pVtx->col = D3DCOLOR_RGBA(255,255,255,255);

				// �e�N�X�`�����W�̐ݒ�
				pVtx->tex.x = nCntH * width * TEX_COUNT_LOOP;

				if(nCntV == m_nNumBlockV)
				{
					pVtx->tex.y = 0.01f;
				}
				else
				{
					pVtx->tex.y = 1.0f - nCntV * height;
				}
			}
		}
		// ���_�f�[�^���A�����b�N����
		m_pVtxBuff->Unlock();

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuffTop->Lock( 0, 0, (void**)&pVtx, 0);
		// ���_���W�̐ݒ�
		pVtx->vtx.x = 0.0f;
		pVtx->vtx.y = sinf(angleV * (m_nNumBlockV + 1)) * m_fRadius * DOME_HEIGHT_RATE;
		pVtx->vtx.z = 0.0f;

		// �@���̐ݒ�
		nor = pVtx->vtx;
		D3DXVec3Normalize(&nor, &nor);
		pVtx->nor = nor;

		// ���_�J���[�̐ݒ�
		pVtx->col = D3DCOLOR_RGBA(255,255,255,255);

		// �e�N�X�`�����W�̐ݒ�
		pVtx->tex.x = 0.5f;
		pVtx->tex.y = 0.0f;

		// ���_�o�b�t�@�̃|�C���^���C���N�������g
		pVtx++;

		lengthXZ = cosf(angleV * m_nNumBlockV) * m_fRadius;
		for(int nCntH = 0; nCntH < m_nNumBlockH; nCntH++, pVtx++)
		{
			// ���_���W�̐ݒ�
			pVtx->vtx.x = -sinf(angleH * nCntH) * lengthXZ;
			pVtx->vtx.y = sinf(angleV * m_nNumBlockV) * m_fRadius * DOME_HEIGHT_RATE;
			pVtx->vtx.z = -cosf(angleH * nCntH) * lengthXZ;

			// �@���̐ݒ�
			nor = pVtx->vtx;
			D3DXVec3Normalize(&nor, &nor);
			pVtx->nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx->col = D3DCOLOR_RGBA(255,255,255,255);

			// �e�N�X�`�����W�̐ݒ�
			pVtx->tex.x = 0.5f;
			pVtx->tex.y = 1.0f;
		}

		// ���_�f�[�^���A�����b�N����
		m_pVtxBuffTop->Unlock();
	}

	{//�C���f�b�N�X�o�b�t�@�̒��g�𖄂߂�
		WORD *pIdx;

		// �C���f�b�N�X�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pIdxBuff->Lock( 0, 0, (void**)&pIdx, 0);
		for(int nCntV = 0; nCntV < m_nNumBlockV; nCntV++)
		{
			if(nCntV != 0)
			{
				*pIdx = nCntV * (m_nNumBlockH + 1);
				pIdx++;
			}

			for(int nCntH = 0; nCntH < m_nNumBlockH + 1; nCntH++)
			{
				*pIdx = nCntV * (m_nNumBlockH + 1) + nCntH;
				pIdx++;

				*pIdx = (nCntV + 1) * (m_nNumBlockH + 1) + nCntH;
				pIdx++;
			}

			if(nCntV != (m_nNumBlockV - 1))
			{
				*pIdx = (nCntV + 1) * (m_nNumBlockH + 1);
				pIdx++;
			}
		}

		// �C���f�b�N�X�f�[�^���A�����b�N����
		m_pIdxBuff->Unlock();

		// �C���f�b�N�X�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pIdxBuffTop->Lock( 0, 0, (void**)&pIdx, 0);
		for(int nCntH = 0; nCntH < m_nNumBlockH + 1; nCntH++, pIdx++)
		{
			*pIdx = nCntH;
		}
		*pIdx = 1;

		// �C���f�b�N�X�f�[�^���A�����b�N����
		m_pIdxBuffTop->Unlock();
	}

	return S_OK;
}
//=============================================================================
// ���V���|���S���̏I������
//=============================================================================
void CMeshDome::Uninit(void)
{
	if(m_pVtxBuff != NULL)
	{// ���_�o�b�t�@�̊J��
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	if(m_pIdxBuff != NULL)
	{// �C���f�b�N�X�o�b�t�@�̊J��
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	if(m_pVtxBuffTop != NULL)
	{// ���_�o�b�t�@�̊J��
		m_pVtxBuffTop->Release();
		m_pVtxBuffTop = NULL;
	}

	if(m_pIdxBuffTop != NULL)
	{// �C���f�b�N�X�o�b�t�@�̊J��
		m_pIdxBuffTop->Release();
		m_pIdxBuffTop = NULL;
	}

	if(m_pTexture != NULL && m_bLoadTexture == true)
	{// �e�N�X�`���̊J��
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}
//=============================================================================
// ���V���|���S���̍X�V����
//=============================================================================
void CMeshDome::Update(void)
{

}
//=============================================================================
// ���V���|���S���̕`�揈��
//=============================================================================
void CMeshDome::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTranslate;

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);	// ���ʂ��J�����O

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

	// ���_�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
		0,								//�ŏ��̒��_�C���f�b�N�X�܂ł̃I�t�Z�b�g
		0,								//�ŏ��̒��_�C���f�b�N�X
		m_nNumVertex,		//���_�̐�
		0,								//�ǂݎ����J�n����ʒu
		m_nNumPolygon		//�|���S���̐�
	);

	// ���_�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuffTop, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetIndices(m_pIdxBuffTop);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLEFAN,				//�v���~�e�B�u�̎��
		0,								//�ŏ��̒��_�C���f�b�N�X�܂ł̃I�t�Z�b�g
		0,								//�ŏ��̒��_�C���f�b�N�X
		(m_nNumBlockH + 1),		//���_�̐�
		0,								//�ǂݎ����J�n����ʒu
		m_nNumBlockH		//�|���S���̐�
	);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	// ���ʂ��J�����O
}

//=============================================================================
// ���V���|���S���̐���
//=============================================================================
CMeshDome *CMeshDome::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, int nNumBlockH, int nNumBlockV)
{
	CMeshDome *pDome;
	pDome = new CMeshDome;
	pDome->Init(pos, rot, fRadius, nNumBlockH, nNumBlockV);

	//�e�N�X�`���̓ǂݍ���
	pDome->Load();

	return pDome;
}

//=============================================================================
// ���W�̎擾
//=============================================================================
D3DXVECTOR3 CMeshDome::GetPosition(void)
{
	return m_pos;
}
//=============================================================================
// �T�C�Y�̎擾
//=============================================================================
D3DXVECTOR3 CMeshDome::GetSize(void)
{
	return D3DXVECTOR3( m_fRadius, m_fRadius, m_fRadius);
}


//=============================================================================
// ���V���|���S���̃e�N�X�`����ǂݍ���
//=============================================================================
HRESULT CMeshDome::Load(void)
{
	if( m_pTexture == NULL)
	{
		LPDIRECT3DDEVICE9 pDevice;
		pDevice = CManager::GetRenderer()->GetDevice();

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile( pDevice, TEXTURE_MESHDOME, &m_pTexture);

		// �e�N�X�`���̓ǂݍ��݃t���O
		m_bLoadTexture = true;
	}

	return S_OK;
}

//=============================================================================
// ���V���|���S���̃e�N�X�`�������蓖�Ă�
//=============================================================================
void CMeshDome::BindTexture( LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
//=============================================================================
// ���W�̐ݒ�
//=============================================================================
void CMeshDome::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}