//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: scene2D.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/10/19
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"

//============================================
// �}�N����`
//============================================
#define NUM_VERTEX (4)
#define NUM_POLYGON (2)

//=============================================================================
// �\���̒�`
//=============================================================================


//=============================================================================
//�R���X�g���N�^
//=============================================================================
CScene2D::CScene2D()
{
	m_pTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	m_pos = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);			// �|���S���̈ʒu
	m_bLoadTexture = false;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CScene2D::~CScene2D()
{
	
}


//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CScene2D::Init(void)
{
	return S_OK;
}

HRESULT CScene2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �|���S���̏���ݒu
	m_pos = pos;
	m_size = size;
	m_bLoadTexture = false;

	// ���_�o�b�t�@�̐���
	if(FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX,	//���_�f�[�^�̃o�b�t�@�T�C�Y 
		D3DUSAGE_WRITEONLY, 
		FVF_VERTEX_2D,			//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED, 
		&m_pVtxBuff,		//���_�o�b�t�@�C���^�[�t�F�[�X�̃|�C���^
		NULL)))
	{
		return E_FAIL;
	}

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock( 0, 0, (void**)&pVtx, 0);

	// �|���S���̈ʒu��ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x/2), m_pos.y - (m_size.y/2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x/2), m_pos.y - (m_size.y/2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x/2), m_pos.y + (m_size.y/2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x/2), m_pos.y + (m_size.y/2), 0.0f);

	//rhw
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//color
	pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);

	//�e�N�X�`�����W�w��
	pVtx[0].tex = D3DXVECTOR2(0.0F, 0.0F);
	pVtx[1].tex = D3DXVECTOR2(1.0F, 0.0F);
	pVtx[2].tex = D3DXVECTOR2(0.0F, 1.0F);
	pVtx[3].tex = D3DXVECTOR2(1.0F, 1.0F);

	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CScene2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR2 ptnSize)
{
	Init(pos, size);

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock( 0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�w��
	pVtx[0].tex = D3DXVECTOR2( ptnSize.x * 0.0f, ptnSize.y * 0.0f);
	pVtx[1].tex = D3DXVECTOR2( ptnSize.x * 1.0f, ptnSize.y * 0.0f);
	pVtx[2].tex = D3DXVECTOR2( ptnSize.x * 0.0f, ptnSize.y * 1.0f);
	pVtx[3].tex = D3DXVECTOR2( ptnSize.x * 1.0f, ptnSize.y * 1.0f);

	m_pVtxBuff->Unlock();

	return S_OK;
}


//=============================================================================
// �|���S���̏I������
//=============================================================================
void CScene2D::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if(m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �e�N�X�`���̔j��
	if(m_pTexture != NULL && m_bLoadTexture == true)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}


//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CScene2D::Update(void)
{

}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CScene2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,						//���[�h����ŏ��̒��_�C���f�b�N�X
		NUM_POLYGON				//�|���S���̐�
	);
}

//=============================================================================
// �|���S���̐�������
//=============================================================================
CScene2D *CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, LPCSTR strFileName)
{
	CScene2D *pScene2D;
	pScene2D = new CScene2D;
	pScene2D->Init(pos, size);

	//�e�N�X�`���̓ǂݍ���
	pScene2D->Load( strFileName);

	return pScene2D;
}

//=============================================================================
// �|���S���̍��W�ݒu
//=============================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock( 0, 0, (void**)&pVtx, 0);

	// �|���S���̈ʒu��ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x/2), m_pos.y - (m_size.y/2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x/2), m_pos.y - (m_size.y/2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x/2), m_pos.y + (m_size.y/2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x/2), m_pos.y + (m_size.y/2), 0.0f);

	m_pVtxBuff->Unlock();
}

//=============================================================================
// �|���S���̍��W�擾
//=============================================================================
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	return m_pos;
}

//=============================================================================
// �|���S���̃e�N�X�`����ǂݍ���
//=============================================================================
HRESULT CScene2D::Load(LPCSTR strFileName)
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
void CScene2D::BindTexture( LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//=============================================================================
//�A�j���̃p�^�[����ς���
//=============================================================================
void CScene2D::ChangeTextureAnime( int nPatternAnim, D3DXVECTOR2 ptnSize, D3DXVECTOR2 ptnDivide)
{
	//���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_2D *pVtx;
	float fPosXLeft, fPosXRight;
	float fPosYUp, fPosYDown;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	fPosXLeft	= ptnSize.x * (nPatternAnim % (int)ptnDivide.x);
	fPosXRight	= ptnSize.x * (nPatternAnim % (int)ptnDivide.x + 1);
	fPosYUp		= ptnSize.y * (nPatternAnim / (int)ptnDivide.x);
	fPosYDown	= ptnSize.y * (nPatternAnim / (int)ptnDivide.x + 1);


	pVtx[0].tex = D3DXVECTOR2( fPosXLeft, fPosYUp );
	pVtx[1].tex = D3DXVECTOR2( fPosXRight, fPosYUp );
	pVtx[2].tex = D3DXVECTOR2( fPosXLeft, fPosYDown );
	pVtx[3].tex = D3DXVECTOR2( fPosXRight, fPosYDown );

	// ���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
//�|���S���̃T�C�Y���擾
//=============================================================================
D3DXVECTOR3 CScene2D::GetSize(void)
{
	return m_size;
}

//=============================================================================
//�F��ύX
//=============================================================================
void CScene2D::SetColor(const D3DXCOLOR &col)
{
	// ���_����ݒ�
	VERTEX_2D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock( 0, 0, (void**)&pVtx, 0);

	//color
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	m_pVtxBuff->Unlock();
}