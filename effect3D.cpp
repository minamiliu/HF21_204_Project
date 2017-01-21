//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: effect3D.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2017/01/19
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "effect3D.h"
#include "scene.h"

//============================================
// �}�N����`
//============================================
#define TEXTURE_TOMATO	"data/TEXTURE/effect000.jpg"

//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================
LPDIRECT3DTEXTURE9 CEffect3D::m_pTexture[TYPE_MAX] = {};
//int CEffect3D::m_nColorID = 0;
//D3DXCOLOR CEffect3D::m_paraColor[] =
//{
//	RED(1.0f),
//	ORANGE(1.0f),
//	YELLOW(1.0f),
//	GREEN(1.0f),
//	SYAN(1.0f),	
//	BLUE(1.0f),	
//	MASENTA(1.0f),
//};

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CEffect3D::CEffect3D() : CBillBoard( LAYER_EFFECT)
{
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CEffect3D::~CEffect3D()
{
	
}


//=============================================================================
// �|���S���̏���������
//=============================================================================

HRESULT CEffect3D::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size, TYPE type, const D3DXCOLOR &col, float fPercent)
{
	CBillBoard::Init( pos, size);

	//�������
	m_type = type;
	m_fPercent = fPercent;
	m_col = col;

	//m_col = m_paraColor[m_nColorID];
	//this->SetColor(m_col);
	//m_nColorID = (m_nColorID + 1) % 7;

	return S_OK;
}
//=============================================================================
//
//=============================================================================
void CEffect3D::Uninit(void)
{
	CBillBoard::Uninit();
}
//=============================================================================
//
//=============================================================================
void CEffect3D::Update(void)
{
	m_col.a -= m_fPercent;
	this->SetColor(m_col);
	if( m_col.a <= 0)
	{
		this->Uninit();
		return;
	}
}
//=============================================================================
//
//=============================================================================
void CEffect3D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���Z����
	pDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD);	// ���� = �]����(SRC) + �]����(DEST)
	pDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE);

	// Z��r�Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	// ���C�e�B���O���[�h��OFF
	pDevice->SetRenderState( D3DRS_LIGHTING, FALSE);

	//���e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//�`��
	CBillBoard::Draw();

	// ���C�e�B���O���[�h��ON
	pDevice->SetRenderState( D3DRS_LIGHTING, TRUE);

	// ���e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// �ʏ�u�����h 
	pDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD);	// ���� = �]����(SRC) + �]����(DEST)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// Z��r����
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
}
//=============================================================================
//
//=============================================================================
CEffect3D *CEffect3D::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, TYPE type, const D3DXCOLOR &col, float fPercent)
{
	CEffect3D *pEffect;
	pEffect = new CEffect3D;

	pEffect->Init(pos, size, type, col, fPercent);

	//�e�N�X�`���̊��蓖��
	pEffect->BindTexture( m_pTexture[type]);

	return pEffect;
}
//=============================================================================
//�e�N�X�`���̃��[�h
//=============================================================================
HRESULT CEffect3D::Load(void)
{
	for (int cntType = 0; cntType < TYPE_MAX; cntType++)
	{
		LPCSTR strFileName;
		switch (cntType)
		{
		case TYPE_MARU:
			strFileName = TEXTURE_TOMATO;
			break;
		}

		if (m_pTexture[cntType] == NULL)
		{
			LPDIRECT3DDEVICE9 pDevice;
			pDevice = CManager::GetRenderer()->GetDevice();

			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice, strFileName, &m_pTexture[cntType]);
		}
	}

	return S_OK;
}

//=============================================================================
//�e�N�X�`���̃A�����[�h
//=============================================================================
void CEffect3D::Unload(void)
{
	//�e�N�X�`���̔j��
	for (int cntType = 0; cntType < TYPE_MAX; cntType++)
	{
		if (m_pTexture[cntType] != NULL)
		{
			m_pTexture[cntType]->Release();
			m_pTexture[cntType] = NULL;
		}
	}
}
