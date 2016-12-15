//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: fade.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/19
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "scene2D.h"
#include "fade.h"
#include "renderer.h"
#include "manager.h"

//============================================
// �}�N����`
//============================================

//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================
LPDIRECT3DVERTEXBUFFER9 CFade::m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
int CFade::m_nAlpha = 0;
CFade::FADE CFade::m_state = CFade::FADE_NONE;


//=============================================================================
//�R���X�g���N�^
//=============================================================================
CFade::CFade()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CFade::~CFade()
{
	
}


//=============================================================================
// �|���S���̏���������
//=============================================================================

HRESULT CFade::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();


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
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f + SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f + SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f + SCREEN_WIDTH, 0.0f + SCREEN_HEIGHT, 0.0f);

	//rhw
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//color
	pVtx[0].col = D3DCOLOR_RGBA(0,0,0,0);
	pVtx[1].col = D3DCOLOR_RGBA(0,0,0,0);
	pVtx[2].col = D3DCOLOR_RGBA(0,0,0,0);
	pVtx[3].col = D3DCOLOR_RGBA(0,0,0,0);

	//�e�N�X�`�����W�w��
	pVtx[0].tex = D3DXVECTOR2(0.0F, 0.0F);
	pVtx[1].tex = D3DXVECTOR2(1.0F, 0.0F);
	pVtx[2].tex = D3DXVECTOR2(0.0F, 1.0F);
	pVtx[3].tex = D3DXVECTOR2(1.0F, 1.0F);

	m_pVtxBuff->Unlock();

	return S_OK;
}




//=============================================================================
// �|���S���̏I������
//=============================================================================
void CFade::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if(m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}


//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CFade::Update(void)
{
	switch( m_state)
	{
		case FADE_OUT:
			m_nAlpha += 5;
			if(m_nAlpha >= 255)
			{
				m_nAlpha = 255;
				m_state = FADE_CHANGE;
			}
			SetAlpha(m_nAlpha);
			break;

		case FADE_CHANGE:
			CManager::NextModeChange();
			m_state = FADE_IN;
			break;

		case FADE_IN:
			m_nAlpha -= 5;
			if( m_nAlpha <= 0)
			{
				m_nAlpha = 0;
				m_state = FADE_NONE;
			}
			SetAlpha( m_nAlpha);
			break;

		case FADE_NONE:
			break;
	}
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CFade::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,						//���[�h����ŏ��̒��_�C���f�b�N�X
		NUM_POLYGON				//�|���S���̐�
	);
}

//=============================================================================
// �t�F�[�h�̐ݒu
//=============================================================================
void CFade::SetFade(void)
{
	m_state = FADE_OUT;
}

//=============================================================================
// �t�F�[�h���ł���
//=============================================================================
bool CFade::isFading(void)
{
	if( m_state == FADE_NONE)
	{
		return false;
	}
	return true;
}
//=============================================================================
// �A���t�@�l��ݒ�
//=============================================================================
void CFade::SetAlpha(int alpha)
{
	//���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//color
	pVtx[0].col = D3DCOLOR_RGBA( 0, 0, 0, alpha);
	pVtx[1].col = D3DCOLOR_RGBA( 0, 0, 0, alpha);
	pVtx[2].col = D3DCOLOR_RGBA( 0, 0, 0, alpha);
	pVtx[3].col = D3DCOLOR_RGBA( 0, 0, 0, alpha);

	// ���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}
