//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: trajectory.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@�R�ƌ[��
// �쐬��:       2016/12/08
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "manager.h"
#include "bullet2D.h"
#include "debugproc.h"
#include "trajectory.h"
#include "renderer.h"
//============================================
// �}�N����`
//============================================
#define TEXTURE_TRAJECTORY "data/TEXTURE/maru.png"
#define TEXTURE_EFFECT "data/TEXTURE/effect000.jpg"
#define TEXTURE_GORILLA "data/TEXTURE/�S����.png"
//=============================================================================
// �\���̒�`
//=============================================================================


LPDIRECT3DTEXTURE9 CTrajectory::m_pTexture = NULL;
//=============================================================================
//�R���X�g���N�^
//=============================================================================
CTrajectory::CTrajectory()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CTrajectory::~CTrajectory()
{
	
}


//=============================================================================
// �|���S���̏���������
//=============================================================================

HRESULT CTrajectory::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	m_alpha = 1.0;
	m_nTrajectoryCnt = 0;
	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CTrajectory::Uninit(void)
{
	CScene2D::Uninit();
}


//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CTrajectory::Update(void)
{
	m_alpha=1.0;
	m_nTrajectoryCnt++;
	//SetColor(RED(255));
	SetColor(D3DCOLOR_COLORVALUE(1.0,0.0,1.0,m_alpha));
	CScene2D::Update();
	if(m_nTrajectoryCnt > 30)
	{
		this->Uninit();
		return;
	}
	if(m_tjrType == TJRTYPE_ALLDIRECTION)
	{
		D3DXVECTOR3 pos = this->GetPosition();
		SetPosition(D3DXVECTOR3(pos.x+cos(m_angle)*4,pos.y+sin(m_angle)*4,0.0));
	}
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CTrajectory::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//���Z����
	pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);//Z��r�Ȃ�
	//���e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF,254);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);
	// ���C�e�B���O���[�h��OFF
	pDevice->SetRenderState(D3DRS_LIGHTING,FALSE);

	CScene2D::Draw();

	// ���C�e�B���O���[�h��ON
	pDevice->SetRenderState(D3DRS_LIGHTING,TRUE);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);
	//���e�X�g�����Ƃɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);//Z��r����
}

//=============================================================================
// �|���S���̐�������
//=============================================================================
CTrajectory *CTrajectory::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,TJRTYPE type,float angle)
{
	CTrajectory *pTrajectory;
	pTrajectory = new CTrajectory;
	pTrajectory->Init(pos, size);
	pTrajectory->CScene2D::BindTexture(m_pTexture);
	pTrajectory->m_tjrType = type;
	pTrajectory->m_angle = angle;
	return pTrajectory;
}

void CTrajectory::Load(void)
{
	if( m_pTexture == NULL)
	{
		LPDIRECT3DDEVICE9 pDevice;
		pDevice = CManager::GetRenderer()->GetDevice();

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile( pDevice, TEXTURE_EFFECT, &m_pTexture);
	}
}

